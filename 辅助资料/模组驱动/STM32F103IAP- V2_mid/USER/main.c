/*********************************************************************************
  * �ļ���  ��main.c
 * ����    ��        
 * Ӳ�����ӣ�
 * 4��OLED��GND -> GND; VCC -> 3.3V; SCL -> PC4; SDA -> PC5;
 * ѹ��������1��VCC -> 5V; GND -> GND; AO -> PA0; 
 * ѹ��������2��VCC -> 5V; GND -> GND; AO -> PA2; 
 * USBת����ģ�飺GND -> GND; RX -> PA9; TX -> PA10; 
 * ����������������ѹֵHT1625��������ʾ��
             ���ڽ��ղ������õ���ѹֵ��������115200����
   ʹ��ʱ�Ƚ�������������У׼������У׼ֵ���� Voltage_0   Voltage_40 
**********************************************************************************/


#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "oled.h"
#include "LED.h"
#include "buzzer.h"

#include "common.h"
#include "gpio_defs.h"


int ADC_Channel0, ADC_Channel2;
float Pressure_V0=0.0, Pressure_V2=0.0;
long pressure0=0, pressure2=0;
uint8_t V_disbuff[2][5]={{0},{0}}; 
uint8_t P_disbuff[2][6]={{0},{0}};


//void BEND_Value_Conversion(int ch, int adcValue, long pressure)
//{
//    /* ��ʾ��ѹֵ */
//    V_disbuff[ch][0] = adcValue / 1000 + '0';
//    V_disbuff[ch][1] = (adcValue % 1000) / 100 + '0';
//    V_disbuff[ch][2] = (adcValue % 100) / 10 + '0';
//    V_disbuff[ch][3] = adcValue % 10 + '0';
//    
//    /* ��ʾѹ��ֵ */
//    if (pressure <= 0) pressure = 0;
//    if (pressure >= 40000) pressure = 40000;

//    P_disbuff[ch][0] = pressure / 10000 + '0';
//    P_disbuff[ch][1] = (pressure % 10000) / 1000 + '0';
//    P_disbuff[ch][2] = (pressure % 1000) / 100 + '0';
//    P_disbuff[ch][3] = (pressure % 100) / 10 + '0';
//    P_disbuff[ch][4] = pressure % 10 + '0';
//}
void BEND_Value_Conversion(int ch, int adcValue, float pressure)
	{
		long pressureInt;
    /* ��ʾ��ѹֵ */
    V_disbuff[ch][0] = adcValue / 1000 + '0';
    V_disbuff[ch][1] = (adcValue % 1000) / 100 + '0';
    V_disbuff[ch][2] = (adcValue % 100) / 10 + '0';
    V_disbuff[ch][3] = adcValue % 10 + '0';
    
    /* ��ʾѹ��ֵ */
    pressureInt = (long)(pressure * 1000);  // ת��Ϊ mbar��֧������ֵ
    if (pressureInt <= -99999) pressureInt = -99999; // ��Сѹ������
    if (pressureInt >= 99999) pressureInt = 99999;   // ���ѹ������

    if (pressureInt < 0) {  // ��ѹ����ʾ
        P_disbuff[ch][0] = '-';
        pressureInt = -pressureInt;
    } else {
        P_disbuff[ch][0] = ' ';
    }

    P_disbuff[ch][1] = pressureInt / 10000 + '0';
    P_disbuff[ch][2] = (pressureInt % 10000) / 1000 + '0';
    P_disbuff[ch][3] = (pressureInt % 1000) / 100 + '0';
    //P_disbuff[ch][4] = (pressureInt % 100) / 10 + '0';
    //P_disbuff[ch][5] = pressureInt % 10 + '0';
}


void Mcu_Init(void)
{
  /* system init */
	//SCB->VTOR = FLASH_BASE | 0x10000; /* Vector Table Relocation in Internal FLASH. */
	SystemInit();
  GPIO_Config();
  delay_init();	
  NVIC_Configuration();
  uart_init(115200);
	Adc1_Init();
	LED_Config();
  //Buzzer_Init();//���Ŷ���PA0����ADC_0ͨ����ͻ
	OLED_Init();
  OLED_ColorTurn(0);
  OLED_DisplayTurn(0);
  OLED_Refresh();
  delay_ms(2500);
  OLED_Clear();
}




int main(void)
{		
		int channelIndex;
		Mcu_Init();
    
    while(1)
    {
        for (channelIndex = 0; channelIndex < 2; channelIndex++) {
            int ch = channelIndex == 0 ? 0 : 2; // ʹ��ͨ��0��ͨ��2
            int adcValue = ADC1_Mid_GetAverageValue(ch, 10); // ��ȡÿ��ͨ����ƽ��ֵ
            float pressure = ADC1_Mid_MapValue(adcValue, 1.45,0.0125);
						printf("Channel %d: Voltage: %d mV, Pressure: %f mbar\r\n", ch, adcValue, pressure);
            BEND_Value_Conversion(channelIndex, adcValue, pressure);
						LEDR_OPEN();
						delay_ms(2500);
						LEDR_CLOSE();
						
            // ��ʾ��һ��ͨ��
            OLED_Clear();
            OLED_ShowString(0, 16, "CH_0:", 16, 0);
            OLED_ShowString(72, 16, V_disbuff[0], 16, 0);
            OLED_ShowString(0, 32, "Pre_0:", 16, 0);
            OLED_ShowString(72, 32, P_disbuff[0], 16, 0);

            // ��ʾ�ڶ���ͨ��
            OLED_ShowString(0, 48, "CH_2:", 16, 0);
            OLED_ShowString(72, 48, V_disbuff[1], 16, 0);
            OLED_ShowString(0, 64, "Pre_2:", 16, 0);
            OLED_ShowString(72, 64, P_disbuff[1], 16, 0);

            OLED_Refresh();
        }
        delay_ms(500);
    }
}

