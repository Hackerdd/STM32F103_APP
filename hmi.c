/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�hmi.c
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/

#include "hmi.h"
//#include <stdbool.h>//���涨����bool��true��false�������ǿ�����C++һ���Ķ��岼�����͡�

u8 buffer[5] = {0};


/***
		HMI_Printf(String,Argument)
***/
void HMI_Printf(char *buf, u16 num)
{
	printf(buf, num);
	while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET);
	HMISendb(0xff);//���ͽ�������
}

/***
		Set_PageID()  ����ҳ��
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
		Clearify_PageID( ҳ���� )  �ж�buffer[]��[1]������==page
		������----
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
		���Ϳ�ʼ������Ҳ����
***/
void HMISendstart(void)
{
	Delay_us(200);
	HMISendb(0xff);
	Delay_us(200);
}

/***
		�����ַ�����������
***/
void HMISends(char *buf1)		  //�ַ������ͺ���
{
	u8 i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{
			USART_SendData(SERIAL,buf1[i]);  //����һ���ֽ�
			while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
		 	i++;
		}
	 else 
	 return ;

	}
}



void HMISendb(u8 k)		         //�ֽڷ��ͺ���
{		 
	u8 i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			USART_SendData(SERIAL,k);  //����һ���ֽ�
			while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
		}
	 else 
	 return ;

	 } 
} 


#ifdef SERIAL2
void USART2_IRQHandler(void)
#else
void USART1_IRQHandler(void)
#endif
{
	u8 c;
	static u8 i = 0;
	if(USART_GetITStatus(SERIAL, USART_IT_RXNE) != RESET)
	{ 	
//	  c=SERIAL->DR;
		c = USART_ReceiveData(SERIAL);
		
//		if(c == 0x66)i = 0;							//ʶ����ʼ��ʶ0x66
//		buffer[i++] = c;
		
		if(c != 0xFF)buffer[i++] = c;			//ʶ�������ʶ0xFF 0xFF 0xFF
		else 					i = 0;
	} 	 
}


/**
	*ֱ��ȷ�ϵ�ǰҳ��Ϊ��ȷҳ����˳�����
	*����ȷ���Ϊ��ȷҳ��
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

