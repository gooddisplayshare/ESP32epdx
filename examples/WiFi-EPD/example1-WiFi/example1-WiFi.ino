#include<ESP32epdx.h> //E-paper SPI etc
//EPD
#include"EPD.h"  //E-paper driver
#include"IMAGE.h" //E-paper image data
//WiFi
#include <WiFi.h>

unsigned char ImageBW[EPD_ARRAY];//Define canvas space  






//WiFi username and password setting
/*
const char* ssid     = "GOODISPLAY";
const char* password = "84619565@";
*/
const char* ssid     = "CU_BBc6"; //WiFi username
const char* password = "za9g8jvb"; //WiFi password

//String  WifiData; 
int num;
WiFiServer server(8080); //Default unchanged
 //IPAddress    The local IP address can be set by first querying the local network segment through ImageToWiFi upper computer software.
IPAddress staticIP(192, 168, 2, 208);  //Change network segment and IP number
IPAddress gateway(192, 168, 2, 1); //Change network segment
IPAddress subnet(255, 255, 255, 0); //Default unchanged
IPAddress dns1(192, 168, 2,1); //Change network segment
IPAddress dns2(192, 168, 2,1); //Change network segment


void setup() {
 /* ESP32-WROOM-32D (Using hardware SPI)
  BUSY——GPIO13  RES——GPIO12  DC——GPIO14  CS——GPIO27  SCK—GPIO18  SDIN—GPIO23  */
   pinMode(13, INPUT);  //BUSY
   pinMode(12, OUTPUT); //RES 
   pinMode(14, OUTPUT); //DC   
   pinMode(27, OUTPUT); //CS   
   //SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
   SPI.begin ();  
  //WiFi
   Serial.begin(115200);

   // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

 //WIFI Parameter settings
  WiFi.persistent(true);
  WiFi.mode(WIFI_STA); // switch off AP
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.disconnect();


//Pass in static IP address and gateway parameters DNS1, And 2
  if (WiFi.config(staticIP, gateway, subnet, dns1, dns2) == false) {
    Serial.println("Configuration failed.");
  }
    WiFi.begin(ssid, password); //DNS1  DNS2
Connect1:
int ConnectTimeout = 60; // 30 seconds

    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    Serial.print(WiFi.status());

    if (--ConnectTimeout <= 0)
    {
      Serial.println();
      Serial.println("WiFi connect timeout");
      //goto Connect1;
      delay(10);
       ESP.restart();  //Reset ESP32 to ensure WiFi connection is OK
    }
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); //local IP
    
    server.begin();

}

//Tips//
/*
1.Flickering is normal when EPD is performing a full screen update to clear ghosting from the previous image so to ensure better clarity and legibility for the new image.
2.There will be no flicker when EPD performs a partial update.
3.Please make sue that EPD enters sleep mode when update is completed and always leave the sleep mode command. Otherwise, this may result in a reduced lifespan of EPD.
4.Please refrain from inserting EPD to the FPC socket or unplugging it when the MCU is being powered to prevent potential damage.)
5.Re-initialization is required for every full screen update.
6.When porting the program, set the BUSY pin to input mode and other pins to output mode.
*/



