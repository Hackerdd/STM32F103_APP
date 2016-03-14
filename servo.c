/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�servo.c
		�ļ���ʶ��Servo TIM2 GPIO A0 A1 A2 A3
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
***/
	
#include "servo.h"

/***
		�ŷ��Ƕ����룬����Ƕ�0-180
***/
void Servo_Write_Angle(float Angle[4])
{
	u16 us = 0;
	u8 i = 0;	
	void (*funcPtr[])(TIM_TypeDef* TIMx, uint16_t Compare) = {TIM_SetCompare1, TIM_SetCompare2, TIM_SetCompare3, TIM_SetCompare4};
	
	for(i = 0; i < 4;++i)
	{
		us = (u16)(Angle[i]*1000/180 + 1000);	
		if((us < PWM_Min) || (us > PWM_Max))return;
		(*funcPtr[i])(TIM2, us);
	}
}

/***
		�ŷ��������룬΢��us����1000-2000
***/
void Servo_Write_us(u16 us[4])
{
	u8 i = 0;	
	void (*funcPtr[])(TIM_TypeDef* TIMx, uint16_t Compare) = {TIM_SetCompare1, TIM_SetCompare2, TIM_SetCompare3, TIM_SetCompare4};

	for(i = 0; i < 4;++i)
	{
		if((us[i] < PWM_Min) || (us[i] > PWM_Max))return;
		(*funcPtr[i])(TIM2, us[i]);
	}
}


/*
 * ��������TIM2_GPIO_Config
 * ����  ������TIM2�������PWMʱ�õ���I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM2 clock enable */
	//PCLK1����2��Ƶ����ΪTIM2��ʱ��Դ����72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM2 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * ��������TIM2_Mode_Config
 * ����  ������TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM�źŵ�ƽ����ֵ */
//	u16 CCR1_Val = 1000;        

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 20000-1;       //20ms������������ = Prescaler�̶� * Period
  TIM_TimeBaseStructure.TIM_Prescaler = 72;	    //����Ԥ��Ƶ��72��Ƶ��Ҳ���Ǽ�ʱ�̶�72Mhz/72
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 0;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM2, ENABLE);			 // ʹ��TIM2���ؼĴ���ARR

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //ʹ�ܶ�ʱ��2	
}


/*
 * ��������Servo_Init
 * ����  ��TIM2 ���PWM�źų�ʼ����ֻҪ�����������
 *         TIM2���ĸ�ͨ���ͻ���PWM�ź����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Servo_Init()
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config();	
}
