#include <EPD_SPI.h>
#include "EPD.h"


unsigned char PartImage[1000];//Define Partial canvas space  
unsigned char partFlag=1;
unsigned char partFlag2=1;


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
//UC8179
void EPD_Init(void)
{ 
    EPD_W21_RST_0;    // Module reset
    delay(10);//At least 10ms delay 
    EPD_W21_RST_1;
    delay(10);//At least 10ms delay 
    lcd_chkstatus();
  
    EPD_W21_WriteCMD(0x04); //POWER ON 
    lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

}


  
void EPD_DeepSleep(void)
{
    EPD_W21_WriteCMD(0X02);   //power off
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
    delay(100);    //!!!The delay here is necessary,100mS at least!!!     
    EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);
}
//Full screen refresh update function
void EPD_Update(void)
{   
    //Refresh
    EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
    delay(1);              //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}


void EPD_WhiteScreen_ALL(const unsigned char* datasBW,const unsigned char* datasRW)
{
    unsigned int i;
    //Write Data
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<EPD_ARRAY;i++)    
    { 
      EPD_W21_WriteDATA(datasBW[i]);  //Transfer the actual displayed data
    } 
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<EPD_ARRAY;i++)       
    {
      EPD_W21_WriteDATA(datasRW[i]);  //Transfer the actual displayed data
    }
    EPD_Update();     

}
void EPD_WhiteScreen_White(void)
{
    unsigned int i;
    //Write Data
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<EPD_ARRAY;i++)    
    { 
      EPD_W21_WriteDATA(0x00); 
    }
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<EPD_ARRAY;i++)       
    {
      EPD_W21_WriteDATA(0x00);  //Transfer the actual displayed data
    }
    EPD_Update();     
}


////////////////////////////////Other newly added functions////////////////////////////////////////////
//Display rotation 180 degrees initialization
void EPD_Init_180(void)
{ 
    EPD_W21_RST_0;    // Module reset
    delay(10);//At least 10ms delay 
    EPD_W21_RST_1;
    delay(10);//At least 10ms delay 
    lcd_chkstatus();

    EPD_W21_WriteCMD(0x04); //POWER ON
    lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
  
    EPD_W21_WriteCMD(0X00);     //PANNEL SETTING
    EPD_W21_WriteDATA(0x03);   //KW-3f   KWR-2F BWROTP 0f BWOTP 1f
}


//GUI display
void EPD_Display_BW(unsigned char* datasBW)
{
  unsigned int i;	
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(~datasBW[i]);
   }			 
}
void EPD_Display_RW(unsigned char* datasRW)
{
  unsigned int i;	
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(~datasRW[i]);
   }	 
   EPD_Update();			 
}

/***********************************************************
            end file
***********************************************************/

