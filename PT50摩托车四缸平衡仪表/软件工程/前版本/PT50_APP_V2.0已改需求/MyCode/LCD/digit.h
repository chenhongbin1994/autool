
#ifndef		_DIGIT_H_
#define		_DIGIT_H_

#include "stm32f10x.h"

/*--------------------------功能图标----------------------------*/
#define 	Battery_Data_S1	 			0x01  // 
#define 	Battery_Data_S2 			0x02  // 
#define 	Battery_Data_S3 			0x04  // 
#define 	Battery_Data_S4 			0x08  // 
#define 	Battery_Data_S5 			0x10  // 
#define 	Screen_Data_REC 			0x20  //    REC
#define 	Screen_Data_R1 				0x40  //    搜索图标
#define 	Screen_Data_TypeC 			0x80  //    type_c接口图标
#define 	Screen_Data_lock	 		0x80  //    锁定图标
#define 	Screen_Data_LED 			0x40  // 	LED背光图标
#define 	Screen_Data_BUZZER 			0x20  // 	扬声器图标
#define 	Screen_Data_RPM 			0x01  //    RPM 
#define 	Screen_Data_2T 				0x01  //    2T图标
#define 	Screen_Data_4T 				0x08  //    4T图标
#define 	Screen_Data_rec 			0x10  //    REC小图标
#define 	Screen_Data_Zero	 			0x04  // pin58   ZERO
#define 	Screen_Data_USB 				0x08  // pin58   USB
#define 	Screen_Data_S23					0x10  // pin58   p=0

/*----------------------------功能图标------------------------*/
/*------------------进度块--------------------*/
#define 	ProgressBlock_Data_1 			0x01  // pin20  
#define 	ProgressBlock_Data_2			0x02  // pin20
#define 	ProgressBlock_Data_3			0x04  // pin20
#define 	ProgressBlock_Data_4 			0x08  // pin20
#define 	ProgressBlock_Data_5 			0x08  // pin21
#define 	ProgressBlock_Data_6			0x04  // pin21
#define 	ProgressBlock_Data_7			0x02  // pin21
#define 	ProgressBlock_Data_8 			0x01  // pin21
/*------------------进度块--------------------*/
/*---------------------------编码调整后----------------------------------*/
#define 	Screen_Data_Auto				0x01  //    Auto
#define 	Screen_Data_on 					0x02  // 	 on
#define 	Screen_Data_off 				0x04  //    off
#define 	Screen_Data_S27_REC				0x10  // pin20	 REC
#define 	Screen_Data_DifferValue			0x08  //    △P
#define 	Screen_Data_Time 				0x20  //    Time
#define 	Screen_Data_MIN 				0x40  //    MIN
#define 	Screen_Data_MAX					0x80  //    MAX
/*--------------------------时钟数码段显示--------------------------*/
#define 	Group2_digitron_Data_A	 			0x01 
#define 	Group2_digitron_Data_B 				0x02  
#define 	Group2_digitron_Data_C				0x04  
#define 	Group2_digitron_Data_D 				0x08  
#define 	Group2_digitron_Data_F				0x10  
#define 	Group2_digitron_Data_G 				0x20  
#define 	Group2_digitron_Data_E 				0x40  
#define 	Group2_digitron_point_Data_S33 		0x80  //小数点
#define 	Group2_digitron_TIME_colon_S32 		0x80  //SEG10
#define 	Group2_digitron_TIME_colon_S38 		0x40  //SEG22

/*--------------------------柱形显示--------------------------*/
#define     Mercury_1_Data_K1					0x20  
#define     Mercury_2_Data_K2					0x40  
#define     Mercury_3_Data_K3					0x80 
#define     Mercury_4_Data_K4					0x80  

#define     Mercury_1_Data_Grid1				0x80  
#define     Mercury_1_Data_Grid2				0x40  
#define     Mercury_1_Data_Grid3				0x20  
#define     Mercury_1_Data_Grid4				0x10  
#define     Mercury_1_Data_Grid5				0x08  
#define     Mercury_1_Data_Grid6				0x04 
#define     Mercury_1_Data_Grid7				0x02  // pin12
#define     Mercury_1_Data_Grid8				0x01  // pin12
#define     Mercury_1_Data_Grid9				0x08  // pin13
#define     Mercury_1_Data_Grid10				0x80  // pin13

#define     Mercury_2_Data_Grid1				0x80  // pin11
#define     Mercury_2_Data_Grid2				0x40  // pin11
#define     Mercury_2_Data_Grid3				0x20  // pin11
#define     Mercury_2_Data_Grid4				0x10  // pin11
#define     Mercury_2_Data_Grid5				0x08  // pin11
#define     Mercury_2_Data_Grid6				0x04  // pin11
#define     Mercury_2_Data_Grid7				0x02  // pin11
#define     Mercury_2_Data_Grid8				0x01  // pin11
#define     Mercury_2_Data_Grid9				0x04  // pin13
#define     Mercury_2_Data_Grid10				0x40  // pin13

#define     Mercury_3_Data_Grid1				0x80  // pin10
#define     Mercury_3_Data_Grid2				0x40  // pin10
#define     Mercury_3_Data_Grid3				0x20  // pin10
#define     Mercury_3_Data_Grid4				0x10  // pin10
#define     Mercury_3_Data_Grid5				0x08  // pin10
#define     Mercury_3_Data_Grid6				0x04  // pin10
#define     Mercury_3_Data_Grid7				0x02  // pin10
#define     Mercury_3_Data_Grid8				0x01  // pin10
#define     Mercury_3_Data_Grid9				0x02  // pin13
#define     Mercury_3_Data_Grid10				0x20  // pin13

