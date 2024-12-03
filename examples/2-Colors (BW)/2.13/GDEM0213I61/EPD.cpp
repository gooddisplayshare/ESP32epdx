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
//Full screen update initialization
void EPD_HW_Init(void)
{
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 
  
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



//////////////////////////////Display Update Function///////////////////////////////////////////////////////
//Full screen update function
void EPD_Update(void)
{   
  EPD_W21_WriteCMD(0x22); //Display Update Control
  EPD_W21_WriteDATA(0xF7);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}

//Partial update function
void EPD_Part_Update(void)
{
  EPD_W21_WriteCMD(0x22); //Display Update Control
  EPD_W21_WriteDATA(0xFF);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();      
}
//////////////////////////////Display Data Transfer Function////////////////////////////////////////////
//Full screen update display function
void EPD_WhiteScreen_ALL(const unsigned char *datas)
{
   unsigned int i;  
  EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
   EPD_Update();   
}


//Clear screen display
void EPD_WhiteScreen_White(void)
{
 unsigned int i;
 EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
 for(i=0;i<EPD_ARRAY;i++)
 {
    EPD_W21_WriteDATA(0xff);
  }
  EPD_Update();
}
//Display all black
void EPD_WhiteScreen_Black(void)
{
 unsigned int i;
 EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)
 for(i=0;i<EPD_ARRAY;i++)
 {
    EPD_W21_WriteDATA(0x00);
  }
  EPD_Update();
}
//Partial update of background display, this function is necessary, please do not delete it!!!
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
  unsigned int i;     
  EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
  EPD_W21_WriteCMD(0x26);   //Write Black and White image to RAM
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
   }
   EPD_Update();     
   
}
//Partial update display
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  unsigned int i;  
  unsigned int x_end,y_end;
  
  x_start=x_start/8; //x address start
  x_end=x_start+PART_LINE/8-1; //x address end
  y_start=y_start; //Y address start
  y_end=y_start+PART_COLUMN-1; //Y address end
  
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay  
  EPD_W21_WriteCMD(0x3C); //BorderWavefrom,
  EPD_W21_WriteDATA(0x80);  
  
  EPD_W21_WriteCMD(0x44);       // set RAM x address start/end
  EPD_W21_WriteDATA(x_start);  //x address start
  EPD_W21_WriteDATA(x_end);   //y address end   
  EPD_W21_WriteCMD(0x45);    // set RAM y address start/end
  EPD_W21_WriteDATA(y_start%256);  //y address start2 
  EPD_W21_WriteDATA(y_start/256); //y address start1 
  EPD_W21_WriteDATA(y_end%256);  //y address end2 
  EPD_W21_WriteDATA(y_end/256); //y address end1   

  EPD_W21_WriteCMD(0x4E);        // set RAM x address count to 0;
  EPD_W21_WriteDATA(x_start);   //x start address
  EPD_W21_WriteCMD(0x4F);      // set RAM y address count to 0X127;    
  EPD_W21_WriteDATA(y_start%256);//y address start2
  EPD_W21_WriteDATA(y_start/256);//y address start1
  
  
   EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     EPD_W21_WriteDATA(datas[i]);
   } 
   EPD_Part_Update();

}
//Full screen partial update display
void EPD_Dis_PartAll(const unsigned char * datas)
{
  unsigned int i;  
  unsigned int PART_COLUMN, PART_LINE;
  PART_COLUMN=EPD_HEIGHT,PART_LINE=EPD_WIDTH;

  EPD_W21_RST_0;  // Module reset   
  delay(10); //At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay  
  EPD_W21_WriteCMD(0x3C); //BorderWavefrom,
  EPD_W21_WriteDATA(0x80);  


  EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     EPD_W21_WriteDATA(datas[i]);
   } 
   EPD_Part_Update();

}
//Deep sleep function
void EPD_DeepSleep(void)
{   
  EPD_W21_WriteCMD(0x10); //Enter deep sleep
  EPD_W21_WriteDATA(0x01); 
  delay(100);
}

