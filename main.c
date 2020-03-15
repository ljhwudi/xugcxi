#include "led.h"
#include "es08ma.h"
#include "k1.h"
#include "uart.h"
#include "rcc.h"
#include "stdio.h"
#include "systick.h"
#include "hcsr04.h"
#include "sim900a.h"
#include "misc.h"
#include "atgm336h.h"

#define MAIN_DELAY 500

extern float distance1_value;
extern float distance2_value;
uint8_t issended;

#ifdef __SIM900A_TEST__
uint8_t test_flag;
#endif  //__SIM900A_TEST__

extern uint8_t isfulled;
extern _SaveData Save_Data;
extern char latitude_unicode[50];
extern char longtitude_unicode[50];

int main()
{
	uint8_t tosendmessage = 0;
	uint8_t gpsparse_flag = 0;
	
	rcc_init();
	SYSTICK_Config(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置优先级分组

	led_init();
	k1_Init();
	es08ma_init();
	usart1_init();
	sim900a_init();
	atgm336h_init();
	hcsr04_1_init();
	hcsr04_2_init();

	for(;;)
	{	
		SYSTICK_DelayMs(MAIN_DELAY);
		printf("-----------------------------------------\n");
		printf("distance2 = %.2f cm \n",distance2_value);
		printf("distance1 = %.2f cm \n",distance1_value);
//		printf("%s\n",Save_Data.GPS_Buffer);
//		printf("%s\n",Save_Data.latitude);
//		printf("%s\n",Save_Data.longitude);
//		printf("%s\n",latitude_unicode);
//		printf("%s\n",longtitude_unicode);
//		printf("isfulled = %d \n issended = %d\n",isfulled,issended);
		if(issended == 0)
		{
			if(isfulled == 1)
			{
				tosendmessage++;
				if(tosendmessage == 10000/MAIN_DELAY)
				{
					tosendmessage = 0;
					issended = 1;
					sim900a_send_location_mes();
				}
			}
			else
			{
				tosendmessage = 0;
			}
		}
		
		if(gpsparse_flag == 4)
		{
			gpsparse_flag = 0;
			parsegpsbuffer();
		}
			
		gpsparse_flag++;
		
		#ifdef __SIM900A_TEST__
		if(test_flag == 1)
		{
			test_flag = 0;
			sim900a_send_location_mes();
		}
		#endif  //__SIM900A_TEST__
		
	}
}
