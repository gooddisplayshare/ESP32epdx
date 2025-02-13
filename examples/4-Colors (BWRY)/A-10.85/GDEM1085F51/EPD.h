#ifndef _EPD_H_
#define _EPD_H_

#define EPD_WIDTH   1360/2
#define EPD_HEIGHT  480
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  

//2bit
#define black   0x00	/// 00
#define white   0x01	///	01
#define yellow  0x02	///	10
#define red     0x03	///	11

#define Source_BITS_All     1360
#define Source_BITS     1360/2
#define Gate_BITS   480
#define ALLSCREEN_BYTES   Source_BITS_All*Gate_BITS/4


//EPD
void EPD_init(void);
void PIC_display (const unsigned char* picData);
void EPD_sleep(void);
void EPD_update(void);
void lcd_chkstatus(void);

void Display_All_Black(void);
void Display_All_White(void);
void Display_All_Yellow(void);
void Display_All_Red(void);

void Acep_color(unsigned char color);  
//Fast
void EPD_init_Fast(void);    
#endif



