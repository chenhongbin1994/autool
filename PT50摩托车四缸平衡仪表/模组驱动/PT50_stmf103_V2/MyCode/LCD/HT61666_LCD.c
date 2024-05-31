/*
 * @Author: hong 944278386@qq.com
 * @Date: 2024-05-15 11:54:58
 * @LastEditors: hong 944278386@qq.com
 * @LastEditTime: 2024-05-17 14:56:19
 * @FilePath: \USERc:\Users\IBM\Desktop\四缸平衡仪表\模组驱动\STM32F103coding - V3\MyCode\LCD\HT61666_LCD.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "HT61666_LCD.h"


/* 这里管脚配置需要根据实际情况做出修改的改下管脚和写法即可 */
#define   LCD_D_Port        GPIOD
#define   LCD_D_LED_PIN     GPIO_Pin_6  
#define   LCD_D_CS_PIN     GPIO_Pin_7  

#define   LCD_B_Port        GPIOB
#define   LCD_B_WR_PIN      GPIO_Pin_5  
#define   LCD_B_RD_PIN      GPIO_Pin_4  
#define   LCD_B_Data_PIN    GPIO_Pin_3  

#define		CS_High     	GPIO_SetBits(LCD_D_Port, LCD_D_CS_PIN)
#define		CS_Low      	GPIO_ResetBits(LCD_D_Port, LCD_D_CS_PIN)

#define		WR_High     	GPIO_SetBits(LCD_B_Port, LCD_B_WR_PIN)
#define     WR_Low      	GPIO_ResetBits(LCD_B_Port, LCD_B_WR_PIN)

#define     RD_High     	GPIO_SetBits(LCD_B_Port, LCD_B_RD_PIN)
#define     RD_Low      	GPIO_ResetBits(LCD_B_Port, LCD_B_RD_PIN)

#define     Data_High   	GPIO_SetBits(LCD_B_Port, LCD_B_Data_PIN)            
#define     Data_Low    	GPIO_ResetBits(LCD_B_Port, LCD_B_Data_PIN)

#define		LCD_NORMAL	0xE3 	//LCD正常模式启动
#define		LCD_OFF		0x02	//关闭LCD显示
#define		LCD_ON		0x03	//打开LCD显示
#define		SYS_EN		0x01	//打开系统时钟
#define		RC_32K		0x18	//片内RC时钟使能

static uint8_t CS0_Src[32] = {0}; //源数据 LCD显示数据对应32位输入数据位

/* 设备编号 	对应段码图算出的值			    0    1    2    3    4    5    6    7    8    9    无    -   F */
static const uint8_t CS0_DevId_Num[13] = {0xEF,0x25,0xBB,0xB7,0x75,0xD7,0xDF,0xAD,0xFF,0xF7,0x80,0x11,0x59};

/***********************************************
Function :LCD_GpioInit
Discription:LCD管脚初始化
Parameter: 空
************************************************/
void LCD_GpioInit( void )
{
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD, ENABLE );

	GPIO_InitStructure.GPIO_Pin = LCD_D_LED_PIN|LCD_D_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( LCD_D_Port, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = LCD_B_WR_PIN|LCD_B_RD_PIN|LCD_B_Data_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( LCD_B_Port, &GPIO_InitStructure );

	GPIO_SetBits( LCD_D_Port, LCD_D_LED_PIN|LCD_D_CS_PIN );
	GPIO_SetBits( LCD_B_Port, LCD_B_WR_PIN|LCD_B_RD_PIN|LCD_B_Data_PIN );
}


/*通信方式都是串口通信，这里是模拟IIC的通讯方式写入数据，HT1623指令配置根据自己需求添加修改*/
/***********************************************
Function :LCD_Delay
Discription:延时
Parameter: 空
************************************************/
void LCD_Delay( )
{
	uint8_t i = 0;

	for( i = 0; i < 5; i++ );
}

/***********************************************
Function :void HT1623_SendBit_H(u8 data,u8 bit)
Discription:高bit位写入HT1623
Parameter: data 要写入的数据 
 		   bit要写入的位数
************************************************/
void HT1623_SendBit_H( u8 data, u8 bit )
{
	u8 i;

	for( i = 0; i < bit; i++ )
	{
		if( data & 0x80 )
			Data_High;
		else
			Data_Low;

		WR_Low;
		LCD_Delay();
		WR_High;
		data <<= 1;
		LCD_Delay();
	}
}

