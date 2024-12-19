#ifndef _EPD_H_
#define _EPD_H_

#define EPD_WIDTH   960
#define EPD_HEIGHT  680
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  

//Full screen update display
void EPD_HW_Init(void); 
void EPD_HW_Init_180(void);	
void EPD_WhiteScreen_ALL(const unsigned char* datasBW,const unsigned char* datasRW);
void EPD_WhiteScreen_White(void);
void EPD_WhiteScreen_Black(void);
void EPD_DeepSleep(void);
				 
//GUI
void EPD_HW_Init_GUI(void);				 
void EPD_Display_BW(unsigned char* datasBW);
void EPD_Display_RW(unsigned char* datasRW);												 
#endif



