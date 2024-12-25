#include<ESP32epdx.h> //E-paper SPI etc
//EPD
#include"EPD.h"  //E-paper driver
#include"IMAGE.h" //E-paper image data


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
      EPD_WhiteScreen_ALL_Fast(gImage_2); //To display one image using fast update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.

  #if 1 //Partial update demostration.
  //Partial update demo support displaying a clock at 5 locations with 00:00.  If you need to perform partial update more than 5 locations, please use the feature of using partial update at the full screen demo.
  //After 5 partial updates, implement a full screen update to clear the ghosting caused by partial updates.
  //////////////////////Partial update time demo/////////////////////////////////////
      EPD_HW_Init(); //Electronic paper initialization. 
      EPD_SetRAMValue_BaseMap(gImage_basemap); //Please do not delete the background color function, otherwise it will cause unstable display during partial update.
      for(i=0;i<6;i++)
      EPD_Dis_Part_Time(320,124+48*0, Num[1],         //x-A,y-A,DATA-A
                        320,124+48*1, Num[0],         //x-B,y-B,DATA-B
                        320,124+48*2, gImage_numdot, //x-C,y-C,DATA-C
                        320,124+48*3, Num[0],        //x-D,y-D,DATA-D
                        320,124+48*4,Num[i],48,104); //x-E,y-E,DATA-E,Resolution  32*64
		
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
      EPD_DeepSleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s. 
  #endif
  #if 1 //Demonstration of full screen update with 180-degree rotation, to enable this feature, please change 0 to 1.
      /************Full display(2s)*******************/
      EPD_HW_Init_180(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
  #endif    
#endif


 #if 1 //GUI demostration.
///////////////////////////GUI///////////////////////////////////////////////////////////////////////////////////
   //Data initialization settings
    Paint_NewImage(ImageBW, EPD_HEIGHT, EPD_WIDTH, 90, WHITE); //(is  differrent!!!)Set screen size and display orientation 
    /**************Drawing**********************/
    Paint_SelectImage(ImageBW);//Set the virtual canvas data storage location
    Paint_Clear(WHITE);
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
		Paint_DrawCircle(150, 200, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow circle.
    Paint_DrawCircle(250,200, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1); //solid circle.
    EPD_HW_Init_GUI(); //EPD init GUI
    EPD_Display(ImageBW);//display image
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(2000); //2s   
    
    /***********String&Number***************************/ 
    Paint_SelectImage(ImageBW);//Set the virtual canvas data storage location
    Paint_Clear(WHITE);
    Paint_DrawString_EN(0, 0, "Good Display", &Font8, BLACK, WHITE);  //5*8.
		Paint_DrawString_EN(0, 10, "Good Display", &Font12, BLACK, WHITE); //7*12.
		Paint_DrawString_EN(0, 25, "Good Display", &Font16, BLACK, WHITE); //11*16.
		Paint_DrawString_EN(0, 45, "Good Display", &Font20, BLACK, WHITE); //14*20.
		Paint_DrawString_EN(0, 80, "Good Display", &Font24, BLACK, WHITE); //17*24.
    Paint_DrawNum(200, 200, 123456789, &Font8, BLACK, WHITE);  //5*8.
		Paint_DrawNum(200, 210, 123456789, &Font12, BLACK, WHITE); //7*12.
		Paint_DrawNum(200, 225, 123456789, &Font16, BLACK, WHITE); //11*16.
		Paint_DrawNum(200, 245, 123456789, &Font20, BLACK, WHITE); //14*20.
		Paint_DrawNum(200, 270, 123456789, &Font24, BLACK, WHITE); //17*24.
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
