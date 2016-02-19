/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�hmi_manu.h
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/

#ifndef __HMI_MANU_H
#define __HMI_MANU_H
#include "stm32f10x.h"
#include "hmi.h"
#include "Key_Led.h"

/***
		����ҳ��
***/
typedef enum
{
	page_main = 0,		//��ҳ
	page_manu,				//�˵�ҳ��
	page_sector,			//���Σ�����
	page_parameter,		//������ʾ
	page_grid,				//��������ʾ
	page_dial,				//����
	page_key,         //����
}page;


/***
		�ؼ����
***/
typedef enum
{
	widget_0 = 0,
	widget_1,
	widget_2,
	widget_3,
	widget_4,
	widget_5,
	widget_6,
	widget_7,
	widget_8,
}widget;

/***
		������
***/
typedef enum
{
	cmd_touch = 0x65,						//���������¼����� 
	cmd_Current_pageID,					//��ǰҳ��� ID �ŷ��� 
	cmd_Touch_XY,								//�����������ݷ���
	cmd_Sleep_Touch,						//˯��ģʽ�����¼� 
	cmd_Str_Val = 0x70,					//�ַ����������ݷ���
	cmd_Num,										//��ֵ�������ݷ��� 
	cmd_Start_Success = 0x88,		//ϵͳ�����ɹ� 
}cmd;

void hmi_led(void);

#endif
