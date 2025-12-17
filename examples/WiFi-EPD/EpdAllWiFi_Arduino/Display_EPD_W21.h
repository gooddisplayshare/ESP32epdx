#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   800 
#define EPD_HEIGHT  480
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  


//Full screen update display
void EPD_Init(void); 
void EPD_Init_180(void);  
void EPD_WhiteScreen_ALL(const unsigned char *datas);
void EPD_WhiteScreen_White(void);
void EPD_WhiteScreen_Black(void);

//Partial update display 
void EPD_Init_Part(void);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_WhiteScreen_White_Basemap(void);
void EPD_Dis_PartAll(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Dis_Part_Time(unsigned int x_start,unsigned int y_start,
                        const unsigned char * datas_A,const unsigned char * datas_B,
                        const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE);                    
//Fast update display
void EPD_Init_Fast(void);
void EPD_WhiteScreen_ALL_Fast(const unsigned char *datas);   
//4 Gray
void EPD_Init_4G(void);
void EPD_WhiteScreen_ALL_4G(const unsigned char *datas);		
void Display_4Level_Gray(void);

//WiFi
void EPD_Update_GUI(void);
void connectToWiFi(const char* ssid, const char* password);
void connectToWiFiStatic(const char* ssid, const char* password);
void WiFi_Serialconfiguration(void);
void Reset_reconnectToWiFi(void); //复位并重连WiFi
void EPD_WhiteScreen_GUI(const unsigned char* datasBW);
void EPD_WhiteScreen_GUI_Wrong(const unsigned char* datasBW);
void EPD_WhiteScreen_GUI_WiFiConfigOk(void);
void EPD_WhiteScreen_GUI_WiFiConfigWrong(void); //Wrong--反色	


void EPD_Init750_BW(void);
void EPD_Init750_BWR(void);
void EPD_Init750_BWRY(void);

void EPD_HW_Init1330_BW(void);
void EPD_Init1330_BWRY(void);
void EPD_Update(void);
void EPD_Update_GUI(void);




void EPD_WhiteScreen_ALL_UC_BW(const unsigned char *datas,unsigned int datasize);
void EPD_WhiteScreen_ALL_UC_RW(const unsigned char *datas,unsigned int datasize);

void EPD_WhiteScreen_ALL_SSD1685_BW(const unsigned char *datas,unsigned int datasize);
void EPD_WhiteScreen_ALL_SSD_BW(const unsigned char *datas,unsigned int datasize);
void EPD_WhiteScreen_ALL_SSD_RW(const unsigned char *datas,unsigned int datasize);
void EPD_WhiteScreen_ALL_SSD_BWRY(const unsigned char *datas,unsigned int datasize);
//单色三色
void EPD_HW_Init_097(void); 
void EPD_HW_Init_153(void); 
void EPD_HW_Init_154(void); 
void EPD_HW_Init_213(void); 
void EPD_HW_Init_266(void); 
void EPD_HW_Init_267(void); 
void EPD_HW_Init_270(void); 
void EPD_HW_Init_290(void); 
void EPD_HW_Init_291(void); 
void EPD_HW_Init_370(void); 
void EPD_HW_Init_420(unsigned char mode); //0--bw   1--rw
void EPD_DeepSleep(void);
void EPD_DeepSleep_UC(void);
void EPD_Update_UC(void);
void EPD_Update(void);
//四色
void EPD_HW_Init_BWRY_097(void);
void EPD_HW_Init_BWRY_153(void);
void EPD_HW_Init_BWRY_154(void);
void EPD_HW_Init_BWRY_213(void);
void EPD_HW_Init_BWRY_266(void);
void EPD_HW_Init_BWRY_267(void);
void EPD_HW_Init_BWRY_270(void);
void EPD_HW_Init_BWRY_290(void);
void EPD_HW_Init_BWRY_291(void);
void EPD_HW_Init_BWRY_370(void);
void EPD_HW_Init_BWRY_420(void);
void EPD_Update_BWRY(void);
void EPD_DeepSleep_BWRY(void);

#endif
