/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-06-19 15:44:42
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-21 15:10:11
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50_stmf103_ADC_V14cs\MyCode\TIMER\timer.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE 
 */
#include "timer.h"
#include "usart.h"
#include "stdio.h"
#include "key.h"
#include "includes.h"
#include "key_handler.h"
u8 Second,Minute,Hour;
u8 SecondAuto;//AUTO开关机
u32 count,PreDisp,Battery_time;
u32 P_0_cnt = 0;
uint32_t Long_press_cnt ;
volatile    u8   Flag_o5s_Disp,PressureDisp,Flag_1s,flag_10ms,Battery_ADCflag,Clock_flag;//AutoONOFF_flag
volatile    u8   Timing_Switch_5min,MinAuto; 
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
                        
extern int history_index;  // 当前记录的索引
int powerON_cut;
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除TIMx更新中断标志 
      
    KeyHandler_Process();// 处理按键事件,放这里按键反应灵敏，就是长按时间短

    count++;
    PreDisp++;
	if(PreDisp == 20)
	{
		PreDisp = 0;
		PressureDisp = 1;	
	}
    if(count == 100)
    {
        count = 0;
        
        //Flag_o5s_Disp = 1;
        Flag_1s = !Flag_1s;
        if(Flag_1s == 0){
          Flag_o5s_Disp = 1;//1秒后捕获开始
          Clock_flag = 1;
        //Clock();
        }
    }
    
    //Battery_time++; //
    // if(Battery_time == 1000)//5Supdata
    // {
    //   Battery_time = 0; 
    //   Battery_ADCflag = 1;
    // }
    
     MinAuto++;
    if(MinAuto ==200)
    {
      MinAuto = 0;
       SecondAuto++;  
       if(SecondAuto ==60){                    //到60秒进1
        SecondAuto = 0;                       //秒清零
        Timing_Switch_5min++;   
        Battery_ADCflag++;
        }           //秒+1
    }

		 // 读取每个按键的状态
        KEY_ReadStateMachine(&Key0Cfg);//调用状态机
        KEY_ReadStateMachine(&Key1Cfg);
        KEY_ReadStateMachine(&Key2Cfg);
        KEY_ReadStateMachine(&Key3Cfg);
        KEY_ReadStateMachine(&Key4Cfg);
        KEY_ReadStateMachine(&Key5Cfg);
		
		
		//长按计数器 开机
		if ((power_on ==0)&&(GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 1)){
			powerON_cut++;
		}
		else
		{
			powerON_cut =0;
		}
				if(powerON_cut	> 400)
		{
			power_on = 1;
			return;
		}
		
		
		//关机
		if((power_on == 1)&& (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 1))
		{
			 Long_press_cnt ++;
		}
		else
		{
			Long_press_cnt =0;
		}
			
		if(Long_press_cnt	> 400)
		{
			Handle_Key0_Event( KEY_Event_LongPress);
			Long_press_cnt =	0;
		}
		
		//P=0 长按计数
    if((GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_5) == 0))
    {
      P_0_cnt ++;
    }
    else
    {
      P_0_cnt = 0;
    }

    
			
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



#if 1
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

  //EPM转速
//定时器2通道1输入捕获配置

TIM_ICInitTypeDef  TIM1_ICInitStructure;
u32  TIM2CH1_CAPTURE_Count;		//输入捕获溢出计数
void TIM1_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能TIM1时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0 输入 GPIO_Mode_IPD 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_8);						 //PA0 下拉
	
	//初始化定时器1 TIM1	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM1输入捕获参数
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM1_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
    TIM_Cmd(TIM1,ENABLE ); 	//使能定时器5
   
}

u8  TIM1CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM1CH1_CAPTURE_VAL;	//输入捕获值

int overflow =0;
int state = 0;
int START=0;
int WAIT_RISING,WAIT_FALLING,value;

/*    TIM1 中断服务程序   */
void TIM1_CC_IRQHandler(void)          
{	
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查TIM1更新中断标志 
  {
	
    overflow++;
	printf("overflow= %d\n",overflow);
  }
  else if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) //检查TIM1通道3捕获中断标志
  {
	//printf("已进TIM1中断2!!!!!!!\n");
    if(state == START)		//初始状态	
    {	
            overflow = 0;
            TIM_SetCounter(TIM1,0);
            state = WAIT_FALLING;
            TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//设置为下降沿捕获
    }	
    else if(state == WAIT_RISING)    //捕获上升沿
    {	
       //     TIM1CH3_CAPTURE_VAL = TIM_GetCapture3(TIM1);     
       //     value = TIM1CH3_CAPTURE_VAL + (overflow*7200);	
		
            overflow = 0;
            TIM_SetCounter(TIM1,0);
            state = WAIT_FALLING;
			printf("state= %d\n",state);
            TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling); //设置为下降沿触发				
    }
    else // 捕获下降沿
    {
            TIM1CH1_CAPTURE_VAL = TIM_GetCapture1(TIM1);
            value = TIM1CH1_CAPTURE_VAL + (overflow*65535);
			printf("value= %d\n",value);
            overflow = 0;
            TIM_SetCounter(TIM1,0);
            state = WAIT_RISING;
            TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //设置为上升沿触发		
    }		
  }
  TIM_ClearITPendingBit(TIM1, TIM_IT_Update|TIM_IT_CC1 );     //清除TIM1更新中断标志和捕获标志 
}

#if 1
//定时器1中断服务程序	 
void TIM1_UP_IRQHandler(void)
{ 
	printf("up更新中断已进入1\n");
 	if((TIM1CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)		 
		{	   
			 printf("up更新中断已进入2\n");
			if(TIM1CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{	printf("已经捕获到高电平了\n");
				if((TIM1CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了//if(TIM1CH1_CAPTURE_Count == 0xFFFF)	//高电平太长了
				{
					TIM1CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					printf("TIM1CH1_CAPTURE_Count= %d\n",TIM1CH1_CAPTURE_STA);
					TIM1CH1_CAPTURE_VAL=0XFFFF;
				}else TIM1CH1_CAPTURE_STA++;    //TIM1CH1_CAPTURE_Count++;
			}	 
		}
	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			printf("up更新中断已进入3\n");
			if(TIM1CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM1CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽				
				TIM1CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);
				printf("TIM1CH1_CAPTURE_VAL= %d\n",TIM1CH1_CAPTURE_VAL);
		   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				printf("up更新中断已进入4\n");
				TIM1CH1_CAPTURE_STA=0;			//清空
				TIM1CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM1,0);
				TIM1CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}

#endif



