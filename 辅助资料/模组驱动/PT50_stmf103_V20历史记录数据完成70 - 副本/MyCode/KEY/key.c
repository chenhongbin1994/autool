#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "stdio.h"


/**************************************************************************************************** 
*                             长按、单击、双击定义
* 长按事件：任何大于 KEY_LONG_PRESS_TIME 
* 单击事件：按下时间不超过 KEY_LONG_PRESS_TIME 且 释放后 KEY_WAIT_DOUBLE_TIME 内无再次按下的操作
* 双击事件：俩次短按时间间隔小于KEY_WAIT_DOUBLE_TIME，俩次短按操作合并为一次双击事件。
* 特殊说明：
*          1.短按和长按时间间隔小于 KEY_WAIT_DOUBLE_TIME，响应一次单击和长按事件，不响应双击事件
*          2.连续2n次短按，且时间间隔小于 KEY_WAIT_DOUBLE_TIME，响应为n次双击
*          3.连续2n+1次短按，且时间间隔小于 KEY_WAIT_DOUBLE_TIME，且最后一次KEY_WAIT_DOUBLE_TIME内无操作，
*				响应为n次双击 和 一次单击事件
****************************************************************************************************/

#define KEY_LONG_PRESS_TIME    200 // 20ms*50 = 1s
#define KEY_WAIT_DOUBLE_TIME   50 // 20ms*25 = 500ms，如果没开双击就填1，开双击填300或者500

#define KEY_PRESSED_LEVEL      0  // 按键按下是电平为低
/**************************************************************************************************** 
*                             局部函数定义
****************************************************************************************************/
//static KEY_PinLevel_TypeDef KEY_ReadPin(void);   // 按键读取按键的电平函数
//static void KEY_GetAction_PressOrRelease(void); // 获取按键是按下还是释放，保存到结构体
static KEY_PinLevel_TypeDef KEY_ReadPin0(void);
static KEY_PinLevel_TypeDef KEY_ReadPin1(void);
static KEY_PinLevel_TypeDef KEY_ReadPin2(void);
static KEY_PinLevel_TypeDef KEY_ReadPin3(void);
static KEY_PinLevel_TypeDef KEY_ReadPin4(void);
static KEY_PinLevel_TypeDef KEY_ReadPin5(void);
/**************************************************************************************************** 
*                             全局变量
****************************************************************************************************/
/*-----------------------------------------------------------
		0,						          按键长按计数
		KEY_Action_Release,		  虚拟当前IO电平，按下1，抬起0
		KEY_Status_Idle,        按键状态
		KEY_Event_Null,         按键事件
		KEY_ReadPin,            读IO电平函数
		1                       启用双击功能，默认值
-------------------------------------------------------------*/


KEY_Configure_TypeDef Key0Cfg = {0, KEY_Action_Release, KEY_Status_Idle, KEY_Event_Null, KEY_ReadPin0, 1};
KEY_Configure_TypeDef Key1Cfg = {0, KEY_Action_Release, KEY_Status_Idle, KEY_Event_Null, KEY_ReadPin1, 1};
KEY_Configure_TypeDef Key2Cfg = {0, KEY_Action_Release, KEY_Status_Idle, KEY_Event_Null, KEY_ReadPin2, 1};
KEY_Configure_TypeDef Key3Cfg = {0, KEY_Action_Release, KEY_Status_Idle, KEY_Event_Null, KEY_ReadPin3, 1};
KEY_Configure_TypeDef Key4Cfg = {0, KEY_Action_Release, KEY_Status_Idle, KEY_Event_Null, KEY_ReadPin4, 1};
KEY_Configure_TypeDef Key5Cfg = {0, KEY_Action_Release, KEY_Status_Idle, KEY_Event_Null, KEY_ReadPin5, 1};


/**************************************************************************************************** 
*                             函数定义
****************************************************************************************************/
// 按键读取按键的电平函数

static KEY_PinLevel_TypeDef KEY_ReadPin0(void)//按键读取函数
{
    return (KEY_PinLevel_TypeDef) GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0);
}

static KEY_PinLevel_TypeDef KEY_ReadPin1(void)
{
    return (KEY_PinLevel_TypeDef) GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_1);
}

static KEY_PinLevel_TypeDef KEY_ReadPin2(void)
{
    return (KEY_PinLevel_TypeDef) GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_2);
}

static KEY_PinLevel_TypeDef KEY_ReadPin3(void)
{
    return (KEY_PinLevel_TypeDef) GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_3);
}

static KEY_PinLevel_TypeDef KEY_ReadPin4(void)
{
    return (KEY_PinLevel_TypeDef) GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_4);
}

static KEY_PinLevel_TypeDef KEY_ReadPin5(void)
{
    return (KEY_PinLevel_TypeDef) GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_5);
}

// 获取按键是按下还是释放，保存到结构体
static void KEY_GetAction_PressOrRelease(KEY_Configure_TypeDef* KeyCfg)// 根据实际按下按钮的电平去把它换算成虚拟的结果
{
	if(KeyCfg->KEY_ReadPin_Fcn() == KEY_PRESSED_LEVEL)
	{
		KeyCfg->KEY_Action = KEY_Action_Press;
	}
	else
	{
		KeyCfg->KEY_Action = KEY_Action_Release;
	}
}


