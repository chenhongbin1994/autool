/*
* @Author: ChenHongBin 944278386@qq.com
* @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-07-15 14:51:18
* @FilePath: \Projectc:\Users\IBM\Desktop\PT50project\PT50_stmf103_vscode_V5\App\main.c
* @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
*/
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
#include "includes.h"

#if 1
/*-------------------------------������-------------------------------------*/
//��ʱ����־λ
extern volatile  u8 Flag_o5s_Disp,flag_10ms,Battery_ADCflag,Clock_flag,AutoONOFF_flag;

//������־λ
extern u8 lock_flag,longocked_flag;
extern volatile u8 LCD_BUF[48];
extern uint16_t ADC_Value[4];


/*-------------------------------������-------------------------------------*/


/*--------------------------Mycode-------------------------------*/
//��ʼ��
void Usb_Init(void)
{
  USB_Port_Set(0); 	//USB�ȶϿ�
  delay_ms(100);
  USB_Port_Set(1);	//USB�ٴ�����
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
}
/*--------------------------Mycode-------------------------------*/

/*--------------------------Mycode-------------------------------*/
void Mcu_Init(void)
{
  /* system init */
  //SCB->VTOR = FLASH_BASE | 0x10000; /* Vector Table Relocation in Internal FLASH. */
  SystemInit();
  delay_init();
  NVIC_Configuration();
  InitializeSettings();//flash��ı�־λ��ʼ��
  uart_init(115200);
  Battery_Init();//��ص�ѹ����EN_OUT��ʼ��
  Usb_Init();//USB��ʼ��
  ADC_Init_t();
  Buzzer_Init();//���Ŷ���PA0����ADC_0ͨ����ͻ
  TIM3_Int_Init(50-1,7200-1); //TIM3_Int_Init(200-1,7200-1);���ö�ʱ��ʹ��20ms����һ���жϣ�TIM3_Int_Init(49, 7199); // 5ms�жϣ�TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
  KEY_Init();
}

extern int current_history_display;
int main(void)
{
  /*-------------------------------����������-------------------------------------*/

  /*-------------------------------����������-------------------------------------*/
  Mcu_Init();
  //ADC2_Init();
  LCD_Init();//����ͼ���ʼ��
  printf("----------------in development-------------\n");
  

  while(1)
  {
    if((Clock_flag == 1)&&(lock_flag == 0))//ʱ�ӷ��ⲻ׼���Ŷ�ʱ���ж�׼
    {
      Clock_flag = 0;
      Clock();
    }           
    if((Flag_o5s_Disp == 1)&&(lock_flag == 0)&&(longocked_flag == 0)&&((current_history_display == -1)))
    {
      Flag_o5s_Disp = 0;
      ProcessAndDisplayPressureValues(1.45, 0.0125);//�ĸ�ѹ����ʾ��ϵ��=1.45, Kֵ0.0125
    }
    if(Battery_ADCflag == 1)//6v��Դ��ѹ���,������5S����ʾ�������
    {
      Battery_ADCflag = 0;
      calculateBatteryVoltage(5);
    }
    // if(AutoONOFF_flag == 1)//
    // {
    // }
    //delay_ms(1000);
  }
}

#endif














