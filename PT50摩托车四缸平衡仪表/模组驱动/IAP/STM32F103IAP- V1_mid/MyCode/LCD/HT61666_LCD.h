#ifndef _HT61666LCD_H_
#define _HT61666LCD_H_

/*********************************************************************
 * INCLUDES
 */
#include "stm32f10x.h"
#include "delay.h"
//#include "Spi.h"


/*------------------------------------------------------*/
#define 	Battery_Data_S1	 			0x01  // pin59
#define 	Battery_Data_S2 			0x02  // pin59
#define 	Battery_Data_S3 			0x04  // pin59
#define 	Battery_Data_S4 			0x08  // pin59
#define 	Battery_Data_S5 			0x10  // pin59
#define 	Screen_Data_REC 			0x20  // pin59   REC
#define 	Screen_Data_R1 				0x40  // pin59   搜索图标
#define 	Screen_Data_TypeC 			0x80  // pin59   type_c接口图标
#define 	Screen_Data_lock	 		0x80  // pin58   锁定图标
#define 	Screen_Data_LED 			0x40  // pin58	 LED背光图标
#define 	Screen_Data_BUZZER 			0x20  // pin58	 扬声器图标
#define 	Screen_Data_RPM 			0x01  // pin58   RPM 
#define 	Screen_Data_2T 				0x01  // pin58   2T图标
#define 	Screen_Data_4T 				0x08  // pin19   4T图标
/*-----------------------GROUP1数码段------------------------*/
#define 	Group1_digitron_Data_1A	 			0x01  // pin18
#define 	Group1_digitron_Data_1B 			0x02  // pin18
#define 	Group1_digitron_Data_1C 			0x04  // pin18
#define 	Group1_digitron_Data_1D 			0x08  // pin18
#define 	Group1_digitron_Data_1F 			0x01  // pin19
#define 	Group1_digitron_Data_1G 			0x02  // pin19
#define 	Group1_digitron_Data_1E 			0x04  // pin19
#define 	Group1_digitron_point_Data_Y1 		0x08  // pin17

#define 	Group1_digitron_Data_2A	 			0x01  // pin16
#define 	Group1_digitron_Data_2B 			0x02  // pin16
#define 	Group1_digitron_Data_2C				0x04  // pin16
#define 	Group1_digitron_Data_2D 			0x08  // pin16
#define 	Group1_digitron_Data_2F				0x01  // pin17
#define 	Group1_digitron_Data_2G 			0x02  // pin17
#define 	Group1_digitron_Data_2E 			0x04  // pin17
#define 	Group1_digitron_point_Data_Y2 		0x08  // pin15

#define 	Group1_digitron_Data_3A	 			0x01  // pin14
#define 	Group1_digitron_Data_3B 			0x02  // pin14
#define 	Group1_digitron_Data_3C				0x04  // pin14
#define 	Group1_digitron_Data_3D 			0x08  // pin14
#define 	Group1_digitron_Data_3F				0x01  // pin15
#define 	Group1_digitron_Data_3G 			0x02  // pin15
#define 	Group1_digitron_Data_3E 			0x04  // pin15
#define 	Group1_digitron_point_Data_Y3 		0x08  // pin57

#define 	Group1_digitron_Data_4A	 			0x01  // pin12
#define 	Group1_digitron_Data_4B 			0x01  // pin11
#define 	Group1_digitron_Data_4C				0x01  // pin10
#define 	Group1_digitron_Data_4D 			0x01  // pin19
#define 	Group1_digitron_Data_4F				0x01  // pin57
#define 	Group1_digitron_Data_4G 			0x02  // pin57
#define 	Group1_digitron_Data_4E 			0x04  // pin57
#define 	Group1_digitron_point_Data_Y4 		0x08  // pin55

