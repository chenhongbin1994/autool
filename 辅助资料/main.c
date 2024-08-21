/*
������������У�������λ������������ݵĵ�λ���� DATA_ADC1��DATA_ADC2 �� DATA_ADC_DIF �������ԭʼ���ݵ�λ����Щԭʼ����ͨ���ǴӴ�������ADC��ģ��ת��������ȡ����ֵ���ڴ����У�ͨ�� r_unit ����������Щԭʼ����ת��Ϊ������λ���� hPa��torr��mBar �ȡ�

�����Ǹ��� case ����ĵ�λ��

case 0: pa����˹����
case 1: hpa��������
case 2: torr���У�
case 3: mBar�����ͣ�
case 4: inHg��Ӣ�繯����
case 5: mmHg�����׹�����
case 6: inH2O��Ӣ��ˮ����
case 7: mmH2O������ˮ����
case 8: psi������ÿƽ��Ӣ�磩
case 9: Bar���ͣ�
case 10: kg/cm2��������ÿƽ�����ף�
��Щ��λ�ǲ�ͬѹ������ϵͳ�еĳ�����λ����ԭʼ���ݵ�λ��������λ��ͨ���Ǵ������ṩ��ԭʼ���ݣ���Щ���ݿ���ͨ��У׼��ת�����õ������ѹ����λ��
*/


#include "drv_led.h"
#include "drv_rcc.h"
#include "drv_systick.h"
#include "drv_usart.h"
#include "stdio.h"
#include <stdint.h>


// ����ѹ����λö������
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
            return pa; // Ĭ�Ϸ�����˹��
    }
}

int main(void)
{	
		// ʾ�����ݳ�ʼ��
   float pa = 1000.0f; // ��׼����ѹ����λ Pa
	
	
	
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

  



