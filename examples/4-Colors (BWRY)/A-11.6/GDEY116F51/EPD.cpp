#include <EPD_SPI.h>
#include "EPD.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
   delay(xms);
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
void EPD_init(void)
{
	delay(100);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10);//At least 10ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal


	EPD_W21_WriteCMD(0x00);	//PSR
	EPD_W21_WriteDATA(0x2F);		
	EPD_W21_WriteDATA(0x29);	

	EPD_W21_WriteCMD(0x01);	//PWRR
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x20);	
	EPD_W21_WriteDATA(0x1E);	
	EPD_W21_WriteDATA(0x78);	
	EPD_W21_WriteDATA(0x20);	


	EPD_W21_WriteCMD(0x03);	//POFS
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x06);	//BTST_P
	EPD_W21_WriteDATA(0x0F);	
	EPD_W21_WriteDATA(0x8B);   	
	EPD_W21_WriteDATA(0x9C);   	
	EPD_W21_WriteDATA(0xC1); 	

	EPD_W21_WriteCMD(0x30); //PLL
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD(0x41);	//TSE
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x50);	//CDI
	EPD_W21_WriteDATA(0x37);

	EPD_W21_WriteCMD(0x60);	//TCON
	EPD_W21_WriteDATA(0x04);
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD(0x61); //TRES
	EPD_W21_WriteDATA(Source_BITS/256);		// Source_BITS_H
	EPD_W21_WriteDATA(Source_BITS%256);		// Source_BITS_L
	EPD_W21_WriteDATA(Gate_BITS/256);			// Gate_BITS_H
	EPD_W21_WriteDATA(Gate_BITS%256); 		// Gate_BITS_L	

	EPD_W21_WriteCMD(0x65);	//GSST
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0XE7); 	// PST
	EPD_W21_WriteDATA(0x16);

	EPD_W21_WriteCMD(0xE3);	//PWS
	EPD_W21_WriteDATA(0x65);

	EPD_W21_WriteCMD(0xE0);	//CCSET
	EPD_W21_WriteDATA(0x00);	


	EPD_W21_WriteCMD(0xE9);
	EPD_W21_WriteDATA(0x01); 

	EPD_W21_WriteCMD(0x62);	
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x5C);
	EPD_W21_WriteDATA(0x9F);
	EPD_W21_WriteDATA(0x8C);
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x63);

	EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
}
void EPD_init_Fast(void)
{
	delay_xms(100);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal


	EPD_W21_WriteCMD(0x00);	//PSR
	EPD_W21_WriteDATA(0x2F);		
	EPD_W21_WriteDATA(0x29);	

	EPD_W21_WriteCMD(0x01);	//PWRR
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x19);	
	EPD_W21_WriteDATA(0x78);	
	EPD_W21_WriteDATA(0x28);	
	EPD_W21_WriteDATA(0x19);	


	EPD_W21_WriteCMD(0x03);	//POFS
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x06);	//BTST_P
	EPD_W21_WriteDATA(0x0F);	
	EPD_W21_WriteDATA(0x98);   	
	EPD_W21_WriteDATA(0xA5);   	
	EPD_W21_WriteDATA(0xA0); 	

	EPD_W21_WriteCMD(0x30); //PLL
	EPD_W21_WriteDATA(0x08);

	EPD_W21_WriteCMD(0x41);	//TSE
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x50);	//CDI
	EPD_W21_WriteDATA(0x37);

	EPD_W21_WriteCMD(0x60);	//TCON
	EPD_W21_WriteDATA(0x04);
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD(0x61); //TRES
	EPD_W21_WriteDATA(Source_BITS/256);		// Source_BITS_H
	EPD_W21_WriteDATA(Source_BITS%256);		// Source_BITS_L
	EPD_W21_WriteDATA(Gate_BITS/256);			// Gate_BITS_H
	EPD_W21_WriteDATA(Gate_BITS%256); 		// Gate_BITS_L	

	EPD_W21_WriteCMD(0x65);	//GSST
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0XE7); 	// PST
	EPD_W21_WriteDATA(0x16);

	EPD_W21_WriteCMD(0xE3);	//PWS
	EPD_W21_WriteDATA(0x65);

	EPD_W21_WriteCMD(0xE0);	//CCSET
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x62);	
	EPD_W21_WriteDATA(0x7d);
	EPD_W21_WriteDATA(0x7d);
	EPD_W21_WriteDATA(0x7d);
	EPD_W21_WriteDATA(0x60);
	EPD_W21_WriteDATA(0xa7);
	EPD_W21_WriteDATA(0x93);
	EPD_W21_WriteDATA(0x7d);
	EPD_W21_WriteDATA(0x68);

	EPD_W21_WriteCMD(0xE9);
	EPD_W21_WriteDATA(0x01); 
	
	//Fast
	EPD_W21_WriteCMD(0xe0);
	EPD_W21_WriteDATA(0x02);	
	EPD_W21_WriteCMD(0xe6);
	EPD_W21_WriteDATA(60);

	EPD_W21_WriteCMD(0xa5);	
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
	EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
}		
void EPD_DeepSleep(void)
{  	
	EPD_W21_WriteCMD(0X02);  	//power off
	EPD_W21_WriteDATA(0x00);
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal!     
 
	EPD_W21_WriteCMD(0X07);  	//deep sleep
	EPD_W21_WriteDATA(0xA5);
}
void EPD_update(void)
{   
  EPD_W21_WriteCMD(0x12); //Display Update Control
	EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();   
}

