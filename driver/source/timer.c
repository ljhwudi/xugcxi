
#include "stm32f10x_tim.h"

void timer3_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStruct);

	TIM_ClearFlag( TIM3, TIM_FLAG_Update);
	TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				// PWM1模式
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	// 输出使能
	TIM_OCInitStruct.TIM_Pulse = 0;								// 初始的比较值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;		// 输出极性为低电平.
	TIM_OC1Init( TIM3, &TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig( TIM3, ENABLE);							// 使能自动重装载的预装载功能
	// 5\使能定时器
	TIM_Cmd( TIM3, ENABLE);
}

void timer1_init()
{
	#ifndef __TIMER1_INIT__
	#define __TIMER1_INIT__
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
    TIM_TimeBaseInitStructure.TIM_Period = 65535;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

//    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	TIM_Cmd( TIM1, DISABLE);
	
	#endif  //__TIMER1_INIT__
}

void timer4_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStruct.TIM_Period = 50000-1;
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseInitStruct);

	TIM_ClearFlag( TIM4, TIM_FLAG_Update);
	TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE);
}

void timer5_init()
{
	#ifndef __TIMER5_INIT__
	#define __TIMER5_INIT__
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStruct.TIM_Period = 20-1;
	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseInitStruct);

	TIM_ClearFlag( TIM5, TIM_FLAG_Update);
	TIM_ITConfig( TIM5, TIM_IT_Update, ENABLE);

	#endif  //__TIMER5_INIT__
}

void timer6_init()
{
	#ifndef __TIMER6_INIT__
	#define __TIMER6_INIT__
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStruct.TIM_Period = 50000-1;
	TIM_TimeBaseInit( TIM6, &TIM_TimeBaseInitStruct);

	TIM_ClearFlag( TIM6, TIM_FLAG_Update);
	TIM_ITConfig( TIM6, TIM_IT_Update, ENABLE);

	#endif  //__TIMER6_INIT__
}

void timer7_init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
    TIM_TimeBaseInitStructure.TIM_Period = 65535;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);

//    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	TIM_Cmd( TIM7, DISABLE);
}

