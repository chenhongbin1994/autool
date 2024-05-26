#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"


void Adc1_Init(void);
u16 ADC1_Mid_GetValue(u8 channel); 
u16 ADC1_Mid_GetAverageValue(u8 channel,u8 times); 
float ADC1_Mid_MapValue(float OutputValue, float PositivePressure, float K_Value);

//void Adc2_Init(void);
//u16 ADC2_Mid_GetValue(u8 channel);
//float ADC_Mid_MapValue(int OutputValue, u8 channel); //通过计算可以把ADC输出的数字值转换为对应的压力值（单位可能是毫巴、千帕等）。

#endif 
