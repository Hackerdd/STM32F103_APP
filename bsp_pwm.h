#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#include "stm32f10x.h"
#define PWM_NUM    4

typedef struct int16_rcget{
				int16_t ROLL;
				int16_t PITCH;
				int16_t THROTTLE;
				int16_t YAW;
	      int16_t pitch_offset;
	      int16_t roll_offset;
	      int16_t yaw_offset;}T_RC_DATA;

extern T_RC_DATA Rc_Data;
extern u8  TIM4CH_CAPTURE_STA[PWM_NUM];

void TIM5_PWM_OutInit(u16 Arr,u8 Psc,u16 Ccr);
void TIM5_PWM_OutSet(u16 PWM_Out[PWM_NUM]);
void TIM4_Cap_Init(void);
void TIM4_IRQHandler(void);
#endif
