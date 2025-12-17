#include <WiFi.h>
#include <Preferences.h>
#include "esp_system.h" // Add header file
#include <SPI.h>
//EPD
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h" 
#include "Ap_29demo.h"  
//GUI
#include "GUI_Paint.h"
#include "fonts.h"
//unsigned char BlackImage[(EPD_WIDTH)* (EPD_HEIGHT/8)]; //Define canvas space  Data
#define MAX_SSID_LENGTH 29  //WiFi name length
#define MAX_PASSWORD_LENGTH 29 //WiFi password length
#define MAX_HOST_LENGTH 1  //WiFi device number length
#define MAX_Timeout 30  //WiFi maximum timeout time

//WiFi 
String ssid    = "Goodisplay"; //WiFi Name
String password = "12345678"; //WiFi password
int staticHostNumber = 208; //Host IP number, default 208, user customizable


int num;
int ConnectTimeout; // 30 seconds
WiFiServer server(8080);
//WiFi configuration storage
// NVS namespace
const char* NVS_NAMESPACE = "wifi_config";
// Storage key names
const char* SSID_KEY = "ssid";
const char* PASSWORD_KEY = "password";
const char* HOST_NUMBER_KEY = "host_number";

// New: Restart count related definitions
#define NVS_RESTART_NAMESPACE "restart_counter"  // Independent namespace for restart count storage
#define KEY_RESTART_COUNT "count"
int restartCount = 0;
int Serial_wifi=0;//Serial WiFi configuration status flag

// WiFi periodic check parameters
const unsigned long CHECK_INTERVAL = 30000; // Check every 30 seconds, unit: milliseconds
unsigned long lastCheckTime = 0;           // Last check time

const size_t RECEIVE_BUFFER = 4096*2+400*300/4;  // Receive buffer  4.2-inch 4-color maximum
unsigned char receiveBuffer[RECEIVE_BUFFER];        // Receive buffer

void setup() {
   pinMode(A14, INPUT);  //BUSY
   pinMode(A15, OUTPUT); //RES 
   pinMode(A16, OUTPUT); //DC   
   pinMode(A17, OUTPUT); //CS   
   //SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
   SPI.begin ();
    //WiFi setting/////////////////////////////////////////////////////
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

// Optimize NVS reading logic
  Preferences preferences;
  bool nvsOpened = preferences.begin(NVS_NAMESPACE, true); // Open NVS in read-only mode

  if (!nvsOpened) {
    Serial.println("NVS open failed! Using default configuration.");

  } else {
    // Safe string reading (prevent memory overflow)
    ssid = preferences.getString(SSID_KEY, "");
    password = preferences.getString(PASSWORD_KEY, "");
    staticHostNumber = preferences.getInt(HOST_NUMBER_KEY, 0);
    preferences.end();

  // Print saved WiFi name, password and IP number
    Serial.println("ESP32 Saved WiFi DATA");
    Serial.print("1.WiFi-Name: ");
    Serial.println(ssid);
    Serial.print("2.WiFi-Password: ");
    Serial.println(password);
    Serial.print("3.WiFi-Device IP: ");
    Serial.println(staticHostNumber);

    // Verify configuration validity (prevent empty or illegal values)
    if (ssid.isEmpty() || password.isEmpty() || staticHostNumber <= 0) {
      Serial.println("Invalid NVS configuration! Using defaults.");
    }
  }

  // Connect to WiFi
  // If there is saved configuration, try to connect to WiFi, get network segment information, configure static IP
  if (!ssid.isEmpty() && !password.isEmpty() && staticHostNumber > 0)
  {          
      connectToWiFi(ssid.c_str(), password.c_str());       
    if (WiFi.status() == WL_CONNECTED) {
      connectToWiFiStatic(ssid.c_str(), password.c_str());
    }
  }
  /*************************Reset Counter***************************/
  esp_reset_reason_t reason = esp_reset_reason();
  if (reason != ESP_RST_POWERON) { // Only read count for non-power-on resets
    // Get last restart count (default 0)
    Preferences restartPreferences;
    restartPreferences.begin(NVS_RESTART_NAMESPACE, false);  // Writable mode
    restartCount = restartPreferences.getInt(KEY_RESTART_COUNT, 0);
    restartPreferences.end();
    Serial.println("Software restart count:");
    Serial.println(restartCount);
  }
  else
  {
  // ---------------------- Power-on reset, clear count to 0 ----------------------
    Preferences restartPreferencesWrite;
    restartPreferencesWrite.begin(NVS_RESTART_NAMESPACE, false);
    restartPreferencesWrite.putInt(KEY_RESTART_COUNT, 0);
    restartPreferencesWrite.end();
 
  }


  server.begin(); //Start server
}

