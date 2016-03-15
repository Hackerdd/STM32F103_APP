/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：pulse_capture.h
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
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
