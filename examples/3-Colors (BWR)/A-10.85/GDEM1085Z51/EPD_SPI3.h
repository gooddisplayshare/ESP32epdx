#ifndef _EPD_SPI3_SPI_
#define _EPD_SPI3_SPI_
#include "Arduino.h"

//IO settings
#define isEPD_W21_BUSY digitalRead(A14)  //BUSY
#define EPD_W21_RST_0 digitalWrite(A15,LOW)  //RES
#define EPD_W21_RST_1 digitalWrite(A15,HIGH)
#define EPD_W21_CS2_0 digitalWrite(A16,LOW) //CS2
#define EPD_W21_CS2_1 digitalWrite(A16,HIGH)
#define EPD_W21_CS_0 digitalWrite(A17,LOW) //CS
#define EPD_W21_CS_1 digitalWrite(A17,HIGH)

#define EPD_W21_CLK_0 digitalWrite(18,LOW)
#define EPD_W21_CLK_1 digitalWrite(18,HIGH)
#define EPD_W21_MOSI_0  digitalWrite(23,LOW)
#define EPD_W21_MOSI_1  digitalWrite(23,HIGH) 



void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char datas);
void EPD_W21_WriteCMD(unsigned char command);
void EPD_W21_WriteDATA1(unsigned char datas);
void EPD_W21_WriteCMD1(unsigned char command);
void EPD_W21_WriteDATA2(unsigned char datas);
void EPD_W21_WriteCMD2(unsigned char command);
#endif 
