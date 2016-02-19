/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�servo.h
		�ļ���ʶ��
		ժ    Ҫ��Servo TIM3 A67,B01
		
		
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

void Servo_Write_Angle(u8 Angle);
void Servo_Write_us(u16 us);

void TIM3_GPIO_Config(void);
void TIM3_Mode_Config(u16 CCR1_Val);

void Servo_us_Init(u8 us);
void Servo_Angle_Init(u8 Angle);

#endif /*__SERVO_H*/
