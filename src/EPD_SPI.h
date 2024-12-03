#ifndef _EPD_SPI_H_
#define _EPD_SPI_H_
#include "Arduino.h"

//IO settings
/*
ESP32-WROOM-32D (Using hardware SPI)
BUSY——A14
RES——A15
DC——A16
CS——A17
SCK—GPIO18
SDIN—GPIO23
*/
#define isEPD_W21_BUSY digitalRead(A14)  //BUSY
#define EPD_W21_RST_0 digitalWrite(A15,LOW)  //RES
#define EPD_W21_RST_1 digitalWrite(A15,HIGH)
#define EPD_W21_DC_0  digitalWrite(A16,LOW) //DC
#define EPD_W21_DC_1  digitalWrite(A16,HIGH)
#define EPD_W21_CS_0 digitalWrite(A17,LOW) //CS
#define EPD_W21_CS_1 digitalWrite(A17,HIGH)


void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char datas);
void EPD_W21_WriteCMD(unsigned char command);


#endif 
