
#ifndef __ATGM336H_H__
#define __ATGM336H_H__

#include "stm32f10x.h"

#define GPS_Buffer_Length 100
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2 

typedef struct SaveData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//是否获取到GPS数据
	char isParseData;	//是否解析完成
	char UTCTime[UTCTime_Length];		//UTC时间
	char latitude[latitude_Length];		//纬度
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//经度
	char E_W[E_W_Length];		//E/W
	char isUsefull;		//定位信息是否有效
} _SaveData;

typedef struct timeandloaction_data
{
	uint8_t is_real;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	float latitude;  //纬度
	char rN_S;
	float longitude;  //经度
	char rE_W;
}_timeandloaction_data;

void atgm336h_init(void);
void parsegpsbuffer(void);

#endif  //__ATGM336H_H__
