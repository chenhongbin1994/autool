/*
* @Author: ChenHongBin 944278386@qq.com
* @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-21 14:29:47
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
/*-------------------------------������-------------------------------------*/
extern Settings current_settings;
//��ʱ����־λ
extern volatile  u8 Flag_o5s_Disp,PressureDisp,flag_10ms,Battery_ADCflag,Clock_flag;

//������־λ
//extern u8 lock_flag,longocked_flag,Switch_flag;

 extern u8  TIM1CH1_CAPTURE_STA;		//���벶��״̬		    				
 extern u16	TIM1CH1_CAPTURE_VAL;	//���벶��ֵ
extern int value;
/*-------------------------------������-------------------------------------*/
extern int history_index;  // ��ǰ��¼������
extern int current_history_display;//��ʷ����ģʽ
extern u8  Timing_Switch_5min;
extern u8   Timing_Switch_5min,MinAuto,SecondAuto; 
extern u8 Zero_flag,REC_flag;
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
  SystemInit();//IAPʱ��Ҫ����VECT_TAB_OFFSET�ĵ�ַ
  delay_init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  InitializeSettings();//flash��ı�־λ��ʼ��
  uart_init(115200);
  Battery_Init();//��ص�ѹ����EN_OUT��ʼ��
   Usb_Init();//USB��ʼ��
  ADC_Init_t();
  Buzzer_Init();//���Ŷ���PA0����ADC_0ͨ����ͻ
	KEY_Init();
  TIM3_Int_Init(50-1,7200-1); //TIM3_Int_Init(200-1,7200-1);���ö�ʱ��ʹ��20ms����һ���жϣ�TIM3_Int_Init(49, 7199); // 5ms�жϣ�TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
}




int main(void)
{
  /*-------------------------------����������-------------------------------------*/ 
  u32 temp=0; 



	u8 usbstatus=0;	
  float coefficient = 1.45;//ѹ������ϵ��
  float Kvalue = 0.0125;//ѹ������Kֵ
  /*-------------------------------����������-------------------------------------*/
  Mcu_Init();
	while(!power_on);
  LCD_Init();//����ͼ���ʼ��
  printf("----------------�汾��V1.0-------------\n");
  calculateBatteryVoltage(5);
  AUutoshutdownONOFF_display();
  TIM1_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
  // ʹ��ȫ���ж�
    __enable_irq();
  printf("��ʷ��¼����:%d\n",history_index); //
  // Digital_tube_display(26, 27, 28, 29,30, 55555, 1900);//1�Ÿ�
  // delay_ms(2000);
  while(1)
  {
		//printf("�������ɷ���\n");delay_ms(500);
#if 1  //�Ƿ����USB״̬�ж�   

    //WFI_SET();//˯��ģʽ

  
		if(usbstatus!=bDeviceState)//USB����״̬�����˸ı�.
		{
      INTX_DISABLE();//�ر������ж�
			usbstatus=bDeviceState;//��¼�µ�״̬
			if(usbstatus==CONFIGURED)
			{				
				//��ʾUSB���ӳɹ�
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,1);
			}else
			{
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,0); 
				//��ʾUSB�Ͽ�

			}
      INTX_ENABLE();//���������ж�
		}
#endif //�Ƿ����USB״̬�ж�

		if((power_on == 1)&& (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 0))
		{
			 Long_press_cnt =0;

		}

    if((Clock_flag == 1)&&(!settings_mode)&&(lock_flag == 0)&&((current_history_display == -1)))//ʱ�ӷ��ⲻ׼���Ŷ�ʱ���ж�׼
    {
      INTX_DISABLE();//�ر������ж�
      if(Zero_flag ==1){
        Zero_flag =0;
            Dig_Zero();                      
      }
      Clock_flag = 0;
      Clock();
      
      // Digital_tube_display(21, 22, 23, 24,25, 888, 1900);//1�Ÿ�
      INTX_ENABLE(); //���������ж�
    }           
    if((PressureDisp == 1)&&(!settings_mode)&&(lock_flag == 0)&&(longocked_flag == 0)&&((current_history_display == -1)))
    {
      INTX_DISABLE();//�ر������ж�
      PressureDisp = 0;
      ProcessAndDisplayPressureValues(coefficient, Kvalue);//�ĸ�ѹ����ʾ��ϵ��=1.45, Kֵ0.0125
      
      //Digital_tube_display(21, 22, 23, 24,25, i, 1900);//1�Ÿ�
      INTX_ENABLE();//���������ж�
    }
    
    if((Flag_o5s_Disp == 1)&&(!settings_mode)&&(lock_flag == 0)&&(longocked_flag == 0)&&((current_history_display == -1)))
    {
        	Flag_o5s_Disp = 0;
          
          //printf("δץ��HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
          delay_ms(100);
 		      if(TIM1CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		      {
			        temp=TIM1CH1_CAPTURE_STA&0X3F;
			        temp*=65536;//���ʱ���ܺ�
			        temp+=TIM1CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			        printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
			        TIM1CH1_CAPTURE_STA=0;//������һ�β���
              temp =0;
		      }
          if (value > 0)
        {
            // �����񵽵�����ֵ
            printf("Captured Pulse Width: %d\n", value);

            // ��ղ���ֵ�Ա����ظ���ӡ
            value = 0;
        }


    }
    //uiFanSpeed = 60*(Tim_Chn1_CountSUM/TIM1CH1_CAPTURE_VAL)/2;
    //����ת��  N = 60*f/P; p = 2; f = TIM2CH1_CAPTURE_VAL/

    if(Battery_ADCflag == 2)//6v��Դ��ѹ���,�����Ӽ��һ��
    {
      INTX_DISABLE();//�ر������ж�
      Battery_ADCflag = 0;
      calculateBatteryVoltage(5);
      INTX_ENABLE();//���������ж�
    }

/*----------------------------------------------------Auto�Զ��ػ�------------------------------------------------------------*/
    if((current_settings.auto_shutdown_enabled == 1)&&(Timing_Switch_5min == 5))//AutoONOFF
    {
        Timing_Switch_5min = 0;
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);  // �����
        cleandisp();          
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);  // ��Դ
    }
    if(ADC_Value[0]<1700){MinAuto = 0;SecondAuto = 0;Timing_Switch_5min =0;}//�Զ��ػ��ر������¼�ʱ  
/*----------------------------------------------------Auto�Զ��ػ�------------------------------------------------------------*/   
  }

}















