#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"




void TIM3_Int_Init(u16 arr, u16 psc);
void Clock(void);                          //ʱ�ӳ���(��+1����+1��ʱ+1)


void TIM2_Backlight_PWM_Init(void);//�����ʼ��
void Set_Backlight_Brightness(uint16_t brightness);// ����PWMռ�ձȣ��������ȣ�
void TIM1_Cap_Init(u16 arr,u16 psc);

extern u32 Long_press_cnt ;

#endif
