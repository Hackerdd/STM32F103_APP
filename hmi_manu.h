/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：hmi_manu.h
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/

#ifndef __HMI_MANU_H
#define __HMI_MANU_H
#include "stm32f10x.h"
#include "hmi.h"
#include "Key_Led.h"

/***
		定义页面
***/
typedef enum
{
	page_main = 0,		//主页
	page_manu,				//菜单页面
	page_sector,			//扇形，表针
	page_parameter,		//参数显示
	page_grid,				//网格波形显示
	page_dial,				//滑块
	page_key,         //键盘
}page;


/***
		控件编号
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
		命令编号
***/
typedef enum
{
	cmd_touch = 0x65,						//触摸热区事件返回 
	cmd_Current_pageID,					//当前页面的 ID 号返回 
	cmd_Touch_XY,								//触摸坐标数据返回
	cmd_Sleep_Touch,						//睡眠模式触摸事件 
	cmd_Str_Val = 0x70,					//字符串变量数据返回
	cmd_Num,										//数值变量数据返回 
	cmd_Start_Success = 0x88,		//系统启动成功 
}cmd;

void hmi_led(void);

#endif
