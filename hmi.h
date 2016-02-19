/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：hmi.h
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/

#ifndef __HMI_H
#define __HMI_H

#include "stm32f10x.h"
#include "usart.h"
#include "SysTick.h"

//u8 key,beep;

//u8 idfind(u8 *buf,u8 *val,u8 len);

void HMI_Printf(char *buf1, u16 num);
u8 Set_PageID(u8 PageID);
void Clearify_PageID(u8 PageID);
void HMISends(char *buf1);
void HMISendb(u8 buf);
void HMISendstart(void);
void beepms(u16 va);

#endif
