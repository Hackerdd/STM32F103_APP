/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：servo.h
		文件标识：
		摘    要：Servo TIM2 GPIO A0 A1 A2 A3
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
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
