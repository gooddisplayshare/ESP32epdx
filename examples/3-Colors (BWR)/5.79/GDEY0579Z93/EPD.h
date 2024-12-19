#ifndef _EPD_H_
#define _EPD_H_

#define EPD_WIDTH   800
#define EPD_HEIGHT  272
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8

#define Source_BYTES    400/8
#define Gate_BITS  272
#define ALLSCREEN_BYTES   Source_BYTES*Gate_BITS

#define NUM_LINE_BYTES 8// =64/8  
#define NUM_COLUMN_BYTES  30 

#define PART_LINE_BYTES 8// =64/8
#define PART_COLUMN_BYTES  150
//EPD
void Epaper_READBUSY(void);
void Epaper_Spi_WriteByte(unsigned char TxData);
void Epaper_Write_Command(unsigned char cmd);
void Epaper_Write_Data(unsigned char data);


void Epaper_HW_SW_RESET(void);
void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Update(void);

void EPD_Part_Init(void);//Local refresh initialization
void EPD_Part_Update(void); 

void EPD_WhiteScreen_ALL(const unsigned char* datasBW,const unsigned char* datasRW);
void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);
//Display 

void EPD_SetRAMValue_BaseMap(const unsigned char* datasBW,const unsigned char* datasRW);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Dis_Part_myself_M(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
											   unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      );
void EPD_Dis_Part_myself_S(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
											   unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      );
void EPD_Dis_Part_myself_All(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
												 unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      );
//Display canvas function
void EPD_HW_Init_GUI(void); //EPD init GUI
//Fast
void EPD_HW_Init_Fast(void);
void EPD_WhiteScreen_ALL_Fast(const unsigned char* datasBW,const unsigned char* datasRW);
	
void EPD_HW_Init_Part(void);												 
void EPD_Dis_Part_M(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);												 
void EPD_Dis_Part_S(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);												 

	
//Num display
void EPD_Part_Num_M(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
									  unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
									  unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
									  unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
									  unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,	 
									  unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Part_Num_S(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
									  unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
									  unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
									  unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
									  unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,	 
									  unsigned int PART_COLUMN,unsigned int PART_LINE);										
										
void EPD_Part_Num_S2(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
									  unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,	 
									  unsigned int PART_COLUMN,unsigned int PART_LINE);				

void EPD_Display(const unsigned char* datasBW,const unsigned char* datasRW);												 
#endif
/***********************************************************
						end file
***********************************************************/
												 