#define 	Group1_digitron_Data_5A	 			0x01  // pin54
#define 	Group1_digitron_Data_5B 			0x02  // pin54
#define 	Group1_digitron_Data_5C				0x04  // pin54
#define 	Group1_digitron_Data_5D 			0x08  // pin54
#define 	Group1_digitron_Data_5F				0x01  // pin55
#define 	Group1_digitron_Data_5G 			0x02  // pin55
#define 	Group1_digitron_Data_5E 			0x04  // pin55


#define 	Screen_Data_Zero	 			0x04  // pin58   ZERO
#define 	Screen_Data_USB 				0x08  // pin58   USB
#define 	Screen_Data_S23					0x10  // pin58   p=0
/*------------------进度块--------------------*/
#define 	ProgressBlock_Data_1 			0x01  // pin53   
#define 	ProgressBlock_Data_2			0x02  // pin53
#define 	ProgressBlock_Data_3			0x04  // pin53
#define 	ProgressBlock_Data_4 			0x08  // pin53
#define 	ProgressBlock_Data_5 			0x08  // pin52   
#define 	ProgressBlock_Data_6			0x04  // pin52
#define 	ProgressBlock_Data_7			0x02  // pin52
#define 	ProgressBlock_Data_8 			0x01  // pin52
/*------------------进度块--------------------*/
#define 	Screen_Data_Auto				0x01  // pin20   Auto
#define 	Screen_Data_on 					0x02  // pin20	 on
#define 	Screen_Data_off 				0x04  // pin20   off
#define 	Screen_Data_S27_REC					0x10  // pin20	 REC
#define 	Screen_Data_S28					0x08  // pin20   △P
#define 	Screen_Data_Time 				0x20  // pin20   Time
#define 	Screen_Data_MIN 				0x40  // pin20   MIN
#define 	Screen_Data_MAX					0x10  // pin20   MAX

#define 	Group2_digitron_Data_6A	 			0x10  // pin18
#define 	Group2_digitron_Data_6B 			0x20  // pin18
#define 	Group2_digitron_Data_6C				0x40  // pin18
#define 	Group2_digitron_Data_6D 			0x80  // pin18
#define 	Group2_digitron_Data_6F				0x10  // pin19
#define 	Group2_digitron_Data_6G 			0x20  // pin19
#define 	Group2_digitron_Data_6E 			0x40  // pin19
#define 	Group2_digitron_point_Data_S33 		0x80  // pin17
/*------------------------------------------------*/
#define 	Group2_digitron_Data_7A	 			0x10  // pin16
#define 	Group2_digitron_Data_7B 			0x20  // pin16
#define 	Group2_digitron_Data_7C				0x40  // pin16
#define 	Group2_digitron_Data_7D 			0x80  // pin16
#define 	Group2_digitron_Data_7F				0x10  // pin17
#define 	Group2_digitron_Data_7G 			0x20  // pin17
#define 	Group2_digitron_Data_7E 			0x40  // pin17
#define 	Group2_digitron_point_Data_S34 		0x80  // pin15   小数点图标
#define 	Group2_digitron_colon_Data_S32 		0x80  // pin19   冒号图标

#define 	Group2_digitron_Data_8A	 			0x10  // pin14
#define 	Group2_digitron_Data_8B 			0x20  // pin14
#define 	Group2_digitron_Data_8C				0x40  // pin14
#define 	Group2_digitron_Data_8D 			0x80  // pin14
#define 	Group2_digitron_Data_8F				0x10  // pin15
#define 	Group2_digitron_Data_8G 			0x20  // pin15
#define 	Group2_digitron_Data_8E 			0x40  // pin15
#define 	Group2_digitron_point_Data_S35	 	0x80  // pin57	 小数点图标

#define 	Group2_digitron_Data_9A	 			0x10  // pin56
#define 	Group2_digitron_Data_9B 			0x20  // pin56
#define 	Group2_digitron_Data_9C				0x40  // pin56
#define 	Group2_digitron_Data_9D 			0x80  // pin56
#define 	Group2_digitron_Data_9F				0x10  // pin57
#define 	Group2_digitron_Data_9G 			0x20  // pin57
#define 	Group2_digitron_Data_9E 			0x40  // pin57
#define 	Group2_digitron_point_Data_S36	 	0x80  // pin55   小数点图标
#define 	Group2_digitron_colon_Data_S38 		0x40  // pin51   冒号图标

