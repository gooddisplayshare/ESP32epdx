//EPD
#include"EPD.h"  //E-paper driver
#include"IMAGE.h" //E-paper image data


unsigned char ImageBW[EPD_ARRAY];//Define canvas space  
void setup() {
 /* ESP32-WROOM-32D (Using 3-wire SPI)
  BUSY——GPIO13  RES——GPIO12  CS2——GPIO14  CS——GPIO27  SCK—GPIO18  SDIN—GPIO23  */
   pinMode(A14, INPUT);  //BUSY
   pinMode(A15, OUTPUT); //RES 
   pinMode(A16, OUTPUT); //CS2    
   pinMode(A17, OUTPUT); //CS    
   pinMode(18, OUTPUT); //SCLK 
   pinMode(23, OUTPUT); //SDI     
 
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

      EPD_Init(); //Full screen update initialization.
      EPD_WhiteScreen_White(); //Clear screen function.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s. 
     /************Full display(4s)*******************/
      EPD_Init(); //Full screen update initialization.
      EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
            
  #if 1    //Demo of using partial refresh to update the full screen, to enable this feature, please change 0 to 1.
  //After 5 partial refreshes, implement a full screen refresh to clear the ghosting caused by partial refreshes.
  //////////////////////Partial refresh time demo/////////////////////////////////////
      EPD_Init(); //Full screen refresh initialization.
      EPD_WhiteScreen_White(); //Clear screen function.   
      EPD_Init_Part();
      EPD_WhiteScreen_ALL_P(gImage_p1,gImage_p1);
      EPD_WhiteScreen_ALL_P(gImage_p1,gImage_p2);
      EPD_WhiteScreen_ALL_P(gImage_p2,gImage_p3); 
      EPD_DeepSleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
      
  #endif
  
  #if 1 //Demonstration of full screen update with 180-degree rotation, to enable this feature, please change 0 to 1.
      /************Full display(4s)*******************/
      EPD_Init_180(); //Full screen update initialization.
      EPD_WhiteScreen_ALL180(gImage_1); //To Display one image using full screen update.
      EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
      delay(2000); //Delay for 2s.
  #endif        
  
#endif

    //Clear
    EPD_Init(); //Full screen update initialization.
    EPD_WhiteScreen_White(); //Clear screen function.
    EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
    delay(2000); //Delay for 2s.

  while(1); // The program stops here
  
} 
