/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-06-19 15:44:42
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-07-13 20:16:34
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50_stmf103_ADC_V14cs\MyCode\TIMER\timer.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "timer.h"
#include "usart.h"
#include "stdio.h"
#include "key.h"
#include "includes.h"

u8 Second,Minute,Hour;
u32 count,Battery_time;

volatile    u8   Flag_o5s_Disp,Flag_1s,flag_10ms,Battery_ADCflag,Clock_flag;//AutoONOFF_flag

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
void TIM3_Int_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3, ENABLE);					 
}




extern KEY_Configure_TypeDef Key0Cfg;
extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;
                        

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除TIMx更新中断标志 
      
    KeyHandler_Process();// 处理按键事件,放这里按键反应灵敏，就是长按时间短

    count++;
    Battery_time++; //
    if(count == 100)
    {
        count = 0;
        //Flag_o5s_Disp = 1;
        Flag_1s = !Flag_1s;
        if(Flag_1s == 0){
          Flag_o5s_Disp = 1;
          Clock_flag = 1;
        //Clock();
        }
    }
    if(Battery_time == 1000)//5Supdata
    {
      Battery_time = 0; 
      Battery_ADCflag = 1;
      

    }
  


		 // 读取每个按键的状态
        KEY_ReadStateMachine(&Key0Cfg);//调用状态机
        KEY_ReadStateMachine(&Key1Cfg);
        KEY_ReadStateMachine(&Key2Cfg);
        KEY_ReadStateMachine(&Key3Cfg);
        KEY_ReadStateMachine(&Key4Cfg);
        KEY_ReadStateMachine(&Key5Cfg);
	}
}

void Clock(void)                          //时钟程序(秒+1、分+1、时+1)
{
    Second++;                             //秒+1
      if(Second ==60){                    //到60秒进1
        Second = 0;                       //秒清零
        Minute++;
          if(Minute == 60){
            Minute =0;
            Hour++;
            if(Hour == 24)Hour=0;
          }
      }
      Clock_Display();
}

#if 0
// 初始化TIM2通道2作为PWM输出
void TIM2_Backlight_PWM_Init(void)
{
 
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); // 修改: 增加RCC_APB2Periph_AFIO
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//不知解除注释为何开机会有自启动
  GPIO_InitStruct.GPIO_Mode 	=  GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;;
  GPIO_Init(GPIOB,&GPIO_InitStruct);
  GPIO_ResetBits( GPIOB, GPIO_Pin_3);

  // 配置TIM2基本定时器
  TIM_TimeBaseStructure.TIM_Period = 999; // 计数周期
  TIM_TimeBaseStructure.TIM_Prescaler = 71; // 预分频系数
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  // 配置TIM2通道2为PWM模式
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // 初始占空比为0（关闭背光）
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  // 6，使能ARR的预装载寄存器
   TIM_ARRPreloadConfig(TIM2, ENABLE);
   TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

  // 使能TIM2
  TIM_Cmd(TIM2, ENABLE);
	
}

// 设置PWM占空比（背光亮度）
void Set_Backlight_Brightness(uint16_t brightness)
{
  // 限制亮度在0到1000之间
  if (brightness > 1000)
    brightness = 1000;

  // 设置TIM2通道2的捕获比较寄存器值
  TIM_SetCompare2(TIM2, brightness);
	
	 // 输出调试信息
  //printf("Set Backlight Brightness: %d\n", brightness);
}
#endif







