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
#include "timer.h"

#if 0
extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
 int main(void)
 {		
 	u32 temp=0; 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Config();			     //LED�˿ڳ�ʼ��
 
 	TIM3_PWM_Init(899,0); 		//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
 	TIM5_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
   	while(1)
	{
 		delay_ms(10);
	
		TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);

		if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
			TIM5CH1_CAPTURE_STA=0;//������һ�β���
		}
	}
 }
#endif


#if 1
int ADC_Channel0, ADC_Channel2;
float Pressure_V0=0.0, Pressure_V2=0.0;
long pressure0=0, pressure2=0;
uint8_t V_disbuff[2][5]={{0},{0}}; 
uint8_t P_disbuff[2][6]={{0},{0}};


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
            float pressure = ADC1_Mid_MapValue(adcValue, 1.43,0.0125);
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
#endif
