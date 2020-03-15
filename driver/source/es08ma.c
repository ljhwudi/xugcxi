#include "nvic.h"
#include "stm32f10x_tim.h"
#include "led.h"
#include "gpio.h"
#include "timer.h"

uint16_t es08ma_flag;

void es08ma_open()
{
	TIM_SetCompare1( TIM3, 950);
	led_on();
}

void es08ma_close()
{
	TIM_SetCompare1( TIM3, 1950);
	led_off();
}

void es08ma_init(void)
{
	es08ma_gpio_init();
	timer3_init();
	timer3_nvic_init();
	es08ma_close();
}

void es08ma_open_5s()
{
	es08ma_open();
	es08ma_flag = 0;
	NVIC_EnableIRQ( TIM3_IRQn);
}

void TIM3_IRQHandler()
{
	if(TIM_GetITStatus( TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit( TIM3, TIM_IT_Update);
		if(es08ma_flag == 250)
		{
			es08ma_flag = 0;
			es08ma_close();
			NVIC_DisableIRQ( TIM3_IRQn);
		}
		es08ma_flag++;
	}
}
