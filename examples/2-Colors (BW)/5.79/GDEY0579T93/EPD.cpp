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
//SSD1683
void EPD_HW_Init(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
	
	
}
void EPD_HW_Init_Fast(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
  
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
 	
  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	
	  	
	EPD_W21_WriteCMD(0x22); // Load temperature value
	EPD_W21_WriteDATA(0xB1);		
  EPD_W21_WriteCMD(0x20);	
  Epaper_READBUSY();   

	EPD_W21_WriteCMD(0x1A); // Write to temperature register
	EPD_W21_WriteDATA(0x64);		
  EPD_W21_WriteDATA(0x00);	
				  	
	EPD_W21_WriteCMD(0x22); // Load temperature value
	EPD_W21_WriteDATA(0x91);		
  EPD_W21_WriteCMD(0x20);	
	Epaper_READBUSY();   
}

void EPD_HW_Init_4G(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
  
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
 	
  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	
	  	
	EPD_W21_WriteCMD(0x22); // Load temperature value
	EPD_W21_WriteDATA(0xB1);		
  EPD_W21_WriteCMD(0x20);	
  Epaper_READBUSY();   

	EPD_W21_WriteCMD(0x1A); // Write to temperature register
	EPD_W21_WriteDATA(0x5A);		
  EPD_W21_WriteDATA(0x00);	
				  	
	EPD_W21_WriteCMD(0x22); // Load temperature value
	EPD_W21_WriteDATA(0x91);		
  EPD_W21_WriteCMD(0x20);	
	Epaper_READBUSY();   
}

/////////////////////////////////////////////////////////////////////////////////////////
/*When the electronic paper screen is updated, do not unplug the electronic paper to avoid damage to the screen*/

void EPD_Update(void)
{   
  EPD_W21_WriteCMD(0x22); //Display Update Control
  EPD_W21_WriteDATA(0xF7);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   
	
}
void EPD_Update_Fast(void)
{   
  EPD_W21_WriteCMD(0x22); //Display Update Control
  EPD_W21_WriteDATA(0xC7);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}

void EPD_Update_4G(void)
{   
  EPD_W21_WriteCMD(0x22); //Display Update Control  
	EPD_W21_WriteDATA(0xCF);   
  EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();   

}
/*When the electronic paper screen is updated, do not unplug the electronic paper to avoid damage to the screen*/
void EPD_Part_Update(void)
{
	EPD_W21_WriteCMD(0x22); //Display Update Control
	EPD_W21_WriteDATA(0xFF);   
	EPD_W21_WriteCMD(0x20); //Activate Display Update Sequence
	Epaper_READBUSY(); 			
}

void Set_ramMP(void) // Set RAM X - address Start / End position  ; Set RAM Y - address Start / End position  -MASTER
{
	EPD_W21_WriteCMD(0x11);	 // Data Entry mode setting
	EPD_W21_WriteDATA(0x05);     // 1 ¨CY decrement, X increment
	EPD_W21_WriteCMD(0x44);	 						 // Set Ram X- address Start / End position
	EPD_W21_WriteDATA(0x00);     						 // XStart, POR = 00h
	EPD_W21_WriteDATA(0x31); //400/8-1
	EPD_W21_WriteCMD(0x45);	 									// Set Ram Y- address  Start / End position 
	EPD_W21_WriteDATA(0x0f);  
	EPD_W21_WriteDATA(0x01);  //300-1	
	EPD_W21_WriteDATA(0x00);     									// YEnd L
	EPD_W21_WriteDATA(0x00);											// YEnd H 
			
}

void Set_ramMA(void)  // Set RAM X address counter ;  Set RAM Y address counter                             -MASTER
{
	EPD_W21_WriteCMD(0x4e);	 						 
	EPD_W21_WriteDATA(0x00);	
	EPD_W21_WriteCMD(0x4f);	 
	EPD_W21_WriteDATA(0x0f);  
	EPD_W21_WriteDATA(0x01); 	
}