//Partial update write address and data
void EPD_Dis_Part_RAM(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  unsigned int i;  
  unsigned int x_end,y_end;
  
  x_start=x_start/8; //x address start
  x_end=x_start+PART_LINE/8-1; //x address end
  
  y_start=y_start-1; //Y address start
  y_end=y_start+PART_COLUMN-1; //Y address end
  
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay  
  EPD_W21_WriteCMD(0x3C); //BorderWavefrom,
  EPD_W21_WriteDATA(0x80);  
  
  EPD_W21_WriteCMD(0x44);       // set RAM x address start/end
  EPD_W21_WriteDATA(x_start);  //x address start
  EPD_W21_WriteDATA(x_end);   //y address end   
  EPD_W21_WriteCMD(0x45);     // set RAM y address start/end
  EPD_W21_WriteDATA(y_start%256);  //y address start2 
  EPD_W21_WriteDATA(y_start/256); //y address start1 
  EPD_W21_WriteDATA(y_end%256);  //y address end2 
  EPD_W21_WriteDATA(y_end/256); //y address end1   

  EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_W21_WriteDATA(x_start);   //x start address
  EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
  EPD_W21_WriteDATA(y_start%256); //y address start2
  EPD_W21_WriteDATA(y_start/256); //y address start1
    
  EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
  for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {                         
     EPD_W21_WriteDATA(datas[i]);
   } 
}
//Clock display
void EPD_Dis_Part_Time(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
                         unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
                         unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
                         unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
                         unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
                         unsigned int PART_COLUMN,unsigned int PART_LINE
                        )
{
  EPD_Dis_Part_RAM(x_startA,y_startA,datasA,PART_COLUMN,PART_LINE);
  EPD_Dis_Part_RAM(x_startB,y_startB,datasB,PART_COLUMN,PART_LINE);
  EPD_Dis_Part_RAM(x_startC,y_startC,datasC,PART_COLUMN,PART_LINE);
  EPD_Dis_Part_RAM(x_startD,y_startD,datasD,PART_COLUMN,PART_LINE);
  EPD_Dis_Part_RAM(x_startE,y_startE,datasE,PART_COLUMN,PART_LINE);
  EPD_Part_Update();
}                        




////////////////////////////////Other newly added functions////////////////////////////////////////////
//Display rotation 180 degrees initialization
void EPD_HW_Init_180(void)
{
  EPD_W21_RST_0;  // Module reset   
  delay(10); //At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 
  
  Epaper_READBUSY();   
  EPD_W21_WriteCMD(0x12);  //SWRESET
  Epaper_READBUSY();   
  
  EPD_W21_WriteCMD(0x3C); //BorderWavefrom
  EPD_W21_WriteDATA(0x05);
  
  EPD_W21_WriteCMD(0x01); //Driver output control      
  EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);    
  EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);
  EPD_W21_WriteDATA(0x00); 

  EPD_W21_WriteCMD(0x11); //data entry mode       
  EPD_W21_WriteDATA(0x02);

  EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
  EPD_W21_WriteDATA(EPD_WIDTH/8-1);   
  EPD_W21_WriteDATA(0x00);  

  EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x00); 
  EPD_W21_WriteDATA((EPD_HEIGHT-1)%256);  
  EPD_W21_WriteDATA((EPD_HEIGHT-1)/256);

  EPD_W21_WriteCMD(0x21); //  Display update control
  EPD_W21_WriteDATA(0x00);    
  EPD_W21_WriteDATA(0x00);  

  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
  EPD_W21_WriteDATA(0x80);  

  EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_W21_WriteDATA(EPD_WIDTH/8-1);    
  EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x00);
  Epaper_READBUSY();
}

// GUI initialization
void EPD_HW_Init_GUI(void)
{
  EPD_W21_RST_0;  // Module reset   
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10); //At least 10ms delay 
  
  Epaper_READBUSY();   
  EPD_W21_WriteCMD(0x12);  //SWRESET
  Epaper_READBUSY();   
    
  EPD_W21_WriteCMD(0x01); //Driver output control      
  EPD_W21_WriteDATA((EPD_HEIGHT+46-1)%256);    
  EPD_W21_WriteDATA((EPD_HEIGHT+46-1)/256);
  EPD_W21_WriteDATA(0x01); //mirror

  EPD_W21_WriteCMD(0x11); //data entry mode       
  EPD_W21_WriteDATA(0x01);

  EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(EPD_WIDTH/8-1);   

  EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
  EPD_W21_WriteDATA((EPD_HEIGHT+46-1)%256);    
  EPD_W21_WriteDATA((EPD_HEIGHT+46-1)/256);
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
  EPD_W21_WriteDATA((EPD_HEIGHT+46-1)%256);   
  EPD_W21_WriteDATA((EPD_HEIGHT+46-1)/256);
  Epaper_READBUSY();
	
}

//GUI display
void EPD_Display(unsigned char *Image)
{
	unsigned int Width, Height,i,j;
	Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	Height = EPD_HEIGHT;

	EPD_W21_WriteCMD(0x24);
	for ( j = 0; j < Height; j++) {
			for ( i = 0; i < Width; i++) {
				 EPD_W21_WriteDATA(Image[i + j * Width]);
			}
	}
	EPD_Update();		 
}





/***********************************************************
            end file
***********************************************************/

