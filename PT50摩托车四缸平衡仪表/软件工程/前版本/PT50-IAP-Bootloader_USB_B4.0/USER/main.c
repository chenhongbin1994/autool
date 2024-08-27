#include "includes.h"
extern u8 firmware_received;
  u16 oldcount=0;				//老的串口接收数据值
  u16 applenth=0;				//接收到的app代码长度
  u8 clearflag=0;
	extern int power_on;
	extern uint32_t Long_press_cnt ;
void Usb_Init(void)
{
  USB_Port_Set(0); 	//USB先断开
  delay_ms(100);
  USB_Port_Set(1);	//USB再次连接
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

	KEY_Init();					//初始化按键	
		//while(!power_on);
	for (int i = 0; i < 0xFFFF; i++) {
			if(GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_3)== 1) {
					if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
					{
						iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
					}
			}
	}
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Battery_Init();//电池电压检测和EN_OUT初始化
  uart_init(115200);	//串口初始化为115200
	TIM3_Int_Init(50-1,7200-1); 
	SystemInit ();
  delay_init();	   	 	//延时初始化
	while(!power_on);
	LCD_Init();					//部分图标初始化
	Usb_Init();

#if 1
while(1)
{
	
		if((power_on == 1)&& (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 0))
		{
			 Long_press_cnt =0;
		}

	if(usbstatus!=bDeviceState)//USB连接状态发生了改变.
		{
			usbstatus=bDeviceState;//记录新的状态
			if(usbstatus==CONFIGURED)
			{
				
				//提示USB连接成功
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,1);
				UpdateReadModifyWriteDisplay(14,Screen_Data_TypeC,1);
			}else
			{
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,0); 
				UpdateReadModifyWriteDisplay(14,Screen_Data_TypeC,0);
				//提示USB断开
			}
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			len=USB_USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			usb_printf("\r\n您发送的消息为:%d\r\n\r\n",len);
			for(t=0;t<len;t++)
			{
				USB_USART_SendData(USB_USART_RX_BUF[t]);//以字节方式,发送给USB 
			}
			usb_printf("\r\n\r\n");//插入换行
			USB_USART_RX_STA=0;
		}
  

  

  }


}


#endif







