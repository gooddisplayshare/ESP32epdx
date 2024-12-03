#ifndef FONTS_H
#define FONTS_H

/*锟斤拷锟斤拷锟斤拷锟轿拷锟斤拷藕锟�24 (32x41) */
#define MAX_HEIGHT_FONT         41
#define MAX_WIDTH_FONT          32
#define OFFSET_BITMAP           

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

//ASCII
typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;


//GB2312
typedef struct                                          // 锟斤拷锟斤拷锟斤拷模锟斤拷锟捷结构
{
  unsigned char index[2];                               // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
  const char matrix[MAX_HEIGHT_FONT*MAX_WIDTH_FONT/8];  // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
}CH_CN;


typedef struct
{    
  const CH_CN *table;
  uint16_t size;
  uint16_t ASCII_Width;
  uint16_t Width;
  uint16_t Height;
  
}cFONT;

extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;

extern cFONT Font12CN;
extern cFONT Font24CN;


//锟街匡拷锟侥硷拷
extern const CH_CN Font12CN_Table[];
#ifdef __cplusplus
}
#endif
  
#endif /* __FONTS_H */
 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