//Tips//
/*
1.Flickering is normal when EPD is performing a full screen update to clear ghosting from the previous image so to ensure better clarity and legibility for the new image.
2.There will be no flicker when EPD performs a partial refresh.
3.Please make sue that EPD enters sleep mode when refresh is completed and always leave the sleep mode command. Otherwise, this may result in a reduced lifespan of EPD.
4.Please refrain from inserting EPD to the FPC socket or unplugging it when the MCU is being powered to prevent potential damage.)
5.Re-initialization is required for every full screen update.
6.When porting the program, set the BUSY pin to input mode and other pins to output mode.
*/

int epdInch=0;//E-paper size
int epdColor;//E-paper color
int epdIC;//E-paper IC
int epdWidth;//E-paper global width
int epdHeight;//E-paper global height
int HandpacketSize=4096*2;//2 empty data packets to prevent packet loss
void loop() {
  long i;
  long num;
  long dataLong= 0;
  
  #if 1 //Full screen refresh, fast refresh, and partial refresh demostration.
     /************Full display*******************/
 if (WiFi.status() == WL_CONNECTED)  //After successful serial WiFi configuration, the e-paper will no longer display configuration info on next boot to retain last displayed image
  {
    Serial.println("E-paper Display WiFi Network Status");
    //EPD_WhiteScreen_GUI_WiFiConfigOk(); 
    Serial.println("WiFi Configuration Successful");
    //WiFi connected successfully, reset restart count to 0
    Preferences restartPreferences;
    restartPreferences.begin(NVS_RESTART_NAMESPACE, false);  // Writable mode
    restartPreferences.putInt(KEY_RESTART_COUNT, 0);
    restartPreferences.end();
  }
  // ---------------------- New: Restart count threshold check ----------------------
  if (WiFi.status()!= WL_CONNECTED) //WiFi connection failed, device restarts once
  {
    Serial.println("E-paper Display WiFi Network Status");
    //EPD_WhiteScreen_GUI_WiFiConfigWrong(); 
    Serial.println("WiFi Configuration Failed!!!");
  }
   while(1)
  {
    WiFi_Serialconfiguration();//WiFi serial port configuration

      // Non-blocking check if detection time is reached
    if (millis() - lastCheckTime >= CHECK_INTERVAL) {
      lastCheckTime = millis();
      checkWiFiStatus();//Check WiFi status every 30 seconds 
    }
      

     WiFiClient client = server.available();   // listen for incoming clients  
      if (client) 
      {      
        while (client.connected()) // loop while the client's connected
        {            
          if (client.available())  // if there's bytes to read from the client,
          { 
            //black and white datas////////////////////
            if(num<HandpacketSize) //Read excess data, receive complete packet before processing to prevent packet loss
            {
               receiveBuffer[num] = (char)client.read(); // Read byte by byte (-1 means read failure) 
            }
            if(num==HandpacketSize)  //Get e-paper related parameters from buffer
            {
              epdWidth=receiveBuffer[0]*256+receiveBuffer[1];//E-paper global width
              epdHeight=receiveBuffer[2]*256+receiveBuffer[3];//E-paper global height
              epdColor=receiveBuffer[4];//E-paper color
              epdInch=receiveBuffer[6]*256+receiveBuffer[7];//E-paper size       
              Serial.println(epdColor);
              Serial.println(epdInch);
            }
           if(num>=HandpacketSize)  //Get e-paper related parameters from buffer
           {
              if(epdInch==750)
              {
                if(epdColor==2)
                {
                
                  if(num==HandpacketSize)  //First HandpacketSize: 2 placeholder packets to prevent loss, first 10 bytes are e-paper resolution/color parameters
                  {
                    dataLong=800*480/8;
                    EPD_Init750_BW(); //Full screen update initialization.
                    EPD_W21_WriteCMD(0x10); //Old  Data         
                  }          
                  if(num>=HandpacketSize&&num<dataLong+HandpacketSize) //black and white
                    EPD_W21_WriteDATA(client.read()); //Write Old Data，This is necessary   
                  if(num==dataLong+HandpacketSize)  
                    EPD_W21_WriteCMD(0x13);//New Data
                  if(num>=dataLong+HandpacketSize&&num<dataLong*2+HandpacketSize)//Red and White
                    EPD_W21_WriteDATA(~client.read());  //Write New Data   
                  if(num>=dataLong*2+HandpacketSize) //Read excess data
                  {
                    client.read(); //Read only without processing 
                  }
                    
                }
                if(epdColor==3) //3-color
                {
                  if(num==HandpacketSize)
                  {
                    dataLong=800*480/8;
                    EPD_Init750_BWR(); //Full screen update initialization.
                    EPD_W21_WriteCMD(0x10); //Old  Data         
                  }          
                  if(num>=HandpacketSize&&num<dataLong+HandpacketSize) //black and white
                    EPD_W21_WriteDATA(client.read()); //Write Old Data，This is necessary   
                  if(num==dataLong+HandpacketSize)  
                    EPD_W21_WriteCMD(0x13);//New Data
                  if(num>=dataLong+HandpacketSize&&num<dataLong*2+HandpacketSize) //Red and White
                    EPD_W21_WriteDATA(~client.read());  //Write New Data   
                  if(num>=dataLong*2+HandpacketSize) //Read excess data
                  {
                    client.read(); //Read only without processing 
                  }
                }    
                
                if(epdColor==4) //4-color
                {
                  if(num==HandpacketSize)
                  {
                    dataLong=800*480/4;
                    EPD_Init750_BWRY(); //Full screen update initialization.
                    EPD_W21_WriteCMD(0x10); //Old  Data         
                  }          
                  if(num>=HandpacketSize&&num<dataLong+HandpacketSize) //black and white
                    EPD_W21_WriteDATA(client.read()); //Write Old Data，This is necessary     
                  if(num>=dataLong+HandpacketSize) //Read excess data
                    client.read(); //Read only without processing   
                }  
              } 
              else if(epdInch==1330)
              {
                if(epdColor==2)
                {               
                  if(num==HandpacketSize)  //First HandpacketSize: 2 placeholder packets to prevent loss, first 10 bytes are e-paper resolution/color parameters
                  {
                    dataLong=960*680/8;
                    EPD_HW_Init1330_BW(); //Full screen update initialization.
                    EPD_W21_WriteCMD(0x24); //Old  Data         
                  }          
                  if(num>=HandpacketSize&&num<dataLong+HandpacketSize) //black and white
                    EPD_W21_WriteDATA(client.read()); //Write Old Data，This is necessary   
                  if(num>=dataLong+HandpacketSize) //Read excess data
                    client.read(); //Read only without processing   
                }
                if(epdColor==3) //3-color
                {
                  if(num==HandpacketSize)
                  {
                    dataLong=960*680/8;
                    EPD_HW_Init1330_BW(); //Full screen update initialization.
                    EPD_W21_WriteCMD(0x24); //Old  Data         
                  }          
                  if(num>=HandpacketSize&&num<dataLong+HandpacketSize) //black and white
                    EPD_W21_WriteDATA(client.read()); //Write Old Data，This is necessary   
                  if(num==dataLong+HandpacketSize)  
                    EPD_W21_WriteCMD(0x26);//New Data
                  if(num>=dataLong+HandpacketSize&&num<dataLong*2+HandpacketSize) //Red and White
                    EPD_W21_WriteDATA(~client.read());  //Write New Data   
                  if(num>=dataLong*2+HandpacketSize) //Read excess data
                    client.read(); //Read only without processing   
                }    
                
                if(epdColor==4) //4-color
                {
                  if(num==HandpacketSize)
                  {
                    dataLong=960*680/4;
                    EPD_Init1330_BWRY(); //Full screen update initialization.
                    EPD_W21_WriteCMD(0x10); //Old  Data         
                  }          
                  if(num>=HandpacketSize&&num<dataLong+HandpacketSize) //black and white
                    EPD_W21_WriteDATA(client.read()); //Write Old Data，This is necessary     
                  if(num>=dataLong+HandpacketSize) //Read excess data
                    client.read(); //Read only without processing   
                }  
              }
              else //Continue saving data to buffer for sizes below 4.2 inches
              {         
                receiveBuffer[num] = (char)client.read(); // Read byte by byte (-1 means read failure)
              }   
            }                          
           num++; //count add
          }         
        }
       


      if(epdColor==2) //2-color (Black/White)
      {
        dataLong= epdWidth*epdHeight/8;
        Serial.println("BW mode");
        if(epdInch==97) //0.97 inch low resolution
        {
          Serial.println("0.97 inch");
          EPD_HW_Init_097(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
         if(epdInch==153) //1.54 inch low resolution
        {
          Serial.println("1.54L inch");
          EPD_HW_Init_153(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==154) //1.54 inch
        {
          Serial.println("1.54 inch");
          EPD_HW_Init_154(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==213) //2.13 inch
        {
          Serial.println("2.13 inch");
          EPD_HW_Init_213(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==266) //2.66 inch
        {
          Serial.println("2.66 inch");
          EPD_HW_Init_266(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==267) //2.66H inch
        {
          Serial.println("2.66H inch");
          EPD_HW_Init_267(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD1685_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==270) //2.7 inch
        {
          Serial.println("2.7 inch");
          EPD_HW_Init_270(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==290) //2.9 inch
        {
          Serial.println("2.9 inch");
          EPD_HW_Init_290(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==291) //2.9H inch
        {
          Serial.println("2.9H inch");
          EPD_HW_Init_291(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD1685_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==370) //3.7 inch
        {
          Serial.println("3.7 inch");
          EPD_HW_Init_370(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_UC_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_UC(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==420) //4.2 inch
        {
          Serial.println("4.2 inch");
          EPD_HW_Init_420(0); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==750) //7.5 inch
        {
            Serial.println("7.5 inch 2-color update");
            EPD_Update_UC();//EPD refresh
            EPD_DeepSleep_UC(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.                        
        }
        if(epdInch==1330)
        {
          Serial.println("13.3 inch 2-color update");
          EPD_Update(); //EPD refresh       
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.       
        }

      }      
      if(epdColor==3) //3-color (Black/White/Red)
      {
        dataLong= epdWidth*epdHeight/4;
        Serial.println("RW mode");
        if(epdInch==97) //0.97 inch 
        {
          Serial.println("0.97 inch");
          EPD_HW_Init_097(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==153) //1.54 inch low resolution
        {
          Serial.println("1.54L inch");
          EPD_HW_Init_153(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==154) //1.54 inch  
        {
          Serial.println("1.54 inch");
          EPD_HW_Init_154(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==213) //2.13 inch
        {
          Serial.println("2.13 inch");
          EPD_HW_Init_213(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==266) //2.66 inch
        {
          Serial.println("2.66 inch");
          EPD_HW_Init_266(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==270) //2.7 inch
        {
          Serial.println("2.7 inch");
          EPD_HW_Init_270(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==290) //2.9 inch
        {
          Serial.println("2.9 inch");
          EPD_HW_Init_290(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==370) //3.7 inch
        {
          Serial.println("3.7 inch");
          EPD_HW_Init_370(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_UC_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_UC(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==420) //4.2 inch
        {
          Serial.println("4.2 inch");
          EPD_HW_Init_420(1); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_RW(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==750) //7.5 inch
        {
            Serial.println("7.5 inch 3-color update");
            EPD_Update_UC();//EPD refresh
            EPD_DeepSleep_UC(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.                        
        }
        if(epdInch==1330)
        {
          Serial.println("13.3 inch 3 color update");
          EPD_Update(); //EPD refresh       
          EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.       
        }
      }
      if(epdColor==4) //4-color (Black/White/Red/Yellow)
      {
        dataLong= epdWidth*epdHeight/4;
        Serial.println("BWRY mode");
        if(epdInch==97) //0.97 inch
        {
          Serial.println("0.97 inch");
          EPD_HW_Init_BWRY_097(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }        
        if(epdInch==153) //1.54L inch
        {
          Serial.println("1.54L inch");
          EPD_HW_Init_BWRY_153(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==154) //1.54 inch
        {
          Serial.println("1.54 inch");
          EPD_HW_Init_BWRY_154(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==213) //2.13 inch
        {
          Serial.println("2.13 inch");
          EPD_HW_Init_BWRY_213(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==266) //2.66 inch
        {
          Serial.println("2.66 inch");
          EPD_HW_Init_BWRY_266(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==267) //2.66H inch
        {
          Serial.println("2.66H inch");
          EPD_HW_Init_BWRY_267(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==270) //2.7 inch
        {
          Serial.println("2.7 inch");
          EPD_HW_Init_BWRY_270(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==290) //2.9 inch
        {
          Serial.println("2.9 inch");
          EPD_HW_Init_BWRY_290(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==291) //2.9H inch
        {
          Serial.println("2.9H inch");
          EPD_HW_Init_BWRY_291(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==370) //3.7 inch
        {
          Serial.println("3.7 inch");
          EPD_HW_Init_BWRY_370(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==420) //4.2 inch
        {
          Serial.println("4.2 inch");
          EPD_HW_Init_BWRY_420(); //Full screen refresh initialization.
          Serial.println("Display");
          EPD_WhiteScreen_ALL_SSD_BWRY(receiveBuffer,dataLong);
          Serial.println("Sleep");
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
          Serial.println("Update is ok");
        }
        if(epdInch==750||epdInch==1330) //7.5/13.3 inch
        {
          Serial.println("7.5/13.3 4-color update");
          EPD_Update_BWRY();//EPD refresh
          EPD_DeepSleep_BWRY(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
        }
      }
      epdInch=0;
      epdColor=0;
      num=0; //RESET 0


















       client.stop();       
      }
          
  }

  #endif
     
}






void connectToWiFi(const char* ssid, const char* password) {
  WiFi.persistent(true);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.disconnect();

  WiFi.begin(ssid, password);
  ConnectTimeout = MAX_Timeout; //30 seconds

  while (WiFi.status() != WL_CONNECTED && ConnectTimeout > 0) {
    delay(1000);
    Serial.print(".");
    ConnectTimeout--;
    WiFi_Serialconfiguration();//WiFi serial port configuration
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi setup successful");
  } else {
    Serial.println("");
    Serial.println("WiFi Connection Failed");
  }
}
void connectToWiFiStatic(const char* ssid, const char* password) {
  WiFi.persistent(true);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.disconnect();

  // Obtain gateway address and extract network segment information from it
  IPAddress gateway = WiFi.gatewayIP();
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns1 = gateway;
  IPAddress dns2 = gateway;
  // Generate static IP addresses using customizable host numbers
  IPAddress staticIP(gateway[0], gateway[1], gateway[2], staticHostNumber);
  // Set static IP address
  if (WiFi.config(staticIP, gateway, subnet, dns1, dns2) == false) {
      Serial.println("Configuration failed.");
  }

  WiFi.begin(ssid, password);
  ConnectTimeout = MAX_Timeout; //30 seconds

  while (WiFi.status() != WL_CONNECTED && ConnectTimeout > 0) {
    delay(1000);
    Serial.print(".");
    ConnectTimeout--;
    WiFi_Serialconfiguration();//WiFi serial port configuration
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("WiFi Connection Failed");
  }
}
/*
void Reset_reconnectToWiFi(void) //Reset and reconnect WiFi
{
    ConnectTimeout = MAX_Timeout; // 30 seconds
    while (WiFi.status() != WL_CONNECTED) //Check WiFi connection status for 30 seconds
    {
        delay(1000);
        Serial.print(".");
        Serial.print(WiFi.status());
        WiFi_Serialconfiguration();//WiFi serial port configuration
        if (--ConnectTimeout <= 0) {
            Serial.println();
            Serial.println("WiFi connect timeout");
            delay(10);
            Serial.println("The device will restart...");
            //Record ESP32 restart count  
// ---------------------- Increase count only before restart ----------------------
            Preferences restartPreferencesWrite;
            restartPreferencesWrite.begin(NVS_RESTART_NAMESPACE, false);
            restartCount = restartPreferencesWrite.getInt(KEY_RESTART_COUNT, 0);
            restartCount++; // Increment count
            if(restartCount==2880) //Reset count after 24 hours
            restartCount=0;
            restartPreferencesWrite.putInt(KEY_RESTART_COUNT, restartCount);
            restartPreferencesWrite.end();
            Serial.printf("Restart count update:%d\r\n", restartCount);
            Serial.println("--3--");
            delay(1000);
            Serial.println("--2--");
            delay(1000);
            Serial.println("--1--");
            delay(1000);
            ESP.restart();  //Reset ESP32 to ensure WiFi connection is OK
        }

    }

}
*/
// Check WiFi status and reconnect when disconnected
void checkWiFiStatus() {
  Serial.print("Check WiFi status...");
  
  // Check WiFi connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi has been disconnected, try to reconnect...");
   // Connect to WiFi
  // If there is saved configuration, try to connect to WiFi, get network segment information, configure static IP
  if (!ssid.isEmpty() && !password.isEmpty() && staticHostNumber > 0)
  {          
      connectToWiFi(ssid.c_str(), password.c_str());       
    if (WiFi.status() == WL_CONNECTED) {
      connectToWiFiStatic(ssid.c_str(), password.c_str());
    }
  }
  } else {
    Serial.println("WiFi connection is ok");
  }
}
/*
//WiFi configuration via serial commands
void WiFi_Serialconfiguration(void)
{
  if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim();

      // Parse command
      if (command.startsWith("setwifi")) {
        // Extract WiFi name, password and IP number
        int firstSpaceIndex = command.indexOf(' ', 7);
        int lastSpaceIndex = command.lastIndexOf(' ');
        ssid = command.substring(7, firstSpaceIndex);
        password = command.substring(firstSpaceIndex + 1, lastSpaceIndex);
        staticHostNumber = command.substring(lastSpaceIndex + 1).toInt();
        // Print newly received WiFi name, password and IP number
        Serial.println("");
        Serial.print("1.Received WiFi-Name: ");
        Serial.println(ssid);
        Serial.print("2.Received WiFi-Password: ");
        Serial.println(password);
        Serial.print("3.Received WiFi-Device IP: ");
        Serial.println(staticHostNumber);

       // Save configuration to NVS (optimized write logic)
      Preferences preferences;
      bool nvsOpened = preferences.begin(NVS_NAMESPACE, false); // Writable mode

      if (!nvsOpened) {
        Serial.println("NVS write failed!");
        return; // Return directly on write failure
      }

      preferences.putString(SSID_KEY, ssid);
      preferences.putString(PASSWORD_KEY, password);
      preferences.putInt(HOST_NUMBER_KEY, staticHostNumber);
      preferences.end(); // Ensure NVS connection is closed

      Serial.println("Configuration saved to NVS.");

        // Connect to WiFi
          // If there is saved configuration, try to connect to WiFi, get network segment information
          if (!ssid.isEmpty() && !password.isEmpty() && staticHostNumber > 0) {
            connectToWiFi(ssid.c_str(), password.c_str());
          }
          if (WiFi.status() == WL_CONNECTED)
          {
            // If there is saved configuration, try to connect to WiFi, configure static IP
            if (!ssid.isEmpty() && !password.isEmpty() && staticHostNumber > 0) {
              connectToWiFiStatic(ssid.c_str(), password.c_str());
            }   
          }
      }
  }

}
*/
void WiFi_Serialconfiguration(void) {
  static byte buffer[64];
  static int bufferIndex = 0;
  static bool receiving = false;
  
  while (Serial.available()) {
    byte b = Serial.read();
    
    if (!receiving) {
      // Start receiving new data
      bufferIndex = 0;
      receiving = true;
    }
    
    buffer[bufferIndex++] = b;
    
    // Check if 64 bytes are received
    if (bufferIndex == 64) {
      // Verify end markers
      if (buffer[62] == 0x0D && buffer[63] == 0x0A) {
        // Extract field lengths
        byte ssidLength = buffer[0];
        byte passwordLength = buffer[30];
        byte hostLength = buffer[60];
        
        // Verify lengths are within valid range
        if (ssidLength <= MAX_SSID_LENGTH && 
            passwordLength <= MAX_PASSWORD_LENGTH && 
            hostLength <= MAX_HOST_LENGTH) {
            
            // Extract WiFi information
            char ssid1[MAX_SSID_LENGTH + 1] = {0};
            char password1[MAX_PASSWORD_LENGTH + 1] = {0};
            char host1[MAX_HOST_LENGTH + 1] = {0};
            
            memcpy(ssid1, &buffer[1], ssidLength);
            memcpy(password1, &buffer[31], passwordLength);
            memcpy(host1, &buffer[61], hostLength);
           
            Serial.println(buffer[61]);
            // Convert IP number
            staticHostNumber = buffer[61];
            
            // Print received information
            Serial.println("");
            Serial.print("1.Received WiFi-Name: ");
            Serial.println(ssid1);
            Serial.print("2.Received WiFi-Password: ");
            Serial.println(password1);
            Serial.print("3.Received WiFi-Device IP: ");
            Serial.println(staticHostNumber);
            
            // Save configuration to NVS
            Preferences preferences;
            preferences.begin(NVS_NAMESPACE, false);
            preferences.putString(SSID_KEY, ssid1);
            preferences.putString(PASSWORD_KEY, password1);
            preferences.putInt(HOST_NUMBER_KEY, staticHostNumber);
            preferences.end();
            /*
            // Connect to WiFi
            if (!String(ssid1).isEmpty() && !String(password1).isEmpty() && staticHostNumber > 0) 
            {          
               connectToWiFi(ssid1, password1);            
              if (WiFi.status() == WL_CONNECTED) {
                connectToWiFiStatic(ssid1, password1);
              }
              ConnectTimeout=0;//Set timeout to 0 to exit upper layer WiFi detection
            }
            if (WiFi.status() == WL_CONNECTED)  //WiFi connected successfully, display WiFi connection status
            {
              Serial_wifi=1;//Serial WiFi configuration successful flag
              Serial.println("E-paper Display WiFi Network Status");
              EPD_WhiteScreen_GUI_WiFiConfigOk(); 
              Serial.println("WiFi Configuration Successful");
              //WiFi connected successfully, reset restart count to 0
              Preferences restartPreferences;
              restartPreferences.begin(NVS_RESTART_NAMESPACE, false);  // Writable mode
              restartPreferences.putInt(KEY_RESTART_COUNT, 0);
              restartPreferences.end();
            }
            else
            {
              Serial_wifi=0;//Serial WiFi configuration failed flag
              Serial.println("E-paper Display WiFi Network Status");
              EPD_WhiteScreen_GUI_WiFiConfigWrong(); 
              Serial.println("WiFi Configuration Failed!!!");
            }*/
            Serial.println("--3--");
            delay(1000);
            Serial.println("--2--");
            delay(1000);
            Serial.println("--1--");
            delay(1000);
            ESP.restart();  //Reset ESP32 to ensure WiFi connection is OK
        } else {
          Serial.println("Error: Invalid data length!");
        }
      } else {
        Serial.println("Error: Invalid end marker!");
      }
      
      receiving = false; // Reset receive status
    }
  }
}

/*
void EPD_WhiteScreen_GUI_WiFiConfigOk(void)
{
   //Data initialization settings.
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set canvas parameters, GUI image rotation, please change 270 to 0/90/180/270.
		Paint_SelectImage(BlackImage); //Select current settings.
	  EPD_Init();
    // Drawing on the image	
		Paint_Clear(WHITE);  
    Paint_DrawString_EN(10, 40, "--WiFi connection successful--", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(10, 85, "1.WiFi-Name:", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(180, 80, ssid.c_str(), &Font24, BLACK, WHITE);
    Paint_DrawString_EN(10, 85+30, "2.WiFi-Password:", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(240, 80+30, password.c_str(), &Font24,  BLACK, WHITE);
    Paint_DrawString_EN(10, 85+30*2, "3.WiFi-StaticHostNumber:", &Font20, WHITE, BLACK);
    Paint_DrawNum(360, 80+30*2, staticHostNumber, &Font24, BLACK, WHITE);
    EPD_WhiteScreen_GUI(BlackImage);//display image B
		//EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen..	
}
void EPD_WhiteScreen_GUI_WiFiConfigWrong(void) //NG--inverse color
{
   //Data initialization settings.
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set canvas parameters, GUI image rotation, please change 270 to 0/90/180/270.
		Paint_SelectImage(BlackImage); //Select current settings.
	  EPD_Init();
    // Drawing on the image	
		Paint_Clear(WHITE);  
    Paint_DrawString_EN(10, 20, "--WiFi connection failed !!!--", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(10, 40, "--Please check the WiFi configuration !!!--", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(10, 85, "1.WiFi-Name:", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(180, 80, ssid.c_str(), &Font24, BLACK, WHITE);
    Paint_DrawString_EN(10, 85+30, "2.WiFi-Password:", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(240, 80+30, password.c_str(), &Font24, BLACK, WHITE);
    Paint_DrawString_EN(10, 85+30*2, "3.WiFi-StaticHostNumber:", &Font20, WHITE, BLACK);
    Paint_DrawNum(360, 80+30*2, staticHostNumber, &Font24, BLACK, WHITE);
    EPD_WhiteScreen_GUI_Wrong(BlackImage);//display image B
		//EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen..	
}
*/



//////////////////////////////////END//////////////////////////////////////////////////