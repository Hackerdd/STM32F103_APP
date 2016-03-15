/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�pulse_capture.c
		�ļ���ʶ��pulse_capture
		ժ    Ҫ��TIM4 GPIOB 6 7 8 9
							 
		
		��ǰ�汾��
		��    �ߣ�
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/


#include "pulse_capture.h"

_Pulse pulse;

u16 PWM_Value[4] = {0};
#define PWM_Chanal1 PWM_Value[0]
#define PWM_Chanal2 PWM_Value[1]
#define PWM_Chanal3 PWM_Value[2]
#define PWM_Chanal4 PWM_Value[3]

u16 TIM4CH_CAPTURE_Rise[PWM_NUM];
u16 TIM4CH_CAPTURE_Drop[PWM_NUM];

void TIM4_Cap_Init(void)
{	 
	  GPIO_InitTypeDef         GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef        TIM4_ICInitStructure;
		NVIC_InitTypeDef         NVIC_InitStructure;
	  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //ʹ��TIM4ʱ��
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��

	
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;             
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;            
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_6);		

	  //��ʼ����ʱ��4 TIM4	 
	  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                   //�趨�������Զ���װֵ 
	  TIM_TimeBaseStructure.TIM_Prescaler =71; 	                   //Ԥ��Ƶ��   
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	  //��ʼ��TIM4���벶�����
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;                //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;	   //�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;
		TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;
		TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;
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

		TIM_Cmd(TIM4,ENABLE); 
}

void TIM4_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)   //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); //����жϱ�־λ
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 1) 
			{
				  TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
          TIM4CH_CAPTURE_Rise[0]=TIM_GetCapture1(TIM4);
      }
			else 
			{
				  TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
          TIM4CH_CAPTURE_Drop[0]=TIM_GetCapture1(TIM4);
				  if(TIM4CH_CAPTURE_Rise[0]>TIM4CH_CAPTURE_Drop[0])  PWM_Chanal1 = 65535-TIM4CH_CAPTURE_Rise[0] + TIM4CH_CAPTURE_Drop[0];
					else 	                                             PWM_Chanal1 = TIM4CH_CAPTURE_Drop[0] - TIM4CH_CAPTURE_Rise[0];
      }			
		}	
	 
	  if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)            //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2); //����жϱ�־λ
	    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 1) 
			{
				  TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
          TIM4CH_CAPTURE_Rise[1]=TIM_GetCapture2(TIM4);
      }
			else 
			{
				  TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
          TIM4CH_CAPTURE_Drop[1]=TIM_GetCapture2(TIM4);
				  if(TIM4CH_CAPTURE_Rise[1]>TIM4CH_CAPTURE_Drop[1])  PWM_Chanal2 = 65535-TIM4CH_CAPTURE_Rise[1] + TIM4CH_CAPTURE_Drop[1];
					else 	                                             PWM_Chanal2 = TIM4CH_CAPTURE_Drop[1] - TIM4CH_CAPTURE_Rise[1];
      }	
		}	
  	
    if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)            //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3); //����жϱ�־λ
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 1) 
			{
				  TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
          TIM4CH_CAPTURE_Rise[2]=TIM_GetCapture3(TIM4);
      }
			else 
			{
				  TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
          TIM4CH_CAPTURE_Drop[2]=TIM_GetCapture3(TIM4);
				  if(TIM4CH_CAPTURE_Rise[2]>TIM4CH_CAPTURE_Drop[2]) PWM_Chanal3 = 65535-TIM4CH_CAPTURE_Rise[2] + TIM4CH_CAPTURE_Drop[2];
					else 	                                            PWM_Chanal3 = TIM4CH_CAPTURE_Drop[2] - TIM4CH_CAPTURE_Rise[2];
      }	 
		}	

    if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)            //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); //����жϱ�־λ
		  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1) 
			{
				  TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
          TIM4CH_CAPTURE_Rise[3]=TIM_GetCapture4(TIM4);
      }
			else 
			{
				  TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
          TIM4CH_CAPTURE_Drop[3]=TIM_GetCapture4(TIM4);
				  if(TIM4CH_CAPTURE_Rise[3]>TIM4CH_CAPTURE_Drop[3])  PWM_Chanal4 = 65535-TIM4CH_CAPTURE_Rise[3] + TIM4CH_CAPTURE_Drop[3];
					else 	                                             PWM_Chanal4 = TIM4CH_CAPTURE_Drop[3] - TIM4CH_CAPTURE_Rise[3];
      }	  
		}	
}

