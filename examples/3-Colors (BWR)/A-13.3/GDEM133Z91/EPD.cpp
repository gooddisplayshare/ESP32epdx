#include <EPD_SPI.h>
#include "EPD.h"

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
  {  //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
  }  
}
//SSD1677
void EPD_HW_Init(void)
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
  EPD_W21_WriteDATA(0x00);

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
void EPD_Update(void)
{   
  EPD_W21_WriteCMD(0x22); //Display Update Control
  EPD_W21_WriteDATA(0xF7);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}
void EPD_DeepSleep(void)
{
  EPD_W21_WriteCMD(0x10); //enter deep sleep
  EPD_W21_WriteDATA(0x01); 
  delay(100);
}

void EPD_WhiteScreen_ALL(const unsigned char* datasBW,const unsigned char* datasRW)
{
   unsigned int i;  
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datasBW[i]);
   }
  EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(~datasRW[i]);
   }
  //update
  EPD_Update();  
}
void EPD_WhiteScreen_White(void)
{
   unsigned int i;  
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(0xff);
   }
  EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(0x00);
   }
  //update
  EPD_Update();      
}

//GUI display
//SSD1677
void EPD_HW_Init_GUI(void)
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
  EPD_W21_WriteDATA(0x01); //mirror

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
void EPD_Display_BW(unsigned char* datasBW)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datasBW[i]);
   }
}
void EPD_Display_RW(unsigned char* datasRW)
{
   unsigned int i;	
  EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(~datasRW[i]);
   }
	//update
  EPD_Update();	 
}
/***********************************************************
            end file
***********************************************************/

