#ifndef _EPD_H_
#define _EPD_H_

#define EPD_WIDTH   112
#define EPD_HEIGHT  208
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  
//Full screen update display
void EPD_Init(void); 
void EPD_Init_180(void);	
void EPD_WhiteScreen_ALL(const unsigned char *datas);
void EPD_WhiteScreen_White(void);
void EPD_WhiteScreen_Black(void);
void EPD_DeepSleep(void);
//Partial update display 
void EPD_Init_Part(void);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_PartAll(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Dis_Part_Time(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
												const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE);										 
//GUI display				
void EPD_Init_GUI(void);												
void EPD_Display(unsigned char *Image); 
												 
#endif



