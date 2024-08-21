/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-06-06 10:33:26
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50project\PT50_stmf103_vscode_V5\MyCode\ADC\adc.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define Sample_Num 20
#define Channel_Num 4
 
extern uint16_t ADC_ConvertedValue[Sample_Num][Channel_Num];
extern u16 AD_After_Filter[Channel_Num];

void ADC1_Init(void);
u16 Read_ADC_AverageValue(u16 Channel);
void ADC2_Init(void);
u16 ADC2_GetValue(u8 channel);
#endif
