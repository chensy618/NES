/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "led.h"  
#include "usart.h"

static TaskHandle_t led_task_handle = NULL;
static TaskHandle_t uart_task_handle = NULL;

void led_task(void *arg)
{
	while(1)                            
	{
		led_status_set(LED_STATUS_ON);
		vTaskDelay(500/portTICK_PERIOD_MS);
		led_status_set(LED_STATUS_OFF);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void uart_task(void *arg)
{
	while(1)                            
	{
		printf("hello world!\r\n");
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{

  /* Add your application code here
     */
	led_init();
	usart_config();

	xTaskCreate(led_task, "led_task", 1024, NULL, 20, &led_task_handle);
	xTaskCreate(uart_task, "uart_task", 1024, NULL, 20, &uart_task_handle);

  vTaskStartScheduler();
	while(1);
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
