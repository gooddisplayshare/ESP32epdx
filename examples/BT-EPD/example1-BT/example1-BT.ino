#include<ESP32epdx.h> //E-paper SPI etc
//EPD
#include"EPD.h"  //E-paper driver
#include"IMAGE.h" //E-paper image data
//BT
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT; 
char BT_RX_BUF[100]; //BT receive data
char StringNum[100];// BT display  data
unsigned int DataLength;// Data length

unsigned char ImageBW[EPD_ARRAY];//Define canvas space  

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
  //BT
   Serial.begin(115200);
   SerialBT.begin("ESP32test"); //Bluetooth device name
   Serial.println("The device started, now you can pair it with bluetooth!");
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
void loop() {
    unsigned char i;
    int num;
    EPD_HW_Init(); //Full screen update initialization.
    EPD_WhiteScreen_White(); //Clear screen function.
    EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.

//Send the following test data in hexadecimal format using Bluetooth debugging assistant
//AA 55 E1 00 08 40 41 42 43 44 45 46 47 04 FF 0D 0A    （40~47：@ABCDEFG   ascii） 
/*AA 55: Data Header 
  E1: Function Bit 
  00: Reserved 
  08: Data Length 
  40-47: Data Bit
  04: Verification 
  FF 0D 0A: Data Tail 
*/ 
while(1)
{   
    if(SerialBT.available()) //Bluetooth data reception
    {
      
      BT_RX_BUF[num++]=SerialBT.read(); 
    }
    if(BT_RX_BUF[16]==0x0A) //Determine the data tail
      {
        Serial.println("BT_RX_BUF[16]==0x0A");
        //Get display data
        for(i=0;i<BT_RX_BUF[4];i++)
        {
            StringNum[i]=BT_RX_BUF[i+5];  //Extract data: 5-12 data sections
         }
         //Confirm BT data
        for(i=0;i<17;i++)
        {
          SerialBT.write(BT_RX_BUF[i]); 
          Serial.write(BT_RX_BUF[i]);
          BT_RX_BUF[i]=0;
          }
        if(i==17) 
        {
            i=0;
            num=0;
        }

    //After receiving Bluetooth data, the electronic paper GUI displays the StrinNum, which is the real data sent by the phone:@ ABCDEFG
    #if 1  //Bluetooth receives 8 bytes of data
      //Data initialization settings
      Paint_NewImage(ImageBW, EPD_WIDTH, EPD_HEIGHT, 270, WHITE); // Set screen size and display orientation
      Paint_SelectImage(ImageBW);// Set the virtual canvas data storage location
      /***********String***************************/ 
      Paint_Clear(WHITE);
      Paint_DrawString_EN(0, 0, "Good Display", &Font12, WHITE, BLACK);  // Display Good Display
      Paint_DrawString_EN(0, 50,  StringNum, &Font20, BLACK, WHITE);  // Display Bluetooth data sent by mobile phone，@ABCDEFG
      Paint_DrawString_EN(0, 70,  StringNum, &Font24, BLACK, WHITE);  // Display Bluetooth data sent by mobile phone，@ABCDEFG
      EPD_HW_Init_GUI(); //EPD init GUI
      EPD_Display(ImageBW);//Display image 
      EPD_DeepSleep();// EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!        
    #endif

    #if 0 //StringNum is image data, use this function.
      EPD_HW_Init(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(StringNum); // To Display one image using full screen refresh.
      EPD_DeepSleep(); // Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
    #endif
  }
}





 #if 0 //Full screen update, fast update, and partial update demostration.
      EPD_HW_Init(); //Full screen update initialization.
      EPD_WhiteScreen_White(); //Clear screen function.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s. 
     /************Full display(2s)*******************/
      EPD_HW_Init(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.         
			/************Fast update mode(1.5s)*******************/
			EPD_HW_Init_Fast(); //Fast update initialization.
			EPD_WhiteScreen_ALL_Fast(gImage_2); //To display the second image using fast update.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(2000); //Delay for 2s. 

     /************4 Gray update mode*******************/
	#if 1		//To enable this feature, please change 0 to 1
			EPD_HW_Init_4G(); //4 Gray update initialization.
			EPD_WhiteScreen_ALL_4G(gImage_4G1); //To display one image using fast update.
			EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
			delay(2000); //Delay for 2s. 

	 #endif 
  
  #if 1 //Partial update demostration.
  //Partial update demo support displaying a clock at 5 locations with 00:00.  If you need to perform partial update more than 5 locations, please use the feature of using partial update at the full screen demo.
  //After 5 partial updates, implement a full screen update to clear the ghosting caused by partial updates.
  //////////////////////Partial update time demo/////////////////////////////////////
      EPD_HW_Init(); //Electronic paper initialization. 
      EPD_SetRAMValue_BaseMap(gImage_basemap); //Please do not delete the background color function, otherwise it will cause unstable display during partial update.
      for(i=0;i<6;i++)
      EPD_Dis_Part_Time(32,92+32*0,Num[i],         //x-A,y-A,DATA-A
                        32,92+32*1,Num[0],         //x-B,y-B,DATA-B
                        32,92+32*2,gImage_numdot, //x-C,y-C,DATA-C
                        32,92+32*3,Num[0],        //x-D,y-D,DATA-D
                        32,92+32*4,Num[1],32,64); //x-E,y-E,DATA-E,Resolution 32*64

      EPD_DeepSleep();  //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
  #endif  
  
  #if 1 //Demo of using partial update to update the full screen, to enable this feature, please change 0 to 1.
  //After 5 partial updates, implement a full screen update to clear the ghosting caused by partial updates.
  //////////////////////Partial update time demo/////////////////////////////////////
      EPD_HW_Init(); //E-paper initialization 
      EPD_SetRAMValue_BaseMap(gImage_p1); //Please do not delete the background color function, otherwise it will cause an unstable display during partial update.
      EPD_Dis_PartAll(gImage_p1); //Image 1
      EPD_Dis_PartAll(gImage_p2); //Image 2
      EPD_Dis_PartAll(gImage_p3); //Image 3
      EPD_Dis_PartAll(gImage_p4); //Image 4
      EPD_Dis_PartAll(gImage_p5); //Image 5
      EPD_DeepSleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s. 

  #endif
  #if 1 //Demonstration of full screen update with 180-degree rotation, to enable this feature, please change 0 to 1.
      /************Full display(2s)*******************/
      EPD_HW_Init_180(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000);//Delay for 2s.
  #endif        
#endif   


 #if 0 //GUI demostration.
///////////////////////////GUI///////////////////////////////////////////////////////////////////////////////////
   //Data initialization settings
    Paint_NewImage(ImageBW, EPD_WIDTH, EPD_HEIGHT, 270, WHITE); //Set screen size and display orientation
    /**************Drawing**********************/
    Paint_SelectImage(ImageBW);//Set the virtual canvas data storage location
    Paint_Clear(WHITE);
		//Point.   
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT); //point 1x1.
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT); //point 2x2.
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT); //point 3x3.
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT); //point 4x4.
		//Line.
    Paint_DrawLine(20, 5, 50, 35, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 1.
    Paint_DrawLine(50, 5, 20, 35, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 2.
		//Rectangle.
    Paint_DrawRectangle(20, 5, 50, 35, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow rectangle 1.
    Paint_DrawRectangle(70, 5, 100, 35, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //Hollow rectangle 2.
    //Circle.
		Paint_DrawCircle(30, 50, 10, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow circle.
    Paint_DrawCircle(80, 50, 10, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //solid circle.
    EPD_HW_Init_GUI(); //EPD init GUI
    EPD_Display(ImageBW);//display image
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //2s   
    
    /***********String&Number***************************/ 
    Paint_SelectImage(ImageBW);//Set the virtual canvas data storage location
    Paint_Clear(WHITE);
    Paint_DrawString_EN(0, 0, "Good Display", &Font8, BLACK, WHITE);  //Font8
    Paint_DrawString_EN(0, 10, "Good Display", &Font12, BLACK, WHITE); //Font12
    Paint_DrawString_EN(0, 25, "Good Display", &Font16, BLACK, WHITE); //Font16
    Paint_DrawString_EN(0, 45, "Good Display", &Font20, BLACK, WHITE); //Font20
    Paint_DrawNum(0, 80, 123456789, &Font8, BLACK, WHITE);  //Font8
    Paint_DrawNum(0, 90, 123456789, &Font12, BLACK, WHITE); //Font12
    Paint_DrawNum(0, 105, 123456789, &Font16, BLACK, WHITE); //Font16
    EPD_HW_Init_GUI(); //EPD init GUI
    EPD_Display(ImageBW); //display image
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //2s    
#endif 
    //Clear
    EPD_HW_Init(); //EPD init
    EPD_WhiteScreen_White();//EPD Clear
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //2s  




 
  while(1); // The program stops here
  
} 
