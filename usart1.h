/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：usart.h
		文件标识：
		摘    要：默认USART1，若定义了SERIAL2，则为USART2
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/


#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>

#define Tx_Pin GPIO_Pin_9
#define Rx_Pin GPIO_Pin_10
#define SERIAL USART1

void USART_Config(u16 BaudRate);
void NVIC_Configuration(void);
//int fputc(int ch, FILE *f);

#endif /* __USART_H */
