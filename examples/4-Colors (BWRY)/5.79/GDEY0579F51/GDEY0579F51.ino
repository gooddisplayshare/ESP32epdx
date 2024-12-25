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
 
#if 1//Full screen update demostration.

	 /************Full display*******************/
		EPD_init(); //Full screen update initialization.
		PIC_display(gImage_1);//To Display one image using full screen update.
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
		delay(3000); //Delay for 3s.

#endif				
#if 1//GUI Demo(GUI examples can display points, lines, rectangles, circles, letters, numbers, etc).
   //Data initialization settings.
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 180, WHITE0); //Set canvas parameters, GUI image rotation, please change 270 to 0/90/180/270.
    Paint_SetScale(4);
		Paint_SelectImage(BlackImage); //Select current settings.

		/**************Drawing******************************/	
		Paint_Clear(WHITE0);   
    // Drawing on the image
		//Point.   
    Paint_DrawPoint(5, 10, BLACK0, DOT_PIXEL_1X1, DOT_STYLE_DFT); //point 1x1.
    Paint_DrawPoint(5, 25, BLACK0, DOT_PIXEL_2X2, DOT_STYLE_DFT); //point 2x2.
    Paint_DrawPoint(5, 40, RED0, DOT_PIXEL_3X3, DOT_STYLE_DFT); //point 3x3.
    Paint_DrawPoint(5, 55, YELLOW0, DOT_PIXEL_4X4, DOT_STYLE_DFT); //point 4x4.
		//Line.
    Paint_DrawLine(20, 5, 50, 35, BLACK0, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 1.
    Paint_DrawLine(50, 5, 20, 35, BLACK0, LINE_STYLE_SOLID, DOT_PIXEL_1X1); //1x1line 2.
		//Rectangle.
    Paint_DrawRectangle(20, 5, 50, 35, RED0, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow rectangle 1.
    Paint_DrawRectangle(70, 5, 100, 35, YELLOW0, DRAW_FILL_FULL, DOT_PIXEL_1X1); //Hollow rectangle 2.
    //Circle.
		Paint_DrawCircle(30, 50, 10, RED0, DRAW_FILL_EMPTY, DOT_PIXEL_1X1); //Hollow circle.
    Paint_DrawCircle(80, 50, 10, YELLOW0, DRAW_FILL_FULL, DOT_PIXEL_1X1); //solid circle.
    EPD_init(); //Full screen update initialization.
    PIC_display(BlackImage);//display image
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
		delay(3000); //Delay for 3s.	
    /***********String&Number***************************/ 
    Paint_Clear(WHITE0);
    Paint_DrawString_EN(5, 10, "Good Display", &Font8, RED0, WHITE0);  //Font8
    Paint_DrawString_EN(5, 25, "Good Display", &Font12, YELLOW0, WHITE0); //Font12
		Paint_DrawNum(5, 45, 123456789, &Font16, BLACK0, WHITE0); //Font16
    Paint_DrawNum(5, 70, 123456789, &Font20, BLACK0, WHITE0); //Font20
    EPD_init(); //Full screen update initialization.
    PIC_display(BlackImage);//display image
		EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
		delay(3000); //Delay for 3s.	

#endif
    //Clear
    EPD_init(); //Full screen update initialization.
    Display_All_White();//EPD Clear
    EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
    delay(3000); //Delay for 3s.

  while(1); // The program stops here

  
} 
