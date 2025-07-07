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
	int read_temp;
	delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	//Read temperature
	EPD_W21_WriteCMD(0x40);
	delay_xms(100);
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	delay_xms(1);
	read_temp=EPD_W21_ReadDATA(); 
  Serial.println(read_temp);

	if((read_temp&0x80)==0x80)	//0C	
	{
    EPD_W21_WriteCMD(0xe0);
    EPD_W21_WriteDATA(0x01);
		delay_xms(10);
	}	
	else
	{
		EPD_W21_WriteCMD(0xe0); //OTP
		EPD_W21_WriteDATA(0x01);
		delay_xms(10);	
		
		EPD_W21_WriteCMD(0xA5);
		delay_xms(10);
		lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal		
	}
	
	EPD_W21_WriteCMD(0xA2);//MASTER enable
	EPD_W21_WriteDATA(0x01);
	
	EPD_W21_WriteCMD(0x00);  //PSR
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x29);

	EPD_W21_WriteCMD(0xA2);//close
	EPD_W21_WriteDATA(0x00);
	
	EPD_W21_WriteCMD(0xA2); //SLAVE enable
	EPD_W21_WriteDATA(0x02);
	
	EPD_W21_WriteCMD(0x00);  //PSR
	EPD_W21_WriteDATA(0x03);
	EPD_W21_WriteDATA(0x29);	
	
	EPD_W21_WriteCMD(0xA2);//close
	EPD_W21_WriteDATA(0x00);	
	
	EPD_W21_WriteCMD(0x01);	//0x01 PWRR
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x26);
	EPD_W21_WriteDATA(0x78);
	EPD_W21_WriteDATA(0x24);
	EPD_W21_WriteDATA(0x26);
		
	EPD_W21_WriteCMD(0x06);	//0x06 BTST_P
	EPD_W21_WriteDATA(0xC0);	
	EPD_W21_WriteDATA(0xC0);	
	EPD_W21_WriteDATA(0xC0);	

	EPD_W21_WriteCMD(0x50);//CDI
	EPD_W21_WriteDATA(0x97);  //border white
	
	EPD_W21_WriteCMD(0x61);//0x61	
	EPD_W21_WriteDATA(Source_BITS/256);	
	EPD_W21_WriteDATA(Source_BITS%256);	
	EPD_W21_WriteDATA(Gate_BITS/256);	
	EPD_W21_WriteDATA(Gate_BITS%256);	

	EPD_W21_WriteCMD(0x65);	//0x65 GSST
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	
	EPD_W21_WriteCMD(0xE3);	//0xE3 PWS
	EPD_W21_WriteDATA(0x77);	
		
//PWM_ADJ////////////////////////////
	EPD_W21_WriteCMD(0xFF);       
  EPD_W21_WriteDATA(0xA5);     
	
	EPD_W21_WriteCMD(0xEF);//PWM
	
  EPD_W21_WriteDATA(1); 	 //H0 
	EPD_W21_WriteDATA(30);  //L0
	EPD_W21_WriteDATA(6);   //H1   
	EPD_W21_WriteDATA(30);  //L1 
	EPD_W21_WriteDATA(14);   //H2
	EPD_W21_WriteDATA(28);   //L2
	EPD_W21_WriteDATA(18);   //H3
	EPD_W21_WriteDATA(16);   //L3  

	EPD_W21_WriteCMD(0xDB);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xCF);
	EPD_W21_WriteDATA(0x00);		    

	EPD_W21_WriteCMD(0xDF);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xFD);
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0xE8);
	EPD_W21_WriteDATA(0x03);

	EPD_W21_WriteCMD(0xDC);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xDD);
	EPD_W21_WriteDATA(10);	 
	EPD_W21_WriteCMD(0xDE);
	EPD_W21_WriteDATA(60);	 

	EPD_W21_WriteCMD(0xFF);        
	EPD_W21_WriteDATA(0xE3); 
	
	EPD_W21_WriteCMD(0xE9);
	EPD_W21_WriteDATA(0x01); 
	
	EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
}
	