#define 	Group2_digitron_Data_10A	 		0x10  // pin54
#define 	Group2_digitron_Data_10B 			0x20  // pin54
#define 	Group2_digitron_Data_10C			0x40  // pin54
#define 	Group2_digitron_Data_10D 			0x80  // pin54
#define 	Group2_digitron_Data_10F			0x10  // pin55
#define 	Group2_digitron_Data_10G 			0x20  // pin55
#define 	Group2_digitron_Data_10E 			0x40  // pin55
#define 	Group2_digitron_point_Data_S37	 	0x80  // pin53   小数点图标

#define 	Group2_digitron_Data_11A	 		0x10  // pin5
#define 	Group2_digitron_Data_11B 			0x20  // pin54
#define 	Group2_digitron_Data_11C			0x40  // pin54
#define 	Group2_digitron_Data_11D 			0x80  // pin54
#define 	Group2_digitron_Data_11F			0x10  // pin55
#define 	Group2_digitron_Data_11G 			0x20  // pin55
#define 	Group2_digitron_Data_11E 			0x40  // pin55

/*--------------------------柱形显示--------------------------*/
#define     Mercury_1_Data_K1					0x20  // pin29
#define     Mercury_1_Data_Grid1				0x80  // pin12
#define     Mercury_1_Data_Grid2				0x40  // pin12
#define     Mercury_1_Data_Grid3				0x20  // pin12
#define     Mercury_1_Data_Grid4				0x10  // pin12
#define     Mercury_1_Data_Grid5				0x08  // pin12
#define     Mercury_1_Data_Grid6				0x04  // pin12
#define     Mercury_1_Data_Grid7				0x02  // pin12
#define     Mercury_1_Data_Grid8				0x01  // pin12
#define     Mercury_1_Data_Grid9				0x08  // pin13
#define     Mercury_1_Data_Grid10				0x80  // pin13

#define     Mercury_2_Data_K2					0x40  // pin29
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

#define     Mercury_3_Data_K3					0x40  // pin29
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

#define     Mercury_4_Data_K4					0x80  // pin50
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

/*------------------------单位切换显示------------------------*/
#define     Switching_Unit_Data_K				0x10  // pin51
#define     Switching_Unit_Data_pa				0x40  // pin51
#define     Switching_Unit_Data_mmHg			0x08  // pin51
#define     Switching_Unit_Data_Torr			0x04  // pin51
#define     Switching_Unit_Data_m				0x02  // pin51
#define     Switching_Unit_Data_bar				0x01  // pin51
#define     Switching_Unit_Data_inHg			0x01  // pin50
#define     Switching_Unit_Data_inH2O			0x02  // pin50
#define     Switching_Unit_Data_mmH2O			0x04  // pin50
#define     Switching_Unit_Data_Kgcm2			0x08  // pin50
#define     Switching_Unit_Data_psi				0x20  // pin50
#define     Switching_Unit_Data_hpa				0x10  // pin50
/*------------------------单位切换显示------------------------*/

/*------------------------压力值显示------------------------*/
#define 	Group3_cylinder_1_Data	 			0x08  // pin29
#define 	Group3_digitron_Data_12A	 		0x80  // pin31
#define 	Group3_digitron_Data_12B 			0x40  // pin31
#define 	Group3_digitron_Data_12C			0x20  // pin31
#define 	Group3_digitron_Data_12D 			0x10  // pin31
#define 	Group3_digitron_Data_12F			0x80  // pin30
#define 	Group3_digitron_Data_12G 			0x40  // pin30
#define 	Group3_digitron_Data_12E 			0x20  // pin30
#define 	Group3_digitron_point_Data_p12	 	0x10  // pin32   小数点图标

