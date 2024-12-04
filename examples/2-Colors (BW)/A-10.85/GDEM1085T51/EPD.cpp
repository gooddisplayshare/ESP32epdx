#include "EPD_SPI3.h" //E-paper 3-wire SPI 
#include "EPD.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
   delay(xms);
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
unsigned char partFlag=1;
void lcd_chkstatus(void)
{
  while(isEPD_W21_BUSY==0);
                   
}


void EPD_Init(void)
{	
	delay(100);//At least 10ms delay 
	EPD_W21_RST_0;		// Module reset
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10);//At least 10ms delay 
	lcd_chkstatus();
	
	EPD_W21_WriteCMD(0x4D);
	EPD_W21_WriteDATA(0x55);

	EPD_W21_WriteCMD(0xA6);
	EPD_W21_WriteDATA(0x38);

	EPD_W21_WriteCMD(0xB4);
	EPD_W21_WriteDATA(0x5D);

	EPD_W21_WriteCMD(0xB6);
	EPD_W21_WriteDATA(0x80);

	EPD_W21_WriteCMD(0xB7);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xF7);
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD2(0xAE);
	EPD_W21_WriteDATA2(0xA0);

	EPD_W21_WriteCMD(0xE0);
	EPD_W21_WriteDATA(0x01);


	EPD_W21_WriteCMD(0x00);//Panel setting	
	EPD_W21_WriteDATA(0x9F);
	EPD_W21_WriteDATA(0x0D);

	EPD_W21_WriteCMD(0x06);//boost
	EPD_W21_WriteDATA(0x57);
	EPD_W21_WriteDATA(0x24);
	EPD_W21_WriteDATA(0x28);
	EPD_W21_WriteDATA(0x32);
	EPD_W21_WriteDATA(0x08);	
	EPD_W21_WriteDATA(0x48);

	EPD_W21_WriteCMD(0x61);//resolution setting
	EPD_W21_WriteDATA(0X02);//680   1360*480
	EPD_W21_WriteDATA(0XA8);
	EPD_W21_WriteDATA(0X01);//480
	EPD_W21_WriteDATA(0XE0);

	EPD_W21_WriteCMD(0x62);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x60);
	EPD_W21_WriteDATA(0x31);

	EPD_W21_WriteCMD(0x50);//VCOM and DATA interval setting(CDI)	
	EPD_W21_WriteDATA(0x97);

	EPD_W21_WriteCMD(0xE8);  
	EPD_W21_WriteDATA(0x01); 

	EPD_W21_WriteCMD(0x04);  //power on  
	delay(200);  
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

void EPD_Init_Part(void)
{
	delay(100);//At least 100ms delay 
	EPD_W21_RST_0;		// Module reset
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10);//At least 10ms delay 
	lcd_chkstatus();

	EPD_W21_WriteCMD(0x4D);
	EPD_W21_WriteDATA(0x55);

	EPD_W21_WriteCMD(0xA6);
	EPD_W21_WriteDATA(0x38);

	EPD_W21_WriteCMD(0xB4);
	EPD_W21_WriteDATA(0x5D);

	EPD_W21_WriteCMD(0xB6);
	EPD_W21_WriteDATA(0x80);

	EPD_W21_WriteCMD(0xB7);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xF7);
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD2(0xAE);
	EPD_W21_WriteDATA2(0xA0);

	EPD_W21_WriteCMD(0xE0);
	EPD_W21_WriteDATA(0x01);

	EPD_W21_WriteCMD(0x00);//Panel setting	
	EPD_W21_WriteDATA(0x9F);
	EPD_W21_WriteDATA(0x0D);

	EPD_W21_WriteCMD(0x06);//boost
	EPD_W21_WriteDATA(0x57);
	EPD_W21_WriteDATA(0x24);
	EPD_W21_WriteDATA(0x28);
	EPD_W21_WriteDATA(0x32);
	EPD_W21_WriteDATA(0x08);	
	EPD_W21_WriteDATA(0x48);


	EPD_W21_WriteCMD(0x61);//resolution setting
	EPD_W21_WriteDATA(0X02);//680   1360*480
	EPD_W21_WriteDATA(0XA8);
	EPD_W21_WriteDATA(0X01);//480
	EPD_W21_WriteDATA(0XE0);

	EPD_W21_WriteCMD(0x62);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x82);  // VCOM DC Setting
	EPD_W21_WriteDATA(0x12);  // 1-0=11: internal power
	
	EPD_W21_WriteCMD(0x60);
	EPD_W21_WriteDATA(0x31);
	
	EPD_W21_WriteCMD(0x50);  // VCOM and DATA interval setting    
	EPD_W21_WriteDATA(0x97);
		
	EPD_W21_WriteCMD(0x50);  // VCOM and DATA interval setting    
	EPD_W21_WriteDATA(0x97);

	EPD_W21_WriteCMD(0xE0);  
	EPD_W21_WriteDATA(0x03); 
	EPD_W21_WriteCMD(0xE5);  //100du
	EPD_W21_WriteDATA(0x64); 

	EPD_W21_WriteCMD(0x04); //POWER ON
	delay(100);  
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

}
  