void Set_ramSP(void)  // Set RAM X - address Start / End position  ; Set RAM Y - address Start / End position  -SLAVE
{
	EPD_W21_WriteCMD(0x91);	 						 
	EPD_W21_WriteDATA(0x04); 
	EPD_W21_WriteCMD(0xc4);	 						 // Set Ram X- address Start / End position
	EPD_W21_WriteDATA(0x30);   //392/8-1   						 // XStart, POR = 00h
	EPD_W21_WriteDATA(0x00); 
	EPD_W21_WriteCMD(0xc5);	 									// Set Ram Y- address  Start / End position 
	EPD_W21_WriteDATA(0x0f);  
	EPD_W21_WriteDATA(0x01);  	
	EPD_W21_WriteDATA(0x00);     									// YEnd L
	EPD_W21_WriteDATA(0x00);											// YEnd H 	
}

void Set_ramSA(void)   // Set RAM X address counter ;  Set RAM Y address counter                             -SLAVE
{
	EPD_W21_WriteCMD(0xce);	 						 
	EPD_W21_WriteDATA(0x31); 
	EPD_W21_WriteCMD(0xcf);	 
	EPD_W21_WriteDATA(0x0f);  
	EPD_W21_WriteDATA(0x01); 	
}

//////////////////////////////All screen update////////////////////////////////////////////

//Horizontal scanning, from right to left, from bottom to top
void EPD_WhiteScreen_ALL_Fast(const unsigned char *datas)
{
  unsigned int i; 
  unsigned char tempOriginal;      
  unsigned int tempcol=0;
  unsigned int templine=0;

    EPD_W21_WriteCMD(0x11);     
    EPD_W21_WriteDATA(0x05); 
  
    EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
    EPD_W21_WriteDATA(0x00);
	  EPD_W21_WriteDATA(0x31);    //0x12-->(18+1)*8=152
  
    EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
    EPD_W21_WriteDATA(0x0F);   //0x97-->(151+1)=152      
    EPD_W21_WriteDATA(0x01);
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x00); 

    EPD_W21_WriteCMD(0x4E);     
    EPD_W21_WriteDATA(0x00);	
	  EPD_W21_WriteCMD(0x4F);       
		EPD_W21_WriteDATA(0x0F);
	  EPD_W21_WriteDATA(0x01);	
	
	Epaper_READBUSY();
    EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)	
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {          
     tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(~tempOriginal);
   } 
	 
    EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)	
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {            
     EPD_W21_WriteDATA(0X00);
   } 	 
	 

    EPD_W21_WriteCMD(0x91);     
    EPD_W21_WriteDATA(0x04); 
  
    EPD_W21_WriteCMD(0xC4); //set Ram-X address start/end position   
    EPD_W21_WriteDATA(0x31);
	  EPD_W21_WriteDATA(0x00);    //0x12-->(18+1)*8=152
  
    EPD_W21_WriteCMD(0xC5); //set Ram-Y address start/end position          
    EPD_W21_WriteDATA(0x0F);   //0x97-->(151+1)=152  ÐÞ¸ÄµÄ    
    EPD_W21_WriteDATA(0x01);
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x00); 
    
    EPD_W21_WriteCMD(0xCE);     
    EPD_W21_WriteDATA(0x31);	
	  EPD_W21_WriteCMD(0xCF);       
		EPD_W21_WriteDATA(0x0F);
	  EPD_W21_WriteDATA(0x01);	
	
	Epaper_READBUSY();

	tempcol=tempcol-1; //Byte dislocation processing
	templine=0;
    EPD_W21_WriteCMD(0xa4);   //write RAM for black(0)/white (1)
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {          
     tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(~tempOriginal);
   } 
	 
    EPD_W21_WriteCMD(0xa6);   //write RAM for black(0)/white (1)	
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {            
     EPD_W21_WriteDATA(0X00);
   } 	
	 
   EPD_Update_Fast();	 
}
///////////////////////////Part update//////////////////////////////////////////////
//The x axis is reduced by one byte, and the y axis is reduced by one pixel.
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
	unsigned int i; 
	  unsigned char tempOriginal;      
  unsigned int tempcol=0;
  unsigned int templine=0;
Set_ramMP();
Set_ramMA();
	EPD_W21_WriteCMD(0x24);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
     tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(~tempOriginal);
		 //EPD_W21_WriteDATA(0xff);
	}

Set_ramMA();
	EPD_W21_WriteCMD(0x26);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
			EPD_W21_WriteDATA(0x00);
	}

