
#ifndef LCD_H
#define LCD_H
#include "stm32f10x.h"


#define LIGHT_H  GPIO_SetBits(GPIOA,GPIO_Pin_12)   //�����
#define LIGHT_L  GPIO_ResetBits(GPIOA,GPIO_Pin_12) //�����

#define LCS_H    GPIO_SetBits(GPIOA,GPIO_Pin_1)  	//Ƭѡ1
#define LCS_L    GPIO_ResetBits(GPIOA,GPIO_Pin_1)  	//Ƭѡ0

#define LRD_H    GPIO_SetBits(GPIOA,GPIO_Pin_0)   	//��1
#define LRD_L    GPIO_ResetBits(GPIOA,GPIO_Pin_0)   //��0

#define LWR_H    GPIO_SetBits(GPIOC,GPIO_Pin_2)  	//д1
#define LWR_L    GPIO_ResetBits(GPIOC,GPIO_Pin_2)  	//д0

#define LDA_H    GPIO_SetBits(GPIOC,GPIO_Pin_1)  	//����1
#define LDA_L    GPIO_ResetBits(GPIOC,GPIO_Pin_1)  	//����0
//#define LIRQ         C0   //���Ź����������������־�������ж�

/////////////////////commend ////////////////

#define SYS_Dis      0x00   //ϵͳʧ�ܣ��ڲ��񵴹أ���ʾ�ء� �ϵ�Ĭ��
#define SYS_EN       0x01   //��ϵͳ����
#define LCD_OFF      0x02   //�ر�LCD��ʾ  �ϵ�Ĭ��
#define LCD_ON       0x03   //��LCD��ʾ  
#define Timer_Dis    0x04   //��ʱ����   �ϵ�Ĭ��
#define WDT_Dis      0x05   //���Ź�ʧ�� �ϵ�Ĭ��
#define Timer_EN     0x06   //��ʱ��ʹ��
#define WDT_EN       0x07   //�����Ź�
#define Tone_OFF     0x08   //ʧ�����  �ϵ�Ĭ��
#define Clr_Timer    0x0D   //�嶨ʱ��
#define Clr_WDT      0x0f   //�忴�Ź�
#define RC_32K       0x18   //ʹ��Ƭ��RC�� �ϵ�Ĭ��
#define EXT_32K      0x1C   //ʹ���ⲿ32K����
#define Tone_4K      0x40   //���4K��Ƶ
#define Tone_2K      0x60   //���2K��Ƶ
#define IRQ_Dis      0x80   //�ж����ʧ��  �ϵ�Ĭ��
#define IRQ_EN       0x88   //ʹ���ж����

extern void LCD_init(void);
extern u8 Read_1625     (u8 addr,u8 cnt);
extern void  SendCmd       (u8 command);
extern void  Write_1625    (u8 addr,u8 mdata);
extern void  WriteAll_1625 (u8 addr,u8 *p,u8 cnt);
extern void  full_or_clear (u8 F_C);

#endif
