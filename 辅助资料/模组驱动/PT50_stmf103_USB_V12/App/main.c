/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-06-19 09:17:08
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


#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "LED.h"
#include "buzzer.h"
#include "timer.h"
#include "key.h"
#include "LCD_HT1623.h" 

#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	
void USB_APP(void);
#if 1
/*-------------------------------������-------------------------------------*/
extern volatile u8 LCD_BUF[48];
void TurnOnSegment(u8 segment) {
    LCD_BUF[0] |= segment;  // ��pin18��Ӧ�Ļ�����λ��������λ
}

void UpdateDisplay(void) {
    W1623_success(0, 48,LCD_BUF);
	//W1623_success(8, 2,LCD_BUF);
}
/*-------------------------------������-------------------------------------*/


/*--------------------------Mycode-------------------------------*/
//��ʼ��
void Usb_Init(void)
{
	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(700);
	USB_Port_Set(1);	//USB�ٴ�����
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	    	
}
//����app


/*--------------------------Mycode-------------------------------*/

void Mcu_Init(void)
{
  /* system init */
	//SCB->VTOR = FLASH_BASE | 0x10000; /* Vector Table Relocation in Internal FLASH. */
	SystemInit();
  delay_init();	
  NVIC_Configuration();
  uart_init(115200);
	Usb_Init();//USB��ʼ��
	ADC1_Init();
	Button_Init();//������ʼ��
	One_Backlight();//�����ʼ��	
  TIM2_Backlight_PWM_Init();//��ʼ������pwm	
  Buzzer_Init();//���Ŷ���PA0����ADC_0ͨ����ͻ

}


int main(void)
{			
/*-------------------------------USB������-------------------------------------*/
	 u16 t;
	 u16 len;	
	 u16 times=0;    
	 u8 usbstatus=0;	
/*-------------------------------USB������-------------------------------------*/
		Mcu_Init();	 		
		LCD_GpioInit(  );
		LCD_Init();
/*-------------------------------������-------------------------------------*/
		cleandisp();
	//disp_All();
    //TurnOnSegment(0x80);

    //UpdateDisplay();
			printf("----------------in development-------------\n");
	// ��ȡLCD��ַ0������
  //unsigned char Data = HT1623_ReadByte(0);
	 //printf("\r\nRead data: 0x%02X\r\n", Data);
		// ִ�ж�-�޸�-д����
    //HT1623_ReadData_From_Lcd(addr, value, opr);
	

	
	
//	for (int i = 0; i < 48; i++) {
//        LCD_BUF[i] = 0x00;
//    }    
//    // �� SEG 2 �� COM 3 ��
//    dispON(4, 1);

  
	
	
/*-------------------------------������-------------------------------------*/

	
	
	
    while(1)
    {		
usb_printf("\r\nUSB Connected\r\n\r\n");


		Button_Debounce();	
#if 1
/*-------------------------------USB������-------------------------------------*/						
			if(usbstatus!=bDeviceState)//USB����״̬�����˸ı�.
		{
			usbstatus=bDeviceState;//��¼�µ�״̬
			if(usbstatus==CONFIGURED)
			{
				
				usb_printf("\r\nUSB Connected\r\n\r\n",len);
				
			}else
			{
				usb_printf("\r\nUSB disConnected\r\n\r\n",len);
				
			}
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			len=USB_USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
			usb_printf("\r\n�����͵���ϢΪ:%d\r\n\r\n",len);
			for(t=0;t<len;t++)
			{
				USB_USART_SendData(USB_USART_RX_BUF[t]);//���ֽڷ�ʽ,���͸�USB 
			}
			usb_printf("\r\n\r\n");//���뻻��
			USB_USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				usb_printf("\r\nUSB���⴮��ʵ��\r\n");
				
			}
			//if(times%200==0)usb_printf("����������,�Իس�������\r\n");  
			//if(times%30==0)usb_printf("��˸LED,��ʾϵͳ��������\r\n");//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
/*-------------------------------USB������-------------------------------------*/			
#endif
    }
}
#endif










