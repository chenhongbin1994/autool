#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


// 按键端口定义
#define KEY_PORT GPIOC
// 按键引脚定义
#define KEY_PIN_0  GPIO_Pin_0
#define KEY_PIN_1  GPIO_Pin_1
#define KEY_PIN_2  GPIO_Pin_2
#define KEY_PIN_3  GPIO_Pin_3
#define KEY_PIN_4  GPIO_Pin_4
#define KEY_PIN_5  GPIO_Pin_5
// 按键状态
typedef enum _KEY_StatusList_TypeDef 
{
	KEY_Status_Idle = 0				, // 空闲
	KEY_Status_Debounce   		    , // 消抖
	KEY_Status_ConfirmPress		    , // 确认按下	
	KEY_Status_ConfirmPressLong		, // 确认长按着	
	KEY_Status_WaiteAgain		    , // 等待再次按下
	KEY_Status_SecondPress          , // 第二次按下
}KEY_StatusList_TypeDef;

// 按键事件
typedef enum _KEY_EventList_TypeDef 
{
	KEY_Event_Null 		   = 0x00,  // 无事件
	KEY_Event_SingleClick  = 0x01,  // 单击
	KEY_Event_DoubleClick  = 0x02,  // 双击
	KEY_Event_LongPress    = 0x04   // 长按
}KEY_EventList_TypeDef;

// 按键动作，按下、释放
typedef enum
{ 
	KEY_Action_Press = 0,
	KEY_Action_Release
}KEY_Action_TypeDef;

// 按键引脚的电平
typedef enum
{ 
	KKEY_PinLevel_Low = 0,
	KEY_PinLevel_High
}KEY_PinLevel_TypeDef;

// 按键配置结构体
typedef struct _KEY_Configure_TypeDef 
{
	uint16_t                        KEY_Count;        //按键长按计数
	KEY_Action_TypeDef             KEY_Action;        //按键动作，按下1，抬起0
	KEY_StatusList_TypeDef         KEY_Status;        //按键状态
	KEY_EventList_TypeDef          KEY_Event;          //按键事件
	KEY_PinLevel_TypeDef          (*KEY_ReadPin_Fcn)(void);    //读IO电平函数
	uint8_t Enable_DoubleClick; // 新增的标志位，用于启用或禁用双击功能
} KEY_Configure_TypeDef;

void KEY_Init(void);
void KEY_ReadStateMachine(KEY_Configure_TypeDef* KeyCfg);// 读取按键状态机


#endif

