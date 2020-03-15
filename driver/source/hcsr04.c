#include "systick.h"
#include "stdio.h"
#include "timer.h"
#include "gpio.h"
#include "nvic.h"
#include "exti.h"
#include "stm32f10x_gpio.h"
#include "led.h"
#include "es08ma.h"

float distance1_value;
float distance2_value;
uint8_t isfulled;

void hcsr04_1_init()
{
	#ifndef __HCSR04_1_INIT__
	#define __HCSR04_1_INIT__
	
	hcsr04_1_gpio_init();
	timer1_init();

	#ifndef __HCSR04_COMMON_INIT__
	#define __HCSR04_COMMON_INIT__
	
	timer5_init();
	timer5_nvic_init();
	exti7and9_nvic_init();
	TIM_Cmd( TIM5, ENABLE);
	
	#endif  //__HCSR04_COMMON_INIT__
	
	hcsr04_1_exti_init();

	
	#endif  //__HCSR04_1_INIT__
}

void hcsr04_2_init()
{
	#ifndef __HCSR04_2_INIT__
	#define __HCSR04_2_INIT__
	
	hcsr04_2_gpio_init();
	timer7_init();

	#ifndef __HCSR04_COMMON_INIT__
	#define __HCSR04_COMMON_INIT__

	timer5_init();
	timer5_nvic_init();
	exti7and9_nvic_init();
	TIM_Cmd( TIM5, ENABLE);

	#endif  //__HCSR04_COMMON_INIT__
		
	hcsr04_2_exti_init();

	#endif  //__HCSR04_2_INIT__
}

void TIM5_IRQHandler()
{
	static uint16_t tim5_handler_t;
	if(TIM_GetITStatus( TIM5, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit( TIM5, TIM_IT_Update);
		if(tim5_handler_t == 0)
		{
			#ifdef __HCSR04_1_INIT__
			GPIO_SetBits( HCSR04_1_TRIG_PORT, HCSR04_1_TRIG_PIN);
			#endif

			#ifdef __HCSR04_2_INIT__
			GPIO_SetBits( HCSR04_2_TRIG_PORT, HCSR04_2_TRIG_PIN);
			#endif
		}
		else if(tim5_handler_t == 1)
		{
			#ifdef __HCSR04_1_INIT__
			GPIO_ResetBits( HCSR04_1_TRIG_PORT, HCSR04_1_TRIG_PIN);
			#endif

			#ifdef __HCSR04_2_INIT__
			GPIO_ResetBits( HCSR04_2_TRIG_PORT, HCSR04_2_TRIG_PIN);
			#endif
		}
		tim5_handler_t = (tim5_handler_t+1)%2500;
	}
}

void EXTI9_5_IRQHandler()
{
	#ifdef __HCSR04_1_INIT__
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		if(GPIO_ReadInputDataBit( HCSR04_1_ECHO_PORT, HCSR04_1_ECHO_PIN) == SET)
		{
			TIM_SetCounter( TIM1, 0);
			TIM_Cmd( TIM1, ENABLE);
		}
		else
		{
			TIM_Cmd( TIM1, DISABLE);
			distance1_value = (float)((float)(TIM_GetCounter(TIM1) * 340) / 20000.0);
			if(distance1_value < 20.0)
			{
				isfulled = 1;
			}
			else
			{
				isfulled = 0;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	#endif  //__HCSR04_1_INIT__

	#ifdef __HCSR04_2_INIT__
	#ifndef __HCSR04_2_CHANGE_PIN__
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	#else
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	#endif  //__HCSR04_2_CHANGE_PIN__
	{
		if(GPIO_ReadInputDataBit( HCSR04_2_ECHO_PORT, HCSR04_2_ECHO_PIN) == SET)
		{
			TIM_SetCounter( TIM7, 0);
			TIM_Cmd( TIM7, ENABLE);
		}
		else
		{
			TIM_Cmd( TIM7, DISABLE);
			distance2_value = (float)((float)(TIM_GetCounter(TIM7) * 340) / 20000.0);
//			printf("TIM7->cnt = %d\n",TIM_GetCounter(TIM7));
//			printf("distance2 = %.2f cm \n",distance2_value);
			if(distance2_value < 30.0)
			{
				es08ma_open_5s();
			}
		}
		#ifndef __HCSR04_2_CHANGE_PIN__
		EXTI_ClearITPendingBit(EXTI_Line9); 
		#else
		EXTI_ClearITPendingBit(EXTI_Line6); 
		#endif  //__HCSR04_2_CHANGE_PIN__
	}
	#endif  //__HCSR04_2_INIT__
}

#if 0

static void hcsr04_1_US_SendStartSignal(void)
{
	GPIO_SetBits( HCSR04_1_TRIG_PORT, HCSR04_1_TRIG_PIN);
	SYSTICK_DelayUs(20);
	GPIO_ResetBits( HCSR04_1_TRIG_PORT, HCSR04_1_TRIG_PIN);

}

static void hcsr04_2_US_SendStartSignal(void)
{
	GPIO_SetBits( HCSR04_2_TRIG_PORT, HCSR04_2_TRIG_PIN);
	SYSTICK_DelayUs(20);
	GPIO_ResetBits( HCSR04_2_TRIG_PORT, HCSR04_2_TRIG_PIN);

}


float hcsr04_1_get_distance()
{
	float value;

	hcsr04_1_US_SendStartSignal();
	while(GPIO_ReadInputDataBit( HCSR04_1_ECHO_PORT, HCSR04_1_ECHO_PIN) == 0);
	TIM_SetCounter( TIM1, 0);
	TIM_Cmd( TIM1, ENABLE);
//	printf("TIM1->CNT = %d \n",TIM_GetCounter(TIM1));
	while(GPIO_ReadInputDataBit( HCSR04_1_ECHO_PORT, HCSR04_1_ECHO_PIN) == 1);
	TIM_Cmd( TIM1, DISABLE);
//	printf("TIM1->CNT = %d \n",TIM_GetCounter(TIM1));
	value = (float)((float)(TIM_GetCounter(TIM1) * 340) / 20000.0);

	return value;
}

float hcsr04_2_get_distance()
{
	float value;

	hcsr04_2_US_SendStartSignal();
	while(GPIO_ReadInputDataBit( HCSR04_2_ECHO_PORT, HCSR04_2_ECHO_PIN) == 0);
	TIM_SetCounter( TIM1, 0);
	TIM_Cmd( TIM1, ENABLE);
//	printf("TIM1->CNT = %d \n",TIM_GetCounter(TIM1));
	while(GPIO_ReadInputDataBit( HCSR04_2_ECHO_PORT, HCSR04_2_ECHO_PIN) == 1);
	TIM_Cmd( TIM1, DISABLE);
//	printf("TIM1->CNT = %d \n",TIM_GetCounter(TIM1));
	value = (float)((float)(TIM_GetCounter(TIM1) * 340) / 20000.0);

	return value;
}

#endif
