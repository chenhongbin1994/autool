#ifndef __BATTERY_H
#define __BATTERY_H

#include "stm32f10x.h"

void Battery_Init(void);
void Battery_CheckAndDisplay(void);
float ADC2_array_sort(uint16_t *ACD2_array, uint8_t Array_size);
	

#endif
