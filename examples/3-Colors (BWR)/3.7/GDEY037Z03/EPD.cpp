#include <EPD_SPI.h>
#include "EPD.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
   delay(xms);
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
unsigned char oldData[12480];
unsigned char oldDataP[256];
unsigned char oldDataA[256];
unsigned char oldDataB[256];
unsigned char oldDataA2[256];
unsigned char oldDataB2[256];
unsigned char oldDataC[256];
unsigned char oldDataD[256];
unsigned char oldDataE[256];
unsigned char partFlag=1;
unsigned char partFlag2=1;

void lcd_chkstatus(void)
{
  while(!isEPD_W21_BUSY); //0:BUSY, 1:FREE
                     
}

//UC8253
void EPD_Init(void)
{	
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	
  EPD_W21_WriteCMD(0x04);  //Power on
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
}
void EPD_Init_Fast(void) //16s
{	
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	
  EPD_W21_WriteCMD(0x04);  //Power on
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

	EPD_W21_WriteCMD(0xE0);
	EPD_W21_WriteDATA(0x02); 

	EPD_W21_WriteCMD(0xE5);
	EPD_W21_WriteDATA(0x5A);  

}	

void EPD_Init_Part(void)
{	
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 

	EPD_W21_WriteCMD(0x00);			//panel setting
	EPD_W21_WriteDATA(0xd7);				// RES[1:0], REG, KW/R, UD, SHL, SHD_N, RST_N          LUT_REG	
	
  EPD_W21_WriteCMD(0x04);  //Power on
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

	EPD_W21_WriteCMD(0xE0);
	EPD_W21_WriteDATA(0x02); 

	EPD_W21_WriteCMD(0xE5);
	EPD_W21_WriteDATA(0x6E);
	
	EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING			
	EPD_W21_WriteDATA(0x17); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7	

}	
void EPD_DeepSleep(void)
{
	EPD_W21_WriteCMD(0X02);  	//power off
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
	delay_xms(100);//At least 100ms delay 
	EPD_W21_WriteCMD(0X07);  	//deep sleep
	EPD_W21_WriteDATA(0xA5); 
	
}
void Power_off(void)
{	
	EPD_W21_WriteCMD(0x02); //POWER ON
	lcd_chkstatus();
}
//Full screen update function
void EPD_Update(void)
{   
	// update
	EPD_W21_WriteCMD(0x12);		//DISPLAY  update 	
	delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}
void EPD_WhiteScreen_ALL(const unsigned char *datasBW,const unsigned char *datasRW)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)	  
    {	
			 EPD_W21_WriteDATA(datasBW[i]);  //Transfer the actual displayed data
    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)	     
	  {
	    EPD_W21_WriteDATA(~datasRW[i]);  //Transfer the actual displayed data
	  }		
    EPD_Update();	   
}

//Clear screen display
void EPD_WhiteScreen_White(void)
{
		unsigned int i;
		//Write Data
		EPD_W21_WriteCMD(0x10);	     
		for(i=0;i<EPD_ARRAY;i++)	     
		{
			EPD_W21_WriteDATA(0xFF);  
		}
		EPD_W21_WriteCMD(0x13);	     
		for(i=0;i<EPD_ARRAY;i++)	     
		{
			EPD_W21_WriteDATA(0x00);  
		}
    EPD_Update();	   
		Power_off();
}

//Partial  update of background display, this function is necessary, please do not delete it!!!
void EPD_SetRAMValue_BaseMap( const unsigned char * datasBW,const unsigned char * datasRW)
{
  unsigned int i,a;	
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datasBW[i]);
   }
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(~datasRW[i]); 
   }	 
    EPD_Update();	   
	  
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   { 
     a=(datasBW[i])&(datasRW[i]);		 
     EPD_W21_WriteDATA(a);
   }	 
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     a=(datasBW[i])&(datasRW[i]);		 
     EPD_W21_WriteDATA(a);
   }	  	 
}
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
unsigned int i;
unsigned int x_end,y_end;	
	x_start=x_start-x_start%8;
	x_end=x_start+PART_LINE-1; 
  y_end=y_start+PART_COLUMN-1;

	  EPD_Init_Part();	
	
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end);	 //x-end	

		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start    
		
		EPD_W21_WriteDATA (y_end/256);		
		EPD_W21_WriteDATA (y_end%256);  //y-end
		EPD_W21_WriteDATA (0x01);	
 
		if(partFlag==1) 
		 {
			 	partFlag=0;
			 
			 	EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
			  for(i=0;i<PART_COLUMN*PART_LINE/8;i++)      
				   EPD_W21_WriteDATA(0xFF); 
		 }
		else
		 {
			 	EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
			  for(i=0;i<PART_COLUMN*PART_LINE/8;i++)      
				   EPD_W21_WriteDATA(oldDataP[i]);  
			} 
 
		EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
	 {
		EPD_W21_WriteDATA(datas[i]);
    oldDataP[i]=datas[i];
	 } 
    EPD_Update();    
		Power_off();	
	  
}


