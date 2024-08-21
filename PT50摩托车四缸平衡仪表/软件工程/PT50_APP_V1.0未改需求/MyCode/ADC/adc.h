/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-06-19 11:29:37
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50project\PT50_stmf103_vscode_V5\MyCode\ADC\adc.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

extern uint16_t ADC_Value[4];


void ADC_Init_t(void);
void ADC_GetAverageValues(void);

void ADC1_GetValue(void);


float ADC1_MapValue(float OutputValue, float PositivePressure, float K_Value);
void ADC2_Init(void);
u16 ADC2_GetValue(u8 channel);
u16 Get_ADC2_ChannelAverage(u8 Channel);
#endif