void EPD_init_Fast(void)
{
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

	EPD_W21_WriteCMD(0xe6);	//Fast
	EPD_W21_WriteDATA(60);

	EPD_W21_WriteCMD(0xe0);
	EPD_W21_WriteDATA(0x03);
	delay_xms(2);

	EPD_W21_WriteCMD(0xA5);
	delay_xms(10);
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal	
	
	EPD_W21_WriteCMD(0xA2);
	EPD_W21_WriteDATA(0x01);
	
	EPD_W21_WriteCMD(0x00);  //PSR
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x29);

	EPD_W21_WriteCMD(0xA2);	//close
	EPD_W21_WriteDATA(0x00);	
		
	EPD_W21_WriteCMD(0xA2);
	EPD_W21_WriteDATA(0x02);
	
	EPD_W21_WriteCMD(0x00);  //PSR
	EPD_W21_WriteDATA(0x03);
	EPD_W21_WriteDATA(0x29);	
	
	EPD_W21_WriteCMD(0xA2); //close
	EPD_W21_WriteDATA(0x00);	
	
	EPD_W21_WriteCMD(0x01);	//0x01 PWRR
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x26);
	EPD_W21_WriteDATA(0x78);
	EPD_W21_WriteDATA(0x24);
	EPD_W21_WriteDATA(0x26);
		
	EPD_W21_WriteCMD(0x06);	//0x06 BTST_P
	EPD_W21_WriteDATA(0xC0);	
	EPD_W21_WriteDATA(0xC0);	
	EPD_W21_WriteDATA(0xC0);	
	
	EPD_W21_WriteCMD(0x50);//CDI
	EPD_W21_WriteDATA(0x97);  //border white

	EPD_W21_WriteCMD(0x61);//0x61	
	EPD_W21_WriteDATA(Source_BITS/256);	
	EPD_W21_WriteDATA(Source_BITS%256);	
	EPD_W21_WriteDATA(Gate_BITS/256);	
	EPD_W21_WriteDATA(Gate_BITS%256);	

	EPD_W21_WriteCMD(0x65);	//0x65 GSST
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
		
	EPD_W21_WriteCMD(0xE3);	//0xE3 PWS
	EPD_W21_WriteDATA(0x77);	
	
	//PWM_ADJ////////////////////////////
	EPD_W21_WriteCMD(0xFF);       
  EPD_W21_WriteDATA(0xA5);     
	
	EPD_W21_WriteCMD(0xEF);//PWM
	
  EPD_W21_WriteDATA(1); 	 //H0 
	EPD_W21_WriteDATA(30);  //L0
	EPD_W21_WriteDATA(6);   //H1   
	EPD_W21_WriteDATA(30);  //L1 
	EPD_W21_WriteDATA(14);   //H2
	EPD_W21_WriteDATA(28);   //L2
	EPD_W21_WriteDATA(18);   //H3
	EPD_W21_WriteDATA(16);   //L3  

	EPD_W21_WriteCMD(0xDB);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xCF);
	EPD_W21_WriteDATA(0x00);		    

	EPD_W21_WriteCMD(0xDF);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xFD);
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0xE8);
	EPD_W21_WriteDATA(0x03);

	EPD_W21_WriteCMD(0xDC);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xDD);
	EPD_W21_WriteDATA(10);	 
	EPD_W21_WriteCMD(0xDE);
	EPD_W21_WriteDATA(60);	 

	EPD_W21_WriteCMD(0xFF);        
	EPD_W21_WriteDATA(0xE3); 
	
	
	EPD_W21_WriteCMD(0xE9);
	EPD_W21_WriteDATA(0x01); 
	
	EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
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
  EPD_W21_WriteCMD(0xA2); 
	EPD_W21_WriteDATA(0x00);	
	
  EPD_W21_WriteCMD(0x12); 
	EPD_W21_WriteDATA(0x01);
  lcd_chkstatus();   
}


void Display_All_Black(void)
{
  unsigned long i; 
  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x01);
  EPD_W21_WriteCMD(0x10);
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0x00);
	}  
  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x02);
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
  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x01);
  EPD_W21_WriteCMD(0x10);

	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0x55);
	}
  
  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteCMD(0x10);
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0x55);
	}

	 EPD_update();	
}

void Display_All_Yellow(void)
{
  unsigned long i;
  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x01);
  EPD_W21_WriteCMD(0x10);  
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0xAA);
	}

  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteCMD(0x10);
  {
    for(i=0;i<ALLSCREEN_BYTES;i++)
    {
      EPD_W21_WriteDATA(0xAA);
    }
  } 
	 EPD_update();	
}


void Display_All_Red(void)
{
  unsigned long i;
  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x01);
  EPD_W21_WriteCMD(0x10);
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0xFF);
	}
   
  EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteCMD(0x10);
	for(i=0;i<ALLSCREEN_BYTES;i++)
	{
		EPD_W21_WriteDATA(0xFF);
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
	 
	EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x01);
	EPD_W21_WriteCMD(0x10);	       
  for(i=0;i<Gate_BITS/2;i++)  //Source_BITS*Gate_BITS/4
	{ 
    for(j=0;j<Source_BITS/4;j++)
		{	  
			temp1=picData[(272-i-1)*2*Source_BITS/4+j]; 

			data_H1=Color_get(temp1>>6&0x03)<<6;			
			data_H2=Color_get(temp1>>4&0x03)<<4;
			data_L1=Color_get(temp1>>2&0x03)<<2;
			data_L2=Color_get(temp1&0x03);
			
			data=data_H1|data_H2|data_L1|data_L2;
      EPD_W21_WriteDATA(data);
		}
	      
    for(j=0;j<Source_BITS/4;j++)
		{	  
			temp1=picData[i*2*Source_BITS/4+j]; 

			data_H1=Color_get(temp1>>6&0x03)<<6;			
			data_H2=Color_get(temp1>>4&0x03)<<4;
			data_L1=Color_get(temp1>>2&0x03)<<2;
			data_L2=Color_get(temp1&0x03);
			
			data=data_H1|data_H2|data_L1|data_L2;
      EPD_W21_WriteDATA(data);
		}
  }		
	
	
	EPD_W21_WriteCMD(0xA2);
  EPD_W21_WriteDATA(0x02);
	EPD_W21_WriteCMD(0x10);	       
  for(i=0;i<Gate_BITS/2;i++)  //Source_BITS*Gate_BITS/4
	{ 
    for(j=Source_BITS/4;j<2*Source_BITS/4;j++)
		{	  
			temp1=picData[(272-i-1)*2*Source_BITS/4+j]; 

			data_H1=Color_get(temp1>>6&0x03)<<6;			
			data_H2=Color_get(temp1>>4&0x03)<<4;
			data_L1=Color_get(temp1>>2&0x03)<<2;
			data_L2=Color_get(temp1&0x03);
			
			data=data_H1|data_H2|data_L1|data_L2;
      EPD_W21_WriteDATA(data);
		}	
	
    for(j=Source_BITS/4;j<2*Source_BITS/4;j++)
		{	  
			temp1=picData[i*2*Source_BITS/4+j]; 

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




/***********************************************************
						end file
***********************************************************/


