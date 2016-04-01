/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：usart.c
		文件标识：
		摘    要：执行USART_Config(9600)以初始化
							默认USART1，若定义了SERIAL2，则为USART2
							自由选择串口1/2
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/

#include "usart.h"
#include "misc.h"

/***
		用于存放收到的指令
***/
u8 buffer[10] = {0};

/*
 * 函数名：USART1_Config
 * 描述  ：USART1 GPIO 配置,工作模式配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */

void USART_Config(u16 BaudRate)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
#ifdef SERIAL2
		/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

#else	
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
#endif

		
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = Tx_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PA.3) as input floating */
	GPIO_InitStructure.GPIO_Pin = Rx_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(SERIAL, &USART_InitStructure);
	USART_ITConfig(SERIAL, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(SERIAL, ENABLE);
	
	USART_NVIC_Configuration();
}


void USART_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the USARTy Interrupt */
#ifdef SERIAL2
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
#else
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
#endif
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



/*
 * 函数名：fputc,现已调用microlib，不需要了
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */

int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(SERIAL, (unsigned char) ch);
	while (!(SERIAL->SR & USART_FLAG_TXE)); 
	
	return (ch);
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

#ifdef SERIAL2
		void USART2_IRQHandler(void)
#else
		void USART1_IRQHandler(void)
#endif
{
	u8 c;
	static u8 i = 0;
	if(USART_GetITStatus(SERIAL, USART_IT_RXNE) != RESET)
	{ 	
//	  c=SERIAL->DR;
		c = USART_ReceiveData(SERIAL);
		
//		if(c == 0x5A)i = 0;							//识别起始标识0x5A
//		buffer[i++] = c;
		
		if(c != 0xFF)buffer[i++] = c;			//识别结束标识0xFF 0xFF 0xFF
		else 					i = 0;
	} 	 
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