void EPD_DeepSleep(void)
{

  EPD_W21_WriteCMD(0x02); //power off 
  delay(100);  
  lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
    
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
    unsigned int i,j;
    //Master
    EPD_W21_WriteCMD1(0x10);         //Transfer old data
    for(i=0;i<EPD_ARRAY;i++){   
      EPD_W21_WriteDATA1(0xFF);}  
    EPD_W21_WriteCMD1(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=0;i<85;i++){    
      EPD_W21_WriteDATA1(datas[170*j+i]);}  

    //Slave
    EPD_W21_WriteCMD2(0x10);         //Transfer old data
    for(i=0;i<EPD_ARRAY;i++){   
      EPD_W21_WriteDATA2(0xFF);}  
    EPD_W21_WriteCMD2(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=85;i<85*2;i++){   
      EPD_W21_WriteDATA2(datas[170*j+i]);}    
  
    EPD_Update();     
}
void EPD_WhiteScreen_ALL180(const unsigned char *datas)
{
    unsigned int i,j;
    //Master
    EPD_W21_WriteCMD1(0x10);         //Transfer old data
    for(i=0;i<EPD_ARRAY;i++){   
      EPD_W21_WriteDATA1(0xFF);}  
    EPD_W21_WriteCMD1(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=85;i<85*2;i++){   
      EPD_W21_WriteDATA1(datas[170*j+i]);}   
          
    //Slave
    EPD_W21_WriteCMD2(0x10);         //Transfer old data
    for(i=0;i<EPD_ARRAY;i++){   
      EPD_W21_WriteDATA2(0xFF);}  
    EPD_W21_WriteCMD2(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=0;i<85;i++){    
      EPD_W21_WriteDATA2(datas[170*j+i]);}  

    EPD_Update();     
}
void EPD_WhiteScreen_ALL_P(const unsigned char *oldDatas,const unsigned char *newDatas)
{
    unsigned int i,j;
    //Master
    EPD_W21_WriteCMD1(0x10);         //Transfer old data 
    if(partFlag==1){ 
          for(j=0;j<480;j++)
          for(i=0;i<85;i++){  
          EPD_W21_WriteDATA1(0xFF);}
        }
    else{
          for(j=0;j<480;j++)
          for(i=0;i<85;i++){    
          EPD_W21_WriteDATA1(oldDatas[170*j+i]);}  
          }   
      
    EPD_W21_WriteCMD1(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=0;i<85;i++){    
      EPD_W21_WriteDATA1(newDatas[170*j+i]);}  

    //Slave
    EPD_W21_WriteCMD2(0x10);         //Transfer old data
    if(partFlag==1){ 
          partFlag=0;
          for(j=0;j<480;j++)
          for(i=85;i<85*2;i++){ 
          EPD_W21_WriteDATA2(0xFF);}
        }
    else{
          for(j=0;j<480;j++)
          for(i=85;i<85*2;i++){   
          EPD_W21_WriteDATA2(oldDatas[170*j+i]);}  
          }   
    EPD_W21_WriteCMD2(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=85;i<85*2;i++){   
      EPD_W21_WriteDATA2(newDatas[170*j+i]);}    
  
    EPD_Update();     


}


