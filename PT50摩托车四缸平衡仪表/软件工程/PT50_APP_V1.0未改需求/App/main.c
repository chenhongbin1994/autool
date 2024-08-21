/*
* @Author: ChenHongBin 944278386@qq.com
* @Date: 2024-06-05 22:26:51
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-16 16:59:11
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
/*-------------------------------测试用-------------------------------------*/
extern Settings current_settings;
//定时器标志位
extern volatile  u8 Flag_o5s_Disp,flag_10ms,Battery_ADCflag,Clock_flag;

//按键标志位
//extern u8 lock_flag,longocked_flag,Switch_flag;


/*-------------------------------测试用-------------------------------------*/
extern int history_index;  // 当前记录的索引
extern int current_history_display;//历史数据模式
extern u8  Timing_Switch_5min;
extern u8   Timing_Switch_5min,MinAuto,SecondAuto; 
extern u8 Zero_flag,REC_flag;
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
  SystemInit();//IAP时需要更改VECT_TAB_OFFSET的地址
  delay_init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  InitializeSettings();//flash里的标志位初始化
  uart_init(115200);
  Battery_Init();//电池电压检测和EN_OUT初始化
   Usb_Init();//USB初始化
  ADC_Init_t();
  Buzzer_Init();//引脚定义PA0，与ADC_0通道冲突
	KEY_Init();
  TIM3_Int_Init(50-1,7200-1); //TIM3_Int_Init(200-1,7200-1);调用定时器使得20ms产生一个中断，TIM3_Int_Init(49, 7199); // 5ms中断；TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms
}




int main(void)
{
  /*-------------------------------变量测试用-------------------------------------*/  
	u8 usbstatus=0;	
  float coefficient = 1.45;//压力计算系数
  float Kvalue = 0.0125;//压力计算K值
  /*-------------------------------变量测试用-------------------------------------*/
  Mcu_Init();
	while(!power_on);
  LCD_Init();//部分图标初始化
  printf("----------------版本号V1.0-------------\n");
  calculateBatteryVoltage(5);
  AUutoshutdownONOFF_display();

  while(1)
  {
		//printf("老铁来干饭吗？\n");delay_ms(500);
#if 1  //是否插入USB状态判断   
WFI_SET();//睡眠模式

		if(usbstatus!=bDeviceState)//USB连接状态发生了改变.
		{
      INTX_DISABLE();//关闭所有中断
			usbstatus=bDeviceState;//记录新的状态
			if(usbstatus==CONFIGURED)
			{				
				//提示USB连接成功
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,1);
			}else
			{
				UpdateReadModifyWriteDisplay(15,Screen_Data_USB,0); 
				//提示USB断开

			}
      INTX_ENABLE();//开启所有中断
		}
#endif //是否插入USB状态判断

		if((power_on == 1)&& (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 0))
		{
			 Long_press_cnt =0;

		}

    if((Clock_flag == 1)&&(!settings_mode)&&(lock_flag == 0)&&((current_history_display == -1)))//时钟放这不准，放定时器中断准
    {
      INTX_DISABLE();//关闭所有中断
      if(Zero_flag ==1){
        Zero_flag =0;
            Dig_Zero();                      
      }
      Clock_flag = 0;
      Clock();
      INTX_ENABLE(); //开启所有中断
    }           
    if((Flag_o5s_Disp == 1)&&(!settings_mode)&&(lock_flag == 0)&&(longocked_flag == 0)&&((current_history_display == -1)))
    {
      INTX_DISABLE();//关闭所有中断
      Flag_o5s_Disp = 0;
      ProcessAndDisplayPressureValues(coefficient, Kvalue);//四缸压力显示；系数=1.45, K值0.0125
      INTX_ENABLE();//开启所有中断
    }
    
    if(Battery_ADCflag == 2)//6v电源电压检测,两分钟检测一次
    {
      INTX_DISABLE();//关闭所有中断
      Battery_ADCflag = 0;
      calculateBatteryVoltage(5);
      INTX_ENABLE();//开启所有中断
    }

/*----------------------------------------------------Auto自动关机------------------------------------------------------------*/
    if((current_settings.auto_shutdown_enabled == 1)&&(Timing_Switch_5min == 5))//AutoONOFF
    {
        Timing_Switch_5min = 0;
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);UpdateReadModifyWriteDisplay(15, Screen_Data_LED, 0);  // 背光关
        cleandisp();          
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);  // 电源
    }
    if(ADC_Value[0]<1700){MinAuto = 0;SecondAuto = 0;Timing_Switch_5min =0;}//自动关机关背光重新计时  
/*----------------------------------------------------Auto自动关机------------------------------------------------------------*/   
  }

}















