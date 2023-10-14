#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED0_GPIO_PORT    	GPIOC			            	// GPIO端口
#define LED0_GPIO_CLK 	    RCC_APB2Periph_GPIOE		// GPIO端口时钟
#define LED0_GPIO_PIN				GPIO_Pin_13			        // 连接到SCL时钟线的GPIO

typedef enum{
	LED_STATUS_ON,
	LED_STATUS_OFF
}LED_STATUS;

void led_init(void);
void led_status_set(LED_STATUS led_status);
#endif
