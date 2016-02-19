/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：Timer.c
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/
#include "Timer.h"

extern volatile u32 time; // ms 计时变量

void TIM6_Init(void)
{
	TIM6_NVIC_Configuration();
	TIM6_Configuration();
	
	START_TIME;
}
/*
 * 函数名：TIM6_NVIC_Configuration
 * 描述  ：TIM6中断优先级配置
 * 输入  ：无
 * 输出  ：无	
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


/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
    TIM_DeInit(TIM6);
    TIM_TimeBaseStructure.TIM_Period=5000;		 								/* us自动重装载寄存器周期的值(计数值) */
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (7200 - 1);				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM6,TIM_IT_Update | TIM_IT_Trigger,ENABLE);
//    TIM_Cmd(TIM6, ENABLE);																		/* 开启时钟 */
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , DISABLE);		/*先关闭等待使用*/    
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
