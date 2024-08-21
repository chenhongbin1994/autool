#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED1 PCout(13)// PC13

void LED_Config(void);
void LEDR_OPEN(void);
void LEDR_CLOSE(void);

#endif


