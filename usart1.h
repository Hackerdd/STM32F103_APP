/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�usart.h
		�ļ���ʶ��
		ժ    Ҫ��Ĭ��USART1����������SERIAL2����ΪUSART2
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
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
