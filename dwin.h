/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：dwin.c
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
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
