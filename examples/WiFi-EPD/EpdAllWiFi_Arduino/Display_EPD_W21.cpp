#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
  delay(xms);
}


////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
//Busy function
void Epaper_READBUSY(void)
{ 
  while(1)
  {	 //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
  }  
}
void lcd_chkstatus(void)
{ 
  while(1)
  {	 //=0 BUSY
     if(isEPD_W21_BUSY==1) break;
  } 	
}
void EPD_DeepSleep_UC(void)
{
	EPD_W21_WriteCMD(0X02);  	//power off
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	EPD_W21_WriteCMD(0X07);  	//deep sleep
	EPD_W21_WriteDATA(0xA5); 
	
}
//Deep sleep function
void EPD_DeepSleep(void)
{  	
  EPD_W21_WriteCMD(0x10); //Enter deep sleep
  EPD_W21_WriteDATA(0x01); 
  delay_xms(100);
}
void EPD_DeepSleep_BWRY(void)
{  	
	EPD_W21_WriteCMD(0X02);  	//power off
	EPD_W21_WriteDATA(0x00);
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
	EPD_W21_WriteCMD(0X07);  	//deep sleep
	EPD_W21_WriteDATA(0xA5);
}







//Full screen update initialization
void EPD_Init750_BW(void)
{
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 

  EPD_W21_WriteCMD(0x01);     //POWER SETTING
  EPD_W21_WriteDATA (0x07);
  EPD_W21_WriteDATA (0x07);    //VGH=20V,VGL=-20V
  EPD_W21_WriteDATA (0x3f);   //VDH=15V
  EPD_W21_WriteDATA (0x3f);   //VDL=-15V

  //Enhanced display drive(Add 0x06 command)
  EPD_W21_WriteCMD(0x06);     //Booster Soft Start 
  EPD_W21_WriteDATA (0x17);
  EPD_W21_WriteDATA (0x17);   
  EPD_W21_WriteDATA (0x28);   
  EPD_W21_WriteDATA (0x17); 

  EPD_W21_WriteCMD(0x04); //POWER ON
  delay(100);  
  lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

  EPD_W21_WriteCMD(0X00);     //PANNEL SETTING
  EPD_W21_WriteDATA(0x1F);   //KW-3f   KWR-2F BWROTP 0f BWOTP 1f

  EPD_W21_WriteCMD(0x61);         //tres      
  EPD_W21_WriteDATA (0x03);   //source 800
  EPD_W21_WriteDATA (0x20);
  EPD_W21_WriteDATA (0x01);   //gate 480
  EPD_W21_WriteDATA (0xE0);  

  EPD_W21_WriteCMD(0X15);   
  EPD_W21_WriteDATA(0x00);    

  EPD_W21_WriteCMD(0X50);     //VCOM AND DATA INTERVAL SETTING
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x07);

  EPD_W21_WriteCMD(0X60);     //TCON SETTING
  EPD_W21_WriteDATA(0x22);
  
}
void EPD_Init750_BWR(void)
{
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 

  EPD_W21_WriteCMD(0x01);     //POWER SETTING
  EPD_W21_WriteDATA (0x07);
  EPD_W21_WriteDATA (0x07);    //VGH=20V,VGL=-20V
  EPD_W21_WriteDATA (0x3f);   //VDH=15V
  EPD_W21_WriteDATA (0x3f);   //VDL=-15V

  //Enhanced display drive(Add 0x06 command)
  EPD_W21_WriteCMD(0x06);     //Booster Soft Start 
  EPD_W21_WriteDATA (0x17);
  EPD_W21_WriteDATA (0x17);   
  EPD_W21_WriteDATA (0x28);   
  EPD_W21_WriteDATA (0x17); 

  EPD_W21_WriteCMD(0x04); //POWER ON
  delay(100);  
  lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

  EPD_W21_WriteCMD(0X00);     //PANNEL SETTING
  EPD_W21_WriteDATA(0x0F);   //KW-3f   KWR-2F BWROTP 0f BWOTP 1f

  EPD_W21_WriteCMD(0x61);         //tres      
  EPD_W21_WriteDATA (0x03);   //source 800
  EPD_W21_WriteDATA (0x20);
  EPD_W21_WriteDATA (0x01);   //gate 480
  EPD_W21_WriteDATA (0xE0);  

  EPD_W21_WriteCMD(0X15);   
  EPD_W21_WriteDATA(0x00);    

  EPD_W21_WriteCMD(0X50);     //VCOM AND DATA INTERVAL SETTING
  EPD_W21_WriteDATA(0x11);
  EPD_W21_WriteDATA(0x07);

  EPD_W21_WriteCMD(0X60);     //TCON SETTING
  EPD_W21_WriteDATA(0x22);
  
}
void EPD_Init750_BWRY(void)
{
  #define EPD_WIDTH   800 
  #define EPD_HEIGHT  480
  delay(100);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10);//At least 10ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
		
  EPD_W21_WriteCMD(0x00);	//0x00
	EPD_W21_WriteDATA(0x0F);	
	EPD_W21_WriteDATA(0x29);	

	EPD_W21_WriteCMD(0x06);	//0x06
	EPD_W21_WriteDATA(0x0F);	
	EPD_W21_WriteDATA(0x8B);	
	EPD_W21_WriteDATA(0x93);	
	EPD_W21_WriteDATA(0xa1);

	
	EPD_W21_WriteCMD(0x41);	//0x41
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x50);	//0x50
	EPD_W21_WriteDATA(0x37);	

	EPD_W21_WriteCMD(0x60);	//0x60
	EPD_W21_WriteDATA(0x02);	
	EPD_W21_WriteDATA(0x02);	

	EPD_W21_WriteCMD(0x61);//0x61	
	EPD_W21_WriteDATA(EPD_WIDTH/256);	
	EPD_W21_WriteDATA(EPD_WIDTH%256);	
	EPD_W21_WriteDATA(EPD_HEIGHT/256);	
	EPD_W21_WriteDATA(EPD_HEIGHT%256);	

	EPD_W21_WriteCMD(0x62);
	EPD_W21_WriteDATA(0x98); 
	EPD_W21_WriteDATA(0x98);
	EPD_W21_WriteDATA(0x98); 
	EPD_W21_WriteDATA(0x75);
	EPD_W21_WriteDATA(0xCA); 
	EPD_W21_WriteDATA(0xB2);	
	EPD_W21_WriteDATA(0x98); 
	EPD_W21_WriteDATA(0x7E); 

	EPD_W21_WriteCMD(0x65);	//0x65
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	
	EPD_W21_WriteCMD(0xE7);	//0xE7
	EPD_W21_WriteDATA(0x1C);	

	EPD_W21_WriteCMD(0xE3);	//0xE3
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0xE9);	
	EPD_W21_WriteDATA(0x01);

  EPD_W21_WriteCMD(0x30);// frame go with waveform
  EPD_W21_WriteDATA(0x08); 		
	
	
  EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
}

             
/*****************13.3寸********************************/
//SSD1677
void EPD_HW_Init1330_BW(void)
{    
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 

  EPD_W21_WriteCMD(0x12);       //SWRESET
  Epaper_READBUSY();        //waiting for the electronic paper IC to release the idle signal

  EPD_W21_WriteCMD(0x0C);  // Soft start setting
  EPD_W21_WriteDATA(0xAE);
  EPD_W21_WriteDATA(0xC7);
  EPD_W21_WriteDATA(0xC3);
  EPD_W21_WriteDATA(0xC0);
  EPD_W21_WriteDATA(0x80);    

  EPD_W21_WriteCMD(0x01);  // Set MUX as 527
  EPD_W21_WriteDATA(0xA7);
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x00);//Cancel mirror operation

  EPD_W21_WriteCMD(0x11);  // Data entry mode
  EPD_W21_WriteDATA(0x01);
  
  EPD_W21_WriteCMD(0x44);
  EPD_W21_WriteDATA(0x00); // RAM x address start at 0
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0xBF); // RAM x address end at 36Fh -> 879
  EPD_W21_WriteDATA(0x03);
  EPD_W21_WriteCMD(0x45);
  EPD_W21_WriteDATA(0xA7); // RAM y address start at 20Fh;
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x00); // RAM y address end at 00h;
  EPD_W21_WriteDATA(0x00);

  EPD_W21_WriteCMD(0x3C); // VBD
  EPD_W21_WriteDATA(0x01); // LUT1, for white

  EPD_W21_WriteCMD(0x18);
  EPD_W21_WriteDATA(0X80);

  EPD_W21_WriteCMD(0x4E); 
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteCMD(0x4F); 
  EPD_W21_WriteDATA(0xA7);
  EPD_W21_WriteDATA(0x02);
  
}
void EPD_Init1330_BWRY(void)
{
  #define EPD_WIDTH   960 
  #define EPD_HEIGHT  680 
  delay(100);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10);//At least 10ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
		
  EPD_W21_WriteCMD(0x00);	//0x00
	EPD_W21_WriteDATA(0x2F);	
	EPD_W21_WriteDATA(0x29);	

  EPD_W21_WriteCMD(0x01);	//0x01
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x19);	//RED 6.2
  EPD_W21_WriteDATA(0x78);	//WHITE 6.0	*****************************************
  EPD_W21_WriteDATA(0x28);	
  EPD_W21_WriteDATA(0x19);	//RED	
	
	
	EPD_W21_WriteCMD(0x03);	//0x03
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x06);	//0x06
	EPD_W21_WriteDATA(0x0F);	
	EPD_W21_WriteDATA(0x98);	
	EPD_W21_WriteDATA(0xA5);	
	EPD_W21_WriteDATA(0xC3);
	
  EPD_W21_WriteCMD(0x30);// frame go with waveform
  EPD_W21_WriteDATA(0x08);	
	
	EPD_W21_WriteCMD(0x41);	//0x41
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x50);	//0x50
	EPD_W21_WriteDATA(0x37);	

	EPD_W21_WriteCMD(0x60);	//0x60
	EPD_W21_WriteDATA(0x04);	
	EPD_W21_WriteDATA(0x02);	

	EPD_W21_WriteCMD(0x61);//0x61	
	EPD_W21_WriteDATA(EPD_WIDTH/256);	
	EPD_W21_WriteDATA(EPD_WIDTH%256);	
	EPD_W21_WriteDATA(EPD_HEIGHT/256);	
	EPD_W21_WriteDATA(EPD_HEIGHT%256);	

	EPD_W21_WriteCMD(0x65);	//0x65
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0xE7);	//0xE7
	EPD_W21_WriteDATA(0x16);	

	EPD_W21_WriteCMD(0xE3);	//0xE3
	EPD_W21_WriteDATA(0x65);	

	EPD_W21_WriteCMD(0xE0);	
	EPD_W21_WriteDATA(0x00);
	
	EPD_W21_WriteCMD(0xE9);	
	EPD_W21_WriteDATA(0x01);

 
	EPD_W21_WriteCMD(0x62);
	EPD_W21_WriteDATA(0x7D); 
  EPD_W21_WriteDATA(0x7D);
  EPD_W21_WriteDATA(0x7D); 
  EPD_W21_WriteDATA(0x60);
  EPD_W21_WriteDATA(0xA7); 
  EPD_W21_WriteDATA(0x93);	
	EPD_W21_WriteDATA(0x7D); 
	EPD_W21_WriteDATA(0x68); 
	
  EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
}

















