/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-06-19 09:17:08
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50project\PT50_stmf103_vscode_V5\App\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*********************************************************************************
  * 文件名  ：main.c
 * 描述    ：        
 * 硬件连接：
 * 4针OLED：GND -> GND; VCC -> 3.3V; SCL -> PC4; SDA -> PC5;
 * 压力传感器1：VCC -> 5V; GND -> GND; AO -> PA0; 
 * 压力传感器2：VCC -> 5V; GND -> GND; AO -> PA2; 
 * USB转串口模块：GND -> GND; RX -> PA9; TX -> PA10; 
 * 功能描述：测量气压值HT1625断码屏显示；
             串口接收测量所得的气压值（波特率115200）；
   使用时先进行零点和满量程校准，依据校准值调整 Voltage_0   Voltage_40 
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
/*-------------------------------测试用-------------------------------------*/
extern volatile u8 LCD_BUF[48];
void TurnOnSegment(u8 segment) {
    LCD_BUF[0] |= segment;  // 在pin18对应的缓冲区位置上设置位
}

void UpdateDisplay(void) {
    W1623_success(0, 48,LCD_BUF);
	//W1623_success(8, 2,LCD_BUF);
}
/*-------------------------------测试用-------------------------------------*/


/*--------------------------Mycode-------------------------------*/
//初始化
void Usb_Init(void)
{
	USB_Port_Set(0); 	//USB先断开
	delay_ms(700);
	USB_Port_Set(1);	//USB再次连接
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	    	
}
//测试app


/*--------------------------Mycode-------------------------------*/

void Mcu_Init(void)
{
  /* system init */
	//SCB->VTOR = FLASH_BASE | 0x10000; /* Vector Table Relocation in Internal FLASH. */
	SystemInit();
  delay_init();	
  NVIC_Configuration();
  uart_init(115200);
	Usb_Init();//USB初始化
	ADC1_Init();
	Button_Init();//按键初始化
	One_Backlight();//背光初始化	
  TIM2_Backlight_PWM_Init();//初始化背光pwm	
  Buzzer_Init();//引脚定义PA0，与ADC_0通道冲突

}


int main(void)
{			
/*-------------------------------USB测试用-------------------------------------*/
	 u16 t;
	 u16 len;	
	 u16 times=0;    
	 u8 usbstatus=0;	
/*-------------------------------USB测试用-------------------------------------*/
		Mcu_Init();	 		
		LCD_GpioInit(  );
		LCD_Init();
/*-------------------------------测试用-------------------------------------*/
		cleandisp();
	//disp_All();
    //TurnOnSegment(0x80);

    //UpdateDisplay();
			printf("----------------in development-------------\n");
	// 读取LCD地址0的数据
  //unsigned char Data = HT1623_ReadByte(0);
	 //printf("\r\nRead data: 0x%02X\r\n", Data);
		// 执行读-修改-写操作
    //HT1623_ReadData_From_Lcd(addr, value, opr);
	

	
	
//	for (int i = 0; i < 48; i++) {
//        LCD_BUF[i] = 0x00;
//    }    
//    // 打开 SEG 2 的 COM 3 段
//    dispON(4, 1);

  
	
	
/*-------------------------------测试用-------------------------------------*/

	
	
	
    while(1)
    {		
usb_printf("\r\nUSB Connected\r\n\r\n");


		Button_Debounce();	
#if 1
/*-------------------------------USB测试用-------------------------------------*/						
			if(usbstatus!=bDeviceState)//USB连接状态发生了改变.
		{
			usbstatus=bDeviceState;//记录新的状态
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
			len=USB_USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			usb_printf("\r\n您发送的消息为:%d\r\n\r\n",len);
			for(t=0;t<len;t++)
			{
				USB_USART_SendData(USB_USART_RX_BUF[t]);//以字节方式,发送给USB 
			}
			usb_printf("\r\n\r\n");//插入换行
			USB_USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				usb_printf("\r\nUSB虚拟串口实验\r\n");
				
			}
			//if(times%200==0)usb_printf("请输入数据,以回车键结束\r\n");  
			//if(times%30==0)usb_printf("闪烁LED,提示系统正在运行\r\n");//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
/*-------------------------------USB测试用-------------------------------------*/			
#endif
    }
}
#endif