tempcol=tempcol-1; //Byte dislocation processing
templine=0;
Set_ramSP();
Set_ramSA();
	EPD_W21_WriteCMD(0xA4);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
     tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(~tempOriginal); 
    // EPD_W21_WriteDATA(0xff);		 
	}

Set_ramSA();
	EPD_W21_WriteCMD(0xA6);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
			EPD_W21_WriteDATA(0x00);
	}	
	EPD_Update();
	
	
	
	 //basemap  
Set_ramMA();
	tempcol=0;
	templine=0;
	EPD_W21_WriteCMD(0x26);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
     tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(~tempOriginal);
		 //EPD_W21_WriteDATA(0xff);
	}
Set_ramSA();
	tempcol=tempcol-1; //Byte dislocation processing
	templine=0;
	EPD_W21_WriteCMD(0xa6);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
     tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(~tempOriginal);
		 //EPD_W21_WriteDATA(0xff);
	}	
}


void EPD_DeepSleep(void)
{  	
  EPD_W21_WriteCMD(0x10); //enter deep sleep
  EPD_W21_WriteDATA(0x01); 
  delay_xms(100);
}



/////////////////////////////////Single display////////////////////////////////////////////////

void EPD_WhiteScreen_White(void)

{
	unsigned int i; 
	
Set_ramMP();
Set_ramMA();
	EPD_W21_WriteCMD(0x24);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
			EPD_W21_WriteDATA(0xff);
	}

Set_ramMA();
	EPD_W21_WriteCMD(0x26);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
			EPD_W21_WriteDATA(0x00);
	}

		
Set_ramSP();
Set_ramSA();
	EPD_W21_WriteCMD(0xA4);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
			EPD_W21_WriteDATA(0xff);
	}

Set_ramSA();
	EPD_W21_WriteCMD(0xA6);   
	for(i=0;i<Source_BYTES*Gate_BITS;i++)
	{
			EPD_W21_WriteDATA(0x00);
	}	
	EPD_Update();
	

}

void EPD_WhiteScreen_ALL(const unsigned char *datas)

{
		unsigned int i; 
		unsigned char tempOriginal;      
		unsigned int tempcol=0;
		unsigned int templine=0;
		Set_ramMP();
		Set_ramMA();
		EPD_W21_WriteCMD(0x24);   
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		{
			tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
			templine++;
			if(templine>=Gate_BITS)
			{
			tempcol++;
			templine=0;
			}     
			EPD_W21_WriteDATA(~tempOriginal);
		}

		Set_ramMA();
		EPD_W21_WriteCMD(0x26);   
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		{
		  EPD_W21_WriteDATA(0x00);
		}

		tempcol=tempcol-1; //Byte dislocation processing
		templine=0;
		Set_ramSP();
		Set_ramSA();
		EPD_W21_WriteCMD(0xA4);   
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		{
			tempOriginal=*(datas+templine*Source_BYTES*2+tempcol);
			templine++;
			if(templine>=Gate_BITS)
			{
			tempcol++;
			templine=0;
			}     
			EPD_W21_WriteDATA(~tempOriginal); 	 
		}

		Set_ramSA();
		EPD_W21_WriteCMD(0xA6);   
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		{
		  EPD_W21_WriteDATA(0x00);
		}	
		EPD_Update();
}
void EPD_HW_Init_Part(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	Epaper_READBUSY();   
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   

	EPD_W21_WriteCMD(0x11);	 // Data Entry mode setting
	EPD_W21_WriteDATA(0x03);     // 1 ¨CY decrement, X increment
		
	EPD_W21_WriteCMD(0x3C); //BorderWavefrom
	EPD_W21_WriteDATA(0x80);		
	
}