////////////////////////////////Other newly added functions////////////////////////////////////////////
//Display rotation 180 degrees initialization
void EPD_Init_180(void)
{
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 

  EPD_W21_WriteCMD(0x01);     //POWER SETTING
  EPD_W21_WriteDATA (0x07);
  EPD_W21_WriteDATA (0x07);    //VGH=20V,VGL=-20V
  EPD_W21_WriteDATA (0x3f);   //VDH=15V
  EPD_W21_WriteDATA (0x3f);   //VDL=-15V

  //Enhanced display drive(Add 0x06 command)
  EPD_W21_WriteCMD(0x06);     //Booster Soft Start 
  EPD_W21_WriteDATA (0x17);
  EPD_W21_WriteDATA (0x17);   
  EPD_W21_WriteDATA (0x28);   
  EPD_W21_WriteDATA (0x17); 

  EPD_W21_WriteCMD(0x04); //POWER ON
  delay(100);  
  lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

  EPD_W21_WriteCMD(0X00);     //PANNEL SETTING
  EPD_W21_WriteDATA(0x13);   //KW-3f   KWR-2F BWROTP 0f BWOTP 1f

  EPD_W21_WriteCMD(0x61);         //tres      
  EPD_W21_WriteDATA (0x03);   //source 800
  EPD_W21_WriteDATA (0x20);
  EPD_W21_WriteDATA (0x01);   //gate 480
  EPD_W21_WriteDATA (0xE0);  

  EPD_W21_WriteCMD(0X15);   
  EPD_W21_WriteDATA(0x00);    

  EPD_W21_WriteCMD(0X50);     //VCOM AND DATA INTERVAL SETTING
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x07);

  EPD_W21_WriteCMD(0X60);     //TCON SETTING
  EPD_W21_WriteDATA(0x22);
}

