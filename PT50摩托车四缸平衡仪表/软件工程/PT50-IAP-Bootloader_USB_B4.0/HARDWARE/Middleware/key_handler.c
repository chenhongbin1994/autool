#include "key_handler.h"
#include "stdio.h"
#include "buzzer.h"
#include "delay.h"
#include "LCD_HT1623.h"
#include "stmflash.h"
#include "iap.h"
#include "usart.h"
#include "hw_config.h"
extern	u16 oldcount;				//�ϵĴ��ڽ�������ֵ
extern  u16 applenth;				//���յ���app���볤��
extern  u8  clearflag;


extern float pressure_offset[4];// ���ڴ洢У׼��ѹ��ƫ��ֵ
// �������ýṹ����ⲿ����
extern KEY_Configure_TypeDef Key0Cfg;
//extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
//extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;





Settings current_settings;  // ��ǰ����

u8 Zero_flag = 0;  // �����־


#if 1
 int power_on = 0;
    static int backlight_on = 0;
// ������0�¼�
void Handle_Key0_Event(KEY_EventList_TypeDef event) {    
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            backlight_on = !backlight_on;
            if (!backlight_on) {
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // ���⿪
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
							delay_ms(50);
            } else {
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // �����
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);
            }
            break;
        case KEY_Event_LongPress:            
            power_on = !power_on;
            if (power_on) {
                GPIO_SetBits(GPIOA, GPIO_Pin_4);  // ��Դ��
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // ���⿪
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
							delay_ms(50);
            } else {
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // �����
								cleandisp();//������һЩ���ܿ��ܲ�������������Ŀǰ�ǵ�����
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);
                GPIO_ResetBits(GPIOA, GPIO_Pin_4);  // �ػ���Դ
            }
            break;
        default:
            break;
    }
}
#endif

// ������2�¼�
void Handle_Key2_Event(KEY_EventList_TypeDef event) {
   
   
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            if(applenth)
    {
      usb_printf("��ʼ���¹̼�...\r\n");
      if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
      {
        iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//����FLASH����
        usb_printf("�̼��������!\r\n");
      }
      else
      {
        usb_printf("��FLASHӦ�ó���!\r\n");
      }
    }
    else
    {
      usb_printf("û�п��Ը��µĹ̼�!\r\n");
    }
    clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ
  
            break;
        case KEY_Event_LongPress:
           
            break;
        default:
            break;
    }
}

// ������3�¼� 
void Handle_Key3_Event(KEY_EventList_TypeDef event) {
   
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
        usb_printf("��ʼִ��FLASH�û�����!!\r\n");
    if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
    {
			//������Ҫ�ӹر��������ͼ�꣬����ֱ�ӹػ�
			NVIC_SystemReset();	
      //iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
    }
    else
    {
      usb_printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
    }
    clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ  
            break;
        case KEY_Event_LongPress:
           usb_printf("��ʼִ��SRAM�û�����!!\r\n");
    if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x20000000)//�ж��Ƿ�Ϊ0X20XXXXXX.
    {
      iap_load_app(0X20001000);//SRAM��ַ
    }
    else
    {
      usb_printf("��SRAMӦ�ó���,�޷�ִ��!\r\n");
    }
    clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ
            break;
        default:
            break;
    }
}


// ������5�¼�
void Handle_Key5_Event(KEY_EventList_TypeDef event) {
   
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // ������������100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            UpdateReadModifyWriteDisplay(15, Screen_Data_Zero, 1);
            Zero_flag = 1;
            delay_ms(300);
            UpdateReadModifyWriteDisplay(15, Screen_Data_Zero, 0);
            printf("ZERO\r\n");
		usb_printf("û�п��Ը��µĹ̼�!\r\n");
    if(applenth)
    {
      usb_printf("�̼�������!\r\n");
      applenth=0;
    }
    else
    {
      usb_printf("û�п�������Ĺ̼�!\r\n");
    }
    clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ
  
            break;
        case KEY_Event_LongPress:        
            
            
            break;
        default:
            break;
    }
}

// ����������
void KeyHandler_Process(void) {
    if (Key0Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key0_Event(Key0Cfg.KEY_Event);
        Key0Cfg.KEY_Event = KEY_Event_Null;
    }

    if (Key2Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key2_Event(Key2Cfg.KEY_Event);
        Key2Cfg.KEY_Event = KEY_Event_Null;
    }
    if (Key3Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key3_Event(Key3Cfg.KEY_Event);
        Key3Cfg.KEY_Event = KEY_Event_Null;
    }

    if (Key5Cfg.KEY_Event != KEY_Event_Null) {
        Handle_Key5_Event(Key5Cfg.KEY_Event);
        Key5Cfg.KEY_Event = KEY_Event_Null;
    }
}