//Horizontal scanning
void EPD_Dis_Part_M(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i,j;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	
  char tempData,data1;

	
	
	x_start=x_start/8;
	x_end=x_start+PART_LINE/8-1; 
	
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
	
  EPD_W21_WriteCMD(0x22); 
  EPD_W21_WriteDATA(0xc0);   
  EPD_W21_WriteCMD(0x20); 
  Epaper_READBUSY(); 	
	
//	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_start);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    // ????=0	


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_start); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing
				 tempData=datas[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }

	 EPD_Part_Update();

}
void EPD_Dis_Part_S(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	x_start=x_start/8;
	x_end=x_start+PART_LINE/8-1; 
	
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

	
  EPD_W21_WriteCMD(0x22); 
  EPD_W21_WriteDATA(0xc0);   
  EPD_W21_WriteCMD(0x20); 
  Epaper_READBUSY(); 	
	
//
	EPD_W21_WriteCMD(0x91);    						 
	EPD_W21_WriteDATA(0x03); 
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_start);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    // ????=0	


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_start); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
	 
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datas[i]);
   }

	 EPD_Part_Update();

}

/////////////////////////////////////TIME///////////////////////////////////////////////////
void EPD_Dis_Part_myself_M(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
											   unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      )
{
	unsigned int i,j;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	
  char tempData,data1;

	
	//Data A//////////////////////////////
	x_startA=x_startA/8;//Convert to byte
	x_end=x_startA+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startA-1;
	if(y_startA>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startA+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		

//
  EPD_W21_WriteCMD(0x22); 
  EPD_W21_WriteDATA(0xc0);   
  EPD_W21_WriteCMD(0x20); 
  Epaper_READBUSY(); 	
	
//	
	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startA);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startA); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing	 
				 tempData=datasA[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }
	 
	//Data B/////////////////////////////////////

	x_startB=x_startB/8;//Convert to byte
	x_end=x_startB+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startB-1;
	if(y_startB>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startB+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startB);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);   


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startB); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing 
				 tempData=datasB[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }
	 
	//Data C//////////////////////////////////////
	x_startC=x_startC/8;//Convert to byte
	x_end=x_startC+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startC-1;
	if(y_startC>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startC+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startC);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);   


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startC); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing 
				 tempData=datasC[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }	 	 
 	 
	//Data D//////////////////////////////////////
	x_startD=x_startD/8;//Convert to byte
	x_end=x_startD+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startD-1;
	if(y_startD>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startD+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startD);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);        // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startD); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing
				 tempData=datasD[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }
	//Data E//////////////////////////////////////
	x_startE=x_startE/8;//Convert to byte
	x_end=x_startE+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startE-1;
	if(y_startE>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startE+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startE);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startE); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing		 
				 tempData=datasE[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }  
	 EPD_Part_Update(); 

}

void EPD_Dis_Part_myself_S(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
											   unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      )
{
	unsigned int i;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;


	//Data A//////////////////////////////
	x_startA=x_startA/8;//Convert to byte
	x_end=x_startA+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startA-1;
	if(y_startA>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startA+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		

//
  EPD_W21_WriteCMD(0x22); 
  EPD_W21_WriteDATA(0xc0);   
  EPD_W21_WriteCMD(0x20); 
  Epaper_READBUSY(); 	

	EPD_W21_WriteCMD(0x91);    						 
	EPD_W21_WriteDATA(0x03); 	
//	
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startA);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startA); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasA[i]);
   }

	 
	//Data B/////////////////////////////////////

	x_startB=x_startB/8;//Convert to byte
	x_end=x_startB+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startB-1;
	if(y_startB>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startB+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startB);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);   


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startB); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasB[i]);
   }

	 
	//Data C//////////////////////////////////////
	x_startC=x_startC/8;//Convert to byte
	x_end=x_startC+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startC-1;
	if(y_startC>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startC+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startC);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);   


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startC); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasC[i]);
   }
 	 
 	 
	//Data D//////////////////////////////////////
	x_startD=x_startD/8;//Convert to byte
	x_end=x_startD+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startD-1;
	if(y_startD>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startD+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startD);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);        // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startD); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasD[i]);
   }

	//Data E//////////////////////////////////////
	x_startE=x_startE/8;//Convert to byte
	x_end=x_startE+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startE-1;
	if(y_startE>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startE+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startE);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startE); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasE[i]);
   }
 
	 EPD_Part_Update(); 

}

