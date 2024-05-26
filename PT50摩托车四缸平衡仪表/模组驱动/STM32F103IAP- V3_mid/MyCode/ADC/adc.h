#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"


void Adc1_Init(void);
u16 ADC1_Mid_GetValue(u8 channel); 
u16 ADC1_Mid_GetAverageValue(u8 channel,u8 times); 
float ADC1_Mid_MapValue(float OutputValue, float PositivePressure, float K_Value);//ͨ��������԰�ADC���������ֵת��Ϊ��Ӧ��ѹ��ֵ����λ�����Ǻ��͡�ǧ���ȣ���

void Adc2_Init(void);
u16 ADC2_Mid_GetValue(u8 channel);


#endif 
