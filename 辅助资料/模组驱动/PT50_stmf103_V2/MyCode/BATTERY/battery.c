#include "battery.h"
#include "HT61666_LCD.h" 
#include "adc.h" 
#include "delay.h"

#define RF_PACKET_SIZE 32
#define Screen_Data_2_Addr1 0x00 // 根据具体地址定义
#define Screen_Data_2_Addr2 0x00 // 根据具体地址定义
#define Screen_Data_3_Addr1 0x00 // 根据具体地址定义
#define Screen_Data_3_Addr2 0x00 // 根据具体地址定义
#define Screen_Data_4_Addr1 0x00 // 根据具体地址定义
#define Screen_Data_4_Addr2 0x00 // 根据具体地址定义
#define Screen_Data_V_Addr 0x00 // 根据具体地址定义

uint8_t TIme_300ms_Adc_Flag;
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
		GPIO_InitTypeDef GPIO_InitStruct;
    // 初始化 ADC 
		Adc2_Init();    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; // 修改为PB0
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct); // 修改为GPIOB
}

void Battery_CheckAndDisplay(void)
{
	u8 i_cnt=0;
	GPIO_InitTypeDef GPIO_InitStruct;
    if (TIme_300ms_Adc_Flag > 5)
    {
        TIme_300ms_Adc_Flag = 0;

        for ( i_cnt = 0; i_cnt < 16; i_cnt++)
        {
            Adc_array[i_cnt] = ADC2_Mid_GetValue(8); // 修改为ADC通道8，PB0对应的通道
        }

        Adc_Avg_Value = ADC2_array_sort(Adc_array, 16);
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

//        HT_1621_Data_Library(Screen_Data_2_Addr1, Screen_Data_2_Addr2, Screen_RF_Data2);
//        HT_1621_Data_Library(Screen_Data_3_Addr1, Screen_Data_3_Addr2, Screen_RF_Data3);
//        HT_1621_Data_Library(Screen_Data_4_Addr1, Screen_Data_4_Addr2, Screen_RF_Data4);
//        HT1621_WriteData4Bit(Screen_Data_V_Addr, Screen_Data_V);

        Previous_Adc_Value = Adc_Data;
    }

    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; // 修改为PB0
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct); // 修改为GPIOB
    GPIO_ResetBits(GPIOB, GPIO_Pin_0); // 修改为PB0
//    //vTaskDelay(100000);
		delay_ms(2500);
}
#if 0
void Battery_Level_Check(void)
{
    uint16_t Adc_Data = ADC2_Mid_GetValue(8);
    uint16_t Adc_Restrict = Previous_Adc_Value;
    uint16_t adc_dat;
    uint8_t Electric_quantity;

    if (Adc_Restrict > Adc_Data)
        adc_dat = Adc_Restrict - Adc_Data;
    else
        adc_dat = Adc_Data - Adc_Restrict;

    if (adc_dat < 66)
    {
        Adc_Data = Adc_Restrict;
    }
    else
    {
        Adc_Restrict = Adc_Data;
    }

    if (Adc_Data < 2500)
    {
        Adc_Data = ADC2_Mid_GetValue(8);
    }

    if (Adc_Data < 3100)
    {
        Electric_quantity = 1;
    }
    else if (Adc_Data < 3460)
    {
        Electric_quantity = 2;
    }
    else if (Adc_Data < 3750)
    {
        Electric_quantity = 3;
    }
    else if (Adc_Data < 4000)
    {
        Electric_quantity = 4;
    }
    else
    {
        Electric_quantity = 5;
    }

    if (4 !=   R_mode)
    {
        switch (Electric_quantity)
        {
        case 1:
            if (Battery_dead_sign == 1)
            {
                HT1621_WriteData4Bit(Screen_Data_S1_Addr, 0);
                HT1621_WriteData4Bit(Screen_Data_S5_Addr, 0);
                HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_S5);
            }
            else
            {
                HT1621_WriteData4Bit(Screen_Data_S1_Addr, 0);
                HT1621_WriteData4Bit(Screen_Data_S5_Addr, 0);
            }
            break;

        case 2:
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_S5);
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, Screen_Data_S1);
            break;
        case 3:
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_S5);
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, Screen_Data_S1 + Screen_Data_S2);
            break;
        case 4:
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_S5);
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, Screen_Data_S1 + Screen_Data_S2 + Screen_Data_S3);
            break;
        case 5:
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, 0);
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_S5);
            HT1621_WriteData4Bit(Screen_Data_S1_Addr, Screen_Data_S1 + Screen_Data_S2 + Screen_Data_S3 + Screen_Data_S4);
            break;
        }
    }

    if (1 == R_mode)
    {
        if (1 != Electric_quantity)
        {
            HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_S5 + Screen_Data_BAT);
        }
        else
        {
            if (Battery_dead_sign == 1)
            {
                HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_S5 + Screen_Data_BAT);
            }
            else
            {
                HT1621_WriteData4Bit(Screen_Data_S5_Addr, Screen_Data_BAT);
            }
        }
    }

    if (1 == Beep_Flag)
    {
        Time_5min_flag = 1;
        Beep_Flag = 0;
        Full_Scale_Warning();
        GPIO_ResetBits(GPIOC, GPIO_Pin_8); // 确保PC8为低时停止蜂鸣器
    }
    else
    {
        system_delay_10us(1000);
    }

    if (Time_1s_Flag == 1)
    {
        Time_1s_Flag = 0;
    }
}

#endif 

float ADC2_array_sort(uint16_t *ACD2_array, uint8_t Array_size)
{
    float return_value;
    uint16_t array_temp[16];
    uint32_t temp_array;
    uint8_t i, j;

    for (i = 0; i < Array_size; i++)
        array_temp[i] = ACD2_array[i];

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





#if 0

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
#endif
