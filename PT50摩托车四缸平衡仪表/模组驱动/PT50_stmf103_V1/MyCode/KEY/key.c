#include "key.h"
#include "stm32f10x.h"
#include "misc.h"
#include "core_cm3.h"
#include "delay.h"
#if 1
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
 	return 0;// 无按键按下
}
#endif


























#if 0

#define DEBOUNCE_TIME 20 // 去抖动时间，单位：毫秒
#define LONG_PRESS_TIME 1000 // 长按时间，单位：毫秒
// 定义按键引脚
#define BUTTON1_PIN GPIO_Pin_0
#define BUTTON2_PIN GPIO_Pin_1
#define BUTTON3_PIN GPIO_Pin_2
#define BUTTON4_PIN GPIO_Pin_3
#define BUTTON5_PIN GPIO_Pin_4
#define BUTTON6_PIN GPIO_Pin_5
#define BUTTON_GPIO_PORT GPIOA

// 按键状态定义
typedef enum {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_LONG_PRESSED
} ButtonState;

// 按键状态变量
volatile ButtonState button1State = BUTTON_RELEASED;
volatile ButtonState button2State = BUTTON_RELEASED;
volatile ButtonState button3State = BUTTON_RELEASED;
volatile ButtonState button4State = BUTTON_RELEASED;
volatile ButtonState button5State = BUTTON_RELEASED;
volatile ButtonState button6State = BUTTON_RELEASED;


// 按键初始化
void Button_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能GPIO和AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // 配置按键引脚
    GPIO_InitStructure.GPIO_Pin = BUTTON1_PIN | BUTTON2_PIN | BUTTON3_PIN | BUTTON4_PIN | BUTTON5_PIN | BUTTON6_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);

    // 连接按键引脚到中断线
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);

    // 配置外部中断线
    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 配置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStructure);
    
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&NVIC_InitStructure);
}

// EXTI中断服务例程
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        button1State = BUTTON_PRESSED;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        button2State = BUTTON_PRESSED;
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

// EXTI2中断服务例程（按键3）
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        button3State = BUTTON_PRESSED;
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

// EXTI3中断服务例程（按键4）
void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        button4State = BUTTON_PRESSED;
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

// EXTI4中断服务例程（按键5）
void EXTI4_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
        button5State = BUTTON_PRESSED;
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

// EXTI9_5中断服务例程（按键6）
void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        button6State = BUTTON_PRESSED;
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
    // 处理其他按键的中断线6-9
    // if (EXTI_GetITStatus(EXTI_Line6) != RESET) { ... }
    // if (EXTI_GetITStatus(EXTI_Line7) != RESET) { ... }
    // if (EXTI_GetITStatus(EXTI_Line8) != RESET) { ... }
    // if (EXTI_GetITStatus(EXTI_Line9) != RESET) { ... }
}
// 添加其他按键的中断服务例程



