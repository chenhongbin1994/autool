#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"


void TIM3_Int_Init(u16 arr, u16 psc);
void Clock(void);                          //时钟程序(秒+1、分+1、时+1)


void TIM2_Backlight_PWM_Init(void);//背光初始化
void Set_Backlight_Brightness(uint16_t brightness);// 设置PWM占空比（背光亮度）

#endif
