#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	 
 

 int main(void)
 {	 
 	u16 t;
	u16 len;	
	u16 times=0;    
	u8 usbstatus=0;	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	delay_ms(1800);
	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(700);
	USB_Port_Set(1);	//USB�ٴ�����
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	    
	while(1)
	{
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
			if(times%200==0)usb_printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}
}