/***********************************************
Function :void HT1623_SendBit_L(u8 data,u8 bit)
Discription:低bit位写入HT1623
Parameter: data 要写入的数据 
		   bit要写入的位数
************************************************/
void HT1623_SendBit_L( u8 data,u8 bit )
{
	u8 i;

	for( i = 0; i < bit; i++ )
	{
		if( data & 0x01 )
			Data_High;
		else
			Data_Low;

		WR_Low;
		LCD_Delay();
		WR_High;
		data >>= 1;
		LCD_Delay();
	}
}

/***********************************************
Function :void SendCmd(u8 command)
Discription:发送命令
Parameter: command 命令
************************************************/
void SendCmd( u8 command )
{
	CS_Low;
	HT1623_SendBit_H( 0x80,3 );        //写入标志码"100"
	HT1623_SendBit_H( command,9 );     //写入9 位数据,其中前8 位为command 命令,最后1 位任意
	CS_High;
}

/***********************************************
Function :void Write_1623Byte(u8 SEG,u8 dat)
Discription:写入HT1623数据
Parameter: SEG 要写入的地址  
		   dat要写入得数据
************************************************/
void  Write_1623Byte( u8 SEG,u8 dat )
{
	u8 addr;
	addr = SEG;                     
	CS_Low;
	HT1623_SendBit_H( 0xa0,3 );        //写入标志码"101" 
	HT1623_SendBit_H( addr<<2,6 );     //写入7 位addr    32

	/* 这里可以四位写法是方便其他4COM屏幕使用时改写程序,当然你也可以改写为8位写入 */
	HT1623_SendBit_L( dat<<1,8 );      //写入data 的低4 位
	HT1623_SendBit_H( dat,8 );		   //写入data 的高4 位

	CS_High;
}

/***********************************************
Function :void HT1623_INIT(void)
Discription:HT1623初始化
Parameter:
************************************************/
void HT1623_INIT( void )
{
	/* 这里配置要根据自己的需求添加或更改配置 详见DataSheet */
	SendCmd( SYS_EN );        //打开系统时钟
	SendCmd( RC_32K );        //片内RC时钟
	SendCmd( LCD_ON );        //使能LCD显示
	SendCmd( LCD_NORMAL );    //LCD正常启动
}

/***********************************************
Function :void DisPlay_Init(void)
Discription:显示初始化
Parameter:
************************************************/
void DisPlay_Init( void )
{
	LCD_GpioInit(); //LCD GPIO初始化
	HT1623_INIT();	//HT1623初始化
}

/***********************************************
Function :void LCD_Clear_All(void)
Discription:清屏
Parameter:
************************************************/
void LCD_Clear_All( void )
{
	u8  i;

	for( i=0; i<32; i++ )
	{
		CS0_Src[i] = 0x00;    //全清
		Write_1623Byte( i,CS0_Src[i] );//写入数据
	}
}

/***********************************************
Function :void LCD_Display_All(void)
Discription:显示所有
Parameter:
************************************************/
void LCD_Display_All( void )
{
	u8  i;

	for( i=0; i<32; i++ )
	{
		CS0_Src[i] = 0xFF;    //全显
		Write_1623Byte( i,CS0_Src[i] );//写入数据
	}
}




/*----------------------------操作段码屏例程----------------------------*/
/***********************************************
Function :uint8_t LCD_DeviceID(uint8_t *pData)
Discription: 设备编码,数据长度六位
Parameter: pData 六位设备编码
************************************************/
uint8_t LCD_DeviceID( uint8_t *pData )
{
	uint8_t addr = 0,i = 0;

	while( i < 6 )
	{
		if( pData[i] < '0' | pData[i] > '9' )
			return 1;//原来空

		i++;
	}

	for( i = 0; i < 6; i++ )
	{
		CS0_Src[i] = CS0_DevId_Num[( pData[i]-0x30 )]; //0~5 六位设备编码
		Write_1623Byte( i,CS0_Src[i] );
	}

	return 0;
}

/***********************************************
Function :void DisPlay_Task(void)
Discription: 屏幕显示任务，这里使用的是RTOS写的任务
Parameter: 
************************************************/
void DisPlay_Task( void *pvParameters )
{
	static u8 Dvice_Init_Flag = 0; 
	uint8_t id[6] = "123456";

	if( Dvice_Init_Flag == 0 )
	{
		Dvice_Init_Flag = 1;

		/* 初始化配置 */
		DisPlay_Init();

		/* 清屏 */
		LCD_Clear_All();

		/* 全部显示 */
		LCD_Display_All();

		/* 清屏 */
		LCD_Clear_All();
	}
	
	while(1)
	{
		/* 设备ID */
		LCD_DeviceID( id );
		delay_ms(200);
		//vTaskDelay( 200 );
	}
}












