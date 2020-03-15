#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "gpio.h"

#define	K1_GPIO_PortSourceGPIOX			GPIO_PortSourceGPIOA
#define K1_GPIO_PinSource				GPIO_PinSource0
#define K1_EXTI_Line					EXTI_Line0

#define	HCSR04_1_GPIO_PortSourceGPIOX	GPIO_PortSourceGPIOB
#define HCSR04_1_GPIO_PinSource			GPIO_PinSource7
#define HCSR04_1_EXTI_Line				EXTI_Line7

#ifndef __HCSR04_2_CHANGE_PIN__
#define	HCSR04_2_GPIO_PortSourceGPIOX	GPIO_PortSourceGPIOB
#define HCSR04_2_GPIO_PinSource			GPIO_PinSource9
#define HCSR04_2_EXTI_Line				EXTI_Line9
#else
#define	HCSR04_2_GPIO_PortSourceGPIOX	GPIO_PortSourceGPIOA
#define HCSR04_2_GPIO_PinSource			GPIO_PinSource6
#define HCSR04_2_EXTI_Line				EXTI_Line6

#endif

void k1_exti_init()
{
	GPIO_EXTILineConfig(K1_GPIO_PortSourceGPIOX, K1_GPIO_PinSource); //配置外部中断线

	EXTI_InitTypeDef EXTI_InitStructure; 
	EXTI_InitStructure.EXTI_Line = K1_EXTI_Line; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure); 
}

void hcsr04_1_exti_init()
{
	GPIO_EXTILineConfig(HCSR04_1_GPIO_PortSourceGPIOX, HCSR04_1_GPIO_PinSource); //配置外部中断线

	EXTI_InitTypeDef EXTI_InitStructure; 
	EXTI_InitStructure.EXTI_Line = HCSR04_1_EXTI_Line; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure); 
}

void hcsr04_2_exti_init()
{
	GPIO_EXTILineConfig(HCSR04_2_GPIO_PortSourceGPIOX, HCSR04_2_GPIO_PinSource); //配置外部中断线

	EXTI_InitTypeDef EXTI_InitStructure; 
	EXTI_InitStructure.EXTI_Line = HCSR04_2_EXTI_Line; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure); 
}

