/*
 * @Author: ChenHongBin chenhongbin@cnautool.com
 * @Date: 2024-08-05 09:08:55
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-16 13:43:19
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50_APP_A1.0\MyCode\BUZ\buzzer.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "buzzer.h"
#include "delay.h"
#include "key_handler.h"
// ����ʹ��TIM2����PWM�ź�
#define BUZZER_PWM_PIN GPIO_Pin_15
#define BUZZER_PWM_PORT GPIOA
#define BUZZER_PWM_TIM TIM2
#define BUZZER_PWM_TIM_CHANNEL TIM_Channel_1

void Buzzer_Init(void)
{
    // GPIO��ʼ��
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
    // ����GPIOΪ���ù����������
    GPIO_InitStructure.GPIO_Pin = BUZZER_PWM_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BUZZER_PWM_PORT, &GPIO_InitStructure);
		
    // ���ö�ʱ��
    TIM_TimeBaseStructure.TIM_Period = 999;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(BUZZER_PWM_TIM, &TIM_TimeBaseStructure);

    // ����PWM���
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(BUZZER_PWM_TIM, &TIM_OCInitStructure);

    // ʹ�ܶ�ʱ��
    TIM_Cmd(BUZZER_PWM_TIM, ENABLE);
		GPIO_ResetBits(BUZZER_PWM_PORT,BUZZER_PWM_PIN);
}

void Buzzer_On(void)
{
    // ����PWMռ�ձ�Ϊ50%
    TIM_SetCompare1(BUZZER_PWM_TIM, 500);
}

void Buzzer_Off(void)
{
    // ����PWMռ�ձ�Ϊ0%
    TIM_SetCompare1(BUZZER_PWM_TIM, 0);
}

void Buzzer_SetFrequency(uint16_t frequency)//�ɵ��ƣ�����Ƶ��Ϊ1kHz����
{
    // ��������Ƶ�ʵ�����ʱ����Period��Prescaler
    uint16_t period = (SystemCoreClock / (frequency * (BUZZER_PWM_TIM->PSC + 1))) - 1;
    TIM_SetAutoreload(BUZZER_PWM_TIM, period);
    TIM_SetCompare1(BUZZER_PWM_TIM, period / 2);
}

   // ��������
void Key_Beep(void)
{
	if (current_settings.buzzer_enabled) {
    Buzzer_On();
    delay_ms(100);  // ����100ms
    Buzzer_Off();
    }
}
//void Bz_Key(void)
//{
//	u16 i=0,j=300;
//	for(;i<j;i++)
//	{
//		Buzzer_SetFrequency(500);
//	
//		delay_us(130);
//		Buzzer_Off();
//		delay_us(120);
//	}

//}