void EPD_Dis_Part_myself_All(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
												 unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      )
{
	unsigned int i,j;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
  char tempData,data1;

	
	
//
  EPD_W21_WriteCMD(0x22); 
  EPD_W21_WriteDATA(0xc0);   
  EPD_W21_WriteCMD(0x20); 
  Epaper_READBUSY(); 	

	EPD_W21_WriteCMD(0x91);    						 
	EPD_W21_WriteDATA(0x03); 	
//	
	
	//Data A//////////////////////////////
	x_startA=x_startA/8;//Convert to byte
	x_end=x_startA+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startA-1;
	if(y_startA>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startA+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startA);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startA); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasA[i]);
   }  

	 
	//Data B/////////////////////////////////////

	x_startB=x_startB/8;//Convert to byte
	x_end=x_startB+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startB-1;
	if(y_startB>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startB+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startB);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);   


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startB); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasB[i]);
   }
	 
	//Data C/////////////////////////////////////

	x_startC=x_startC/8;//Convert to byte
	x_end=x_startC+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startC-1;
	if(y_startC>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startC+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0xC4);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startC);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0xC5);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);   


	EPD_W21_WriteCMD(0xCE);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startC); 
	EPD_W21_WriteCMD(0xCF);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0xA4);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {   
     EPD_W21_WriteDATA(~datasC[i]);
   }	
	 
	/***************************************************************************/ 
//
  EPD_W21_WriteCMD(0x22); 
  EPD_W21_WriteDATA(0xc0);   
  EPD_W21_WriteCMD(0x20); 
  Epaper_READBUSY(); 		
//
			 
//Data D//////////////////////////////////////
	x_startD=x_startD/8;//Convert to byte
	x_end=x_startD+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startD-1;
	if(y_startD>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startD+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startD);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);    // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);   


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startD); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM
	 for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing	 
				 tempData=datasD[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }
 	 
	//Data E//////////////////////////////////////
	x_startE=x_startE/8;//Convert to byte
	x_end=x_startE+PART_LINE/8-1; 
	
	y_start1=0;
	y_start2=y_startE-1;
	if(y_startE>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_startE+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
	EPD_W21_WriteCMD(0x44);       // set RAM x address start/end, in page 35
	EPD_W21_WriteDATA(x_startE);    // RAM x address start at 00h;
	EPD_W21_WriteDATA(x_end);        // RAM x address end at 0fh(15+1)*8->128 
	EPD_W21_WriteCMD(0x45);       // set RAM y address start/end, in page 35
	EPD_W21_WriteDATA(y_start2);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_start1);    // RAM y address start at 0127h;
	EPD_W21_WriteDATA(y_end2);    // RAM y address end at 00h;
	EPD_W21_WriteDATA(y_end1);    


	EPD_W21_WriteCMD(0x4E);   // set RAM x address count to 0;
	EPD_W21_WriteDATA(x_startE); 
	EPD_W21_WriteCMD(0x4F);   // set RAM y address count to 0X127;    
	EPD_W21_WriteDATA(y_start2);
	EPD_W21_WriteDATA(y_start1);
	
	
	 EPD_W21_WriteCMD(0x24);   //Write Black and White image to RAM

   for(i=0;i<PART_COLUMN;i++)
	    for(j=0;j<PART_LINE/8;j++)
			 {   
				 //Byte image processing 
				 tempData=datasE[i*(PART_LINE/8)+(PART_LINE/8)-j-1];	 
				 data1=(tempData>>7&0x01)+(tempData>>5&0x02)+(tempData>>3&0x04)+(tempData>>1&0x08)+(tempData<<7&0x80)+(tempData<<5&0x40)+(tempData<<3&0x20)+(tempData<<1&0x10); //×Ö½ÚÄÚÊý¾Ý·´Ðò
		     EPD_W21_WriteDATA(~data1); 
				 
			 }
	 EPD_Part_Update(); 

}



void EPD_HW_Init_GUI(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
  
	EPD_W21_WriteCMD(0x12);  //SWRESET
	Epaper_READBUSY();   
 	
  EPD_W21_WriteCMD(0x18); //Read built-in temperature sensor
	EPD_W21_WriteDATA(0x80);	
	  	
	EPD_W21_WriteCMD(0x22); // Load temperature value
	EPD_W21_WriteDATA(0xB1);		
  EPD_W21_WriteCMD(0x20);	
  Epaper_READBUSY();   

	EPD_W21_WriteCMD(0x1A); // Write to temperature register
	EPD_W21_WriteDATA(0x64);		
  EPD_W21_WriteDATA(0x00);	
				  	
	EPD_W21_WriteCMD(0x22); // Load temperature value
	EPD_W21_WriteDATA(0x91);		
  EPD_W21_WriteCMD(0x20);	
	Epaper_READBUSY();   
}


