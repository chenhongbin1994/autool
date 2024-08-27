#include "includes.h"
extern u8 firmware_received;
  u16 oldcount=0;				//�ϵĴ��ڽ�������ֵ
  u16 applenth=0;				//���յ���app���볤��
  u8 clearflag=0;
	extern int power_on;
	extern uint32_t Long_press_cnt ;
void Usb_Init(void)
{
  USB_Port_Set(0); 	//USB�ȶϿ�
  delay_ms(100);
  USB_Port_Set(1);	//USB�ٴ�����
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
}

int main(void)
{
  u16 t;
	u16 len;	
	u16 times=0;    
	u8 usbstatus=0;	

	KEY_Init();					//��ʼ������	
		//while(!power_on);
	for (int i = 0; i < 0xFFFF; i++) {
			if(GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_3)== 1) {
					if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
					{
						iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
					}
			}
	}
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Battery_Init();//��ص�ѹ����EN_OUT��ʼ��
  uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	TIM3_Int_Init(50-1,7200-1); 
	SystemInit ();
  delay_init();	   	 	//��ʱ��ʼ��
	while(!power_on);
	LCD_Init();					//����ͼ���ʼ��
	Usb_Init();

#if 1
while(1)
{
	
		if((power_on == 1)&& (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 0))
		{
			 Long_press_cnt =0;
		}

	if(usbstatus!=bDeviceState)//USB����״̬�����˸ı�.
		{
			usbstatus=bDeviceState;//��¼�µ�״̬
			if(usbstatus==CONFIGURED)
			{
				
				//��ʾUSB���ӳɹ�
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,1);
				UpdateReadModifyWriteDisplay(14,Screen_Data_TypeC,1);
			}else
			{
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,0); 
				UpdateReadModifyWriteDisplay(14,Screen_Data_TypeC,0);
				//��ʾUSB�Ͽ�
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
		}
  

  

  }


}


#endif







