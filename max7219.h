/*******************************************************

 *  �������ƣ�MAX7219.H

 *  �����ܣ�MAX7219.H��ͷ�ļ�

 *  �������ߣ�������

 *  ����ʱ�䣺2013-12-7

 *  �޸�ʱ�䣺2013-12-9

 *  ����汾��V0.3

 ******************************************************/


#ifndef __MAX7219_H__

#define __MAX7219_H__

#include "stm32f10x.h"
#include "SysTick.h"
#include "string.h"
#include <stdio.h>

/******************************************************

 * �������ƣ�

 * �������ܣ����ݵķ���

 * ��ڲ�����unsigned int uiDataOne, unsigned int uiDataTwo

 * ���ڲ�����void

*******************************************************/ 
extern u8 disp1[38][8];
extern const u8 nAsciiDot[96][8];
//extern const u8 AsciiCode[96][8];
extern void SendData(unsigned int uiDataOne, unsigned int uiDataTwo);
extern u16 Seg_Num;

/* λ��� */



#define ON  1
#define OFF 0

#define Seg_time 25

#define MAX7219_PORT GPIOA

//#define MAX7219_CLK_PIN GPIO_Pin_0
//#define Max7219_CS_PIN  GPIO_Pin_2
//#define Max7219_DIN_PIN  GPIO_Pin_4

#define MAX7219_CLK_PIN  GPIO_Pin_1
#define Max7219_CS_PIN   GPIO_Pin_2
#define Max7219_DIN_PIN  GPIO_Pin_3

//���κ꣬��������������һ��ʹ��
#define MAX7219_CLK(a)	if (a)	\
					GPIO_SetBits(MAX7219_PORT,MAX7219_CLK_PIN);\
					else		\
					GPIO_ResetBits(MAX7219_PORT,MAX7219_CLK_PIN)

#define Max7219_CS(a)	if (a)	\
					GPIO_SetBits(MAX7219_PORT,Max7219_CS_PIN);\
					else		\
					GPIO_ResetBits(MAX7219_PORT,Max7219_CS_PIN)

#define Max7219_DIN(a)	if (a)	\
					GPIO_SetBits(MAX7219_PORT,Max7219_DIN_PIN);\
					else		\
					GPIO_ResetBits(MAX7219_PORT,Max7219_DIN_PIN)

#define SHOW_SEGMENT(num) (Seg_Num = num) 					
					
void Max7219_GPIO_Config(void);
void Delay_ms(__IO u32 nCount);
void Init_MAX7219(void);
void Write_Max7219(u8 address,u8 dat);
void Write_Max7219_byte(u8 DATA);
void Matrix_printf(char *ptr);
void Draw_Dot(u8 l, u8 c);
void Matrix(void);
void Circle(void);
void Line(void);

#endif
