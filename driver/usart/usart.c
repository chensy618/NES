/*
       
 * Hardware connection	 ------------------------
 *          						| PA9  - USART1(Tx)      |
 *          						| PA10 - USART1(Rx)      |
 *           						 ------------------------
 *
**********************************************************************************/

#include "usart.h"
//support printf function
typedef struct __FILE FILE;	  
#if 1
#pragma import(__use_no_semihosting)             
          
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef' d in stdio.h. */ 
FILE __stdout;       

void _sys_exit(int x) 
{ 
	x = x; 
} 
//Redirect the C library function printf to the serial port. 
//Printf can be used after redirection.
int fputc(int ch, FILE *f)
{      
	/* send 1B data to uart */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* wait for finished sending */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

#endif

/**
  * @brief  USART GPIO configuration
  */
void usart_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// open uart's gpio clock
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// open uart peripherals clock
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// Configure the GPIO of usart Tx to push-pull multiplexing mode
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // Configure the GPIO of usart Rx to floating input mode
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// Configure the working parameters of the serial port
	// config baudrate
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// config data bit
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// config stop bot
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// config parity bit
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// config hardware stream control
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// config working mode: rx and tx
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// uart initialization
	USART_Init(DEBUG_USARTx, &USART_InitStructure);	
	
	// enable uart
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}

/*****************  send one char**********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* send one byte data to USART */
	USART_SendData(pUSARTx,ch);
		
	/* Waiting for transmit data register to be empty*/
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  send string **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* Wait for sending to complete */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  send a 16 bits number**********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* high 8 bits*/
	temp_h = (ch&0XFF00)>>8;
	/* low 8 bits*/
	temp_l = ch&0XFF;
	
	/* send high 8 bits*/
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* sned low 8 bits*/
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
#if 0
int fputc(int ch, FILE *f)
{
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
	
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
#endif
//Redirect the C library function scanf to the serial port. 
//scanf can be used after redirection.
int fgetc(FILE *f)
{
		/* wait for input*/
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


