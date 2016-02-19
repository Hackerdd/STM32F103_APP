/***
		Copyright (c) 2016
		All rights reserved.
		
		�ļ����ƣ�Key_Led.c
		�ļ���ʶ��
		ժ    Ҫ��
		
		
		��ǰ�汾��
		��    �ߣ�Hacker
		������ڣ�
		
		ȡ���汾��
		ԭ����  ��
		������ڣ�
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
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOB������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

	/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
	GPIO_InitStructure.GPIO_Pin = KEY_PIN;	

	/*��������ģʽΪͨ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);			  

	/* �ر�����led��	*/
//	GPIO_ResetBits(KEY_PORT, KEY_PIN);	 
	
}
/*

*/
void LED_GPIO_Config(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIO������ʱ��*/
	if(GPIOA == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	if(GPIOB == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	if(GPIOC == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	if(GPIOD == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	if(GPIOE == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	if(GPIOF == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	if(GPIOG == GPIOx)RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

	/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;	

	/*��������ģʽΪͨ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(GPIOx, &GPIO_InitStructure);			  

	/* �ر�����led��	*/
	GPIO_ResetBits(GPIOx, GPIO_Pin);	 
	
}

 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*����Ƿ��а������� */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*��ʱ����*/
	  	Delay_ms(20);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*�ȴ������ͷ� */
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}