//Full screen refresh display function
void EPD_WhiteScreen_GUI(const unsigned char* datasBW)
{
   unsigned int i;  
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(0x00);
   }
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(~datasBW[i]);
   }  
    EPD_Update_GUI();	    

}

void EPD_WhiteScreen_GUI_Wrong(const unsigned char* datasBW)
{
   unsigned int i;  
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(0x00);
   }
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datasBW[i]);
   }  
    EPD_Update_GUI();	    

}

















/*******************************小尺寸电子纸****************************************************/
void EPD_HW_Init_097(void)
{
  #define EPD_WIDTH   88
  #define EPD_HEIGHT  184
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);   

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	

	EPD_W21_WriteCMD(0x21); //  Display update control
	EPD_W21_WriteDATA(0x00);		
  EPD_W21_WriteDATA(0x80);	
	
  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
void EPD_HW_Init_153(void)
{
  #define EPD_WIDTH   152
  #define EPD_HEIGHT  152
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);   

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	

  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
void EPD_HW_Init_154(void)
{
  #define EPD_WIDTH   200
  #define EPD_HEIGHT  200
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);   

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	

  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
void EPD_HW_Init_213(void)
{
  #define EPD_WIDTH   128
  #define EPD_HEIGHT  250
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);   

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	

	EPD_W21_WriteCMD(0x21); //  Display update control
	EPD_W21_WriteDATA(0x00);		
  EPD_W21_WriteDATA(0x80);	
	
  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
