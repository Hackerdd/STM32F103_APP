/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：hmi_manu.c
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/

#include "hmi_manu.h"


const u8 ON = 1;
const u8 OFF = 0;

/***
		0    1    2    3    4
		66   01   01   00   FF FF FF
		命令 页码 控件 状态
***/
extern u8 buffer[5];

void hmi_led(void)
{
	static u8 i = 0;
	
	if((buffer[0] == 0x65)&&(buffer[1] == 0x07)&&(buffer[2] == 0x05)&&(buffer[3] == 0x01)&&(i == 0))
	{
		led(ON);
		i = 1;
	}
		
	if((buffer[0] == 0x65)&&(buffer[1] == 0x07)&&(buffer[2] == 0x05)&&(buffer[3] == 0x00)&&(i == 1))
	{
		led(OFF);
		i = 0;
	}
}

//void manu_process(void)
//{
//	
//	switch(buffer[1])
//	{
//		case page_main:
//			break;
//		case page_manu:
//			break;
//		case page_sector:
//			break;
//		case page_parameter:
//			break;
//		case page_grid:
//			break;
//		case page_dial:
//			break;
//	}
//}

//void page_main_task(void)
//{
//	
//}

//void page_manu_task(void)
//{
//	
//}

//void page_sector_task(void)
//{
//	
//}

//void page_parameter_task(void)
//{
//	
//}

//void page_grid_task(void)
//{
//	
//}

//void page_dial_task(void)
//{
//	
//}


