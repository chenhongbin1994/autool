#include "buzzer.h"

// ����ʹ��TIM2����PWM�ź�
#define BUZZER_PWM_PIN GPIO_Pin_0
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

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

void Buzzer_SetFrequency(uint16_t frequency)
{
    // ��������Ƶ�ʵ�����ʱ����Period��Prescaler
    uint16_t period = (SystemCoreClock / (frequency * (BUZZER_PWM_TIM->PSC + 1))) - 1;
    TIM_SetAutoreload(BUZZER_PWM_TIM, period);
    TIM_SetCompare1(BUZZER_PWM_TIM, period / 2);
}

#if 0

int main(void)
{
    // ��ʼ������ϵͳ���
    Mcu_Init();

    // ��ʼ��������ģ��
    Buzzer_Init();

    // ���Է�����
    while (1)
    {
        Buzzer_On();
        Buzzer_SetFrequency(1000); // ����Ƶ��Ϊ1kHz
        system_delay_ms(1000); // ��ʱ1��

        Buzzer_Off();
        system_delay_ms(1000); // ��ʱ1��
    }
}
#endif


