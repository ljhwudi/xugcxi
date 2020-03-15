#include "uart.h"
#include "atgm336h.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

_SaveData Save_Data;
//_timeandloaction_data tal_data;

#define BUF_SIZE		200

char usart3_rx_buf[BUF_SIZE];

void atgm336h_init()
{
	usart3_init();
}

float getlatitude()
{
	float value;

	value = (Save_Data.latitude[0]-'0')*10
		   +(Save_Data.latitude[1]-'0')
		   +
		   (
		    (Save_Data.latitude[2]-'0')*10
		   +(Save_Data.latitude[3]-'0')
		   +(Save_Data.latitude[4]-'0')*0.1
		   +(Save_Data.latitude[5]-'0')*0.01
		   +(Save_Data.latitude[6]-'0')*0.001
		   +(Save_Data.latitude[7]-'0')*0.0001
		   );

	return value;
}

float getlongtitude()
{
	float value;

	value = (Save_Data.longitude[0]-'0')*100
		   +(Save_Data.longitude[1]-'0')*10
		   +(Save_Data.longitude[2]-'0')
		   +
		   (
		    (Save_Data.longitude[3]-'0')*10
		   +(Save_Data.longitude[4]-'0')
		   +(Save_Data.longitude[5]-'0')*0.1
		   +(Save_Data.longitude[6]-'0')*0.01
		   +(Save_Data.longitude[7]-'0')*0.001
		   +(Save_Data.longitude[8]-'0')*0.0001
		   );

	return value;
}


void parsegpsbuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
//		printf("%s\n",Save_Data.GPS_Buffer);

		
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
				{
					Save_Data.isUsefull = false;	//解析错误
					break;
				}
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

				}
				else
				{
					Save_Data.isUsefull = false;	//解析错误
					break;
				}
			}


		}
	}
}


void USART3_IRQHandler(void) 
{
	uint8_t usart3_recv_byte;
	static uint8_t point;
	if(USART_GetITStatus( USART3, USART_IT_RXNE) != RESET)
	{
		usart3_recv_byte = USART_ReceiveData( USART3);
//		USART_SendData( USART1, usart3_recv_byte);

		if(usart3_recv_byte == '$')
		{
			point = 0;
		}

		usart3_rx_buf[point++] = usart3_recv_byte;

		if(usart3_rx_buf[0] == '$' && usart3_rx_buf[4] == 'M' && usart3_rx_buf[5] == 'C')
		{
			if(usart3_recv_byte == '\n')
			{
				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //清空
				memcpy(Save_Data.GPS_Buffer, usart3_rx_buf, point); 	//保存数据
				Save_Data.isGetData = true;
				point = 0;
				memset(usart3_rx_buf, 0, BUF_SIZE);   
			}
		}

		if(point >= BUF_SIZE)
		{
			point = BUF_SIZE-1;
		}
		
		USART_ClearITPendingBit( USART3, USART_IT_RXNE);
	}
}


