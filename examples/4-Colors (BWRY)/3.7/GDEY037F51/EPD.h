#ifndef _EPD_H_
#define _EPD_H_


#define EPD_WIDTH   240
#define EPD_HEIGHT  416
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/4   

//2bit
#define black   0x00	/// 00
#define white   0x01	///	01
#define yellow  0x02	///	10
#define red     0x03	///	11


#define Source_BITS     240
#define Gate_BITS   416
#define ALLSCREEN_BYTES   Source_BITS*Gate_BITS/4

//EPD
void EPD_init(void);
void PIC_display (const unsigned char* picData);
void EPD_DeepSleep(void);
void EPD_update(void);
void lcd_chkstatus(void);
void EPD_init_180(void);

void Display_All_Black(void);
void Display_All_White(void);
void Display_All_Yellow(void);
void Display_All_Red(void);

void Acep_color(unsigned char color);
void EPD_init_Fast(void);
							 

//GUI display					 
void EPD_HW_Init_GUI(void); 
void EPD_Display(unsigned char *datasBW,unsigned char *datasRW);
												 
#endif



