#include "gpio.h"
#include "exti.h"
#include "nvic.h"
#include "stm32f10x_tim.h"
#include "es08ma.h"
#include "stdio.h"
#include "uart.h"
#include "k1.h"

extern uint8_t issended;
extern uint8_t test_flag;

void  k1_Init()//配置CPU以外的部分相关电路
{
	k1_gpio_init();
	k1_exti_init();
	exti0_nvic_init();
}

void EXTI0_IRQHandler()//启动文件去查 264行 323行所有的我们自己的片上外设中断处理函数都在这里
{
	static u16 cval;
    if(EXTI_GetITStatus(EXTI_Line0))//这个底层其实就是去相关的寄存器 去判断，到底什么原因进入到这个中断函数
	{		
//		TIM_Cmd( TIM4, ENABLE);
//		latitude_str2unicode();
//		longtitude_str2unicode();
		issended = 0;

		#ifdef __SIM900A_TEST__
		test_flag = 1;;
		#endif  //__SIM900A_TEST__
		
		if(GPIO_ReadInputDataBit( GPIOC, GPIO_Pin_6) == 0)
		{
//			printf("k1 was pressed!\n");
			if(cval == 0)
				es08ma_open();
			else
				es08ma_close();

			cval=!cval;
		}
		EXTI_ClearITPendingBit(EXTI_Line0); 
	}	
}