#define 	Group3_digitron_Data_13A	 		0x80  // pin33
#define 	Group3_digitron_Data_13B 			0x40  // pin33
#define 	Group3_digitron_Data_13C			0x20  // pin33
#define 	Group3_digitron_Data_13D 			0x10  // pin33
#define 	Group3_digitron_Data_13F			0x80  // pin32
#define 	Group3_digitron_Data_13G 			0x40  // pin32
#define 	Group3_digitron_Data_13E 			0x20  // pin32
#define 	Group3_digitron_point_Data_p13	 	0x10  // pin34   小数点图标

#define 	Group3_digitron_Data_14A	 		0x80  // pin35
#define 	Group3_digitron_Data_14B 			0x40  // pin35
#define 	Group3_digitron_Data_14C			0x20  // pin35
#define 	Group3_digitron_Data_14D 			0x10  // pin35
#define 	Group3_digitron_Data_14F			0x80  // pin34
#define 	Group3_digitron_Data_14G 			0x40  // pin34
#define 	Group3_digitron_Data_14E 			0x20  // pin34
#define 	Group3_digitron_point_Data_p14	 	0x10  // pin36   小数点图标

#define 	Group3_digitron_Data_15A	 		0x80  // pin37
#define 	Group3_digitron_Data_15B 			0x40  // pin37
#define 	Group3_digitron_Data_15C			0x20  // pin37
#define 	Group3_digitron_Data_15D 			0x10  // pin37
#define 	Group3_digitron_Data_15F			0x80  // pin36
#define 	Group3_digitron_Data_15G 			0x40  // pin36
#define 	Group3_digitron_Data_15E 			0x20  // pin36
#define 	Group3_digitron_point_Data_p15	 	0x10  // pin38   小数点图标

#define 	Group3_digitron_Data_16A	 		0x80  // pin39
#define 	Group3_digitron_Data_16B 			0x40  // pin39
#define 	Group3_digitron_Data_16C			0x20  // pin39
#define 	Group3_digitron_Data_16D 			0x10  // pin39
#define 	Group3_digitron_Data_16F			0x80  // pin38
#define 	Group3_digitron_Data_16G 			0x40  // pin38
#define 	Group3_digitron_Data_16E 			0x20  // pin38

#define 	Group4_cylinder_2_Data	 			0x04  // pin29
#define 	Group4_digitron_Data_17A	 		0x08  // pin31
#define 	Group4_digitron_Data_17B 			0x04  // pin31
#define 	Group4_digitron_Data_17C			0x02  // pin31
#define 	Group4_digitron_Data_17D 			0x01  // pin31
#define 	Group4_digitron_Data_17F			0x08  // pin30
#define 	Group4_digitron_Data_17G 			0x04  // pin30
#define 	Group4_digitron_Data_17E 			0x02  // pin30
#define 	Group4_digitron_point_Data_p17	 	0x01  // pin32   小数点图标

#define 	Group4_digitron_Data_18A	 		0x08  // pin33
#define 	Group4_digitron_Data_18B 			0x04  // pin33
#define 	Group4_digitron_Data_18C			0x02  // pin33
#define 	Group4_digitron_Data_18D 			0x01  // pin33
#define 	Group4_digitron_Data_18F			0x08  // pin32
#define 	Group4_digitron_Data_18G 			0x04  // pin32
#define 	Group4_digitron_Data_18E 			0x02  // pin32
#define 	Group4_digitron_point_Data_p18	 	0x01  // pin34   小数点图标

#define 	Group4_digitron_Data_19A	 		0x08  // pin35
#define 	Group4_digitron_Data_19B 			0x04  // pin35
#define 	Group4_digitron_Data_19C			0x02  // pin35
#define 	Group4_digitron_Data_19D 			0x01  // pin35
#define 	Group4_digitron_Data_19F			0x08  // pin34
#define 	Group4_digitron_Data_19G 			0x04  // pin34
#define 	Group4_digitron_Data_19E 			0x02  // pin34
#define 	Group4_digitron_point_Data_p19	 	0x01  // pin36   小数点图标