void EPD_HW_Init_266(void)
{
  #define EPD_WIDTH   152
  #define EPD_HEIGHT  296
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);   

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	

	EPD_W21_WriteCMD(0x21); //  Display update control
	EPD_W21_WriteDATA(0x00);		
  EPD_W21_WriteDATA(0x80);	
	
  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
void EPD_HW_Init_267(void)
{
#define EPD_WIDTH   184 
#define EPD_HEIGHT  360
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);    

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x01);	

  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
void EPD_HW_Init_270(void)
{
  #define EPD_WIDTH   176
  #define EPD_HEIGHT  264
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
}
//Full screen update initialization
void EPD_HW_Init_290(void)
{
  #define EPD_WIDTH   128
  #define EPD_HEIGHT  296
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);   

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	

	EPD_W21_WriteCMD(0x21); //  Display update control
	EPD_W21_WriteDATA(0x00);		
  EPD_W21_WriteDATA(0x80);	
	
  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
void EPD_HW_Init_291(void)
{
#define EPD_WIDTH   168 
#define EPD_HEIGHT  384
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
	
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);    

	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	

  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}
//Full screen update initialization
void EPD_HW_Init_370(void)
{
  #define EPD_WIDTH   240
  #define EPD_HEIGHT  416
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	
  EPD_W21_WriteCMD(0x04);  //Power on
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

	//EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING			
	//EPD_W21_WriteDATA(0x97); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7	
  
}

void EPD_HW_Init_420(unsigned char mode) //0--bw   1--rw
{
  
#define EPD_WIDTH   400
#define EPD_HEIGHT  300
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
		
	EPD_W21_WriteCMD(0x01); //Driver output control      
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
  if(mode==0)
  {
	EPD_W21_WriteCMD(0x21); //  Display update control
	EPD_W21_WriteDATA(0x40);		
  EPD_W21_WriteDATA(0x00);		
  }
	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x05);	
	
	EPD_W21_WriteCMD(0x11); //data entry mode       
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(EPD_WIDTH/8-1);   
	EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00); 

	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
	EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);   
	EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  Epaper_READBUSY();
	
}




/********BWRY*************************************/
void EPD_HW_Init_BWRY_097(void)
{
  
#define EPD_WIDTH   88
#define EPD_HEIGHT  184
  delay_xms(100);//At least 100ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(50);//At least 50ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
	lcd_chkstatus();
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);

  EPD_W21_WriteCMD(0x00);	//PSR
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0x01);	//PWRR
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(0x03);	//POFS
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x44);
  
  EPD_W21_WriteCMD(0x06);	//BTST_P
	EPD_W21_WriteDATA(0x0F);
	EPD_W21_WriteDATA(0x0A);
	EPD_W21_WriteDATA(0x2F);
	EPD_W21_WriteDATA(0x25);
	EPD_W21_WriteDATA(0x22);
	EPD_W21_WriteDATA(0x2E);
	EPD_W21_WriteDATA(0x21);

  EPD_W21_WriteCMD(0x50);	//CDI
  EPD_W21_WriteDATA(0x37);  
  
  EPD_W21_WriteCMD(0x61); //TRES
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	
  
  EPD_W21_WriteCMD(0xE3);
  EPD_W21_WriteDATA(0x22);
	
  EPD_W21_WriteCMD(0xB6);
  EPD_W21_WriteDATA(0x6F);
  
  EPD_W21_WriteCMD(0xB4);
  EPD_W21_WriteDATA(0xD0);

  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}
void EPD_HW_Init_BWRY_153(void)
{
  
#define EPD_WIDTH   152
#define EPD_HEIGHT  152
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(50);//At least 50ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
	lcd_chkstatus();
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);

  EPD_W21_WriteCMD(0x00);	//PSR
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0X06); //BTST_P
  EPD_W21_WriteDATA(0x0D);  //47uH
  EPD_W21_WriteDATA(0x12);
  EPD_W21_WriteDATA(0x30);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x19);
  EPD_W21_WriteDATA(0x2A);
  EPD_W21_WriteDATA(0x22);

  EPD_W21_WriteCMD(0x50);	//CDI
  EPD_W21_WriteDATA(0x37);

  EPD_W21_WriteCMD(0x61); //0x61
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	

  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();    
}
void EPD_HW_Init_BWRY_154(void)
{
  
#define EPD_WIDTH   200
#define EPD_HEIGHT  200
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(50);//At least 50ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
	lcd_chkstatus();
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);

  EPD_W21_WriteCMD(0x00);	//PSR
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0X06); //BTST_P
  EPD_W21_WriteDATA(0x0D);  //47uH
  EPD_W21_WriteDATA(0x12);
  EPD_W21_WriteDATA(0x30);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x19);
  EPD_W21_WriteDATA(0x2A);
  EPD_W21_WriteDATA(0x22);

  EPD_W21_WriteCMD(0x50);	//CDI
  EPD_W21_WriteDATA(0x37);

  EPD_W21_WriteCMD(0x61); //0x61
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	

  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}
