#ifndef __HT1623_H
#define __HT1623_H

#include "stm32f1xx_hal.h"

#define uchar unsigned char
#define uint unsigned int

#define GPIO_CS GPIOB
#define GPIO_PIN_CS GPIO_PIN_13
#define GPIO_WR GPIOB
#define GPIO_PIN_WR GPIO_PIN_14
#define GPIO_DATA GPIOB
#define GPIO_PIN_DATA GPIO_PIN_15


#define	S17 			1
#define	S16				2
#define	S15 			3
#define	S17S16 		4
#define	S17S15 		5
#define	S16S15 		6
#define	S17S16S15 7

#define	S14 			8
#define	S13 			9
#define	S1  			10
#define	S14S13		11
#define	S14S1			12
#define	S13S1			13
#define	S14S13S1	14

#define	S4 				15
#define	S3 				16
#define	S2  			17
#define	S4S3			18
#define	S4S2			19
#define	S3S2			20
#define	S4S33S2		21

#define S5				78

#define	S8 				22
#define	S7 				23
#define	S6  			24
#define	S8S7			25
#define	S8S6			26
#define	S7S6			27
#define	S8S7S6		28

#define S9				79

#define	S11 			29
#define	S12 			30
#define	S18  			31
#define	S11S12		32
#define	S11S18		33
#define	S12S18		34
#define	S11S12S18	35

#define S10				80

#define	S21 			36
#define	S20 			37
#define	S19  			37
#define	S21S20		39
#define	S21S19		40
#define	S20S19		41
#define	S21S20S19	42

#define S23				81

#define	T20 			82
#define	T22 			83
#define	T20T22 		84

#define	T18 			43
#define	T19 			44
#define	T17  			45
#define	T18T19		46
#define	T18T17		47
#define	T19T17		48
#define	T18T19T17	49

#define S22				85

#define	T14 			50
#define	T15 			51
#define	T13  			52
#define	T14T15		53
#define	T14T13		54
#define	T15T13		55
#define	T14T15T13	56

#define	T16				86

#define	T9 				57
#define	T10 			58
#define	T12  			59
#define	T9T10			60
#define	T9T12			61
#define	T10T12		62
#define	T9T10T12	63

#define T11				87

#define	T2 				64
#define	T4 				65
#define	T6  			66
#define	T2T4			67
#define	T2T6			68
#define	T4T6			69
#define	T2T4T6		70

#define T1				88

#define	T5 				71
#define	T7 				72
#define	T8  			73
#define	T5T7			74
#define	T5T8			75
#define	T7T8			76
#define	T5T7T8		77

#define T3				89



void HT1623_SendBit(unsigned char data,unsigned char cnt);
void HT1623_SendDataBit(unsigned char data,unsigned char cnt);
void HT1623_SendCmd(unsigned char command);
void HT1623_Write(unsigned char addr,unsigned char data);
void HT1623_WriteAll(unsigned char addr, unsigned char *p, unsigned char cnt);
void HT1623_Init(void);

void Clear(void);					//清屏函数
void Full(void);				 	//全显示函数
void display_nb(unsigned char nb1,unsigned char nb2);  //写数字  nb1 第几位  nb2显示几 （0-10）10为不显示
void display_point(unsigned char nb,unsigned char enable);//写点 nb  第几个 en 使能
void display_piece(unsigned char nb,unsigned char enable);//写块  nb  第几个块    enable 使能
void display_time(unsigned char hour,unsigned char min,unsigned char sec);//写时间
void display_money(uint32_t money,unsigned char enable);//写金钱
void display_top(unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e,unsigned char f,unsigned char g,unsigned char h);//顶部 自左向右
void display_left(unsigned char a1,unsigned char a2,unsigned char a3,unsigned char a4,unsigned char a5,unsigned char a6,unsigned char a7,unsigned char a8,unsigned char a9,unsigned char a10);//左
void display_right(unsigned char a1,unsigned char a2,unsigned char a3,unsigned char a4);//
void display_under(unsigned char nb,unsigned char enable); //底部  nb  第几个块    enable 使能  //上下左右见图片

#endif /* __HT1623_H */
