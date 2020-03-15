
#ifndef __GPIO_H__
#define __GPIO_H__

//#define __HCSR04_2_CHANGE_PIN__  //hcsr04_2 引脚从pb8 pb9 改到 pa5 pa6

#define LED_PORT 				GPIOA
#define LED_PIN					GPIO_Pin_8

#define K1_PORT					GPIOA
#define	K1_PIN					GPIO_Pin_0

#define ES08MA_PORT 			GPIOC
#define ES08MA_PIN				GPIO_Pin_6

#define HCSR04_1_TRIG_PORT		GPIOB
#define HCSR04_1_TRIG_PIN		GPIO_Pin_6	

#define HCSR04_1_ECHO_PORT		GPIOB
#define HCSR04_1_ECHO_PIN		GPIO_Pin_7

#ifndef __HCSR04_2_CHANGE_PIN__
#define HCSR04_2_TRIG_PORT		GPIOB
#define HCSR04_2_TRIG_PIN		GPIO_Pin_8	

#define HCSR04_2_ECHO_PORT		GPIOB
#define HCSR04_2_ECHO_PIN		GPIO_Pin_9
#else
#define HCSR04_2_TRIG_PORT		GPIOA
#define HCSR04_2_TRIG_PIN		GPIO_Pin_5	

#define HCSR04_2_ECHO_PORT		GPIOA
#define HCSR04_2_ECHO_PIN		GPIO_Pin_6
#endif

void led_gpio_init(void);
void k1_gpio_init(void);
void es08ma_gpio_init(void);
void hcsr04_1_gpio_init(void);
void hcsr04_2_gpio_init(void);
void usart2_gpio_init(void);
void usart1_gpio_init(void);

#endif  //__GPIO_H__