void KEY_Init(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = KEY_PIN_0 | KEY_PIN_1 | KEY_PIN_2 | KEY_PIN_3 | KEY_PIN_4 | KEY_PIN_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//少了这行可能会导致驱动能力不足，引脚电平无法达到预期的高/低电平。
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IN_FLOATING
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);

	// 初始化时根据实际需要设置是否启用双击功能
	Key0Cfg.Enable_DoubleClick = 0;// 初始化时根据实际需要设置是否启用双击功能
	Key1Cfg.Enable_DoubleClick = 0;
	Key2Cfg.Enable_DoubleClick = 0;
	Key3Cfg.Enable_DoubleClick = 0;
	Key4Cfg.Enable_DoubleClick = 1;
	Key5Cfg.Enable_DoubleClick = 0;
}
/**************************************************************************************************** 
*                             读取按键状态机
****************************************************************************************************/
void KEY_ReadStateMachine(KEY_Configure_TypeDef* KeyCfg)
{
     KEY_GetAction_PressOrRelease(KeyCfg);
	
	switch(KeyCfg->KEY_Status)
	{
		//状态：没有按键按下
		case KEY_Status_Idle:
			if(KeyCfg->KEY_Action == KEY_Action_Press)
			{
				KeyCfg->KEY_Status = KEY_Status_Debounce;
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
			else
			{
				KeyCfg->KEY_Status = KEY_Status_Idle;
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
			break;
		
		//状态：没有按键按下
		case KEY_Status_Debounce:
			if(KeyCfg->KEY_Action == KEY_Action_Press)
			{
				KeyCfg->KEY_Status = KEY_Status_ConfirmPress;
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
			else
			{
				KeyCfg->KEY_Status = KEY_Status_Idle;
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
			break;	

		//状态：继续按下
		case KEY_Status_ConfirmPress:
			if( (KeyCfg->KEY_Action == KEY_Action_Press) && (KeyCfg->KEY_Count >= KEY_LONG_PRESS_TIME))
			{
				KeyCfg->KEY_Status = KEY_Status_ConfirmPressLong;
				KeyCfg->KEY_Event = KEY_Event_LongPress; // 在长按状态时立即标记长按事件
				KeyCfg->KEY_Count = 0;
			}
			else if( (KeyCfg->KEY_Action == KEY_Action_Press) && (KeyCfg->KEY_Count < KEY_LONG_PRESS_TIME))
			{
				KeyCfg->KEY_Count++;
				KeyCfg->KEY_Status = KEY_Status_ConfirmPress;
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
			else
			{
				KeyCfg->KEY_Count = 0;
				KeyCfg->KEY_Status = KEY_Status_WaiteAgain;
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
			break;	
		
		//状态：一直长按着		
		case KEY_Status_ConfirmPressLong:
			if(KeyCfg->KEY_Action == KEY_Action_Press)
			{		// 一直等待其放开
				KeyCfg->KEY_Status = KEY_Status_ConfirmPressLong;
				KeyCfg->KEY_Event = KEY_Event_Null; // 长按状态时不重复标记事件
				KeyCfg->KEY_Count = 0;
			}
			else
			{
				KeyCfg->KEY_Status = KEY_Status_Idle;
				KeyCfg->KEY_Event = KEY_Event_Null; // 按键释放后，清除事件
				KeyCfg->KEY_Count = 0;
			}
			break;	
			
		//状态：等待是否再次按下
			case KEY_Status_WaiteAgain:
			if((KeyCfg->KEY_Action != KEY_Action_Press) && (KeyCfg->KEY_Count >= KEY_WAIT_DOUBLE_TIME))
			{// 第一次短按,且释放时间大于KEY_WAIT_DOUBLE_TIME
				KeyCfg->KEY_Count = 0;
				KeyCfg->KEY_Status = KEY_Status_Idle;  
				KeyCfg->KEY_Event = KEY_Event_SingleClick;// 响应单击
			}
			else if((KeyCfg->KEY_Action != KEY_Action_Press) && (KeyCfg->KEY_Count < KEY_WAIT_DOUBLE_TIME))
			{
				KeyCfg->KEY_Count++;
				KeyCfg->KEY_Status = KEY_Status_WaiteAgain;// 继续等待
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
			else
			{
				KeyCfg->KEY_Count = 0;
				if (KeyCfg->Enable_DoubleClick) // 如果启用了双击功能
				{
					KeyCfg->KEY_Status = KEY_Status_SecondPress;
					KeyCfg->KEY_Event = KEY_Event_Null;
				}
				else // 禁用双击功能时，处理为单击
				{
					KeyCfg->KEY_Status = KEY_Status_Debounce;
					KeyCfg->KEY_Event = KEY_Event_SingleClick;
				}
			}
			break;		
	
			
		case KEY_Status_SecondPress:
			if( (KeyCfg->KEY_Action == KEY_Action_Press) && (KeyCfg->KEY_Count >= KEY_LONG_PRESS_TIME))
			{
				KeyCfg->KEY_Status = KEY_Status_ConfirmPressLong;
				KeyCfg->KEY_Event = KEY_Event_SingleClick;
				KeyCfg->KEY_Count = 0;
			}
			else if( (KeyCfg->KEY_Action == KEY_Action_Press) && (KeyCfg->KEY_Count < KEY_LONG_PRESS_TIME))
			{
                KeyCfg->KEY_Count++;
				KeyCfg->KEY_Status = KEY_Status_SecondPress;
				KeyCfg->KEY_Event = KEY_Event_Null;
			}
            else
            {
                KeyCfg->KEY_Count = 0;
				KeyCfg->KEY_Status = KEY_Status_Idle;
				if (KeyCfg->Enable_DoubleClick) // 如果启用了双击功能
				{
					KeyCfg->KEY_Event = KEY_Event_DoubleClick;
				}
				else // 禁用双击功能时，处理为单击
				{
					KeyCfg->KEY_Event = KEY_Event_SingleClick;
				}
            }
			break;	
		default:
			break;
	}
}





