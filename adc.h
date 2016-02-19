#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
#include "SysTick.h"

void ADC1_Init(void);
u16 Get_Adc_Average(u8 ch,u8 times);
u16 Get_Adc(u8 ch);

#endif /* __ADC_H */