/*
Operation steps:
1. Use the ImageToWiFi upper computer software to locate the local network segment.
2. Set the device IP address.
3. Set the network segment and IP number of the target device on the upper computer.
4. Transfer image data to the device through ImageToWiFi software. Different electronic paper initialization and data sending commands may vary, and the actual electronic paper driver program shall prevail.
*/
void loop() {
    long i;
    long num;
    long dataLong=EPD_ARRAY;
    //If WiFi is connected, e-paper screen clearing
    EPD_Init(); //Full screen update initialization.
    EPD_WhiteScreen_White(); //Clear screen function.
    EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.

 
while(1)
  {

   while (WiFi.status() != WL_CONNECTED) {
           Serial.println("Reconnecting to WiFi...");
           WiFi.disconnect(); //Disconnect WiFi
           WiFi.reconnect(); //Reconnect WiFi
         }

     WiFiClient client = server.available();   // listen for incoming clients  
      if (client) 
      {      
        EPD_Init(); //Full screen update initialization.  
        while (client.connected()) // loop while the client's connected
        {            
          if (client.available())  // if there's bytes to read from the client,
          { 
            //black and white datas////////////////////
            if(num==0)
              EPD_W21_WriteCMD(0x10); //Old  Data
            if(num<dataLong) //black and white
              EPD_W21_WriteDATA(client.read()); //Write Old Data，This is necessary   
            if(num==dataLong)  
              EPD_W21_WriteCMD(0x13);//New Data
            if(num>=dataLong&&num<dataLong*2) //Red and White
              EPD_W21_WriteDATA(~client.read());  //Write New Data   
            if(num>=dataLong*2) //Read excess data
               client.read(); //Read only without processing              
            num++; //count add
          }          
        }
        EPD_Update();//EPD refresh
        EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
        num=0; //RESET 0
        // close the connection:
        client.println("OK");//Send data and receive OK signal
        client.stop(); 
      
      }
  }















 #if 1 //Full screen update, fast update, and partial update demostration.

      EPD_Init(); //Full screen update initialization.
      EPD_WhiteScreen_White(); //Clear screen function.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s. 
     /************Full display(2s)*******************/
      EPD_Init(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
            
      /************Fast update mode(1.5s)*******************/
      EPD_Init_Fast(); //Fast update initialization.
      EPD_WhiteScreen_ALL_Fast(gImage_2); //To display one image using fast update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
			/************4 Gray update mode(2s)*******************/
			EPD_Init_4G(); //Fast update initialization.
			EPD_WhiteScreen_ALL_4G(gImage_4G1); //To display one image using 4 gray update.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(2000); //Delay for 2s.

  #if 1 //Partial update demostration.
  //Partial update demo support displaying a clock at 5 locations with 00:00.  If you need to perform partial update more than 5 locations, please use the feature of using partial update at the full screen demo.
  //After 5 partial updates, implement a full screen update to clear the ghosting caused by partial updates.
  //////////////////////Partial update time demo/////////////////////////////////////
      EPD_Init(); //Electronic paper initialization.  
      EPD_SetRAMValue_BaseMap(gImage_basemap); //Please do not delete the background color function, otherwise it will cause unstable display during partial update.
      EPD_Init_Part(); //Pa update initialization.
      for(i=0;i<6;i++)
      {
        EPD_Dis_Part_Time(200,180,Num[1],Num[0],gImage_numdot,Num[0],Num[i],5,104,48); //x,y,DATA-A~E,Resolution 48*104                 
      }       
      
      EPD_DeepSleep();  //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
      EPD_Init(); //Full screen update initialization.
      EPD_WhiteScreen_White(); //Clear screen function.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
  #endif  
  
  #if 0    //Demo of using partial update to update the full screen, to enable this feature, please change 0 to 1.
  //After 5 partial updates, implement a full screen update to clear the ghosting caused by partial updates.
  //////////////////////Partial update time demo/////////////////////////////////////
      EPD_Init(); //Full screen update initialization.
      EPD_WhiteScreen_White(); //Clear screen function.
      EPD_Init_Part();
      EPD_Dis_PartAll(gImage_p1);

      EPD_DeepSleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s. 
      
      EPD_Init(); //Full screen update initialization.
      EPD_WhiteScreen_White(); //Clear screen function.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
  #endif
  
  #if 0 //Demonstration of full screen update with 180-degree rotation, to enable this feature, please change 0 to 1.
      /************Full display(2s)*******************/
      EPD_Init_180(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
  #endif        
  
#endif


 #if 1 //GUI Demo(GUI examples can display points, lines, rectangles, circles, letters, numbers, etc).
   //Data initialization settings.
    Paint_NewImage(ImageBW, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set canvas parameters, GUI image rotation, please change 0 to 0/90/180/270.
    Paint_SelectImage(ImageBW); //Select current settings.
    /**************Drawing demonstration**********************/   
		
		Paint_Clear(WHITE); //Clear canvas.
		//Point.   
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT); //point 1x1.
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT); //point 2x2.
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT); //point 3x3.
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT); //point 4x4.
		//Line.
    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 1.
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 2.
		//Rectangle.
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow rectangle 1.
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //Hollow rectangle 2.
    //Circle.
		Paint_DrawCircle(150, 90, 30, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow circle.
    Paint_DrawCircle(200, 90, 30, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //solid circle.
    EPD_Init(); //Full screen update initialization.
    EPD_Display(ImageBW); //Display GUI image.
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //Delay for 2s.
		
    /***********Letter demo***************************/
		Paint_Clear(WHITE); //Clear canvas.
    Paint_DrawString_EN(0, 0, "Good Display", &Font8, BLACK, WHITE);  //5*8.
		Paint_DrawString_EN(0, 10, "Good Display", &Font12, BLACK, WHITE); //7*12.
		Paint_DrawString_EN(0, 25, "Good Display", &Font16, BLACK, WHITE); //11*16.
		Paint_DrawString_EN(0, 45, "Good Display", &Font20, BLACK, WHITE); //14*20.
		Paint_DrawString_EN(0, 80, "Good Display", &Font24, BLACK, WHITE); //17*24.`
    Paint_DrawNum(0, 120, 123456789, &Font8, BLACK, WHITE);  //5*8.
		Paint_DrawNum(0, 130, 123456789, &Font12, BLACK, WHITE); //7*12.
		Paint_DrawNum(0, 155, 123456789, &Font16, BLACK, WHITE); //11*16.
		Paint_DrawNum(0, 175, 123456789, &Font20, BLACK, WHITE); //14*20.
		Paint_DrawNum(0, 210, 123456789, &Font24, BLACK, WHITE); //17*24.
    EPD_Init(); //Full screen update initialization.
    EPD_Display(ImageBW);//Display GUI image.
		EPD_DeepSleep(); //EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //Delay for 2s.	

#endif
    //Clear
    EPD_Init(); //Full screen update initialization.
    EPD_WhiteScreen_White(); //Clear screen function.
    EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
    delay(2000); //Delay for 2s.

  while(1); // The program stops here
  
} 
