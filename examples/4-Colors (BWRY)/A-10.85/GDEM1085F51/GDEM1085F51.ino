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
 
#if 1//Full screen update demostration.

		/************Full display*******************/
		EPD_init(); //Full screen update initialization.
		PIC_display(gImage_4G1);//To Display one image using full screen update.
		EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
		delay(3000); //Delay for 3s.
		/************Fast display*******************/
		EPD_init_Fast(); //Fast screen update initialization.
		PIC_display(gImage_4G1);//To Display one image using full screen update.
		EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
		delay(3000); //Delay for 3s.
	#if 0//Demonstration of Display 4 c  0*olors, to enable this feature, please change 0 to 1.
	 /************Full display*******************/
		EPD_init(); //Full screen update initialization.
		Display_All_Black();//To Display one image using full screen update.
		EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
		delay(3000); //Delay for 3s.
		
		EPD_init(); //Full screen update initialization.
		Display_All_Yellow();//To Display one image using full screen update.
		EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
		delay(3000); //Delay for 3s.		

		EPD_init(); //Full screen update initialization.
		Display_All_Red();//To Display one image using full screen update.
		EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
		delay(3000); //Delay for 3s.			
	#endif		
		EPD_init(); //Full screen update initialization.
		Display_All_White(); //Clear screen function.
		EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen..				
#endif				
		while(1);	// The program stops here	
  
} 