void EPD_HW_Init_BWRY_213(void)
{
  
#define EPD_WIDTH   128
#define EPD_HEIGHT  250
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);
   
  EPD_W21_WriteCMD(0x00);	//0x00
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0x01);	//0x01
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(0x03);	//0x03
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x44);
  
  EPD_W21_WriteCMD(0x06);	//0x06 
  EPD_W21_WriteDATA(0x0F);	
  EPD_W21_WriteDATA(0x0A);	
  EPD_W21_WriteDATA(0x2F);	
  EPD_W21_WriteDATA(0x25);	
  EPD_W21_WriteDATA(0x22);	
  EPD_W21_WriteDATA(0x2E);	
  EPD_W21_WriteDATA(0x21);	
	
  EPD_W21_WriteCMD(0x41);	//TSE
  EPD_W21_WriteDATA(0x00);	

  EPD_W21_WriteCMD(0x50);	//0x50
  EPD_W21_WriteDATA(0x37);
  
  EPD_W21_WriteCMD(0x60);	//0x60
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x02);
  
  EPD_W21_WriteCMD(0x61); //0x61
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	

  EPD_W21_WriteCMD(0x65);	//GSST
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	

  EPD_W21_WriteCMD(0xE7);
  EPD_W21_WriteDATA(0x1C);
  
  EPD_W21_WriteCMD(0xE3);	//0xE3
  EPD_W21_WriteDATA(0x22);
	 
  EPD_W21_WriteCMD(0xB4);
  EPD_W21_WriteDATA(0xD0);
  EPD_W21_WriteCMD(0xB5); 
  EPD_W21_WriteDATA(0x03);
  
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);
  
  EPD_W21_WriteCMD(0x04);
	delay_xms(500);
  lcd_chkstatus();   
}
void EPD_HW_Init_BWRY_266(void)
{
  
#define EPD_WIDTH   152
#define EPD_HEIGHT  296
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);
   
  EPD_W21_WriteCMD(0x00);	//0x00
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0x01);	//0x01
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(0x03);	//0x03
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x44);
  
  EPD_W21_WriteCMD(0x06);	//0x06 
  EPD_W21_WriteDATA(0x0F);	
  EPD_W21_WriteDATA(0x0A);	
  EPD_W21_WriteDATA(0x2F);	
  EPD_W21_WriteDATA(0x25);	
  EPD_W21_WriteDATA(0x22);	
  EPD_W21_WriteDATA(0x2E);	
  EPD_W21_WriteDATA(0x21);	
	
  EPD_W21_WriteCMD(0x41);	//TSE
  EPD_W21_WriteDATA(0x00);	

  EPD_W21_WriteCMD(0x50);	//0x50
  EPD_W21_WriteDATA(0x37);
  
  EPD_W21_WriteCMD(0x60);	//0x60
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x02);
  
  EPD_W21_WriteCMD(0x61); //0x61
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	

  EPD_W21_WriteCMD(0x65);	//GSST
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	

  EPD_W21_WriteCMD(0xE7);
  EPD_W21_WriteDATA(0x1C);
  
  EPD_W21_WriteCMD(0xE3);	//0xE3
  EPD_W21_WriteDATA(0x22);
	 
  EPD_W21_WriteCMD(0xB4);
  EPD_W21_WriteDATA(0xD0);
  EPD_W21_WriteCMD(0xB5); 
  EPD_W21_WriteDATA(0x03);
  
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);
  
  EPD_W21_WriteCMD(0x04);
	delay_xms(500);
  lcd_chkstatus();   
}
void EPD_HW_Init_BWRY_270(void)
{
  
#define EPD_WIDTH   176
#define EPD_HEIGHT  264
  delay_xms(100);//At least 100ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(50);//At least 50ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	lcd_chkstatus(); 
	
  EPD_W21_WriteCMD(0x00);	//PSR
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);
  
  EPD_W21_WriteCMD(0x06);	//BTST_P
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x8B);
  EPD_W21_WriteDATA(0x9C);
  EPD_W21_WriteDATA(0x96);

  EPD_W21_WriteCMD(0x50);	//CDI
  EPD_W21_WriteDATA(0x37);
  
  EPD_W21_WriteCMD(0x61); //0x61
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	
	
	EPD_W21_WriteCMD(0xE3);
  EPD_W21_WriteDATA(0x22); 
  
  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08); 
	
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}

