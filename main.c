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


// 声明压力单位枚举类型
typedef enum {
    UNIT_PA,
    UNIT_HPA,
    UNIT_TORR,
    UNIT_MBAR,
    UNIT_INHG,
    UNIT_MMHG,
    UNIT_INH2O,
    UNIT_MMH2O,
    UNIT_PSI,
    UNIT_BAR,
    UNIT_KGCM2
} PressureUnit;

float convert_pressure(float pa, PressureUnit target_unit) {
    switch (target_unit) {
        case UNIT_HPA:
            return pa / 100.0f;
        case UNIT_TORR:
            return pa / 133.322f;
        case UNIT_MBAR:
            return pa / 100.0f;
        case UNIT_INHG:
            return pa / 3386.39f;
        case UNIT_MMHG:
            return pa / 133.322f;
        case UNIT_INH2O:
            return pa / 249.082f;
        case UNIT_MMH2O:
            return pa / 9.80665f;
        case UNIT_PSI:
            return pa / 6894.76f;
        case UNIT_BAR:
            return pa / 100000.0f;
        case UNIT_KGCM2:
            return pa / 98066.5f;
        default:
            return pa; // 默认返回帕斯卡
    }
}

int main(void)
{	
		// 示例数据初始化
   float pa = 1000.0f; // 标准大气压，单位 Pa
	
	
	
	RCC_DeInit();
	RCC_ConfigTo72MHZ();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	LED_Config();
	Systicks_Config(72);
	USART_Config();
	printf("hello world\n");
	
		printf("Pa to hPa: %.2f\n", convert_pressure(pa, UNIT_HPA));
    printf("Pa to Torr: %.2f\n", convert_pressure(pa, UNIT_TORR));
    printf("Pa to mBar: %.2f\n", convert_pressure(pa, UNIT_MBAR));
    printf("Pa to inHg: %.2f\n", convert_pressure(pa, UNIT_INHG));
    printf("Pa to mmHg: %.2f\n", convert_pressure(pa, UNIT_MMHG));
    printf("Pa to inH2O: %.2f\n", convert_pressure(pa, UNIT_INH2O));
    printf("Pa to mmH2O: %.2f\n", convert_pressure(pa, UNIT_MMH2O));
    printf("Pa to psi: %.2f\n", convert_pressure(pa, UNIT_PSI));
    printf("Pa to Bar: %.5f\n", convert_pressure(pa, UNIT_BAR));
    printf("Pa to kg/cm2: %.5f\n", convert_pressure(pa, UNIT_KGCM2));
	while(1){
	
	
	  LED_CTRL(Led_b, Led_open);
		Systicks_DelayNms(2000);
		LED_CTRL(Led_b, Led_close);
		Systicks_DelayNms(2000);	
}
}

  



