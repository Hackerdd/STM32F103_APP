/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�Key_Led.c
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/

#ifndef __KEY_LED_H
#define	__KEY_LED_H

#include "stm32f10x.h"
#include "SysTick.h"


#define KEY_PORT GPIOC
#define KEY_PIN  GPIO_Pin_2

#define LED_PORT GPIOA
#define LED_PIN  GPIO_Pin_9

#define KEY_ON  1
#define KEY_OFF 0

#define led(a) if(a)GPIO_SetBits(LED_PORT, LED_PIN); \
								else GPIO_ResetBits(LED_PORT, LED_PIN)

void Blink(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void LED_GPIO_Config(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
void KEY_GPIO_Config(void);


#endif /*__PULSE_CAPTURE_H*/