void EPD_Display(unsigned char *Image)
{
unsigned long i; 
  unsigned char tempOriginal;      
  unsigned long tempcol=0;
  unsigned long templine=0;

    EPD_W21_WriteCMD(0x11);     
    EPD_W21_WriteDATA(0x05); 
  
    EPD_W21_WriteCMD(0x44); //set Ram-X address start/end position   
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x31);    //0x12-->(18+1)*8=152
  
    EPD_W21_WriteCMD(0x45); //set Ram-Y address start/end position          
    EPD_W21_WriteDATA(0x0F);   //0x97-->(151+1)=152      
    EPD_W21_WriteDATA(0x01);
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x00); 

    EPD_W21_WriteCMD(0x4E);     
    EPD_W21_WriteDATA(0x00);  
    EPD_W21_WriteCMD(0x4F);       
    EPD_W21_WriteDATA(0x0F);
    EPD_W21_WriteDATA(0x01);  
  
  Epaper_READBUSY();
    EPD_W21_WriteCMD(0x24);   //write RAM for black(0)/white (1)  
  for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {          
     tempOriginal=*(Image+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(tempOriginal);
   } 
   
    EPD_W21_WriteCMD(0x26);   //write RAM for black(0)/white (1)  
  for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {            
     EPD_W21_WriteDATA(0X00);
   }   
   

    EPD_W21_WriteCMD(0x91);     
    EPD_W21_WriteDATA(0x04); 
  
    EPD_W21_WriteCMD(0xC4); //set Ram-X address start/end position   
    EPD_W21_WriteDATA(0x31);
    EPD_W21_WriteDATA(0x00);    //0x12-->(18+1)*8=152
  
    EPD_W21_WriteCMD(0xC5); //set Ram-Y address start/end position          
    EPD_W21_WriteDATA(0x0F);   //0x97-->(151+1)=152  ??????    
    EPD_W21_WriteDATA(0x01);
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x00); 
    
    EPD_W21_WriteCMD(0xCE);     
    EPD_W21_WriteDATA(0x31);  
    EPD_W21_WriteCMD(0xCF);       
    EPD_W21_WriteDATA(0x0F);
    EPD_W21_WriteDATA(0x01);  
  
  Epaper_READBUSY();

  tempcol=tempcol-1; //Byte dislocation processing
  templine=0;
    EPD_W21_WriteCMD(0xa4);   //write RAM for black(0)/white (1)
  for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {          
     tempOriginal=*(Image+templine*Source_BYTES*2+tempcol);
     templine++;
     if(templine>=Gate_BITS)
     {
       tempcol++;
       templine=0;
     }     
     EPD_W21_WriteDATA(tempOriginal);
   } 
   
    EPD_W21_WriteCMD(0xa6);   //write RAM for black(0)/white (1)  
  for(i=0;i<Source_BYTES*Gate_BITS;i++)
   {            
     EPD_W21_WriteDATA(0X00);
   }  
		EPD_Update(); 
}



void EPD_WhiteScreen_ALL_4line(void)
{
	unsigned int i,j;    

		Set_ramMP();
		Set_ramMA();
		EPD_W21_WriteCMD(0x24);   

	for(i=0;i<400/8;i++)
	{
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
	}
		Set_ramMA();
		EPD_W21_WriteCMD(0x26);   

	for(i=0;i<50;i++)
	{
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
	}	
		Set_ramSP();
		Set_ramSA();
		
		
		EPD_W21_WriteCMD(0xA4);   

	for(i=0;i<50;i++)
	{
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
	}
		Set_ramSA();
		EPD_W21_WriteCMD(0xA6);   

	for(i=0;i<50;i++)
	{
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0x00);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
		for(j=0;j<68;j++)
		{
			EPD_W21_WriteDATA(0xFF);
		}
	}	
		EPD_Update_4G();

}







