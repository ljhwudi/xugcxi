#include "stm32f10x_tim.h"
#include "nvic.h"
#include "uart.h"
#include "timer.h"
#include "systick.h"
#include "atgm336h.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"

uint8_t sim900a_flag;
uint8_t t4_t;
extern _SaveData Save_Data;
char latitude_unicode[50];
char longtitude_unicode[50];
char unicode_unit[5];

void sim900a_init()
{
	usart2_init();
//	timer4_init();
//	timer4_nvic_init();
}

static void sim_send_message()
{
	char endcode[2] = { 0x1a, 0};
	usart2_print(endcode);
}

static char *str_2_unicode(char ch)
{
	if((ch>='0')&&(ch<='9'))
	{
		unicode_unit[0] = '0';
		unicode_unit[1] = '0';
		unicode_unit[2] = '3';
		unicode_unit[3] = ch;
	}

	if((ch>='A')&&(ch<='I'))
	{
		unicode_unit[0] = '0';
		unicode_unit[1] = '0';
		unicode_unit[2] = '4';
		unicode_unit[3] = ch-'A'+'1';
	}

	if((ch>='J')&&(ch<='O'))
	{
		unicode_unit[0] = '0';
		unicode_unit[1] = '0';
		unicode_unit[2] = '4';
		unicode_unit[3] = ch-'J'+'A';
	}

	if((ch>='P')&&(ch<='Y'))
	{
		unicode_unit[0] = '0';
		unicode_unit[1] = '0';
		unicode_unit[2] = '5';
		unicode_unit[3] = ch-'P'+'0';
	}

	if(ch == 'Z')
	{
		unicode_unit[0] = '0';
		unicode_unit[1] = '0';
		unicode_unit[2] = '5';
		unicode_unit[3] = 'A';
	}

	if(ch == '.')
	{
		unicode_unit[0] = '0';
		unicode_unit[1] = '0';
		unicode_unit[2] = '2';
		unicode_unit[3] = 'E';
	}

	return unicode_unit;
}

 void latitude_str2unicode()
{
	char floattypelatitude[20] = {0};
	char *temp;
	int latitude_integer = (int)atof(Save_Data.latitude)/100;
	sprintf(floattypelatitude,"%.5f",(float)((atof(Save_Data.latitude+2))/60.0)+latitude_integer);
	temp = floattypelatitude;
	for(;*temp;temp++)
	{
		strcat(latitude_unicode,str_2_unicode(*temp));
	}
}

 void longtitude_str2unicode()
{
	char floattypelongtitude[] = {0};
	char *temp;
	int longtitude_integer = (int)atof(Save_Data.longitude)/100;
	sprintf(floattypelongtitude,"%.5f",(float)((atof(Save_Data.longitude+3))/60.0)+longtitude_integer);
	temp = floattypelongtitude;
	for(;*temp;temp++)
	{
		strcat(longtitude_unicode,str_2_unicode(*temp));
	}
}

void sim900a_send_location_mes()
{
	char context[200] = {0};
	char E_Wt[5] = {0};
	char N_St[5] = {0};
	
	if(Save_Data.isGetData == true && Save_Data.isParseData == true && Save_Data.isUsefull == true)
	{
		latitude_str2unicode();
		longtitude_str2unicode();
		memcpy(E_Wt,str_2_unicode(Save_Data.E_W[0]),4);
		memcpy(N_St,str_2_unicode(Save_Data.N_S[0]),4);
	}
	
	sprintf(context,"%s%s0020%s%s5783573E68765DF26EE1",
	E_Wt,longtitude_unicode,N_St,latitude_unicode);
	
	usart2_print("AT+CSCS=\"UCS2\"\r\n");
	SYSTICK_DelayMs(50);
	usart2_print("AT+CMGS=\"00310035003600310036003300320038003800380034\"\r\n");
	SYSTICK_DelayMs(50);
	usart2_print(context);
	SYSTICK_DelayMs(50);
	sim_send_message();
}

void TIM4_IRQHandler()
{
	static uint8_t t3ct;
	if(TIM_GetITStatus( TIM4, TIM_IT_Update) != RESET)
	{
	//	printf("tim3 interrupt!\n");
		if(sim900a_flag == 1)
		{
			if(t3ct == 0)
			{
				usart2_print("AT+CSCS=\"UCS2\"\r\n");
			}
			else if(t3ct == 1)
			{
				usart2_print("AT+CMGS=\"00310035003600310036003300320038003800380034\"\r\n");
			}
			else if(t3ct == 2)
			{
				usart2_print("53174EAC0020003100310036003A003200380045002000330039003A00350034004E");
			}
			else if(t3ct == 3)
			{
				sim_send_message();
				TIM_Cmd( TIM4, DISABLE);
				t3ct = 0;
			}
			t3ct++;
		}
		else
		{
			if(t4_t == 200)
			{
				t4_t = 0;
				sim900a_flag = 1;
			}
			else
			{
				t4_t++;
			}
		}
		TIM_ClearITPendingBit( TIM4, TIM_IT_Update);
	}
}



