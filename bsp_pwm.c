/**
	*Copyright (c) 2016
	*All rights reserved.
	*
	*文件名称：bsp_pwm.c
	*文件标识：
	*摘    要：
	*
	*当前版本：
	*作    者：
	*完成日期：
	*
	*取代版本：
	*原作者  ：
	*完成日期：
	*/
#include "bsp_pwm.h"

T_RC_DATA  Rc_Data;//1000~2000
u8  TIM4CH_CAPTURE_STA[PWM_NUM]={0};	//输入捕获状态	

u16 TIM4CH_CAPTURE_Rise[PWM_NUM];
u16 TIM4CH_CAPTURE_Drop[PWM_NUM];

void TIM4_PWM_OutInit(u16 Arr,u8 Psc,u16 Ccr)
{
		GPIO_InitTypeDef         GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
		TIM_OCInitTypeDef        TIM_OCInitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		
		TIM_TimeBaseInitStructure.TIM_Prescaler = 999;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period = 72-1;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;//默认CCR = 0；
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC1Init(TIM4,&TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
		
		TIM_OC2Init(TIM4,&TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
		
		TIM_OC3Init(TIM4,&TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
		
		TIM_OC4Init(TIM4,&TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(TIM4, ENABLE);
		TIM_Cmd(TIM4, ENABLE);
		
}

void TIM4_PWM_OutSet(u16 PWM_Out[PWM_NUM])
{
		u8 i;
		for(i=0;i<PWM_NUM;i++)
		{
			if(PWM_Out[i]<1000)
			{
					PWM_Out[i] = 1000;
			}
			else if(PWM_Out[i]>2000)
			{
					PWM_Out[i] = 2000;
			}
		
		}
		TIM4->CCR1 = PWM_Out[0] - 1000;
		TIM4->CCR2 = PWM_Out[1] - 1000;
		TIM4->CCR3 = PWM_Out[2] - 1000;
		TIM4->CCR4 = PWM_Out[3] - 1000;
}



void TIM4_Cap_Init(void)
{	 
	  GPIO_InitTypeDef         GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef        TIM4_ICInitStructure;
		NVIC_InitTypeDef         NVIC_InitStructure;
	  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //使能TIM4时钟
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB时钟

	
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;             
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;            
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);		

	  //初始化定时器4 TIM4	 
	  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                   //设定计数器自动重装值 
	  TIM_TimeBaseStructure.TIM_Prescaler =71; 	                   //预分频器   
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	  //初始化TIM4输入捕获参数
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStructure);
	 
		TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);       	
	  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);

		TIM_Cmd(TIM4,ENABLE ); 
}

void TIM4_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)   //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); //清除中断标志位
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 1) 
			{
				  TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
          TIM4CH_CAPTURE_Rise[0]=TIM_GetCapture1(TIM4);
      }
			else 
			{
				  TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
          TIM4CH_CAPTURE_Drop[0]=TIM_GetCapture1(TIM4);
				  if(TIM4CH_CAPTURE_Rise[0]>TIM4CH_CAPTURE_Drop[0])  Rc_Data.YAW = 65535-TIM4CH_CAPTURE_Rise[0] + TIM4CH_CAPTURE_Drop[0];
					else 	                                             Rc_Data.YAW = TIM4CH_CAPTURE_Drop[0] - TIM4CH_CAPTURE_Rise[0];
      }			
		}	
	 
	  if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)            //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2); //清除中断标志位
	    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 1) 
			{
				  TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
          TIM4CH_CAPTURE_Rise[1]=TIM_GetCapture2(TIM4);
      }
			else 
			{
				  TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
          TIM4CH_CAPTURE_Drop[1]=TIM_GetCapture2(TIM4);
				  if(TIM4CH_CAPTURE_Rise[1]>TIM4CH_CAPTURE_Drop[1])  Rc_Data.THROTTLE = 65535-TIM4CH_CAPTURE_Rise[1] + TIM4CH_CAPTURE_Drop[1];
					else 	                                             Rc_Data.THROTTLE = TIM4CH_CAPTURE_Drop[1] - TIM4CH_CAPTURE_Rise[1];
      }	
		}	
  	
    if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)            //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3); //清除中断标志位
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 1) 
			{
				  TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
          TIM4CH_CAPTURE_Rise[2]=TIM_GetCapture3(TIM4);
      }
			else 
			{
				  TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
          TIM4CH_CAPTURE_Drop[2]=TIM_GetCapture3(TIM4);
				  if(TIM4CH_CAPTURE_Rise[2]>TIM4CH_CAPTURE_Drop[2]) Rc_Data.PITCH = 65535-TIM4CH_CAPTURE_Rise[2] + TIM4CH_CAPTURE_Drop[2];
					else 	                                            Rc_Data.PITCH = TIM4CH_CAPTURE_Drop[2] - TIM4CH_CAPTURE_Rise[2];
      }	 
		}	

    if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)            //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); //清除中断标志位
		  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1) 
			{
				  TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
          TIM4CH_CAPTURE_Rise[3]=TIM_GetCapture4(TIM4);
      }
			else 
			{
				  TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
          TIM4CH_CAPTURE_Drop[3]=TIM_GetCapture4(TIM4);
				  if(TIM4CH_CAPTURE_Rise[3]>TIM4CH_CAPTURE_Drop[3])  Rc_Data.ROLL = 65535-TIM4CH_CAPTURE_Rise[3] + TIM4CH_CAPTURE_Drop[3];
					else 	                                             Rc_Data.ROLL = TIM4CH_CAPTURE_Drop[3] - TIM4CH_CAPTURE_Rise[3];
      }	  
		}	
}
