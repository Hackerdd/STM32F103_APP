/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：servo.c
		文件标识：Servo TIM2 GPIO A0 A1 A2 A3
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/
	
#include "servo.h"

/***
		伺服角度输入，输入角度0-180
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
		伺服脉冲输入，微秒us输入1000-2000
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
 * 函数名：TIM2_GPIO_Config
 * 描述  ：配置TIM2复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM2 clock enable */
	//PCLK1经过2倍频后作为TIM2的时钟源等于72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM2 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * 函数名：TIM2_Mode_Config
 * 描述  ：配置TIM2输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
//	u16 CCR1_Val = 1000;        

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 20000-1;       //20ms设置脉冲周期 = Prescaler刻度 * Period
  TIM_TimeBaseStructure.TIM_Prescaler = 72;	    //设置预分频：72分频，也就是计时刻度72Mhz/72
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 0;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	 //使能通道2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	 //使能通道4
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM2, ENABLE);			 // 使能TIM2重载寄存器ARR

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //使能定时器2	
}


/*
 * 函数名：Servo_Init
 * 描述  ：TIM2 输出PWM信号初始化，只要调用这个函数
 *         TIM2的四个通道就会有PWM信号输出
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Servo_Init()
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config();	
}
