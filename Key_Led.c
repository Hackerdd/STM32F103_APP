/***
		Copyright (c) 2016
		All rights reserved.
		
		文件名称：Key_Led.c
		文件标识：
		摘    要：
		
		
		当前版本：
		作    者：Hacker
		完成日期：
		
		取代版本：
		原作者  ：
		完成日期：
***/
	

#include "Key_Led.h"


void Blink(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
	u8 i = 3;
	while(i--)
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin);
		Delay_ms(200);
		GPIO_SetBits(GPIOx, GPIO_Pin);
		Delay_ms(300);
	}
}

void KEY_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOB的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

	/*选择要控制的GPIOC引脚*/															   
	GPIO_InitStructure.GPIO_Pin = KEY_PIN;	

	/*设置引脚模式为通用*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIO*/
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);			  

	/* 关闭所有led灯	*/
//	GPIO_ResetBits(KEY_PORT, KEY_PIN);	 
	
}
/*

*/
void LED_GPIO_Config(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIO的外设时钟*/
	if(GPIOA == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	if(GPIOB == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	if(GPIOC == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	if(GPIOD == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	if(GPIOE == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	if(GPIOF == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	if(GPIOG == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

	/*选择要控制的GPIOC引脚*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;	

	/*设置引脚模式为通用*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIO*/
	GPIO_Init(GPIOx, &GPIO_InitStructure);			  

	/* 关闭所有led灯	*/
	GPIO_ResetBits(GPIOx, GPIO_Pin);	 
	
}

 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*检测是否有按键按下 */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*延时消抖*/
	  	Delay_ms(20);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*等待按键释放 */
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}