#define     Mercury_4_Data_Grid1				0x80  // pin9
#define     Mercury_4_Data_Grid2				0x40  // pin9
#define     Mercury_4_Data_Grid3				0x20  // pin9
#define     Mercury_4_Data_Grid4				0x10  // pin9
#define     Mercury_4_Data_Grid5				0x08  // pin9
#define     Mercury_4_Data_Grid6				0x04  // pin9
#define     Mercury_4_Data_Grid7				0x02  // pin9
#define     Mercury_4_Data_Grid8				0x01  // pin9
#define     Mercury_4_Data_Grid9				0x01  // pin13
#define     Mercury_4_Data_Grid10				0x10  // pin13
/*--------------------------柱形显示--------------------------*/


/*--------------------------数码显示--------------------------*/
#define   Digitron_Cylinder1            0x08  //pin12
#define   Digitron_Cylinder2            0x04
#define   Digitron_Cylinder3            0x02
#define   Digitron_Cylinder4            0x01

#define 	Group6_digitron_Data_A	 		0x08  // pin49
#define 	Group6_digitron_Data_B 			0x04  // pin49
#define 	Group6_digitron_Data_C			0x02  // pin49
#define 	Group6_digitron_Data_D 			0x01  // pin49
#define 	Group6_digitron_Data_F			0x80  // pin48
#define 	Group6_digitron_Data_G 			0x40  // pin48
#define 	Group6_digitron_Data_E 			0x20  // pin48
#define 	Group6_digitron_point_Data_p	 	0x10  // pin48   小数点图标

/*------------------------单位切换显示------------------------*/
#define     Switching_Unit_Data_K				0x10  // 
#define     Switching_Unit_Data_pa				0x20  // 
#define     Switching_Unit_Data_mmHg			0x08  // 
#define     Switching_Unit_Data_Torr			0x04  // 
#define     Switching_Unit_Data_m				0x02  // 
#define     Switching_Unit_Data_bar				0x01  // 
#define     Switching_Unit_Data_inHg			0x01  // 
#define     Switching_Unit_Data_inH2O			0x02  // 
#define     Switching_Unit_Data_mmH2O			0x04  // 
#define     Switching_Unit_Data_Kgcm2			0x08  // 
#define     Switching_Unit_Data_psi				0x20  // 
#define     Switching_Unit_Data_hpa				0x10  // 
/*------------------------单位切换显示------------------------*/

#define          SEGOK_OFF                  0x00
enum Lcd_Addr
{
	Addr0  = 0,
	Addr1  = 1,
	Addr2  = 2,
	Addr3  = 3,
	Addr4  = 4,
	Addr5  = 5,
	Addr6  = 6,
	Addr7  = 7,
	Addr8  = 8,
	Addr9  = 9,
	Addr10 = 10,
	Addr11 = 11,
	Addr12 = 12,
	D13 	 = 13,
	Addr14  = 14,
	Addr15  = 15,
	Addr16  = 16,
	Addr17  = 17,
	Addr18  = 18,
	Addr19  = 19,
	Addr20  = 20,
	Addr21  = 21,
	Addr22  = 22,
	Addr23  = 23,
	D24  = 24,
	D25  = 25,
	D26  = 26,
	D27  = 27,
	D28  = 28,
	D29  = 29,
	D30  = 30,
	D31  = 31,
	D32  = 32,
	D33  = 33,
	D34  = 34,
	D35  = 35,
	D36  = 36,
	D37  = 37,
	D38  = 38,
	D39  = 39,
	D40  = 40,
	D41  = 41,
	D42  = 42
};


//选择缸数
#define   MODE_CH1   0
#define   MODE_CH2   1
#define   MODE_CH3   2
#define   MODE_CH4   3


/*---------------------------调整后----------------------------------*/
void ClearDigitalTubeDisplay(void);//清除四缸数码段，起刷新作用
void ClearMercuryDisplay(void);//清除四缸汞柱，起刷新作用
void Clear_RMP_DigitalTubeDisplay(void);//清除刷新转速数码段
void Clear_Group1dig(void);
void Clear_Group2dig(void);
void mercury_display(u8 addr_1, u16 AD_MercuryValue);//进度条格数按AD值来判断
void Digital_tube_Bit_Display(int num, uint8_t position);
void Digital_tube_display(u8 addr1,u8 addr2,u8 addr3,u8 addr4,u8 addr_5,float display_num,u16 AD_MercuryValue);
void ProcessAndDisplayPressureValues(float PositivePressure, float K_Value);
void SwitcUint(float* inputPressure);//单位换算
void Clock_Display(void);
void Clear_Clock_Display(void);
float calculateBatteryVoltage(int channel);

void Dig_Zero(void);
void Calibration(void);
void NumHistoricalData_Display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,int HistoricalData_num);
void TIME_Digital_tube_Bit_Display(uint32_t Timnum, uint8_t Timposition);

void SettingsUint(float display_value);
void SwitchingNumberCylinders(void);
void Digital_2tube_display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,float display_num);//只显示压力值数码管
void SettingsUint_display(void);
void Switching2T4T_display(void);
void AUutoshutdownONOFF_display(void);


#endif

