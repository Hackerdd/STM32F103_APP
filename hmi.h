/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�hmi.h
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
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