#define 	Group4_digitron_Data_20A	 		0x08  // pin37
#define 	Group4_digitron_Data_20B 			0x04  // pin37
#define 	Group4_digitron_Data_20C			0x02  // pin37
#define 	Group4_digitron_Data_20D 			0x01  // pin37
#define 	Group4_digitron_Data_20F			0x08  // pin36
#define 	Group4_digitron_Data_20G 			0x04  // pin36
#define 	Group4_digitron_Data_20E 			0x02  // pin36
#define 	Group4_digitron_point_Data_p20	 	0x01  // pin38   小数点图标

#define 	Group4_digitron_Data_21A	 		0x08  // pin39
#define 	Group4_digitron_Data_21B 			0x04  // pin39
#define 	Group4_digitron_Data_21C			0x02  // pin39
#define 	Group4_digitron_Data_21D 			0x01  // pin39
#define 	Group4_digitron_Data_21F			0x08  // pin38
#define 	Group4_digitron_Data_21G 			0x04  // pin38
#define 	Group4_digitron_Data_21E 			0x02  // pin38


#define 	Group5_cylinder_3_Data	 			0x02  // pin29
#define 	Group5_digitron_Data_22A	 		0x80  // pin41
#define 	Group5_digitron_Data_22B 			0x40  // pin41
#define 	Group5_digitron_Data_22C			0x20  // pin41
#define 	Group5_digitron_Data_22D 			0x10  // pin41
#define 	Group5_digitron_Data_22F			0x80  // pin40
#define 	Group5_digitron_Data_22G 			0x40  // pin40
#define 	Group5_digitron_Data_22E 			0x20  // pin40
#define 	Group5_digitron_point_Data_p22	 	0x10  // pin42   小数点图标

#define 	Group5_digitron_Data_23A	 		0x80  // pin43
#define 	Group5_digitron_Data_23B 			0x40  // pin43
#define 	Group5_digitron_Data_23C			0x20  // pin43
#define 	Group5_digitron_Data_23D 			0x10  // pin43
#define 	Group5_digitron_Data_23F			0x80  // pin42
#define 	Group5_digitron_Data_23G 			0x40  // pin42
#define 	Group5_digitron_Data_23E 			0x20  // pin42
#define 	Group5_digitron_point_Data_p23	 	0x10  // pin44   小数点图标

#define 	Group5_digitron_Data_24A	 		0x80  // pin45
#define 	Group5_digitron_Data_24B 			0x40  // pin45
#define 	Group5_digitron_Data_24C			0x20  // pin45
#define 	Group5_digitron_Data_24D 			0x10  // pin45
#define 	Group5_digitron_Data_24F			0x80  // pin44
#define 	Group5_digitron_Data_24G 			0x40  // pin44
#define 	Group5_digitron_Data_24E 			0x20  // pin44
#define 	Group5_digitron_point_Data_p24	 	0x10  // pin46   小数点图标

#define 	Group5_digitron_Data_25A	 		0x80  // pin47
#define 	Group5_digitron_Data_25B 			0x40  // pin47
#define 	Group5_digitron_Data_25C			0x20  // pin47
#define 	Group5_digitron_Data_25D 			0x10  // pin47
#define 	Group5_digitron_Data_25F			0x80  // pin46
#define 	Group5_digitron_Data_25G 			0x40  // pin46
#define 	Group5_digitron_Data_25E 			0x20  // pin46
#define 	Group5_digitron_point_Data_p25	 	0x10  // pin48   小数点图标

#define 	Group5_digitron_Data_26A	 		0x80  // pin49
#define 	Group5_digitron_Data_26B 			0x40  // pin49
#define 	Group5_digitron_Data_26C			0x20  // pin49
#define 	Group5_digitron_Data_26D 			0x10  // pin49
#define 	Group5_digitron_Data_26F			0x80  // pin48
#define 	Group5_digitron_Data_26G 			0x40  // pin48
#define 	Group5_digitron_Data_26E 			0x20  // pin48

