#include "gt30l32s4w.h" 
#include <arduino.h>
#include <SPI.h>

unsigned char datas[2000];
void GT30L32S4W_Init(void)
{	

    pinMode(T3, OUTPUT);  //CS1--GT30
    pinMode(T2, OUTPUT);  //CS2 --W25Q
		pinMode(T7, OUTPUT);  //CS--E-paper		 
    GT30_CS_1;		//GT30  Enable
    W25Q_CS1_1;   //W25Qxx  Disable
    EPD_CS_1;  //E-paper Disable 

}  
//Reading method: 1. Send read command + 3 brother internal code address 
//2. Receive and read data

unsigned char GT30_SPI1_ReadWriteByte(unsigned char data)
{
  unsigned char d_read;	
 //d_read=SPI1_ReadWriteByte(data);          //Read a byte
  d_read=SPI.transfer(data);
 return d_read; //Return the most recently received data via SPIx  
}


void GenitopZk_Address(unsigned long Address) 
{
	unsigned char AddH, AddM, AddL;
	
	AddH = Address >> 16;
	AddM = Address >> 8;
	AddL = Address;
	
	GT30_SPI1_ReadWriteByte(0x03);	//General reading method
	GT30_SPI1_ReadWriteByte(AddH);
	GT30_SPI1_ReadWriteByte(AddM);
	GT30_SPI1_ReadWriteByte(AddL);
	
//	SPI2_ReadWriteByte(0x0B);	//Fast reading method
//	SPI2_ReadWriteByte(AddH);
//	SPI2_ReadWriteByte(AddM);
//	SPI2_ReadWriteByte(AddL);
//	SPI2_ReadWriteByte(0xff);
}

////////////////////Chinese character//////////////////////////////////////////////////////////////////////////////////
/********************************************************************************
  * @brief  GB2312_BUF Chinese character reading
  * @param  *GBCode	Chinese internal code
  * @param  *BUF	Read data
  * @param  mode	Chinese Character Mode
  * @retval none
  *******************************************************************************/
void GB2312_BUF(const char *GBCode, unsigned char *BUF,unsigned char mode)     
{
	unsigned int i;
	unsigned char MSB;			//The upper 8 bits of the inner code of Chinese characters
	unsigned char LSB;			//The lower 8 bits of the inner code of Chinese characters
	unsigned long BaseAdd;	//Font base address
	unsigned long Address;	//The address of the character in the chip
	unsigned char temp;
  switch(mode)
	{
		case GB2312_12X12:{
			BaseAdd = BaseAdd_12X12;
		  temp=24;}
		break;
		case GB2312_16X16:{
			BaseAdd = BaseAdd_16X16;
		  temp=32;}
		break;
		case GB2312_24X24:{
			BaseAdd = BaseAdd_24X24;
		  temp=72;}
		break;	
		case GB2312_32X32:{
			BaseAdd = BaseAdd_32X32;
		  temp=128;}
		break;				
		default:
		break;					
		}
	
	MSB = *GBCode;
	LSB = *(++GBCode);
	
	//Calculate character address value
	if(MSB >= 0xA1 && MSB <= 0xA9 && LSB >= 0xA1){
		Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1)) * temp + BaseAdd;
	}
	else if(MSB >= 0xB0 && MSB <= 0xF7 && LSB >= 0xA1){
		Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1) + 846) * temp + BaseAdd;
	}

	//Get character bitmap data
	GT30_CS_0;
	GenitopZk_Address(Address);
	for(i = 0; i < mode; i++){
		datas[i]=GT30_SPI1_ReadWriteByte(0xFF);
	}
	GT30_CS_1;
}
void GB2312_BUF_Char(const char *GBCode, unsigned char *BUF,unsigned char mode)     
{
	unsigned int i;
	unsigned char MSB;			//The upper 8 bits of the inner code of Chinese characters
	unsigned char LSB;			//The lower 8 bits of the inner code of Chinese characters
	unsigned long BaseAdd;	//Font base address
	unsigned long Address;	//The address of the character in the chip
	unsigned char temp;
  switch(mode)
	{
		case GB2312_12X12:{
			BaseAdd = BaseAdd_12X12;
		  temp=24;}
		break;
		case GB2312_16X16:{
			BaseAdd = BaseAdd_16X16;
		  temp=32;}
		break;
		case GB2312_24X24:{
			BaseAdd = BaseAdd_24X24;
		  temp=72;}
		break;	
		case GB2312_32X32:{
			BaseAdd = BaseAdd_32X32;
		  temp=128;}
		break;				
		default:
		break;					
		}
	
	MSB = *GBCode;
	LSB = *(++GBCode);
	
	//Calculate character address value
	if(MSB >= 0xA1 && MSB <= 0xA9 && LSB >= 0xA1){
		Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1)) * temp + BaseAdd;
	}
	else if(MSB >= 0xB0 && MSB <= 0xF7 && LSB >= 0xA1){
		Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1) + 846) * temp + BaseAdd;
	}

	//Get character bitmap data
	GT30_CS_0;
	GenitopZk_Address(Address);
	for(i = 0; i < mode; i++){
		datas[i]=GT30_SPI1_ReadWriteByte(0xFF);
	}
	GT30_CS_1;
}

