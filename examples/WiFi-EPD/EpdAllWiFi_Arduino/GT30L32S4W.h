#ifndef GT30L32S4W_H
#define GT30L32S4W_H		

//GB2312
#define GB2312_12X12 	 16*12/8  //16*12
#define GB2312_16X16 	 16*16/8  //16*16
#define GB2312_24X24 	 24*24/8  //24*24
#define GB2312_32X32 	 32*32/8  //32*32
//ASCII
#define ASCII_5X7	  8*7/8   //5*7
#define ASCII_7X8	  8*8/8   //7*8
#define ASCII_6X12	8*12/8  //8*12
#define ASCII_8X16	8*16/8  //8*16
#define ASCII_12X24	16*24/8 //16*24
#define ASCII_16X32	16*32/8 //16*32

/************** GB2312 Font base address *****************/
#define BaseAdd_12X12	0x00000
#define BaseAdd_16X16	0x2C9D0
#define BaseAdd_24X24	0x68190
#define BaseAdd_32X32	0xEDF00
/************** ASCII Character base address*****************/
#define ASCIIAdd_5X7	0x1DDF80
#define ASCIIAdd_7X8	0x1DE280
#define ASCIIAdd_6X12	0x1DBE00
#define ASCIIAdd_8X16	0x1DD780
#define ASCIIAdd_12X24	0x1DFF00
#define ASCIIAdd_16X32	0x1E5A50

//GT30 CS
//#define GT30_CS_0	GPIO_ResetBits(GPIOA,GPIO_Pin_3) //GT30 film selection
//#define GT30_CS_1	GPIO_SetBits(GPIOA,GPIO_Pin_3)		

#define GT30_CS_0 digitalWrite(T3,LOW) //GT30 film selection
#define GT30_CS_1 digitalWrite(T3,HIGH)    

#define W25Q_CS1_1 digitalWrite(T2,HIGH) //W25Qxx Disable
#define EPD_CS_1 digitalWrite(T7,HIGH) //E-paper Disable
////////////////////////////////////////////////////////////////////////////
 
//Instruction list

#define GT30L32S4W_Read 0x03
#define GT30L32S4W_Fast_Read 0x0B


extern unsigned char datas[2000];

void GT30L32S4W_Init(void); //GT30L32S4W  initialization
void GT30L32S4W_SPI_Read(unsigned long Address,unsigned long byte_long,unsigned char *p_arr);
void GB2312_BUF(const char *GBCode, unsigned char *BUF,unsigned char mode);
void ASCII_BUF(const char *ASCIICode, unsigned char *BUF,unsigned char mode);
void ASCII_BUF_Char(char ASCIICode, unsigned char *BUF,unsigned char mode);
#endif
