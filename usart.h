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

//#ifndef SERIAL1 || SERIAL2
//	#error Please define usart1 or usart2
//#endif

//默认USART1，若定义了SERIAL2，则为USART2
//#define SERIAL1
// #define SERIAL2

#ifdef SERIAL2
	#define Tx_Pin GPIO_Pin_2
	#define Rx_Pin GPIO_Pin_3
	#define SERIAL USART2
#else
	#define Tx_Pin GPIO_Pin_9
	#define Rx_Pin GPIO_Pin_10
	#define SERIAL USART1
#endif

void USART_Config(u16 BaudRate);
void USART_NVIC_Configuration(void);
//int fputc(int ch, FILE *f);

#endif /* __USART_H */