void EPD_HW_Init_BWRY_290(void)
{
  
#define EPD_WIDTH   128
#define EPD_HEIGHT  296
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);
   
  EPD_W21_WriteCMD(0x00);	//0x00
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0x01);	//0x01
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(0x03);	//0x03
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x44);
  
  EPD_W21_WriteCMD(0x06);	//0x06 
  EPD_W21_WriteDATA(0x0F);	
  EPD_W21_WriteDATA(0x0A);	
  EPD_W21_WriteDATA(0x2F);	
  EPD_W21_WriteDATA(0x25);	
  EPD_W21_WriteDATA(0x22);	
  EPD_W21_WriteDATA(0x2E);	
  EPD_W21_WriteDATA(0x21);	
	
  EPD_W21_WriteCMD(0x41);	//TSE
  EPD_W21_WriteDATA(0x00);	

  EPD_W21_WriteCMD(0x50);	//0x50
  EPD_W21_WriteDATA(0x37);
  
  EPD_W21_WriteCMD(0x60);	//0x60
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x02);
  
  EPD_W21_WriteCMD(0x61); //0x61
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	

  EPD_W21_WriteCMD(0x65);	//GSST
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	
  EPD_W21_WriteDATA(0x00);	

  EPD_W21_WriteCMD(0xE7);
  EPD_W21_WriteDATA(0x1C);
  
  EPD_W21_WriteCMD(0xE3);	//0xE3
  EPD_W21_WriteDATA(0x22);
	 
  EPD_W21_WriteCMD(0xB4);
  EPD_W21_WriteDATA(0xD0);
  EPD_W21_WriteCMD(0xB5); 
  EPD_W21_WriteDATA(0x03);
  
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);
  
  EPD_W21_WriteCMD(0x04);
	delay_xms(500);
  lcd_chkstatus();   
}
void EPD_HW_Init_BWRY_267(void)
{
  
#define EPD_WIDTH   184
#define EPD_HEIGHT  360
 delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
	lcd_chkstatus();
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);

  EPD_W21_WriteCMD(0x00);	//PSR
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0x01);	//PWRR
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(0x03);	//POFS
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x44);
  
  EPD_W21_WriteCMD(0x06);	//BTST_P
  EPD_W21_WriteDATA(0x05);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x3F);
  EPD_W21_WriteDATA(0x0A);
  EPD_W21_WriteDATA(0x25);
  EPD_W21_WriteDATA(0x12);
  EPD_W21_WriteDATA(0x1A); 

  EPD_W21_WriteCMD(0x50);	//CDI
  EPD_W21_WriteDATA(0x37);
  
  EPD_W21_WriteCMD(0x60);	//TCON
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x02);
  
  EPD_W21_WriteCMD(0x61); //TRES
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L
  
  EPD_W21_WriteCMD(0xE7);
  EPD_W21_WriteDATA(0x1C);
  
  EPD_W21_WriteCMD(0xE3);	
  EPD_W21_WriteDATA(0x22);
  
  EPD_W21_WriteCMD(0xB4);
  EPD_W21_WriteDATA(0xD0);
  EPD_W21_WriteCMD(0xB5);
  EPD_W21_WriteDATA(0x03);
  
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}
void EPD_HW_Init_BWRY_291(void)
{
  
#define EPD_WIDTH   168
#define EPD_HEIGHT  384
 delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	
	lcd_chkstatus();
  EPD_W21_WriteCMD(0x4D);
  EPD_W21_WriteDATA(0x78);

  EPD_W21_WriteCMD(0x00);	//PSR
  EPD_W21_WriteDATA(0x0F);
  EPD_W21_WriteDATA(0x29);

  EPD_W21_WriteCMD(0x01);	//PWRR
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(0x03);	//POFS
  EPD_W21_WriteDATA(0x10);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x44);
  
  EPD_W21_WriteCMD(0x06);	//BTST_P
  EPD_W21_WriteDATA(0x05);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x3F);
  EPD_W21_WriteDATA(0x0A);
  EPD_W21_WriteDATA(0x25);
  EPD_W21_WriteDATA(0x12);
  EPD_W21_WriteDATA(0x1A); 

  EPD_W21_WriteCMD(0x50);	//CDI
  EPD_W21_WriteDATA(0x37);
  
  EPD_W21_WriteCMD(0x60);	//TCON
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x02);
  
  EPD_W21_WriteCMD(0x61); //TRES
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L
  
  EPD_W21_WriteCMD(0xE7);
  EPD_W21_WriteDATA(0x1C);
  
  EPD_W21_WriteCMD(0xE3);	
  EPD_W21_WriteDATA(0x22);
  
  EPD_W21_WriteCMD(0xB4);
  EPD_W21_WriteDATA(0xD0);
  EPD_W21_WriteCMD(0xB5);
  EPD_W21_WriteDATA(0x03);
  
  EPD_W21_WriteCMD(0xE9);
  EPD_W21_WriteDATA(0x01); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x08);  
	
  EPD_W21_WriteCMD(0x04);
  lcd_chkstatus();   
}
void EPD_HW_Init_BWRY_370(void)
{
  
#define EPD_WIDTH   240
#define EPD_HEIGHT  416
 	delay_xms(100);//At least 100ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(50);//At least 50ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	
	EPD_W21_WriteCMD(0x00);	//0x00
	EPD_W21_WriteDATA(0x0F);	
	EPD_W21_WriteDATA(0x29);	

	EPD_W21_WriteCMD(0x01);	//0x01
	EPD_W21_WriteDATA(0x07);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x22);		//RED 
	EPD_W21_WriteDATA(0x78);
	EPD_W21_WriteDATA(0x0A);		//WHITE
	EPD_W21_WriteDATA(0x22);		//RED 	

	EPD_W21_WriteCMD(0x03);	//0x03
	EPD_W21_WriteDATA(0x10);	
	EPD_W21_WriteDATA(0x54);	
	EPD_W21_WriteDATA(0x44);	

	EPD_W21_WriteCMD(0x06);	//0x06
	EPD_W21_WriteDATA(0xC0);	
	EPD_W21_WriteDATA(0xC0);	
	EPD_W21_WriteDATA(0xC0);	

	EPD_W21_WriteCMD(0x30);	//0x30
	EPD_W21_WriteDATA(0x08);	

	EPD_W21_WriteCMD(0x41);	//0x41
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x50);	//0x50
	EPD_W21_WriteDATA(0x37);	

	EPD_W21_WriteCMD(0x60);	//0x60
	EPD_W21_WriteDATA(0x02);	
	EPD_W21_WriteDATA(0x02);	

  EPD_W21_WriteCMD(0x61); //0x61
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	

	EPD_W21_WriteCMD(0x65);	//0x65
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteDATA(0x00);	


	EPD_W21_WriteCMD(0xE7);	//0xE7
	EPD_W21_WriteDATA(0x1C);	

	EPD_W21_WriteCMD(0xE3);	//0xE3
	EPD_W21_WriteDATA(0x22);	

	EPD_W21_WriteCMD(0xFF);	//Enter
	EPD_W21_WriteDATA(0xA5);	//Enter

	EPD_W21_WriteCMD(0xEF);	//PWM
	EPD_W21_WriteDATA(0x01);	
	EPD_W21_WriteDATA(0x1E);	
	EPD_W21_WriteDATA(0x0A);	
	EPD_W21_WriteDATA(0x1B);	
	EPD_W21_WriteDATA(0x0B);	
	EPD_W21_WriteDATA(0x17);	

	EPD_W21_WriteCMD(0xC3);	//PWM
	EPD_W21_WriteDATA(0xFD);	
	EPD_W21_WriteCMD(0xDC);	//CPCK
	EPD_W21_WriteDATA(0x01);	
	EPD_W21_WriteCMD(0xDD);	
	EPD_W21_WriteDATA(0x08);	
	EPD_W21_WriteCMD(0xDE);	
	EPD_W21_WriteDATA(0x41);	

	EPD_W21_WriteCMD(0xFD);	//VDLOS
	EPD_W21_WriteDATA(0x01);	
	EPD_W21_WriteCMD(0xE8);	
	EPD_W21_WriteDATA(0x03);	

	EPD_W21_WriteCMD(0xDA);	//DAh
	EPD_W21_WriteDATA(0x07);	

	EPD_W21_WriteCMD(0xC9);	//GDR
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0xA8);	//VDH
	EPD_W21_WriteDATA(0x0F);	

	EPD_W21_WriteCMD(0xFF);	
	EPD_W21_WriteDATA(0xE3);	//Exit

	EPD_W21_WriteCMD(0xE9);	
	EPD_W21_WriteDATA(0x01);
	
  EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

	EPD_W21_WriteCMD(0xFF);
	EPD_W21_WriteDATA(0xA5);

	EPD_W21_WriteCMD(0xEF);   
	EPD_W21_WriteDATA(0x03);
	EPD_W21_WriteDATA(0x1E);
	EPD_W21_WriteDATA(0x0A);
	EPD_W21_WriteDATA(0x1B);
	EPD_W21_WriteDATA(0x0E);
	EPD_W21_WriteDATA(0x15);

	EPD_W21_WriteCMD(0xDC); 	 
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0xDD); 	 
	EPD_W21_WriteDATA(0x08);

	EPD_W21_WriteCMD(0xDE);
	EPD_W21_WriteDATA(0x41);

	EPD_W21_WriteCMD(0xFF);
	EPD_W21_WriteDATA(0xE3);
}
//4.2////////////////////////////