void lcd_chkstatus(void)
{ 
  while(1)
  {	 //=0 BUSY
     if(isEPD_W21_BUSY==1) break;
  }  
}

void Display_All_Black(void)
{
  unsigned long i; 

  EPD_W21_WriteCMD(0x10);
  {
    for(i=0;i<ALLSCREEN_BYTES;i++)
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
    for(i=0;i<ALLSCREEN_BYTES;i++)
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
    for(i=0;i<ALLSCREEN_BYTES;i++)
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
    for(i=0;i<ALLSCREEN_BYTES;i++)
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
  unsigned int i,j;
	unsigned char temp1;
	unsigned char data_H1,data_H2,data_L1,data_L2,data;
	 
	EPD_W21_WriteCMD(0x10);	       
  for(i=0;i<Gate_BITS;i++)  //Source_BITS*Gate_BITS/4
	{ 
    for(j=0;j<Source_BITS/4;j++)
		{	  
			temp1=picData[i*Source_BITS/4+j]; 

			data_H1=Color_get(temp1>>6&0x03)<<6;			
			data_H2=Color_get(temp1>>4&0x03)<<4;
			data_L1=Color_get(temp1>>2&0x03)<<2;
			data_L2=Color_get(temp1&0x03);
			
			data=data_H1|data_H2|data_L1|data_L2;
      EPD_W21_WriteDATA(data);
		}
  }	
	
	 //update
    EPD_update();	
}

void PIC_display_Half1(unsigned char* picData)
{
  unsigned int i,j;
  unsigned char temp1;
  unsigned char data_H1,data_H2,data_L1,data_L2,data;
   
  EPD_W21_WriteCMD(0x10);        
  for(i=0;i<Gate_BITS/2;i++)  //Source_BITS*Gate_BITS/4
  { 
    for(j=0;j<Source_BITS/4;j++)
    {   
      temp1=picData[i*Source_BITS/4+j]; 

      data_H1=Color_get(temp1>>6&0x03)<<6;      
      data_H2=Color_get(temp1>>4&0x03)<<4;
      data_L1=Color_get(temp1>>2&0x03)<<2;
      data_L2=Color_get(temp1&0x03);
      
      data=data_H1|data_H2|data_L1|data_L2;
      EPD_W21_WriteDATA(data);
    }
  } 
 
}
void PIC_display_Half2(unsigned char* picData)
{
  unsigned int i,j;
  unsigned char temp1;
  unsigned char data_H1,data_H2,data_L1,data_L2,data;
          
 for(i=0;i<Gate_BITS/2;i++)  //Source_BITS*Gate_BITS/4
  { 
    for(j=0;j<Source_BITS/4;j++)
    {   
      temp1=picData[i*Source_BITS/4+j]; 

      data_H1=Color_get(temp1>>6&0x03)<<6;      
      data_H2=Color_get(temp1>>4&0x03)<<4;
      data_L1=Color_get(temp1>>2&0x03)<<2;
      data_L2=Color_get(temp1&0x03);
      
      data=data_H1|data_H2|data_L1|data_L2;
      EPD_W21_WriteDATA(data);
    }
  } 

   //update
    EPD_update();  
}
void EPD_init_180(void)
{
 	delay(100);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10);//At least 10ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal


	EPD_W21_WriteCMD(0x00);	//PSR
	EPD_W21_WriteDATA(0x23);		
	EPD_W21_WriteDATA(0x29);	

	EPD_W21_WriteCMD(0x01);	//PWRR
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x20);	
	EPD_W21_WriteDATA(0x1E);	
	EPD_W21_WriteDATA(0x78);	
	EPD_W21_WriteDATA(0x20);	


	EPD_W21_WriteCMD(0x03);	//POFS
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x06);	//BTST_P
	EPD_W21_WriteDATA(0x0F);	
	EPD_W21_WriteDATA(0x8B);   	
	EPD_W21_WriteDATA(0x9C);   	
	EPD_W21_WriteDATA(0xC1); 	

	EPD_W21_WriteCMD(0x30); //PLL
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD(0x41);	//TSE
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x50);	//CDI
	EPD_W21_WriteDATA(0x37);

	EPD_W21_WriteCMD(0x60);	//TCON
	EPD_W21_WriteDATA(0x04);
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD(0x61); //TRES
	EPD_W21_WriteDATA(Source_BITS/256);		// Source_BITS_H
	EPD_W21_WriteDATA(Source_BITS%256);		// Source_BITS_L
	EPD_W21_WriteDATA(Gate_BITS/256);			// Gate_BITS_H
	EPD_W21_WriteDATA(Gate_BITS%256); 		// Gate_BITS_L	

	EPD_W21_WriteCMD(0x65);	//GSST
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0XE7); 	// PST
	EPD_W21_WriteDATA(0x16);

	EPD_W21_WriteCMD(0xE3);	//PWS
	EPD_W21_WriteDATA(0x65);

	EPD_W21_WriteCMD(0xE0);	//CCSET
	EPD_W21_WriteDATA(0x00);	


	EPD_W21_WriteCMD(0xE9);
	EPD_W21_WriteDATA(0x01); 

	EPD_W21_WriteCMD(0x62);	
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x5C);
	EPD_W21_WriteDATA(0x9F);
	EPD_W21_WriteDATA(0x8C);
	EPD_W21_WriteDATA(0x77);
	EPD_W21_WriteDATA(0x63);

	EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
}


/***********************************************************
						end file
***********************************************************/


