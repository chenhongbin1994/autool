/*
在这个上下文中，基础单位是最初测量数据的单位，即 DATA_ADC1、DATA_ADC2 和 DATA_ADC_DIF 所代表的原始数据单位。这些原始数据通常是从传感器或ADC（模数转换器）读取的数值。在代码中，通过 r_unit 来决定将这些原始数据转换为其他单位，如 hPa、torr、mBar 等。

以下是各个 case 处理的单位：

case 0: pa（帕斯卡）
case 1: hpa（百帕）
case 2: torr（托）
case 3: mBar（毫巴）
case 4: inHg（英寸汞柱）
case 5: mmHg（毫米汞柱）
case 6: inH2O（英寸水柱）
case 7: mmH2O（毫米水柱）
case 8: psi（磅力每平方英寸）
case 9: Bar（巴）
case 10: kg/cm2（公斤力每平方厘米）
这些单位是不同压力测量系统中的常见单位，而原始数据单位（基础单位）通常是传感器提供的原始数据，这些数据可以通过校准和转换来得到所需的压力单位。
*/


#include "drv_led.h"
#include "drv_rcc.h"
#include "drv_systick.h"
#include "drv_usart.h"
#include "stdio.h"
#include <stdint.h>


typedef uint32_t UINT32;
// 全局变量声明
UINT32 DATA_ADC1[10];
UINT32 DATA_ADC2[10];
UINT32 DATA_ADC_DIF[10];
UINT32 DATA_Pressure[3];
int Rec_Data_Display_Num;
int r_unit;

// 函数声明
void Dsp_RUN_Mode(void);