void EPD_HW_Init_BWRY_420(void)
{
  #define EPD_WIDTH   400
  #define EPD_HEIGHT  300
  delay_xms(20);//At least 20ms delay 	
	EPD_W21_RST_0;		// Module reset
	delay_xms(40);//At least 40ms delay 
	EPD_W21_RST_1;
	delay_xms(50);//At least 50ms delay 
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

	EPD_W21_WriteCMD(0x4D);
	EPD_W21_WriteDATA(0x78);

	EPD_W21_WriteCMD(0x00);  //PSR
	EPD_W21_WriteDATA(0x0F);
	EPD_W21_WriteDATA(0x29);

	EPD_W21_WriteCMD(0x06);//BTST
	EPD_W21_WriteDATA(0x0d);
	EPD_W21_WriteDATA(0x12);
	EPD_W21_WriteDATA(0x24);
	EPD_W21_WriteDATA(0x25);
	EPD_W21_WriteDATA(0x12);
	EPD_W21_WriteDATA(0x29);
	EPD_W21_WriteDATA(0x10);

	EPD_W21_WriteCMD(0x30);// frame go with waveform
	EPD_W21_WriteDATA(0x08); 	

	EPD_W21_WriteCMD(0x50);//CDI
	EPD_W21_WriteDATA(0x37);  //border white

	EPD_W21_WriteCMD(0x61);//0x61	
  EPD_W21_WriteDATA(EPD_WIDTH/256);		// Source_BITS_H
  EPD_W21_WriteDATA(EPD_WIDTH%256);		// Source_BITS_L
  EPD_W21_WriteDATA(EPD_HEIGHT/256);			// Gate_BITS_H
  EPD_W21_WriteDATA(EPD_HEIGHT%256); 		// Gate_BITS_L	

	EPD_W21_WriteCMD(0xae);
	EPD_W21_WriteDATA(0xcf);

	EPD_W21_WriteCMD(0xb0);
	EPD_W21_WriteDATA(0x13);

	EPD_W21_WriteCMD(0xbd);
	EPD_W21_WriteDATA(0x07);

	EPD_W21_WriteCMD(0xbe);
	EPD_W21_WriteDATA(0xfe);

	EPD_W21_WriteCMD(0xE9);
	EPD_W21_WriteDATA(0x01);  

	EPD_W21_WriteCMD(0x04); //Power on
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}