//Partial  update write address and data
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
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end);	 //x-end	

		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start    
		
		EPD_W21_WriteDATA (y_end/256);		
		EPD_W21_WriteDATA (y_end%256);  //y-end
		EPD_W21_WriteDATA (0x01);	 


	if(partFlag==1) 
	 {
			partFlag=0;
		 
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
			for(i=0;i<PART_COLUMN*PART_LINE*num/8;i++)      
				 EPD_W21_WriteDATA(0xFF); 
	 }
	else
	 {
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
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
 

EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
{
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
	}  
}
//Partial  update write address and data
void EPD_Dis_Part_RAM2(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i,x_end,y_end;
	x_start=x_start-x_start%8;
	x_end=x_start+PART_LINE-1; 
  y_end=y_start+PART_COLUMN*num-1;

	  EPD_Init_Part();	
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end);	 //x-end	

		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start    
		
		EPD_W21_WriteDATA (y_end/256);		
		EPD_W21_WriteDATA (y_end%256);  //y-end
		EPD_W21_WriteDATA (0x01);	 


	if(partFlag==1) 
	 {
			partFlag=0;
		 
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
			for(i=0;i<PART_COLUMN*PART_LINE*num/8;i++)      
				 EPD_W21_WriteDATA(0xFF); 
			for(i=0;i<PART_COLUMN*PART_LINE*num/8;i++)      
		     EPD_W21_WriteDATA(0xFF); 
	 }
	else
	 {
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataA[i]);  						 
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataB[i]);  		 
		}  
	EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
	{
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

		}  
}
//Partial  update write address and data
void EPD_Dis_Part_RAM3(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i,x_end,y_end;
	x_start=x_start-x_start%8;
	x_end=x_start+PART_LINE-1; 
  y_end=y_start+PART_COLUMN*num-1;

	  EPD_Init_Part();	
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end);	 //x-end	

		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start    
		
		EPD_W21_WriteDATA (y_end/256);		
		EPD_W21_WriteDATA (y_end%256);  //y-end
		EPD_W21_WriteDATA (0x01);	 


	if(partFlag2==1) 
	 {
			partFlag2=0;
		 
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
			for(i=0;i<PART_COLUMN*PART_LINE*num/8;i++)      
				 EPD_W21_WriteDATA(0xFF); 
			for(i=0;i<PART_COLUMN*PART_LINE*num/8;i++)      
		     EPD_W21_WriteDATA(0xFF); 
	 }
	else
	 {
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataA2[i]);  						 
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataB2[i]);  		 
		}  
	EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
	{
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	
			{			
				EPD_W21_WriteDATA(datas_A[i]);  
				oldDataA2[i]=datas_A[i];
			}					
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	
			{			
				EPD_W21_WriteDATA(datas_B[i]);  
				oldDataB2[i]=datas_B[i];
			}	

		}  
}
//Clock display
void EPD_Dis_Part_Time(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
												const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	EPD_Dis_Part_RAM(x_start,y_start,datas_A,datas_B,datas_C,datas_D,datas_E,num,PART_COLUMN,PART_LINE);
	EPD_W21_WriteCMD(0x92);		//This command makes the display enter partial mode
	EPD_Update();
}												 

//Number display1
void EPD_Dis_Part_Num2(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	EPD_Dis_Part_RAM2(x_start,y_start,datas_A,datas_B,num,PART_COLUMN,PART_LINE);
	EPD_W21_WriteCMD(0x92);		//This command makes the display enter partial mode
	EPD_Update();
}												 
//Number display2
void EPD_Dis_Part_Num3(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	EPD_Dis_Part_RAM3(x_start,y_start,datas_A,datas_B,num,PART_COLUMN,PART_LINE);
	EPD_W21_WriteCMD(0x92);		//This command makes the display enter partial mode
	EPD_Update();
}												 


////////////////////////////////Other newly added functions////////////////////////////////////////////
//Display rotation 180 degrees initialization
void EPD_Init_180(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 
	
	EPD_W21_WriteCMD(0x00);
	EPD_W21_WriteDATA(0x0B); //180 mirror
	
	EPD_W21_WriteCMD(0x04); //POWER ON
	delay_xms(300);  
	lcd_chkstatus();
	
}

//GUI display
//GUI
void EPD_Init_GUI(void)
{	
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	
	EPD_W21_WriteCMD(0x00);
	EPD_W21_WriteDATA(0x03);
	
  EPD_W21_WriteCMD(0x04);  //Power on
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

}
void EPD_Display(unsigned char * datasBW,unsigned char * datasRW)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)	  
    {	
			 EPD_W21_WriteDATA(datasBW[i]);  //Transfer the actual displayed data
    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)	     
	  {
	    EPD_W21_WriteDATA(~datasRW[i]);  //Transfer the actual displayed data
	  }		
    EPD_Update();	  
}

/***********************************************************
            end file
***********************************************************/

