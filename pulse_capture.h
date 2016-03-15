/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�pulse_capture.h
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/

#ifndef __PULSE_CAPTURE_H
#define	__PULSE_CAPTURE_H

#include "stm32f10x.h"

#define PWM_NUM    4


typedef struct
{
	u16 width;
	u16 period;
	u16 frequency;
}_Pulse;


void TIM4_Cap_Init(void);
void TIM4_IRQHandler(void);

#endif /*__PULSE_CAPTURE_H*/
