#include <stdio.h>
#include "stm32f10x_usart.h"
#include "gpio.h"
#include "nvic.h"

#define USART1_BAUDRATE 115200
#define USART2_BAUDRATE 115200
#define USART3_BAUDRATE 9600


void usart1_init()
{
	USART_InitTypeDef USART_InitStruct;
	
	usart1_gpio_init();
	
	USART_InitStruct.USART_BaudRate = USART1_BAUDRATE;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init( USART1,&USART_InitStruct);

	usart1_nvic_init();

	USART_ClearFlag( USART1, USART_FLAG_TC);
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd( USART1, ENABLE);
}

void usart2_init()
{
	USART_InitTypeDef USART_InitStruct;

	usart2_gpio_init();
	
	USART_InitStruct.USART_BaudRate = USART2_BAUDRATE;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init( USART2, &USART_InitStruct);

	usart2_nvic_init();
	
	USART_ClearFlag( USART2, USART_FLAG_TC);
	USART_ITConfig( USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd( USART2, ENABLE);
}

void usart3_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init( GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init( GPIOB, &GPIO_InitStruct);

	USART_InitStruct.USART_BaudRate = USART3_BAUDRATE;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init( USART3, &USART_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init( &NVIC_InitStruct);

	USART_ClearFlag( USART3, USART_FLAG_TC);
	USART_ITConfig( USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd( USART3, ENABLE);
}

void USART1_IRQHandler(void) 
{
	uint8_t usart1_recv_byte;

	if(USART_GetITStatus( USART1, USART_IT_RXNE) != RESET)
	{
		usart1_recv_byte = USART_ReceiveData( USART1);
		USART_SendData( USART2, usart1_recv_byte);
		USART_ClearITPendingBit( USART1, USART_IT_RXNE);
	}
}

void USART2_IRQHandler(void) 
{
	uint8_t usart2_recv_byte;

	if(USART_GetITStatus( USART2, USART_IT_RXNE) != RESET)
	{
		usart2_recv_byte = USART_ReceiveData( USART2);
		USART_SendData( USART1, usart2_recv_byte);
		USART_ClearITPendingBit( USART2, USART_IT_RXNE);
	}
}


void usart2_print(char *str)
{
	int i;
	USART_ClearFlag( USART2, USART_FLAG_TC);
	for(i = 0; str[i]; i++)
	{
		USART_SendData(USART2, (uint8_t)str[i]);
		while (RESET == USART_GetFlagStatus(USART2, USART_FLAG_TXE));
		USART_ClearFlag( USART2, USART_FLAG_TC);
	}
}

// 重构fputc实现输出重定向
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t)ch);
	while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	return ch;
}	










