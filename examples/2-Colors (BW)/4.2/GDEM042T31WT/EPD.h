#ifndef _EPD_H_
#define _EPD_H_

#define EPD_WIDTH   400 
#define EPD_HEIGHT  300
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  

//Full screen update display
void EPD_Init(void);
void EPD_WhiteScreen_ALL(const unsigned char *datas);
void EPD_DeepSleep(void);
void EPD_Update(void);
void lcd_chkstatus(void);
void EPD_WhiteScreen_White(void);		
void EPD_Init_180(void);								 							
//GUI			 
void EPD_Display(unsigned char *Image);
												 
#endif



