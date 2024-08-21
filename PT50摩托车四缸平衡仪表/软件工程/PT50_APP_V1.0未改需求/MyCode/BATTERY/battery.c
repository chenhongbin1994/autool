#include "battery.h"
#include "adc.h" 




void Battery_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO, ENABLE);
    //EN_OUT��Դ����
	GPIO_InitStructure.GPIO_Mode 	=  	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  	= 	GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_50MHz;;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		
	// ��ʼ�� ADC 
	ADC2_Init();    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // �޸�ΪPB0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); // �޸�ΪGPIOB	
	//GPIO_SetBits(GPIOA, GPIO_Pin_4);//��Դ
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);//��Դ
}
