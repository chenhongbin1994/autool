#include "buzzer.h"

// 假设使用TIM2生成PWM信号
#define BUZZER_PWM_PIN GPIO_Pin_0
#define BUZZER_PWM_PORT GPIOA
#define BUZZER_PWM_TIM TIM2
#define BUZZER_PWM_TIM_CHANNEL TIM_Channel_1

void Buzzer_Init(void)
{
    // GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 配置GPIO为复用功能推挽输出
    GPIO_InitStructure.GPIO_Pin = BUZZER_PWM_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BUZZER_PWM_PORT, &GPIO_InitStructure);

    // 配置定时器
    TIM_TimeBaseStructure.TIM_Period = 999;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(BUZZER_PWM_TIM, &TIM_TimeBaseStructure);

    // 配置PWM输出
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(BUZZER_PWM_TIM, &TIM_OCInitStructure);

    // 使能定时器
    TIM_Cmd(BUZZER_PWM_TIM, ENABLE);
}

void Buzzer_On(void)
{
    // 设置PWM占空比为50%
    TIM_SetCompare1(BUZZER_PWM_TIM, 500);
}

void Buzzer_Off(void)
{
    // 设置PWM占空比为0%
    TIM_SetCompare1(BUZZER_PWM_TIM, 0);
}

void Buzzer_SetFrequency(uint16_t frequency)
{
    // 根据输入频率调整定时器的Period和Prescaler
    uint16_t period = (SystemCoreClock / (frequency * (BUZZER_PWM_TIM->PSC + 1))) - 1;
    TIM_SetAutoreload(BUZZER_PWM_TIM, period);
    TIM_SetCompare1(BUZZER_PWM_TIM, period / 2);
}

#if 0

int main(void)
{
    // 初始化其他系统组件
    Mcu_Init();

    // 初始化蜂鸣器模块
    Buzzer_Init();

    // 测试蜂鸣器
    while (1)
    {
        Buzzer_On();
        Buzzer_SetFrequency(1000); // 设置频率为1kHz
        system_delay_ms(1000); // 延时1秒

        Buzzer_Off();
        system_delay_ms(1000); // 延时1秒
    }
}
#endif


