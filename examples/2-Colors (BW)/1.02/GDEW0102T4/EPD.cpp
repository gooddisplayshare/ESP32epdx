#include <EPD_SPI.h>
#include "EPD.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
   delay(xms);
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
unsigned char oldData[2024];
unsigned char oldDataP[256];
unsigned char oldDataA[256];
unsigned char oldDataB[256];
unsigned char oldDataC[256];
unsigned char oldDataD[256];
unsigned char oldDataE[256];
unsigned char partFlag=1;

void lcd_chkstatus(void)
{
  while(isEPD_W21_BUSY==0);
                   
}
//UC8175
void EPD_Init(void)
{ 
    EPD_W21_RST_0;    // Module reset
    delay(10);//At least 10ms delay 
    EPD_W21_RST_1;
    delay(10);//At least 10ms delay 
    lcd_chkstatus();

    EPD_W21_WriteCMD(0x00);      //panel setting
    EPD_W21_WriteDATA(0x5f);     //LUT from OTP  

    EPD_W21_WriteCMD(0x2A); //IC hidden instructions    
    EPD_W21_WriteDATA(0x00); 
    EPD_W21_WriteDATA(0x00);  

    EPD_W21_WriteCMD(0x04);  //Power on
    lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
  
    EPD_W21_WriteCMD(0X50);     //VCOM AND DATA INTERVAL SETTING      
    EPD_W21_WriteDATA(0x97);    //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}


const unsigned char lut_w[] =
{
0x60  ,0x01 ,0x01 ,0x00 ,0x00 ,0x01 ,
0x80  ,0x0f ,0x00 ,0x00 ,0x00 ,0x01 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,

};  
const unsigned char lut_b[] =
{
0x90  ,0x01 ,0x01 ,0x00 ,0x00 ,0x01 ,
0x40  ,0x0f ,0x00 ,0x00 ,0x00 ,0x01 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
0x00  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,

};
void Part_lut_bw(void)
{
  unsigned int count;
  EPD_W21_WriteCMD(0x23);
  for(count=0;count<42;count++)      
  {EPD_W21_WriteDATA(lut_w[count]);}    
  
  EPD_W21_WriteCMD(0x24);
  for(count=0;count<42;count++)      
  {EPD_W21_WriteDATA(lut_b[count]);}          
}

void EPD_Init_Part(void)
{
  EPD_W21_RST_0;    // Module reset
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10);//At least 10ms delay 
  lcd_chkstatus();

  EPD_W21_WriteCMD(0xD2);     
  EPD_W21_WriteDATA(0x3F);
         
  EPD_W21_WriteCMD(0x00);       
  EPD_W21_WriteDATA (0x6F);  //from outside

  EPD_W21_WriteCMD(0x01);     //power setting
  EPD_W21_WriteDATA (0x03);     
  EPD_W21_WriteDATA (0x00);
  EPD_W21_WriteDATA (0x26);   
  EPD_W21_WriteDATA (0x26); 

  EPD_W21_WriteCMD(0x06);       
  EPD_W21_WriteDATA(0x3F);

  EPD_W21_WriteCMD(0x2A);     
  EPD_W21_WriteDATA(0x00); 
  EPD_W21_WriteDATA(0x00); 

  EPD_W21_WriteCMD(0x30);
  EPD_W21_WriteDATA(0x13); //50Hz
    
  EPD_W21_WriteCMD(0x50);     
  EPD_W21_WriteDATA(0xF2);

  EPD_W21_WriteCMD(0x60);     
  EPD_W21_WriteDATA(0x22);

  EPD_W21_WriteCMD(0x82);     
  EPD_W21_WriteDATA(0x12);//-0.1v

  EPD_W21_WriteCMD(0xe3);     
  EPD_W21_WriteDATA(0x33);

  Part_lut_bw();  

  EPD_W21_WriteCMD(0x04);         //power on
  lcd_chkstatus();
  
}
  
void EPD_DeepSleep(void)
{
    EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING     
    EPD_W21_WriteDATA(0xf7); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57    WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7  

    EPD_W21_WriteCMD(0X02);   //power off
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
    delay(100);
    EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);
}
//Full screen update function
void EPD_Update(void)
{   
  //update
  EPD_W21_WriteCMD(0x12);   //DISPLAY update   
  delay(1);              //!!!The delay here is necessary, 200uS at least!!!     
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}


void EPD_WhiteScreen_ALL(const unsigned char *datas)
{
    unsigned int i;
    //Write Data
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<EPD_ARRAY;i++)    
    { 
      EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
    } 
    EPD_W21_WriteCMD(0x13);        //Transfer new data
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
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<EPD_ARRAY;i++)    
    { 
      EPD_W21_WriteDATA(0xFF); 
    }
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<EPD_ARRAY;i++)       
    {
      EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
      oldData[i]=0xFF; 
    }
    EPD_Update();     
}

//Partial update of background display, this function is necessary, please do not delete it!!!
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
  unsigned int i; 
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(0xFF);
   }
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
      oldData[i]=datas[i]; 
   }   
    EPD_Update();     
}

