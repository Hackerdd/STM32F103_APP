/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�servo.h
		�ļ���ʶ��
		ժ    Ҫ��Servo TIM2 GPIO A0 A1 A2 A3
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/

#ifndef __SERVO_H
#define	__SERVO_H

#include "stm32f10x.h"

#define PWM_Max 1998
#define PWM_Min 1002

void Servo_Write_Angle(float Angle[4]);
void Servo_Write_us(u16 us[4]);

void TIM2_GPIO_Config(void);
void TIM2_Mode_Config(void);

void Servo_Init(void);

#endif /*__SERVO_H*/
