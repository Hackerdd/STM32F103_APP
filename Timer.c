/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�Timer.c
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/
#include "Timer.h"

extern volatile u32 time; // ms ��ʱ����

void TIM6_Init(void)
{
	TIM6_NVIC_Configuration();
	TIM6_Configuration();
	
	START_TIME;
}
/*
 * ��������TIM6_NVIC_Configuration
 * ����  ��TIM6�ж����ȼ�����
 * ����  ����
 * ���  ����	
 */
void TIM6_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
    TIM_DeInit(TIM6);
    TIM_TimeBaseStructure.TIM_Period=5000;		 								/* us�Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (7200 - 1);				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM6,TIM_IT_Update | TIM_IT_Trigger,ENABLE);
//    TIM_Cmd(TIM6, ENABLE);																		/* ����ʱ�� */
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , DISABLE);		/*�ȹرյȴ�ʹ��*/    
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval : None
  */

void TIM6_IRQHandler(void)
{
//	static u8 time;
	if ( TIM_GetITStatus(TIM6 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);    
//  		 time++;	
	}		 	
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
