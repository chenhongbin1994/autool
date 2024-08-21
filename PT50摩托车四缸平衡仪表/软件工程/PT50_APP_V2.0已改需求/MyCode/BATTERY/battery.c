#include "battery.h"
#include "adc.h" 




void Battery_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO, ENABLE);
    //EN_OUT电源锁定
	GPIO_InitStructure.GPIO_Mode 	=  	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  	= 	GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_50MHz;;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		
	// 初始化 ADC 
	ADC2_Init();    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // 修改为PB0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); // 修改为GPIOB	
	//GPIO_SetBits(GPIOA, GPIO_Pin_4);//电源
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);//电源
}
