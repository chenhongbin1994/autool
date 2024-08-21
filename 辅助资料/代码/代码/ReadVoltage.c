#include "stm32f10x.h"

#define ADC_PIN GPIO_Pin_0 // 假设电池电压测量引脚连接到GPIOA的引脚0
#define ADC_CHANNEL ADC_Channel_0 // 假设ADC通道0用于电池电压测量
#define VOLTAGE_THRESHOLD 4000 // 电压阈值，单位为mV
#define VOLTAGE_STEP 500 // 每格电压的步长，单位为mV

void delay(uint32_t ms) {
    uint32_t i;
    for (i = 0; i < ms * 1000; i++) {
        __NOP();
    }
}

void ADC1_Init(void) {
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能ADC1和GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

    // 配置ADC引脚为模拟输入
    GPIO_InitStructure.GPIO_Pin = ADC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ADC配置
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // 配置ADC通道
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

    // 使能ADC1
    ADC_Cmd(ADC1, ENABLE);
}

uint16_t Read_Voltage(void) {
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 启动ADC转换
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // 等待转换完成
    return ADC_GetConversionValue(ADC1); // 返回转换结果
}

int main(void) {
    uint16_t voltage;
    uint8_t battery_level = 4;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 使能GPIOC时钟
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // 假设LED连接到GPIOC的引脚13
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    ADC1_Init(); // 初始化ADC

    while (1) {
        voltage = Read_Voltage(); // 读取电压值

        if (voltage < VOLTAGE_THRESHOLD) { // 低于电压阈值时
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))); // 闪烁LED
            delay(500); // 延迟500ms
        } else {
            uint8_t new_battery_level = (voltage - VOLTAGE_THRESHOLD) / VOLTAGE_STEP + 1; // 计算电量格数
            if (new_battery_level != battery_level) {
                // 更新电量显示
                // 这里可以将电量显示在LCD、LED等外设上
                battery_level = new_battery_level;
            }
        }
    }
}
