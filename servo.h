/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：servo.h
		文件标识：
		摘    要：Servo TIM3 A67,B01
		
		
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

void Servo_Write_Angle(u8 Angle);
void Servo_Write_us(u16 us);

void TIM3_GPIO_Config(void);
void TIM3_Mode_Config(u16 CCR1_Val);

void Servo_us_Init(u8 us);
void Servo_Angle_Init(u8 Angle);

#endif /*__SERVO_H*/
