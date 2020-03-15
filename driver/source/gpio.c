#include "stm32f10x_gpio.h"
#include "gpio.h"

#define USART2_TX_PORT			GPIOA
#define USART2_TX_PIN			GPIO_Pin_2

#define USART2_RX_PORT			GPIOA
#define USART2_RX_PIN			GPIO_Pin_3

#define USART1_TX_PORT			GPIOA
#define USART1_TX_PIN			GPIO_Pin_9

#define USART1_RX_PORT			GPIOA
#define USART1_RX_PIN			GPIO_Pin_10

void led_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = LED_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( LED_PORT, &GPIO_InitStruct);
}

void k1_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin = K1_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(K1_PORT, &GPIO_InitStructure);	
}

void es08ma_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_PinRemapConfig( GPIO_FullRemap_TIM3, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = ES08MA_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init( ES08MA_PORT, &GPIO_InitStruct);
}

void hcsr04_1_gpio_init()
{
	GPIO_InitTypeDef GPIO;

    GPIO.GPIO_Pin = HCSR04_1_TRIG_PIN;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(HCSR04_1_TRIG_PORT, &GPIO);
	GPIO_ResetBits( HCSR04_1_TRIG_PORT, HCSR04_1_TRIG_PIN);
	//Register IO 
    GPIO.GPIO_Pin = HCSR04_1_ECHO_PIN;
    GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HCSR04_1_ECHO_PORT, &GPIO);
}

void hcsr04_2_gpio_init()
{
	GPIO_InitTypeDef GPIO;

    GPIO.GPIO_Pin = HCSR04_2_TRIG_PIN;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(HCSR04_2_TRIG_PORT, &GPIO);
	GPIO_ResetBits( HCSR04_2_TRIG_PORT, HCSR04_2_TRIG_PIN);
	//Register IO 
    GPIO.GPIO_Pin = HCSR04_2_TRIG_PIN;
    GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HCSR04_2_ECHO_PORT, &GPIO);
}

void usart2_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = USART2_TX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( USART2_TX_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = USART2_RX_PIN;
	GPIO_Init( USART2_RX_PORT, &GPIO_InitStruct);
}

void usart1_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = USART1_TX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( USART1_TX_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = USART1_RX_PIN;
	GPIO_Init( USART1_RX_PORT, &GPIO_InitStruct);
}