unsigned char R24_DTM1(unsigned char Image_data1,unsigned char Image_data2)
{
	unsigned int i,all; 
	unsigned char TempData1,TempData2;
	unsigned char outdata=0x00;

		TempData1=Image_data1;
		TempData2=Image_data2;
		
		for(i=0;i<4;i++)
		{ 
			outdata=outdata<<1;
			if( ((TempData1&0xC0)==0xC0) || ((TempData1&0xC0)==0x40))
				outdata=outdata|0x01;
			else 
				outdata=outdata|0x00;

			TempData1=TempData1<<2;
 
		}

		for(all=0;all<4;all++)
		{ 
			outdata=outdata<<1;
			if((TempData2&0xC0)==0xC0||(TempData2&0xC0)==0x40)
				outdata=outdata|0x01;
			else 
				outdata=outdata|0x00;

			TempData2=TempData2<<2;

		}
		return outdata;
}
unsigned char R26_DTM2(unsigned char Image_data1,unsigned char Image_data2)
{
	unsigned int i,all; 
	unsigned char TempData1,TempData2;
	unsigned char outdata=0x00;
	TempData1=Image_data1;
	TempData2=Image_data2;
		
		for(i=0;i<4;i++)
		{ 
			outdata=outdata<<1;
			if( ((TempData1&0xC0)==0xC0) || ((TempData1&0xC0)==0x80))
				outdata=outdata|0x01;
			else 
				outdata=outdata|0x00;

			TempData1=TempData1<<2;
		}

		for(all=0;all<4;all++)
		{ 
			outdata=outdata<<1;
			if((TempData2&0xC0)==0xC0||(TempData2&0xC0)==0x80)
				outdata=outdata|0x01;
			else 
				outdata=outdata|0x00;

			TempData2=TempData2<<2;

		}
		return outdata;
}


void EPD_WhiteScreen_ALL_4G(const unsigned char *datas)
{
    unsigned int i,j; 
    unsigned char tempOriginal;      
    unsigned int tempcol=0;
    unsigned int templine=0;  
    unsigned char value;      
		Set_ramMP();
		Set_ramMA();
		EPD_W21_WriteCMD(0x24);   
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		 {          
			 value= R24_DTM1( *(datas+templine*Source_BYTES*4+tempcol),*(datas+templine*Source_BYTES*4+tempcol+1));
			 templine++;
			 if(templine>=Gate_BITS)
			 {
				 tempcol+=2;
				 templine=0;
			 }     
			 EPD_W21_WriteDATA(value);
			 
		 } 
		Set_ramMA();
	 tempcol=0;
	 templine=0;
		EPD_W21_WriteCMD(0x26);   
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		 {          
			 value= R26_DTM2( *(datas+templine*Source_BYTES*4+tempcol),*(datas+templine*Source_BYTES*4+tempcol+1));
			 templine++;
			 if(templine>=Gate_BITS)
			 {
				 tempcol+=2;
				 templine=0;
			 }     
			 EPD_W21_WriteDATA(value);
			 
		 } 
		Set_ramSP();
		Set_ramSA();
		
		tempcol=100-2; 
		templine=0;
		EPD_W21_WriteCMD(0xA4);   
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		 {          
			 value= R24_DTM1( *(datas+templine*Source_BYTES*4+tempcol),*(datas+templine*Source_BYTES*4+tempcol+1));
			 templine++;
			 if(templine>=Gate_BITS)//272
			 {
				 tempcol+=2;
				 templine=0;
			 }      
			 EPD_W21_WriteDATA(value);
			 
		 } 
		Set_ramSA();
	  tempcol=100-2; //Byte dislocation processing
		templine=0;
		EPD_W21_WriteCMD(0xA6); 
		for(i=0;i<Source_BYTES*Gate_BITS;i++)
		 {          
			 value= R26_DTM2( *(datas+templine*Source_BYTES*4+tempcol),*(datas+templine*Source_BYTES*4+tempcol+1));
			 templine++;
			 if(templine>=Gate_BITS)//272
			 {
				 tempcol+=2;
				 templine=0;
			 }      
			 EPD_W21_WriteDATA(value);
			 
		 } 	
			EPD_Update_4G();

}


/***********************************************************
            end file
***********************************************************/

