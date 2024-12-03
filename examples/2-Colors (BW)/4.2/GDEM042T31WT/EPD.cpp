#include <EPD_SPI.h>
#include "EPD.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
   delay(xms);
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////

void lcd_chkstatus(void)
{
  while(isEPD_W21_BUSY==0);                      
}
//UC8276
void EPD_Init(void)
{		
		EPD_W21_RST_0;		// Module reset
		delay_xms(10);//At least 10ms delay 
		EPD_W21_RST_1;
		delay_xms(10);//At least 10ms delay 

    lcd_chkstatus(); 

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();//waiting for the electronic paper IC to release the idle signal		
		
		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x1f);		//LUT from OTP£¬KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f
		
		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (EPD_WIDTH/256);
		EPD_W21_WriteDATA (EPD_WIDTH%256);    	 
		EPD_W21_WriteDATA (EPD_HEIGHT/256);
		EPD_W21_WriteDATA (EPD_HEIGHT%256); 

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}


void EPD_DeepSleep(void)
{
		EPD_W21_WriteCMD(0X02);  	//power off
	  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
    delay_xms(100);    //!!!The delay here is necessary,100mS at least!!!     
	  EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}
//Full screen update function
void EPD_Update(void)
{   
	//update
	EPD_W21_WriteCMD(0x12);		//DISPLAY update 	
	delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}

void EPD_WhiteScreen_ALL(const unsigned char *datas)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)	  
    {	
	    EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)	     
	  {
	    EPD_W21_WriteDATA(datas[i]);  //Transfer the actual displayed data
	  }
    EPD_Update();	 

}
void EPD_WhiteScreen_White(void)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<15000;i++)	  
    {	
	  EPD_W21_WriteDATA(0xFF); 
    }
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<15000;i++)	     
	  {
	  EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
	  }
	 //update
    EPD_Update();
}


////////////////////////////////Other newly added functions////////////////////////////////////////////
//Display rotation 180 degrees initialization
void EPD_Init_180(void)
{	
		EPD_W21_RST_0;		// Module reset
		delay_xms(10);//At least 10ms delay 
		EPD_W21_RST_1;
		delay_xms(10);//At least 10ms delay 
	  
    lcd_chkstatus(); 

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();//waiting for the electronic paper IC to release the idle signal		
		
		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x13);		//LUT from OTP£¬KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f
		
		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (EPD_WIDTH/256);
		EPD_W21_WriteDATA (EPD_WIDTH%256);    	 
		EPD_W21_WriteDATA (EPD_HEIGHT/256);
		EPD_W21_WriteDATA (EPD_HEIGHT%256); 

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

}

//GUI display
void EPD_Display(unsigned char *Image)
{
   unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)	  
    {	
	    EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)	     
	  {
	    EPD_W21_WriteDATA(Image[i]);  //Transfer the actual displayed data
	  }
    EPD_Update();	  
}

/***********************************************************
						end file
***********************************************************/

