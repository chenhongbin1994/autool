#ifndef _HT61666LCD_H_
#define _HT61666LCD_H_


#include "stm32f10x.h"
#include "delay.h"
#include "digit.h"




void LCD_GpioInit( void );
void HT1623_SendBit_H( u8 data, u8 bit );
void HT1623_SendBit_L( u8 data,u8 bit );
void SendCmd( u8 command );

void Write_1623HalfByte(u8 SEG,u8 dat);
void W1623_byte(uint8_t SEG, uint8_t dat);
void W1623_RPMbyte(uint8_t SEG, uint8_t dat);
void W1623_byteMyriabit(uint8_t SEG, uint8_t dat);//����2��SEGд����λ�����ƶ��Ÿ�(��λ�������
void Write_1623LowerHalfByte(u8 SEG,u8 dat);
void W1623_Lowerbyte(uint8_t SEG, uint8_t dat);//����2��SEGд����λ������һ�Ÿ׺Ͷ��Ÿ������
void W1623_LowerbyteMyriabit(uint8_t SEG, uint8_t dat);//����2��SEGд����λ������һ�Ÿ׺Ͷ��Ÿ�(��λ�������
void W1623_TIMELowerbyte(uint8_t SEG, uint8_t dat);//����MINMAX�����

void W1623_bothSeg_byte(uint8_t SEG, uint8_t dat);//1��SEG8��bit����д
void W1623_success(uint8_t SEG, uint8_t cnt, volatile uint8_t *p);
void disp_renew(void);
void dispON(uint8_t com, uint8_t SEG);
void dispOFF(uint8_t com, uint8_t SEG);
void cleandisp(void);
void disp_All(void);
void LCD_Init(void);
void LCD_DISP(void);
void LCD_CLOSE(void);
void lcd_clear1(void);
void lcd_clear2(void);

void HT1623_Read_Bit(void);
unsigned char HT1623_ReadData_Lcd(void);
unsigned char HT1623_ReadByte(u8 address);
void UpdateReadModifyWriteDisplay(uint8_t address, uint8_t mask, uint8_t opr);


#endif 
