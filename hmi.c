/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：hmi.c
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/

#include "hmi.h"
//#include <stdbool.h>//里面定义了bool、true、false，让我们可以像C++一样的定义布尔类型。

/***
		用于存放收到的指令
***/
extern u8 buffer[10];

/***
		HMI_Printf(String,Argument)
***/
void HMI_Printf(char *buf, u16 num)
{
	printf(buf, num);
	while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET);
	HMISendb(0xff);//发送结束符号
}

/***
		Set_PageID()  设置页面
***/
u8 Set_PageID(u8 PageID)
{
	static u8 PageID_Now = 0;
	if(PageID_Now != PageID)
	{
		printf("page %d", PageID);
		HMISendb(0xff);
		PageID_Now = PageID;
	}
	return PageID_Now;
}

/***
		Clearify_PageID( 页面编号 )  判断buffer[]中[1]的数据==page
		待测试----
***/
void Clearify_PageID(u8 PageID)
{
	
	printf("sendme");HMISendb(0xff);
	
	while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET);
	
	if(buffer[1] == PageID) return;

	else 
	{
		
		printf("sendme");HMISendb(0xff);
	
		printf("page %d", PageID);HMISendb(0xff);
		
		Delay_ms(100);
	
		if(buffer[1] == PageID) return;	
	}
}

/***
		发送开始，不用也可以
***/
void HMISendstart(void)
{
	Delay_us(200);
	HMISendb(0xff);
	Delay_us(200);
}

/***
		发送字符串，不带参
***/
void HMISends(char *buf1)		  //字符串发送函数
{
	u8 i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{
			USART_SendData(SERIAL,buf1[i]);  //发送一个字节
			while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET){};//等待发送结束
		 	i++;
		}
	 else 
	 return ;

	}
}



void HMISendb(u8 k)		         //字节发送函数
{		 
	u8 i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			USART_SendData(SERIAL,k);  //发送一个字节
			while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET){};//等待发送结束
		}
	 else 
	 return ;

	 } 
} 


/**
	*直到确认当前页面为正确页面后退出函数
	*不正确则改为正确页面
	*
	*/
/*
void Clearify_PageID(u8 PageID)
{
	Flag = 0;
	printf("sendme");
	HMISendb(0xff);
	Delay_ms(50);
//	while(Flag == 0);
	
	while(buffer[1] != PageID)
	{
		printf("page %d", PageID);
		HMISendb(0xff);
		
		
		Flag = 0;
		printf("sendme");
		HMISendb(0xff);
		Delay_ms(50);

//		while(Flag == 0);//Wait usartTI change Flag value
		
		if(buffer[1] == PageID) break;	
	}
}
*/