#define 	Group6_cylinder_4_Data	 			0x01  // pin29
#define 	Group6_digitron_Data_27A	 		0x08  // pin41
#define 	Group6_digitron_Data_27B 			0x04  // pin41
#define 	Group6_digitron_Data_27C			0x02  // pin41
#define 	Group6_digitron_Data_27D 			0x01  // pin41
#define 	Group6_digitron_Data_27F			0x08  // pin40
#define 	Group6_digitron_Data_27G 			0x04  // pin40
#define 	Group6_digitron_Data_27E 			0x02  // pin40
#define 	Group6_digitron_point_Data_p27	 	0x01  // pin42   小数点图标

#define 	Group6_digitron_Data_28A	 		0x08  // pin43
#define 	Group6_digitron_Data_28B 			0x04  // pin43
#define 	Group6_digitron_Data_28C			0x02  // pin43
#define 	Group6_digitron_Data_28D 			0x01  // pin43
#define 	Group6_digitron_Data_28F			0x08  // pin42
#define 	Group6_digitron_Data_28G 			0x04  // pin42
#define 	Group6_digitron_Data_28E 			0x02  // pin42
#define 	Group6_digitron_point_Data_p28	 	0x01  // pin44   小数点图标

#define 	Group6_digitron_Data_29A	 		0x08  // pin45
#define 	Group6_digitron_Data_29B 			0x04  // pin45
#define 	Group6_digitron_Data_29C			0x02  // pin45
#define 	Group6_digitron_Data_29D 			0x01  // pin45
#define 	Group6_digitron_Data_29F			0x08  // pin44
#define 	Group6_digitron_Data_29G 			0x04  // pin44
#define 	Group6_digitron_Data_29E 			0x02  // pin44
#define 	Group6_digitron_point_Data_p29	 	0x01  // pin46   小数点图标

#define 	Group6_digitron_Data_30A	 		0x08  // pin47
#define 	Group6_digitron_Data_30B 			0x04  // pin47
#define 	Group6_digitron_Data_30C			0x02  // pin47
#define 	Group6_digitron_Data_30D 			0x01  // pin47
#define 	Group6_digitron_Data_30F			0x08  // pin46
#define 	Group6_digitron_Data_30G 			0x04  // pin46
#define 	Group6_digitron_Data_30E 			0x02  // pin46
#define 	Group6_digitron_point_Data_p30	 	0x01  // pin48   小数点图标

#define 	Group6_digitron_Data_31A	 		0x08  // pin49
#define 	Group6_digitron_Data_31B 			0x04  // pin49
#define 	Group6_digitron_Data_31C			0x02  // pin49
#define 	Group6_digitron_Data_31D 			0x01  // pin49
#define 	Group6_digitron_Data_31F			0x08  // pin48
#define 	Group6_digitron_Data_31G 			0x04  // pin48
#define 	Group6_digitron_Data_31E 			0x02  // pin48


enum Lcd_Addr{
	
	Addr1  = 36,
	Addr2  = 20,
	Addr3  = 52,
	Addr4  = 12,
	Addr5  = 44,
	Addr6  = 28,
	Addr7  = 60,
	Addr8  =  3,
	Addr9  = 34,
	Addr10 = 18,
	Addr11 = 50,
	Addr12 = 10
	
};


/*----------------------------编码完毕-----------------------------*/

void LCD_GpioInit( void );
void LCD_Delay( );
void HT1623_SendBit_H( u8 data, u8 bit );
void HT1623_SendBit_L( u8 data,u8 bit );
void SendCmd( u8 command );
void  Write_1623Byte( u8 SEG,u8 dat );
void HT1623_INIT( void );
void DisPlay_Init( void );
void LCD_Clear_All( void );
void LCD_Display_All( void );
uint8_t LCD_DeviceID( uint8_t *pData );
void DisPlay_Task( void *pvParameters );



#endif 
