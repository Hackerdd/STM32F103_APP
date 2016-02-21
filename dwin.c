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

#include "dwin.h"

u8 buffer[10] = {0};

void Dwin(void)
{
//	static u8 i = 0;
//	static u8 j = 0;
//	if(j != buffer[WIDGET_VAL])
//	{
//		angle_Write(Left, buffer[WIDGET_VAL]);
//		j = buffer[WIDGET_VAL];
//	}
	
//	if((plus_Key() == PUSH) && (i == 0))
//	{
//		angle_Write(Left, ++j);
		angle_Write(Left, buffer[WIDGET_VAL]);
//		i = 1;
//	}
//		
//	if((plus_Key() == POP) && (i == 1))
//	{
////		angle_Write(Left, --j);
//		angle_Write(Left, --j);
//		i = 0;
//	}
}

u8 plus_Key(void)
{
	if((buffer[WIDGET_HEAD1] == 0x5A)&&(buffer[WIDGET_HEAD2] == 0xA5)	\
		&&(buffer[WIDGET_ADR] == 0x13)&&(buffer[WIDGET_VAL] == 0x01))
	{
		return PUSH;
	}
	else return POP;
}

void angle_Write(u8 position,u16 angle)
{
	static u8 j;
	u8 i = 0;
	u8 angle_Cmd[8] = {0x5A, 0xA5, 0x05, 0x82, 0x00, 0x07, 0x00, 0x09};
	
	if(angle == j)return;
	else j = angle;
	
	if(position == Left)angle_Cmd[WIDGET_ADR] = 0x07;
	if(position == Right)angle_Cmd[WIDGET_ADR] = 0x09;
	angle_Cmd[WIDGET_VAL-1] = angle;
	for(i = 0; i < 8; ++i)
	{
		USART_SendData(SERIAL,angle_Cmd[i]);  //����һ���ֽ�
		while(USART_GetFlagStatus(SERIAL,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
//		printf("%d",angle_Cmd[i]);
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

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
		
		if(c == 0x5A)i = 0;							//ʶ����ʼ��ʶ0x66
		buffer[i++] = c;
		
//		if(c != 0xFF)buffer[i++] = c;			//ʶ�������ʶ0xFF 0xFF 0xFF
//		else 					i = 0;
	} 	 
}

