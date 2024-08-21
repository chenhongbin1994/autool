
#ifndef LCD_H
#define LCD_H
#include "stm32f10x.h"


#define LIGHT_H  GPIO_SetBits(GPIOA,GPIO_Pin_12)   //背光高
#define LIGHT_L  GPIO_ResetBits(GPIOA,GPIO_Pin_12) //背光低

#define LCS_H    GPIO_SetBits(GPIOA,GPIO_Pin_1)  	//片选1
#define LCS_L    GPIO_ResetBits(GPIOA,GPIO_Pin_1)  	//片选0

#define LRD_H    GPIO_SetBits(GPIOA,GPIO_Pin_0)   	//读1
#define LRD_L    GPIO_ResetBits(GPIOA,GPIO_Pin_0)   //读0

#define LWR_H    GPIO_SetBits(GPIOC,GPIO_Pin_2)  	//写1
#define LWR_L    GPIO_ResetBits(GPIOC,GPIO_Pin_2)  	//写0

#define LDA_H    GPIO_SetBits(GPIOC,GPIO_Pin_1)  	//数据1
#define LDA_L    GPIO_ResetBits(GPIOC,GPIO_Pin_1)  	//数据0
//#define LIRQ         C0   //看门狗（计数器）溢出标志回馈给中断

/////////////////////commend ////////////////

#define SYS_Dis      0x00   //系统失能，内部振荡关，显示关。 上电默认
#define SYS_EN       0x01   //打开系统晶振
#define LCD_OFF      0x02   //关闭LCD显示  上电默认
#define LCD_ON       0x03   //开LCD显示  
#define Timer_Dis    0x04   //定时器关   上电默认
#define WDT_Dis      0x05   //看门狗失能 上电默认
#define Timer_EN     0x06   //定时器使能
#define WDT_EN       0x07   //开看门狗
#define Tone_OFF     0x08   //失能输出  上电默认
#define Clr_Timer    0x0D   //清定时器
#define Clr_WDT      0x0f   //清看门狗
#define RC_32K       0x18   //使用片上RC振荡 上电默认
#define EXT_32K      0x1C   //使用外部32K晶振
#define Tone_4K      0x40   //输出4K音频
#define Tone_2K      0x60   //输出2K音频
#define IRQ_Dis      0x80   //中断输出失能  上电默认
#define IRQ_EN       0x88   //使能中断输出

extern void LCD_init(void);
extern u8 Read_1625     (u8 addr,u8 cnt);
extern void  SendCmd       (u8 command);
extern void  Write_1625    (u8 addr,u8 mdata);
extern void  WriteAll_1625 (u8 addr,u8 *p,u8 cnt);
extern void  full_or_clear (u8 F_C);

#endif