void EPD_Update_UC(void)
{   
	//Refresh
	EPD_W21_WriteCMD(0x12);		//DISPLAY update	
	delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}

//Full screen update update function
void EPD_Update(void)
{   
  EPD_W21_WriteCMD(0x22); //Display Update Control
  EPD_W21_WriteDATA(0xF7);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}
void EPD_Update_BWRY(void)
{   
  EPD_W21_WriteCMD(0x12); //Display Update Control
	EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();   
}


void EPD_WhiteScreen_ALL_UC_BW(const unsigned char *datas,unsigned int datasize)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x10);   //write RAM for black(0)/white (1)
  for(i=0;i<datasize;i++)
   {               
     EPD_W21_WriteDATA(0x00);
   }
  EPD_W21_WriteCMD(0x13);   //write RAM for black(0)/white (1)
  for(i=4096*2;i<datasize+4096*2;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }   
   EPD_Update_UC();	 
}
void EPD_WhiteScreen_ALL_UC_RW(const unsigned char *datas,unsigned int datasize)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x10);   //write RAM for black(0)/white (1)
  for(i=4096*2;i<4096*2+datasize/2;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
  EPD_W21_WriteCMD(0x13);   //write RAM for black(0)/white (1)
  for(i=4096*2+datasize/2;i<4096*2+datasize;i++)
   {               
     EPD_W21_WriteDATA(~datas[i]);
   }   
    EPD_Update_UC();	  
}


void EPD_Update_SSD1685(void)
{   
  EPD_W21_WriteCMD(0x22); //Display Update Control
  EPD_W21_WriteDATA(0xF4);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}
void EPD_WhiteScreen_ALL_SSD1685_BW(const unsigned char *datas,unsigned int datasize)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
  for(i=4096*2;i<datasize+4096*2;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
	 EPD_W21_WriteCMD(0x26);   
	 for(i=0;i<datasize;i++)
	 {
			EPD_W21_WriteDATA(0x00);
		}   
   EPD_Update_SSD1685();	 
}


void EPD_WhiteScreen_ALL_SSD_BW(const unsigned char *datas,unsigned int datasize)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
  for(i=4096*2;i<datasize+4096*2;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
   EPD_Update();	 
}

void EPD_WhiteScreen_ALL_SSD_RW(const unsigned char *datas,unsigned int datasize)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
  for(i=4096*2;i<4096*2+datasize/2;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
  EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)
  for(i=4096*2+datasize/2;i<4096*2+datasize;i++)
   {               
     EPD_W21_WriteDATA(~datas[i]);
   }   
   EPD_Update();	 
}
void EPD_WhiteScreen_ALL_SSD_BWRY(const unsigned char *datas,unsigned int datasize)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x10);   //write RAM for black(0)/white (1)
  for(i=4096*2;i<datasize+4096*2;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
   EPD_Update_BWRY();	 
}



/***********************************************************
            end file
***********************************************************/
