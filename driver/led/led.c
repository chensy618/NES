#include "led.h"   

void led_status_set(LED_STATUS led_status)
{
	if (led_status == LED_STATUS_ON)
	{
		GPIO_ResetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);
	}
	else if (led_status == LED_STATUS_OFF)
	{
		GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);
	}
}

void led_init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LED0_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);

	led_status_set(LED_STATUS_OFF);
}
