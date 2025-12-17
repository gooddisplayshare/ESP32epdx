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
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_LINE,unsigned int PART_COLUMN)
{
	unsigned int i;  
	unsigned int x_end,x_start1,x_start2,x_end1,x_end2;
	unsigned int y_start1,y_start2,y_end1,y_end2;
	x_start=x_start;
	x_end=x_start+PART_LINE-1; 
	
	x_start1=0;
	x_start2=x_start;
	if(x_start>=256)
	{
		x_start1=x_start2/256;
		x_start2=x_start2%256;
	}	
	x_end1=0;
	x_end2=x_end;
	if(x_end2>=256)
	{
		x_end1=x_end2/256;
		x_end2=x_end2%256;		
	}		

	y_start1=0;
	y_start2=y_start;
	if(y_start>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_start+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
//Reset
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	EPD_W21_WriteCMD(0x3C); //BorderWavefrom  
	EPD_W21_WriteDATA(0x80);	
//	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(x_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(x_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(x_end1);    // ????=0	
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    // ????=0	


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_start2);
	EPD_W21_WriteDATA(x_start1);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
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
void EPD_Dis_Part_RAM(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_LINE,unsigned int PART_COLUMN)
{
 	unsigned int i;  
	unsigned int x_end,x_start1,x_start2,x_end1,x_end2;
	unsigned int y_start1,y_start2,y_end1,y_end2;
	x_start=x_start;
	x_end=x_start+PART_LINE-1; 
	
	x_start1=0;
	x_start2=x_start;
	if(x_start>=256)
	{
		x_start1=x_start2/256;
		x_start2=x_start2%256;
	}	
	x_end1=0;
	x_end2=x_end;
	if(x_end2>=256)
	{
		x_end1=x_end2/256;
		x_end2=x_end2%256;		
	}		

	y_start1=0;
	y_start2=y_start;
	if(y_start>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_start+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
//Reset
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	EPD_W21_WriteCMD(0x3C); //BorderWavefrom  
	EPD_W21_WriteDATA(0x80);	
//	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(x_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(x_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(x_end1);    // ????=0	
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    // ????=0	


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_start2);
	EPD_W21_WriteDATA(x_start1);
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
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

// GUI initialization
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