void Button_Debounce(void)
{
    static uint32_t button1PressTime = 0;
    static uint32_t button2PressTime = 0;
    static uint32_t button3PressTime = 0;
    static uint32_t button4PressTime = 0;
    static uint32_t button5PressTime = 0;
    static uint32_t button6PressTime = 0;

    // 按键1处理逻辑
    if (button1State == BUTTON_PRESSED)
    {
        Delay(DEBOUNCE_TIME);
        if (GPIO_ReadInputDataBit(BUTTON_GPIO_PORT, BUTTON1_PIN) == Bit_RESET)
        {
            if (button1PressTime == 0)
            {
                button1PressTime = SysTick->VAL;
            }
            else if ((SysTick->VAL - button1PressTime) >= LONG_PRESS_TIME)
            {
                button1State = BUTTON_LONG_PRESSED;
                button1PressTime = 0;
            }
            else
            {
                // 处理按键1短按逻辑：开关背光
                Toggle_Backlight();
                button1State = BUTTON_RELEASED;
            }
        }
    }

    if (button1State == BUTTON_LONG_PRESSED)
    {
        // 处理按键1长按逻辑：进入设置模式
        Enter_Settings_Mode();
        button1State = BUTTON_RELEASED;
    }

    // 按键2处理逻辑
    if (button2State == BUTTON_PRESSED)
    {
        Delay(DEBOUNCE_TIME);
        if (GPIO_ReadInputDataBit(BUTTON_GPIO_PORT, BUTTON2_PIN) == Bit_RESET)
        {
            if (button2PressTime == 0)
            {
                button2PressTime = SysTick->VAL;
            }
            else if ((SysTick->VAL - button2PressTime) >= LONG_PRESS_TIME)
            {
                button2State = BUTTON_LONG_PRESSED;
                button2PressTime = 0;
            }
            else
            {
                // 处理按键2短按逻辑：向上翻动
                Scroll_Up();
                button2State = BUTTON_RELEASED;
            }
        }
    }

    if (button2State == BUTTON_LONG_PRESSED)
    {
        // 处理按键2长按逻辑：开关声音
        Toggle_Sound();
        button2State = BUTTON_RELEASED;
    }

    // 按键3处理逻辑
    if (button3State == BUTTON_PRESSED)
    {
        Delay(DEBOUNCE_TIME);
        if (GPIO_ReadInputDataBit(BUTTON_GPIO_PORT, BUTTON3_PIN) == Bit_RESET)
        {
            if (button3PressTime == 0)
            {
                button3PressTime = SysTick->VAL;
            }
            else if ((SysTick->VAL - button3PressTime) >= LONG_PRESS_TIME)
            {
                button3State = BUTTON_LONG_PRESSED;
                button3PressTime = 0;
            }
            else
            {
                // 处理按键3短按逻辑：进入REC模式
                Enter_REC_Mode();
                button3State = BUTTON_RELEASED;
            }
        }
    }

    if (button3State == BUTTON_LONG_PRESSED)
    {
        // 处理按键3长按逻辑：查看历史数据
        View_History_Data();
        button3State = BUTTON_RELEASED;
    }

    // 按键4处理逻辑
    if (button4State == BUTTON_PRESSED)
    {
        Delay(DEBOUNCE_TIME);
        if (GPIO_ReadInputDataBit(BUTTON_GPIO_PORT, BUTTON4_PIN) == Bit_RESET)
        {
            // 处理按键4短按逻辑：锁定/解锁数据
            Lock_Unlock_Data();
            button4State = BUTTON_RELEASED;
        }
    }

    // 按键5处理逻辑
    if (button5State == BUTTON_PRESSED)
    {
        Delay(DEBOUNCE_TIME);
        if (GPIO_ReadInputDataBit(BUTTON_GPIO_PORT, BUTTON5_PIN) == Bit_RESET)
        {
            if (button5PressTime == 0)
            {
                button5PressTime = SysTick->VAL;
            }
            else if ((SysTick->VAL - button5PressTime) >= LONG_PRESS_TIME)
            {
                button5State = BUTTON_LONG_PRESSED;
                button5PressTime = 0;
            }
            else
            {
                // 处理按键5短按逻辑：向下翻动
                Scroll_Down();
                button5State = BUTTON_RELEASED;
            }
        }
    }

    if (button5State == BUTTON_LONG_PRESSED)
    {
        // 处理按键5长按逻辑：开/关机
        Toggle_Power();
        button5State = BUTTON_RELEASED;
    }

    // 按键6处理逻辑
    if (button6State == BUTTON_PRESSED)
    {
        Delay(DEBOUNCE_TIME);
        if (GPIO_ReadInputDataBit(BUTTON_GPIO_PORT, BUTTON6_PIN) == Bit_RESET)
        {
            // 处理按键6长按逻辑：清除当前压力值
            Clear_Pressure_Value();
            button6State = BUTTON_RELEASED;
        }
    }
}

void Delay(uint32_t ms)
{
    SysTick_Config(SystemCoreClock / 1000);
    while (ms--)
    {
        while (!SysTick_Config(SystemCoreClock / 1000));
    }
    SysTick_Config(0);
}


/*--------------------功能实现函数-------------------------*/
void Toggle_Backlight(void)
{
    static uint8_t backlightState = 0;

    if (backlightState == 0)
    {
        // 开启背光
        GPIO_SetBits(GPIOB, GPIO_Pin_0);  // 假设背光控制引脚为GPIOB Pin 0
        backlightState = 1;
    }
    else
    {
        // 关闭背光
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        backlightState = 0;
    }
}

void Enter_Settings_Mode(void)
{
    // 进入设置模式
    // 允许切换单位、设置2T和4T模式、设置中英文多语言等

    // 示例：显示设置界面
    Display_Settings_Menu();

    // 等待用户输入进行设置
    while (1)
    {
        if (button2State == BUTTON_PRESSED)
        {
            // 上滚
            Scroll_Up_Settings();
            button2State = BUTTON_RELEASED;
        }
        else if (button5State == BUTTON_PRESSED)
        {
            // 下滚
            Scroll_Down_Settings();
            button5State = BUTTON_RELEASED;
        }
        else if (button1State == BUTTON_PRESSED)
        {
            // 保存设置并退出
            Save_Settings();
            button1State = BUTTON_RELEASED;
            break;
        }
    }
}