void EPD_WhiteScreen_White(void)
{
    unsigned int i;
   //Master
   EPD_W21_WriteCMD1(0x10);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA1(0xFF);}
   EPD_W21_WriteCMD1(0x13);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA1(0xFF);}
   //Slave
   EPD_W21_WriteCMD2(0x10);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA2(0xFF);}
   EPD_W21_WriteCMD2(0x13);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA2(0xFF);}
   
    EPD_Update();     
}
void EPD_WhiteScreen_Black(void)
{
    unsigned int i;
   //Master
   EPD_W21_WriteCMD1(0x10);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA1(0xFF);}
   EPD_W21_WriteCMD1(0x13);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA1(0x00);}
   //Slave
   EPD_W21_WriteCMD2(0x10);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA2(0xFF);}
   EPD_W21_WriteCMD2(0x13);        //Transfer old data
   for(i=0;i<EPD_ARRAY;i++){    
    EPD_W21_WriteDATA2(0x00);}
   
    EPD_Update();     
}

////////////////////////////////Other newly added functions////////////////////////////////////////////
//Display rotation 180 degrees initialization
void EPD_Init_180(void)
{ 
  delay(100);//At least 10ms delay 
	EPD_W21_RST_0;		// Module reset
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10);//At least 10ms delay 
	lcd_chkstatus();
	
	EPD_W21_WriteCMD(0x4D);
	EPD_W21_WriteDATA(0x55);

	EPD_W21_WriteCMD(0xA6);
	EPD_W21_WriteDATA(0x38);

	EPD_W21_WriteCMD(0xB4);
	EPD_W21_WriteDATA(0x5D);

	EPD_W21_WriteCMD(0xB6);
	EPD_W21_WriteDATA(0x80);

	EPD_W21_WriteCMD(0xB7);
	EPD_W21_WriteDATA(0x00);

	EPD_W21_WriteCMD(0xF7);
	EPD_W21_WriteDATA(0x02);

	EPD_W21_WriteCMD2(0xAE);
	EPD_W21_WriteDATA2(0xA0);

	EPD_W21_WriteCMD(0xE0);
	EPD_W21_WriteDATA(0x01);


	EPD_W21_WriteCMD(0x00);//Panel setting	
	EPD_W21_WriteDATA(0x93);
	EPD_W21_WriteDATA(0x0D);

	EPD_W21_WriteCMD(0x06);//boost
	EPD_W21_WriteDATA(0x57);
	EPD_W21_WriteDATA(0x24);
	EPD_W21_WriteDATA(0x28);
	EPD_W21_WriteDATA(0x32);
	EPD_W21_WriteDATA(0x08);	
	EPD_W21_WriteDATA(0x48);

	EPD_W21_WriteCMD(0x61);//resolution setting
	EPD_W21_WriteDATA(0X02);//680   1360*480
	EPD_W21_WriteDATA(0XA8);
	EPD_W21_WriteDATA(0X01);//480
	EPD_W21_WriteDATA(0XE0);

	EPD_W21_WriteCMD(0x62);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x00);	

	EPD_W21_WriteCMD(0x60);
	EPD_W21_WriteDATA(0x31);

	EPD_W21_WriteCMD(0x50);//VCOM and DATA interval setting(CDI)	
	EPD_W21_WriteDATA(0x97);

	EPD_W21_WriteCMD(0xE8);  
	EPD_W21_WriteDATA(0x01); 

	EPD_W21_WriteCMD(0x04);  //power on  
	delay(200);  
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal 
}

void EPD_Display(unsigned char *Image)
{
    unsigned int i,j;
    //Master
    EPD_W21_WriteCMD1(0x10);         //Transfer old data
    for(i=0;i<EPD_ARRAY;i++){   
      EPD_W21_WriteDATA1(0xFF);}  
    EPD_W21_WriteCMD1(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=0;i<85;i++){    
      EPD_W21_WriteDATA1(Image[170*j+i]);}  

    //Slave
    EPD_W21_WriteCMD2(0x10);         //Transfer old data
    for(i=0;i<EPD_ARRAY;i++){   
      EPD_W21_WriteDATA2(0xFF);}  
    EPD_W21_WriteCMD2(0x13);         //Transfer old data
    for(j=0;j<480;j++)
    for(i=85;i<85*2;i++){   
      EPD_W21_WriteDATA2(Image[170*j+i]);}    
  
    EPD_Update();     
}



/***********************************************************
            end file
***********************************************************/