int main(void)
{	
		// 示例数据初始化
    Rec_Data_Display_Num = 0;
    DATA_ADC1[0] = 1772;
    DATA_ADC2[0] = 1769;
    DATA_ADC_DIF[0] = 3541;
	
	
	
	RCC_DeInit();
	RCC_ConfigTo72MHZ();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	LED_Config();
	Systicks_Config(72);
	USART_Config();
	printf("hello world\n");
	
	 
   printf("---------------------pa-----------------------\n"); 
    // 设置 r_unit 的值
    r_unit = 0; // Pa	
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("---------------------hpa----------------------\n"); 
	 // 设置 r_unit 的值
    r_unit = 1; // HPa	
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("---------------------torr----------------------\n"); 
	// 设置 r_unit 的值
    r_unit = 2; // 	托(mm Hg = Torr)
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("---------------------mbar----------------------\n"); 
	 // 设置 r_unit 的值
    r_unit = 3; // mbar	
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("----------------inHg（英寸汞柱）----------------\n"); 
	 // 设置 r_unit 的值
    r_unit = 4; //inHg（英寸汞柱）	
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("-----------------mmHg（毫米汞柱）---------------\n"); 
	 // 设置 r_unit 的值
    r_unit = 5; // mmHg（毫米汞柱）
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("-----------------inH2O（英寸水柱）--------------\n"); 
	// 设置 r_unit 的值
    r_unit = 6; // 	inH2O（英寸水柱）
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("------------------mmH2O（毫米水柱）--------------\n"); 
	 // 设置 r_unit 的值
    r_unit = 7; // mmH2O（毫米水柱）	
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("--------------psi（磅力每平方英寸）---------------\n"); 
	 // 设置 r_unit 的值
    r_unit = 8; // psi（磅力每平方英寸）
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("---------------------Bar（巴）--------------------\n"); 
	// 设置 r_unit 的值
    r_unit = 9; // 	Bar（巴）
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("------------kg/cm2（公斤力每平方厘米）------------\n"); 
	 // 设置 r_unit 的值
    r_unit = 10; // kg/cm2（公斤力每平方厘米）	
	// 调用 Dsp_RUN_Mode 函数
    Dsp_RUN_Mode();
    // 打印结果以检查输出
    printf("Pressure 1: %u\n", DATA_Pressure[0]);
    printf("Pressure 2: %u\n", DATA_Pressure[1]);
    printf("Pressure Difference: %u\n", DATA_Pressure[2]);
	printf("--------------------------------------------------\n"); 
while(1){
	
	
	  LED_CTRL(Led_b, Led_open);
		Systicks_DelayNms(2000);
		LED_CTRL(Led_b, Led_close);
		Systicks_DelayNms(2000);	
}
}

  
void Dsp_RUN_Mode(void) {
    UINT32 tempdsp_unit;
    UINT32 tempdsp_unit_1;
    UINT32 u32_Positive_Side_Cur_Pressure = 1772; // 示例初始化
    UINT32 u32_Negative_Side_Cur_Pressure = 1769; // 示例初始化
    UINT32 CYL_p_avg[3] = {1772, 1769, 3541}; // 示例初始化
    
    switch (r_unit) {
        case 0: // pa
            // lcd_ram[ST65] |= S66; // pa
				//检查 Rec_Data_Display_Num 是否为非零值。如果为非零值，则表示我们需要使用存储在
				//数组 DATA_ADC1、DATA_ADC2 和 DATA_ADC_DIF 中的历史记录数据来进行显示。
            if (Rec_Data_Display_Num) {  
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num];
                DATA_Pressure[0] = (UINT32)(tempdsp_unit);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num];
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1);
                tempdsp_unit = DATA_ADC_DIF[Rec_Data_Display_Num];
                DATA_Pressure[2] = (UINT32)(tempdsp_unit);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure;
                DATA_Pressure[0] = (UINT32)tempdsp_unit;
                CYL_p_avg[1] = u32_Negative_Side_Cur_Pressure;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure;
                DATA_Pressure[1] = (UINT32)tempdsp_unit;
                tempdsp_unit = CYL_p_avg[2];
                DATA_Pressure[2] = (UINT32)tempdsp_unit;
            }
            break;
        case 1: // hpa
            // lcd_ram[ST65] |= S65; // hpa
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num];
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 10);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num];
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 10);
                tempdsp_unit = DATA_ADC_DIF[Rec_Data_Display_Num];
                DATA_Pressure[2] = (UINT32)(tempdsp_unit / 10);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 10;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 10;
                tempdsp_unit = CYL_p_avg[2];
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 10;
            }
            break;
        case 2: // torr
            // lcd_ram[ST65] |= S67; // torr
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] * 3000;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 40000);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] * 3000;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 40000);
                tempdsp_unit = DATA_ADC_DIF[Rec_Data_Display_Num] * 3000;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit / 40000);
            } else {
                tempdsp_unit_1 = u32_Positive_Side_Cur_Pressure * 3000;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit_1 / 40000);
                tempdsp_unit = u32_Negative_Side_Cur_Pressure * 3000;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit / 40000);
                tempdsp_unit = CYL_p_avg[2] * 3000;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit / 40000);
            }
            break;
        case 3: // mBar
            // lcd_ram[ST65] |= S68; // mBar
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num];
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 10);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num];
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 10);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num];
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1 / 10);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 10;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 10;
                tempdsp_unit = CYL_p_avg[2];
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 10;
            }
            break;
        case 4: // inHg
            // lcd_ram[ST65] |= S69; // inHg
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] * 14765;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 500000);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] * 14765;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 500000);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num] * 14765;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1 / 500000);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure * 14765;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 500000;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure * 14765;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 500000;
                tempdsp_unit = CYL_p_avg[2] * 14765;
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 500000;
            }
            break;
        case 5: // mmHg
            // lcd_ram[ST65] |= S70; // mmHg
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] * 3000;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 40000);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] * 3000;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 40000);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num] * 3000;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1 / 40000);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure * 3000;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 40000;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure * 3000;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 40000;
                tempdsp_unit = CYL_p_avg[2] * 3000;
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 40000;
            }
            break;
        case 6: // inH2O
            // lcd_ram[ST65] |= S71; // inH2O
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] * 4015;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 10000);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] * 4015;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 10000);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num] * 4015;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1 / 10000);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure * 4015;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 10000;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure * 4015;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 10000;
                tempdsp_unit = CYL_p_avg[2] * 4015;
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 10000;
            }
            break;
        case 7: // mmH2O
            // lcd_ram[ST77] |= S72; // mmH2O
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] * 10197;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 100000);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] * 10197;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 100000);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num] * 10197;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1 / 100000);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure * 10197;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 100000;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure * 10197;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 100000;
                tempdsp_unit = CYL_p_avg[2] * 10197;
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 100000;
            }
            break;
        case 8: // psi
            // lcd_ram[ST77] |= S74; // psi
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] * 1000;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 68950);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] * 1000;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 68950);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num] * 1000;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1 / 68950);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure * 1000;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 68950;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure * 1000;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 68950;
                tempdsp_unit = CYL_p_avg[2] * 1000;
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 68950;
            }
            break;
        case 9: // Bar
            // lcd_ram[ST77] |= S76; // Bar
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] / 10;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] / 10;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num] / 10;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure / 10;
                DATA_Pressure[0] = (UINT32)tempdsp_unit;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure / 10;
                DATA_Pressure[1] = (UINT32)tempdsp_unit;
                tempdsp_unit = CYL_p_avg[2] / 10;
                DATA_Pressure[2] = (UINT32)tempdsp_unit;
            }
            break;
        case 10: // kg/cm2
            // lcd_ram[ST77] |= S77; // kg/cm2
            if (Rec_Data_Display_Num) {
                tempdsp_unit = DATA_ADC1[Rec_Data_Display_Num] * 10197;
                DATA_Pressure[0] = (UINT32)(tempdsp_unit / 10000000);
                tempdsp_unit_1 = DATA_ADC2[Rec_Data_Display_Num] * 10197;
                DATA_Pressure[1] = (UINT32)(tempdsp_unit_1 / 10000000);
                tempdsp_unit_1 = DATA_ADC_DIF[Rec_Data_Display_Num] * 10197;
                DATA_Pressure[2] = (UINT32)(tempdsp_unit_1 / 10000000);
            } else {
                tempdsp_unit = u32_Positive_Side_Cur_Pressure * 10197;
                DATA_Pressure[0] = (UINT32)tempdsp_unit / 10000000;
                tempdsp_unit = u32_Negative_Side_Cur_Pressure * 10197;
                DATA_Pressure[1] = (UINT32)tempdsp_unit / 10000000;
                tempdsp_unit = CYL_p_avg[2] * 10197;
                DATA_Pressure[2] = (UINT32)tempdsp_unit / 10000000;
            }
            break;
        default:
            break;
    }
}




