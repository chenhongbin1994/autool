#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "stm32f10x.h"

typedef enum Led_rgb{
	Led_r=0,
	Led_g,
	Led_b,
	Led_rgb
}Led_rgb_T;
	
typedef enum Led_cmd{
	Led_open=0,
	Led_close	
}Led_cmd_T;


void   LED_Config(void);
void LED_CTRL(Led_rgb_T led_rgb,Led_cmd_T led_cmd);


#endif //__DRV_LED_H__
