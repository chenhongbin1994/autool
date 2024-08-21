#include "drv_led.h"

void LED_Config(void)
{
	//初始化结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	//  1》打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//  2》初始化GPIOC引脚
	GPIO_InitStruct.GPIO_Pin    =GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7;//GPIO_Pin_8
	GPIO_InitStruct.GPIO_Speed  =GPIO_Speed_2MHz;//速度：2MHZ
	GPIO_InitStruct.GPIO_Mode   =GPIO_Mode_Out_PP;//模式：通用推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	// 关灯
	GPIO_SetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
} 

void LED_CTRL(Led_rgb_T led_rgb,Led_cmd_T led_cmd)
{
	switch(led_rgb){
		case Led_r:
			if(led_cmd==Led_open){
				GPIO_ResetBits( GPIOC, GPIO_Pin_8);
			}else{
				GPIO_SetBits( GPIOC, GPIO_Pin_8);
			}
			break;
		case Led_g:
			if(led_cmd==Led_open){
				GPIO_ResetBits( GPIOC, GPIO_Pin_7);
			}else{
				GPIO_SetBits( GPIOC, GPIO_Pin_7);
			}			
			break;
		case Led_b:
			if(led_cmd==Led_open){
				GPIO_ResetBits( GPIOC, GPIO_Pin_6);
			}else{
				GPIO_SetBits( GPIOC, GPIO_Pin_6);
			}

			break;
		case Led_rgb:
			if(led_cmd==Led_open){
				GPIO_ResetBits( GPIOC, GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
			}else{
				GPIO_SetBits( GPIOC, GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
			}				
			break;
		default:
			break;
	}
}

/*
void LEDR_OPEN(void)
{
	//3》开灯----GPIOC->ODR的第8位配置为0
	//GPIOC->ODR &=~(0x7<<6);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
}

void LEDR_CLOSE(void)
{
	//3》开灯----GPIOC->ODR的第8位配置为1
	//GPIOC->ODR &=~(0x7<<6);
	GPIO_SetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
}*/
