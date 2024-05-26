#include "battery.h"
#include "HT1621.h" // 假设 HT1621 的驱动函数在这个头文件中
#include "adc.h" // 假设 ADC 初始化和读取函数在这个头文件中
#include "gpio.h" // GPIO 配置函数
#include "vTaskDelay.h" // 延迟函数

#define RF_PACKET_SIZE 32
#define Screen_Data_2_Addr1 0x00 // 根据具体地址定义
#define Screen_Data_2_Addr2 0x00 // 根据具体地址定义
#define Screen_Data_3_Addr1 0x00 // 根据具体地址定义
#define Screen_Data_3_Addr2 0x00 // 根据具体地址定义
#define Screen_Data_4_Addr1 0x00 // 根据具体地址定义
#define Screen_Data_4_Addr2 0x00 // 根据具体地址定义
#define Screen_Data_V_Addr 0x00 // 根据具体地址定义

extern uint8_t TIme_300ms_Adc_Flag;
static uint16_t Adc_array[16] = {0};
static uint16_t Previous_Adc_Value = 0;
static float Button_Cell_vol = 0.0;
static uint16_t Adc_Data = 0;
static float Adc_Avg_Value = 0.0;
static double Difference_Value = 0.0;
static uint8_t Screen_RF_Data2 = 0;
static uint8_t Screen_RF_Data3 = 0;
static uint8_t Screen_RF_Data4 = 0;

void Battery_Init(void)
{
    // 初始化 ADC 和 GPIO
    Adc_Init();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; // 修改为PB0
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct); // 修改为GPIOB
}

void Battery_CheckAndDisplay(void)
{
    if (TIme_300ms_Adc_Flag > 5)
    {
        TIme_300ms_Adc_Flag = 0;

        for (uint8_t i_cnt = 0; i_cnt < 16; i_cnt++)
        {
            Adc_array[i_cnt] = Get_ADC1_ChannelAverage(8); // 修改为ADC通道8，PB0对应的通道
        }

        Adc_Avg_Value = ADC_array_sort(Adc_array, 16);
        Adc_Data = (uint16_t)Adc_Avg_Value;

        if (Adc_Data < 30)
        {
            Adc_Data = 0;
        }

        if (Adc_Data > Previous_Adc_Value)
        {
            Difference_Value = Adc_Data - Previous_Adc_Value;
        }
        else
        {
            Difference_Value = Previous_Adc_Value - Adc_Data;
        }

        if (Difference_Value < 15)
        {
            Adc_Data = Previous_Adc_Value;
            Difference_Value = 0;
        }
        else
        {
            Difference_Value = 0;
        }

        Button_Cell_vol = Adc_Data / 4096.0 * 3.3;
        Button_Cell_vol = Button_Cell_vol * 147.0 / 47;
        Adc_Data = Button_Cell_vol * 100;

        Screen_RF_Data2 = Adc_Data / 100 % 10;
        Screen_RF_Data3 = Adc_Data / 10 % 10;
        Screen_RF_Data4 = Adc_Data % 10;

        HT_1621_Data_Library(Screen_Data_2_Addr1, Screen_Data_2_Addr2, Screen_RF_Data2);
        HT_1621_Data_Library(Screen_Data_3_Addr1, Screen_Data_3_Addr2, Screen_RF_Data3);
        HT_1621_Data_Library(Screen_Data_4_Addr1, Screen_Data_4_Addr2, Screen_RF_Data4);
        HT1621_WriteData4Bit(Screen_Data_V_Addr, Screen_Data_V);

        Previous_Adc_Value = Adc_Data;
    }

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; // 修改为PB0
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct); // 修改为GPIOB
    GPIO_ResetBits(GPIOB, GPIO_Pin_0); // 修改为PB0
    vTaskDelay(100000);
}

float ADC_array_sort(uint16_t *ACD_array, uint8_t Array_size)
{
    float return_value;
    uint16_t array_temp[16];
    uint32_t temp_array;
    uint8_t i, j;

    for (i = 0; i < Array_size; i++)
        array_temp[i] = ACD_array[i];

    for (i = 0; i < Array_size; i++)
    {
        for (j = 0; j < (Array_size - 1); j++)
        {
            if (array_temp[j] > array_temp[1 + j])
            {
                temp_array = array_temp[j];
                array_temp[j] = array_temp[1 + j];
                array_temp[1 + j] = temp_array;
            }
        }
    }

    if (Array_size == 10)
    {
        return_value = (float)((array_temp[1] + array_temp[2] + array_temp[3] + array_temp[4] + array_temp[5] + array_temp[6] + array_temp[7] + array_temp[8]) / 8.0);
    }
    else
    {
        return_value = (float)((array_temp[3] + array_temp[4] + array_temp[5] + array_temp[6] + array_temp[7] + array_temp[8] + array_temp[9] + array_temp[10] + array_temp[11] + array_temp[12]) / 10.0);
    }
    return return_value;
}









#include "battery.h"
// 其他包含的头文件

int main(void)
{
    // 初始化其他系统组件
    Mcu_Init();

    // 初始化电池检测模块
    Battery_Init();

    while (1)
    {
        // 调用电池检测和显示函数
        Battery_CheckAndDisplay();

        // 其他主循环代码
    }
}
