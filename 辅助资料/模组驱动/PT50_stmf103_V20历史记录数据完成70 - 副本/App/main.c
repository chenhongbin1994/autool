/*
* @Author: ChenHongBin 944278386@qq.com
* @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-07-15 14:51:18
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
#include "includes.h"

#if 1
/*-------------------------------测试用-------------------------------------*/
//定时器标志位
extern volatile  u8 Flag_o5s_Disp,flag_10ms,Battery_ADCflag,Clock_flag,AutoONOFF_flag;

//按键标志位
extern u8 lock_flag,longocked_flag;
extern volatile u8 LCD_BUF[48];
extern uint16_t ADC_Value[4];


/*-------------------------------测试用-------------------------------------*/


/*--------------------------Mycode-------------------------------*/
//初始化
void Usb_Init(void)
{
  USB_Port_Set(0); 	//USB先断开
  delay_ms(100);
  USB_Port_Set(1);	//USB再次连接
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
  InitializeSettings();//flash里的标志位初始化
  uart_init(115200);
  Battery_Init();//电池电压检测和EN_OUT初始化
  Usb_Init();//USB初始化
  ADC_Init_t();
  Buzzer_Init();//引脚定义PA0，与ADC_0通道冲突
  TIM3_Int_Init(50-1,7200-1); //TIM3_Int_Init(200-1,7200-1);调用定时器使得20ms产生一个中断，TIM3_Int_Init(49, 7199); // 5ms中断；TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms
  KEY_Init();
}

extern int current_history_display;
int main(void)
{
  /*-------------------------------变量测试用-------------------------------------*/

  /*-------------------------------变量测试用-------------------------------------*/
  Mcu_Init();
  //ADC2_Init();
  LCD_Init();//部分图标初始化
  printf("----------------in development-------------\n");
  

  while(1)
  {
    if((Clock_flag == 1)&&(lock_flag == 0))//时钟放这不准，放定时器中断准
    {
      Clock_flag = 0;
      Clock();
    }           
    if((Flag_o5s_Disp == 1)&&(lock_flag == 0)&&(longocked_flag == 0)&&((current_history_display == -1)))
    {
      Flag_o5s_Disp = 0;
      ProcessAndDisplayPressureValues(1.45, 0.0125);//四缸压力显示；系数=1.45, K值0.0125
    }
    if(Battery_ADCflag == 1)//6v电源电压检测,开机等5S才显示，待解决
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














