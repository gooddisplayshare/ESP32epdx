#include <EPD_SPI.h>
#include "EPD.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
   delay(xms);
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
//Busy function
void lcd_chkstatus(void)
{ 
  while(1)
  {	 //=0 BUSY
     if(isEPD_W21_BUSY==1) break;
  }  
}
void EPD_init(void)
{
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	lcd_chkstatus();  

  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}
	
void EPD_init_Fast(void)
{
  delay_xms(100);//At least 100ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	lcd_chkstatus();  

	EPD_W21_WriteCMD(0xe0);
	EPD_W21_WriteDATA(0x02);	
	EPD_W21_WriteCMD(0xe6);
	EPD_W21_WriteDATA(90);

	EPD_W21_WriteCMD(0xa5);	
	lcd_chkstatus();   		
	
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}
void EPD_DeepSleep(void)
{  	
	EPD_W21_WriteCMD(0X02);  	//power off
	EPD_W21_WriteDATA(0x00);
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
	EPD_W21_WriteCMD(0X07);  	//deep sleep
	EPD_W21_WriteDATA(0xA5);
}
void EPD_update(void)
{   
  EPD_W21_WriteCMD(0x12); //Display Update Control
	EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();   
}



void Display_All_Black(void)
{
  unsigned long i; 

  EPD_W21_WriteCMD(0x10);
  {
    for(i=0;i<EPD_ARRAY;i++)
    {
      EPD_W21_WriteDATA(0x00);
    }
  } 
  EPD_update();	
	
}

void Display_All_White(void)
{
  unsigned long i;
 
  EPD_W21_WriteCMD(0x10);
  {
    for(i=0;i<EPD_ARRAY;i++)
    {
      EPD_W21_WriteDATA(0x55);
    }
  }	
	 EPD_update();	
}

void Display_All_Yellow(void)
{
  unsigned long i;
 
  EPD_W21_WriteCMD(0x10);
  {
    for(i=0;i<EPD_ARRAY;i++)
    {
      EPD_W21_WriteDATA(0xaa);
    }
  }
	 EPD_update();	
}


void Display_All_Red(void)
{
  unsigned long i;
 
  EPD_W21_WriteCMD(0x10);
  {
    for(i=0;i<EPD_ARRAY;i++)
    {
      EPD_W21_WriteDATA(0xff);
    }
  }	
	 EPD_update();	
}



unsigned char Color_get(unsigned char color)
{
	unsigned datas;
	switch(color)
	{
		case 0x00:
			datas=white;	
      break;		
		case 0x01:
			datas=yellow;
		  break;
		case 0x02:
			datas=red;
		  break;		
		case 0x03:
			datas=black;
		  break;			
    default:
      break;			
	}
	 return datas;
}


void PIC_display(const unsigned char* picData)
{
  unsigned int i;
	unsigned char temp1;
	unsigned char data_H1,data_H2,data_L1,data_L2,data;
	 
	EPD_W21_WriteCMD(0x10);	       
  for(i=0;i<EPD_ARRAY;i++)  
	{
			temp1=picData[i]; 
			data_H1=Color_get(temp1>>6&0x03)<<6;			
			data_H2=Color_get(temp1>>4&0x03)<<4;
			data_L1=Color_get(temp1>>2&0x03)<<2;
			data_L2=Color_get(temp1&0x03);
			
			data=data_H1|data_H2|data_L1|data_L2;
      EPD_W21_WriteDATA(data);
		
  }	
	 //update
    EPD_update();	
}

void EPD_init_180(void)
{
  delay_xms(100);//At least 100ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	lcd_chkstatus();  

  EPD_W21_WriteCMD(0x00);	//PSR
  EPD_W21_WriteDATA(0x03);

	EPD_W21_WriteCMD(0xe0);
	EPD_W21_WriteDATA(0x02);	
	EPD_W21_WriteCMD(0xe6);
	EPD_W21_WriteDATA(90);

	EPD_W21_WriteCMD(0xa5);	
	lcd_chkstatus();   		
	
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}

/***********************************************************
						end file
***********************************************************/


