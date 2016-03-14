/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�pulse_capture.c
		�ļ���ʶ��pulse_capture
		ժ    Ҫ��TIM4 GPIOB 6// 7 8 9
							 ��������     TIM4  GPIOB6 
							 ������׽����	TIM4  GPIOB7
		
		��ǰ�汾��
		��    �ߣ�
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/


#include "super_sonic.h"

_Pulse pulse;
volatile u16 Speed = 0;

//#define Trig_pin GPIO_Pin_7
//#define Echo_pin GPIO_Pin_0

u16 TIM4CH_CAPTURE_Rise[PWM_NUM];
u16 TIM4CH_CAPTURE_Drop[PWM_NUM];

/***
		��ʼ��				 ��������  ������׽����
		Ӳ������ΪTIM4  GPIOB6    GPIOB7
***/
void SupperSonic_Init(void)
{		
	TIM4_Trig_Config();
	TIM4_Cap_Init();
}


/*
 * ��������TIM4_Mode_Config
 * ����  ������TIM4�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ��12us�ߵ�ƽ������5.069ms
 * ����  ���ڲ�����
 */
void TIM4_Trig_Config(void)
{
	GPIO_InitTypeDef 					 GPIO_InitStructure;	
	TIM_TimeBaseInitTypeDef  	 TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 				 TIM_OCInitStructure;
	
	/* PWM�źŵ�ƽ����ֵ */
	u16 CCR2_Val = 12;    
	
	/* TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);    

/* -----------------------------------------------------------------------
    TIM4 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM4CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
    TIM4 ARR Register = 999 => TIM4 Frequency = TIM4 counter clock/(ARR + 1)
    TIM4 Frequency = 72 KHz.
    TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100 = 50%
    TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100 = 37.5%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 25%
    TIM4 Channel4 duty cycle = (TIM4_CCR4/ TIM4_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 5000-1;       //������������ = Prescaler�̶� * Period
  TIM_TimeBaseStructure.TIM_Prescaler = 72;	    //����Ԥ��Ƶ��72��Ƶ��Ҳ���Ǽ�ʱ�̶�72Mhz/72
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ

  TIM_OC2Init(TIM4, &TIM_OCInitStructure);	 //ʹ��ͨ��2

  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // ʹ��TIM4���ؼĴ���ARR

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //ʹ�ܶ�ʱ��4	
}


void TIM4_Cap_Init(void)
{	 
	  GPIO_InitTypeDef         GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef        TIM4_ICInitStructure;
		NVIC_InitTypeDef         NVIC_InitStructure;
	  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //ʹ��TIM4ʱ��
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��

	
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;// | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;             
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
	

		
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStructure);
	 
		TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);       	


		TIM_Cmd(TIM4,ENABLE); 
}

void TIM4_IRQHandler(void)
{ 
  static u16 Drop_Capture = 0;
	static u16 Rise_Capture = 0;
	static u16 Rise1 = 0;
	static u16 Rise2 = 0;
	static u16 Distance1 = 0;
	static u16 Distance2 = 0;
	static u16 Delta_Distance = 0;
	static u8 i = 0;
	static u8 j = 0;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)   //����1���������¼�
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); //����жϱ�־λ
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 1) 
		{
				TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
				Rise_Capture=TIM_GetCapture1(TIM4);
				if(i == 0)
				{
					Rise1 = Rise_Capture;
					i = 1;
				}
				else
				{
					Rise2 = Rise_Capture;
					i = 0;
				}
				pulse.period = (Rise1>Rise2)?(Rise1-Rise2):(Rise2-Rise1);//us
				//Delta.dis = 
				//Speed = Delta.dis/pulse.period
				Speed = Delta_Distance*1000/5069;//  um*1000/us == m/s*1000 == mm/s
		}
		else 
		{
				TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
				Drop_Capture=TIM_GetCapture1(TIM4);
				if(Rise_Capture>Drop_Capture)  pulse.width = 65535-Rise_Capture + Drop_Capture;
				else 	                         pulse.width = Drop_Capture - Rise_Capture;
				if(j == 0)
				{
					Distance1 = pulse.width;
					j = 1;
				}
				else
				{
					Distance2 = pulse.width;
					j = 0;
				}
				Delta_Distance = ((Distance1>Distance2)?(Distance1-Distance2):(Distance2-Distance1))*170;//um
		}
	}	
	 
}

