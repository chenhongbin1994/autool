#include "LED.h"

void LED_Config(void)
{
	//��ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	//  1����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//  2����ʼ��GPIOC����
	GPIO_InitStruct.GPIO_Pin    =GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7;//GPIO_Pin_8
	GPIO_InitStruct.GPIO_Speed  =GPIO_Speed_2MHz;//�ٶȣ�2MHZ
	GPIO_InitStruct.GPIO_Mode   =GPIO_Mode_Out_PP;//ģʽ��ͨ���������
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	// �ص�
	GPIO_SetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
} 

void LEDR_OPEN(void)
{
	//3������----GPIOC->ODR�ĵ�8λ����Ϊ0
	//GPIOC->ODR &=~(0x7<<6);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
}

void LEDR_CLOSE(void)
{
	//3������----GPIOC->ODR�ĵ�8λ����Ϊ1
	//GPIOC->ODR &=~(0x7<<6);
	GPIO_SetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7);
}