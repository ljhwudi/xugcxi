#include "gpio.h"
#include "stm32f10x_gpio.h"

void led_init()
{
	led_gpio_init();
	GPIO_SetBits( LED_PORT, LED_PIN);
}

void led_on()
{
	GPIO_ResetBits( LED_PORT, LED_PIN);
}

void led_off()
{
	GPIO_SetBits( LED_PORT, LED_PIN);
}




