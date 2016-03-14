/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：pulse_capture.c
		文件标识：pulse_capture
		摘    要：TIM4 GPIOB 6// 7 8 9
							 触发引脚     TIM4  GPIOB6 
							 采样捕捉引脚	TIM4  GPIOB7
		
		当前版本：
		作    者：
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/


#include "super_sonic.h"

_Pulse pulse;
volatile u16 Speed = 0;

//#define Trig_pin GPIO_Pin_7
//#define Echo_pin GPIO_Pin_0

u16 TIM4CH_CAPTURE_Rise[PWM_NUM];
u16 TIM4CH_CAPTURE_Drop[PWM_NUM];

/***
		初始化				 触发引脚  采样捕捉引脚
		硬件配置为TIM4  GPIOB6    GPIOB7
***/
void SupperSonic_Init(void)
{		
	TIM4_Trig_Config();
	TIM4_Cap_Init();
}


/*
 * 函数名：TIM4_Mode_Config
 * 描述  ：配置TIM4输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：12us高电平，周期5.069ms
 * 调用  ：内部调用
 */
void TIM4_Trig_Config(void)
{
	GPIO_InitTypeDef 					 GPIO_InitStructure;	
	TIM_TimeBaseInitTypeDef  	 TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 				 TIM_OCInitStructure;
	
	/* PWM信号电平跳变值 */
	u16 CCR2_Val = 12;    
	
	/* TIM3 clock enable */
	//PCLK1经过2倍频后作为TIM3的时钟源等于72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
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
  TIM_TimeBaseStructure.TIM_Period = 5000-1;       //设置脉冲周期 = Prescaler刻度 * Period
  TIM_TimeBaseStructure.TIM_Prescaler = 72;	    //设置预分频：72分频，也就是计时刻度72Mhz/72
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平

  TIM_OC2Init(TIM4, &TIM_OCInitStructure);	 //使能通道2

  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // 使能TIM4重载寄存器ARR

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //使能定时器4	
}


void TIM4_Cap_Init(void)
{	 
	  GPIO_InitTypeDef         GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef        TIM4_ICInitStructure;
		NVIC_InitTypeDef         NVIC_InitStructure;
	  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //使能TIM4时钟
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB时钟

	
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;// | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;             
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;            
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_6);		

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
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)   //捕获1发生捕获事件
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); //清除中断标志位
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 1) 
		{
				TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
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
				TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
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

