#include "stm32f10x_rcc.h"

void rcc_init()
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|
							RCC_APB2Periph_GPIOB|
							RCC_APB2Periph_GPIOC|
							RCC_APB2Periph_TIM1|
							RCC_APB2Periph_AFIO|
							RCC_APB2Periph_USART1, 
							ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3|
							RCC_APB1Periph_TIM4|
							RCC_APB1Periph_TIM6|
							RCC_APB1Periph_TIM5|
							RCC_APB1Periph_TIM7|
							RCC_APB1Periph_USART3|
							RCC_APB1Periph_USART2,
							ENABLE);
}

