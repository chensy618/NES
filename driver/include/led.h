#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED0_GPIO_PORT    	GPIOC			            	// GPIO�˿�
#define LED0_GPIO_CLK 	    RCC_APB2Periph_GPIOE		// GPIO�˿�ʱ��
#define LED0_GPIO_PIN				GPIO_Pin_13			        // ���ӵ�SCLʱ���ߵ�GPIO

typedef enum{
	LED_STATUS_ON,
	LED_STATUS_OFF
}LED_STATUS;

void led_init(void);
void led_status_set(LED_STATUS led_status);
#endif