void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
    unsigned int i,x_end,y_end;
    x_start=x_start-x_start%8;
    x_end=x_start+PART_LINE-1; 
    y_end=y_start+PART_COLUMN-1;
  
    EPD_Init_Part();  
    EPD_W21_WriteCMD(0x91);   //This command makes the display enter partial mode
    EPD_W21_WriteCMD(0x90);   //resolution setting
    EPD_W21_WriteDATA (x_start);   //x-start     
    EPD_W21_WriteDATA (x_end);   //x-end  
    EPD_W21_WriteDATA (y_start);   //y-start      
    EPD_W21_WriteDATA (y_end);  //y-end
    EPD_W21_WriteDATA (0x00); 
  
    EPD_W21_WriteCMD(0x10);    //writes Old data to SRAM
    if(partFlag==1) 
    {
      partFlag=0;
      for(i=0;i<PART_COLUMN*PART_LINE/8;i++)       
         EPD_W21_WriteDATA(0xFF); 
    }
    else
    {
      for(i=0;i<PART_COLUMN*PART_LINE/8;i++)       
        EPD_W21_WriteDATA(oldData[i]);   
    }
     EPD_W21_WriteCMD(0x13);   //writes New data to SRAM.
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)    
    {   
       EPD_W21_WriteDATA(datas[i]); 
       oldData[i]=datas[i];     
    } 
    EPD_Update();   
}

//Full screen partial update display
void EPD_Dis_PartAll(const unsigned char * datas)
{
    unsigned int i;
    EPD_Init_Part();
    //Write Data
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<EPD_ARRAY;i++)    
    { 
       EPD_W21_WriteDATA(oldData[i]);  //Transfer the actual displayed data
    } 
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<EPD_ARRAY;i++)       
    {
      EPD_W21_WriteDATA(datas[i]);  //Transfer the actual displayed data
       oldData[i]=datas[i]; 
    }  
      
    EPD_Update();      

}
//Partial update write address and data
void EPD_Dis_Part_RAM(unsigned int x_start,unsigned int y_start,
                        const unsigned char * datas_A,const unsigned char * datas_B,
                        const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
    unsigned int i,x_end,y_end;
    x_start=x_start-x_start%8;
    x_end=x_start+PART_LINE-1; 
    y_end=y_start+PART_COLUMN*num-1;
  
    EPD_Init_Part();  
    EPD_W21_WriteCMD(0x91);   //This command makes the display enter partial mode
    EPD_W21_WriteCMD(0x90);   //resolution setting
    EPD_W21_WriteDATA (x_start);   //x-start     
    EPD_W21_WriteDATA (x_end);   //x-end  
    EPD_W21_WriteDATA (y_start);   //y-start      
    EPD_W21_WriteDATA (y_end);  //y-end
    EPD_W21_WriteDATA (0x00); 
  
    EPD_W21_WriteCMD(0x10);    //writes Old data to SRAM
    if(partFlag==1) 
    {
      partFlag=0;
      for(i=0;i<PART_COLUMN*PART_LINE*num/8;i++)       
         EPD_W21_WriteDATA(0xFF); 
    }
    else
    {
      for(i=0;i<PART_COLUMN*PART_LINE/8;i++)       
        EPD_W21_WriteDATA(oldDataA[i]);              
      for(i=0;i<PART_COLUMN*PART_LINE/8;i++)       
        EPD_W21_WriteDATA(oldDataB[i]);  
      for(i=0;i<PART_COLUMN*PART_LINE/8;i++)       
        EPD_W21_WriteDATA(oldDataC[i]);              
      for(i=0;i<PART_COLUMN*PART_LINE/8;i++)       
        EPD_W21_WriteDATA(oldDataD[i]);
      for(i=0;i<PART_COLUMN*PART_LINE/8;i++)       
        EPD_W21_WriteDATA(oldDataE[i]);                    
    } 
    
    EPD_W21_WriteCMD(0x13);     //writes New data to SRAM.  
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)  
    {     
      EPD_W21_WriteDATA(datas_A[i]);  
      oldDataA[i]=datas_A[i];
    }         
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)  
    {     
      EPD_W21_WriteDATA(datas_B[i]);  
      oldDataB[i]=datas_B[i];
    } 
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)  
    {     
      EPD_W21_WriteDATA(datas_C[i]);  
      oldDataC[i]=datas_C[i];
    } 
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)  
    {     
      EPD_W21_WriteDATA(datas_D[i]);  
      oldDataD[i]=datas_D[i];
    } 
    for(i=0;i<PART_COLUMN*PART_LINE/8;i++)  
    {     
      EPD_W21_WriteDATA(datas_E[i]);  
      oldDataE[i]=datas_E[i]; 
    } 
    EPD_Update();
    
}
//Clock display
void EPD_Dis_Part_Time(unsigned int x_start,unsigned int y_start,
                        const unsigned char * datas_A,const unsigned char * datas_B,
                        const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  EPD_Dis_Part_RAM(x_start,y_start,datas_A,datas_B,datas_C,datas_D,datas_E,num,PART_COLUMN,PART_LINE);

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

    EPD_W21_WriteCMD(0x00);      //panel setting
    EPD_W21_WriteDATA(0x53);     //180 mirror

    EPD_W21_WriteCMD(0x2A); //IC hidden instructions    
    EPD_W21_WriteDATA(0x00); 
    EPD_W21_WriteDATA(0x00);  

    EPD_W21_WriteCMD(0x04);  //Power on
    lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
  
    EPD_W21_WriteCMD(0X50);     //VCOM AND DATA INTERVAL SETTING      
    EPD_W21_WriteDATA(0x97);    //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

}
//GUI
void EPD_Display(unsigned char *Image)
{
    unsigned int i;
    //Write Data
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<EPD_ARRAY;i++)    
    { 
      EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
    } 
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<EPD_ARRAY;i++)       
    {
      EPD_W21_WriteDATA(Image[i]);  //Transfer the actual displayed data
    }
    EPD_Update();     


}

/***********************************************************
            end file
***********************************************************/