void Scroll_Up(void)
{
    // 实现向上翻动的逻辑
    Display_Previous_Item();
}

void Toggle_Sound(void)
{
    static uint8_t soundState = 0;

    if (soundState == 0)
    {
        // 开启声音
        Enable_Sound();
        soundState = 1;
    }
    else
    {
        // 关闭声音
        Disable_Sound();
        soundState = 0;
    }
}

void Enter_REC_Mode(void)
{
    // 进入REC模式
    Enter_Record_Mode();

    // 再次点按保存数据
    while (1)
    {
        if (button3State == BUTTON_PRESSED)
        {
            Save_Data_To_EEPROM();
            button3State = BUTTON_RELEASED;
            break;
        }
        else if (button3State == BUTTON_LONG_PRESSED)
        {
            View_History_Data();
            button3State = BUTTON_RELEASED;
            break;
        }
    }
}

void View_History_Data(void)
{
    // 查看历史数据
    Display_History_Data();
}

void Lock_Unlock_Data(void)
{
    static uint8_t lockState = 0;

    if (lockState == 0)
    {
        // 锁定数据
        Lock_Data();
        lockState = 1;
    }
    else
    {
        // 解锁数据
        Unlock_Data();
        lockState = 0;
    }
}

void Scroll_Down(void)
{
    // 实现向下翻动的逻辑
    Display_Next_Item();
}

void Toggle_Power(void)
{
    static uint8_t powerState = 0;

    if (powerState == 0)
    {
        // 开机
        GPIO_SetBits(POWER_CONTROL_PORT, POWER_CONTROL_PIN);
        powerState = 1;
    }
    else
    {
        // 关机
        GPIO_ResetBits(POWER_CONTROL_PORT, POWER_CONTROL_PIN);
        powerState = 0;
    }
}

void Clear_Pressure_Value(void)
{
    // 清除当前压力值
    Clear_Current_Pressure();
}

/*--------------------模拟相关操作的函数示例------------------------*/
void Display_Settings_Menu(void)
{
    // 显示设置菜单
    // 假设通过LCD显示
    LCD_Clear();
    LCD_DisplayString("Settings Menu");
}

void Scroll_Up_Settings(void)
{
    // 在设置菜单中向上滚动
    LCD_DisplayString("Scroll Up");
}

void Scroll_Down_Settings(void)
{
    // 在设置菜单中向下滚动
    LCD_DisplayString("Scroll Down");
}

void Save_Settings(void)
{
    // 保存设置
    LCD_DisplayString("Settings Saved");
}

void Display_Previous_Item(void)
{
    // 显示上一个项目
    LCD_DisplayString("Previous Item");
}

void Enable_Sound(void)
{
    // 启用声音
    // 例如，通过蜂鸣器
    Beep_On();
}

void Disable_Sound(void)
{
    // 禁用声音
    Beep_Off();
}

void Enter_Record_Mode(void)
{
    // 进入录制模式
    LCD_DisplayString("REC Mode");
}

void Save_Data_To_EEPROM(void)
{
    // 保存数据到EEPROM
    LCD_DisplayString("Data Saved");
}

void Display_History_Data(void)
{
    // 显示历史数据
    LCD_DisplayString("History Data");
}

void Lock_Data(void)
{
    // 锁定数据
    LCD_DisplayString("Data Locked");
}

void Unlock_Data(void)
{
    // 解锁数据
    LCD_DisplayString("Data Unlocked");
}

void Display_Next_Item(void)
{
    // 显示下一个项目
    LCD_DisplayString("Next Item");
}

void Clear_Current_Pressure(void)
{
    // 清除当前压力值
    LCD_DisplayString("Pressure Cleared");
}

void Beep_On(void)
{
    // 打开蜂鸣器
    GPIO_SetBits(GPIOB, GPIO_Pin_1);  // 假设蜂鸣器控制引脚为GPIOB Pin 1
}

void Beep_Off(void)
{
    // 关闭蜂鸣器
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}

void LCD_Clear(void)
{
    // 清除LCD显示
}

void LCD_DisplayString(const char* str)
{
    // 在LCD上显示字符串
}

#endif