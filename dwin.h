/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�dwin.c
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/
#ifndef DWIN_H
#define DWIN_H

#include "stm32f10x.h"
#include "usart.h"

#define SERIAL2

typedef enum
{
	WIDGET_HEAD1 = 0,
	WIDGET_HEAD2 = 1,
	WIDGET_ADR = 5,
	WIDGET_VAL = 8,
}Commend;

typedef enum
{
	PUSH = 1,
	POP,
}buttomStatus;

typedef enum
{
	Left = 1,
	Right,
}Angle_Position;

void Dwin(void);
u8 plus_Key(void);
void angle_Write(u8 position,u16 angle);
#endif