/////////////////////ASCII code///////////////////////////////////////////////////////////////////////////////////
/********************************************************************************
  
  * @brief  ASCII_BUF ASCII Character reading
  * @param  *ASCIICode	ASCII Character code
  * @param  *BUF		Character buffer data
  * @param  mode	  Character Mode
  * @retval none
  *******************************************************************************/
void ASCII_BUF(const char *ASCIICode, unsigned char *BUF,unsigned char mode)
{
	unsigned char i;
	unsigned long BaseAdd; //Font base address
	unsigned long Address; //The address of the character in the chip
	unsigned char temp;
  switch(mode)
	{
		case ASCII_5X7:{
			BaseAdd = ASCIIAdd_5X7;
		  temp=8;}
		break;
		case ASCII_7X8:{
			BaseAdd = ASCIIAdd_7X8;
		  temp=8;}
		break;
		case ASCII_6X12:{
			BaseAdd = ASCIIAdd_6X12;
		  temp=12;}
		break;	
		case ASCII_8X16:{
			BaseAdd = ASCIIAdd_8X16;
		  temp=16;}
		break;	
		case ASCII_12X24:{
			BaseAdd = ASCIIAdd_12X24;
		  temp=48;}
		break;	
		case ASCII_16X32:{
			BaseAdd = ASCIIAdd_16X32;
		  temp=64;}
		break;	
    default:
		break;
			
		}
	if(*ASCIICode >= 0x20 && *ASCIICode <= 0x7E){
		Address = (*ASCIICode - 0x20) * temp + BaseAdd;
	}

	GT30_CS_0;

	GenitopZk_Address(Address);
	for(i = 0; i < mode ; i++){  
		BUF[i]=GT30_SPI1_ReadWriteByte(0xFF);
	}
	
	GT30_CS_1;

}



void ASCII_BUF_Char(char ASCIICode, unsigned char *BUF,unsigned char mode)
{
	unsigned char i;
	unsigned long BaseAdd; //Font base address
	unsigned long Address; //The address of the character in the chip
	unsigned char temp;
  switch(mode)
	{
		case ASCII_5X7:{
			BaseAdd = ASCIIAdd_5X7;
		  temp=8;}
		break;
		case ASCII_7X8:{
			BaseAdd = ASCIIAdd_7X8;
		  temp=8;}
		break;
		case ASCII_6X12:{
			BaseAdd = ASCIIAdd_6X12;
		  temp=12;}
		break;	
		case ASCII_8X16:{
			BaseAdd = ASCIIAdd_8X16;
		  temp=16;}
		break;	
		case ASCII_12X24:{
			BaseAdd = ASCIIAdd_12X24;
		  temp=48;}
		break;	
		case ASCII_16X32:{
			BaseAdd = ASCIIAdd_16X32;
		  temp=64;}
		break;	
    default:
		break;
			
		}
	if(ASCIICode >= 0x20 && ASCIICode <= 0x7E){
		Address = (ASCIICode - 0x20) * temp + BaseAdd;
	}

	GT30_CS_0;

	GenitopZk_Address(Address);
	for(i = 0; i < mode ; i++){  
		BUF[i]=GT30_SPI1_ReadWriteByte(0xFF);	
	}
	
	GT30_CS_1;

}
