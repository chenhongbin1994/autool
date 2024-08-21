#include "key_handler.h"
#include "stdio.h"
#include "buzzer.h"
#include "delay.h"
#include "LCD_HT1623.h"
#include "stmflash.h"
#include "iap.h"
#include "usart.h"
#include "hw_config.h"
extern	u16 oldcount;				//老的串口接收数据值
extern  u16 applenth;				//接收到的app代码长度
extern  u8  clearflag;


extern float pressure_offset[4];// 用于存储校准的压力偏移值
// 按键配置结构体的外部声明
extern KEY_Configure_TypeDef Key0Cfg;
//extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
//extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;





Settings current_settings;  // 当前设置

u8 Zero_flag = 0;  // 清零标志


#if 1
 int power_on = 0;
    static int backlight_on = 0;
// 处理按键0事件
void Handle_Key0_Event(KEY_EventList_TypeDef event) {    
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            backlight_on = !backlight_on;
            if (!backlight_on) {
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // 背光开
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
							delay_ms(50);
            } else {
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // 背光关
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);
            }
            break;
        case KEY_Event_LongPress:            
            power_on = !power_on;
            if (power_on) {
                GPIO_SetBits(GPIOA, GPIO_Pin_4);  // 电源开
                GPIO_SetBits(GPIOB, GPIO_Pin_3);  // 背光开
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 1);
							delay_ms(50);
            } else {
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // 背光关
								cleandisp();//清屏，一些功能可能不能设置清屏，目前是调试用
                UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);
                GPIO_ResetBits(GPIOA, GPIO_Pin_4);  // 关机电源
            }
            break;
        default:
            break;
    }
}
#endif

// 处理按键2事件
void Handle_Key2_Event(KEY_EventList_TypeDef event) {
   
   
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            if(applenth)
    {
      usb_printf("开始更新固件...\r\n");
      if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
      {
        iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码
        usb_printf("固件更新完成!\r\n");
      }
      else
      {
        usb_printf("非FLASH应用程序!\r\n");
      }
    }
    else
    {
      usb_printf("没有可以更新的固件!\r\n");
    }
    clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示
  
            break;
        case KEY_Event_LongPress:
           
            break;
        default:
            break;
    }
}

// 处理按键3事件 
void Handle_Key3_Event(KEY_EventList_TypeDef event) {
   
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
        usb_printf("开始执行FLASH用户代码!!\r\n");
    if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
    {
			//这里需要加关背光和其他图标，或者直接关机
			NVIC_SystemReset();	
      //iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
    }
    else
    {
      usb_printf("非FLASH应用程序,无法执行!\r\n");
    }
    clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示  
            break;
        case KEY_Event_LongPress:
           usb_printf("开始执行SRAM用户代码!!\r\n");
    if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x20000000)//判断是否为0X20XXXXXX.
    {
      iap_load_app(0X20001000);//SRAM地址
    }
    else
    {
      usb_printf("非SRAM应用程序,无法执行!\r\n");
    }
    clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示
            break;
        default:
            break;
    }
}


// 处理按键5事件
void Handle_Key5_Event(KEY_EventList_TypeDef event) {
   
    if (current_settings.buzzer_enabled) {
        Key_Beep();  // 按键声音持续100ms
    }
    switch (event) {
        case KEY_Event_SingleClick:
            UpdateReadModifyWriteDisplay(15, Screen_Data_Zero, 1);
            Zero_flag = 1;
            delay_ms(300);
            UpdateReadModifyWriteDisplay(15, Screen_Data_Zero, 0);
            printf("ZERO\r\n");
		usb_printf("没有可以更新的固件!\r\n");
    if(applenth)
    {
      usb_printf("固件清除完成!\r\n");
      applenth=0;
    }
    else
    {
      usb_printf("没有可以清除的固件!\r\n");
    }
    clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示
  
            break;
        case KEY_Event_LongPress:        
            
            
            break;
        default:
            break;
    }
}

// 按键处理函数
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
