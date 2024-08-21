#ifndef __BUZZER_H
#define __BUZZER_H

#include "typedefs.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);	
void Buzzer_SetFrequency(uint16_t frequency);
void Bz_Key(void);

#endif
