#include<ESP32epdx.h> //E-paper SPI etc
//EPD
#include"EPD.h"  //E-paper driver
#include"IMAGE.h" //E-paper image data


unsigned char BlackImage[EPD_ARRAY];//Define canvas space
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
 
 #if 1 //Full screen update, fast update, and partial update demostration.
     /************Full display*******************/
      EPD_HW_Init(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(gImage_BW1,gImage_RW1); //To Display one image using full screen refresh.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(3000); //3s           
#endif   

 #if 1 //GUI demostration.
///////////////////////////GUI///////////////////////////////////////////////////////////////////////////////////
   //Data initialization settings
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set screen size and display orientation
    /**************Drawing**********************/
    //Black and white images/////////////////////////////
    Paint_SelectImage(BlackImage);//Set the virtual canvas data storage location
    Paint_Clear(WHITE);
		//Point.   
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT); //point 1x1.
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT); //point 2x2.
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT); //point 3x3.
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT); //point 4x4.
		EPD_HW_Init_GUI(); //EPD init GUI
    EPD_Display_BW(BlackImage); //Display GUI image.
    //Red and white images///////////////////////
    Paint_Clear(WHITE);
    //Line.
    Paint_DrawLine(20, 5, 50, 35, RED, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 1.
    Paint_DrawLine(50, 5, 20, 35, RED, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 2.
		//Rectangle.
    Paint_DrawRectangle(20, 5, 50, 35, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow rectangle 1.
    Paint_DrawRectangle(70, 5, 100, 35, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1); //Hollow rectangle 2.
    //Circle.
		Paint_DrawCircle(30, 50, 10, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow circle.
    Paint_DrawCircle(80, 50, 10, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1); //solid circle.
    EPD_Display_RW(BlackImage); //Display GUI image.
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(3000); //3s   
    
    /***********String&Number***************************/ 
    //Black and white images/////////////////////////////
    Paint_SelectImage(BlackImage);//Set the virtual canvas data storage location
    Paint_Clear(WHITE);
    Paint_DrawString_EN(0, 0, "Good Display", &Font8, BLACK, WHITE);  //Font8
    Paint_DrawString_EN(0, 10, "Good Display", &Font12, BLACK, WHITE); //Font12
    Paint_DrawString_EN(0, 25, "Good Display", &Font16, BLACK, WHITE); //Font16
    Paint_DrawString_EN(0, 45, "Good Display", &Font20, BLACK, WHITE); //Font20
    EPD_HW_Init_GUI(); //EPD init GUI
    EPD_Display_BW(BlackImage); //Display GUI image.
    //Red and white images///////////////////////
    Paint_Clear(WHITE);
    Paint_DrawNum(0, 80, 123456789, &Font8, RED, WHITE);  //Font8
    Paint_DrawNum(0, 90, 123456789, &Font12, RED, WHITE); //Font12
    Paint_DrawNum(0, 105, 123456789, &Font16, RED, WHITE); //Font16
    EPD_Display_RW(BlackImage); //Display GUI image.
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(3000); //3s    
#endif 
    //Clear
    EPD_HW_Init(); //EPD init
    EPD_WhiteScreen_White();//EPD Clear
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(3000); //3s    


 
  while(1); // The program stops here
  
} 
