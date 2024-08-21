/*
 * @Author: hong 944278386@qq.com
 * @Date: 2024-05-15 11:54:58
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-06-11 18:18:11
 * @FilePath: \USERc:\Users\IBM\Desktop\四缸平衡仪表\模组驱动\STM32F103coding - V3\MyCode\LCD\HT61666_LCD.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "LCD_HT1623.h"
#include "delay.h"
#include "timer.h"

#define TIM_Delay  4  //单位微秒
volatile u8 LCD_BUF[48];
/* 这里管脚配置需要根据实际情况做出修改的改下管脚和写法即可 */
#define   LCD_B_Port        GPIOB
#define   LCD_B_LED_PIN     GPIO_Pin_3  

#define   LCD_B_Port        GPIOB
#define   LCD_B_CS_PIN      GPIO_Pin_15 
#define   LCD_B_RD_PIN      GPIO_Pin_14
#define   LCD_B_WR_PIN      GPIO_Pin_13  
#define   LCD_B_Data_PIN    GPIO_Pin_12 

#define		  CS_High     	GPIO_SetBits(LCD_B_Port, LCD_B_CS_PIN)
#define		  CS_Low      	GPIO_ResetBits(LCD_B_Port, LCD_B_CS_PIN)

#define			WR_High     	GPIO_SetBits(LCD_B_Port, LCD_B_WR_PIN)
#define     WR_Low      	GPIO_ResetBits(LCD_B_Port, LCD_B_WR_PIN)

#define     RD_High     	GPIO_SetBits(LCD_B_Port, LCD_B_RD_PIN)
#define     RD_Low      	GPIO_ResetBits(LCD_B_Port, LCD_B_RD_PIN)

#define     Data_High   	GPIO_SetBits(LCD_B_Port, LCD_B_Data_PIN)            
#define     Data_Low    	GPIO_ResetBits(LCD_B_Port, LCD_B_Data_PIN)

#define		LCD_NORMAL	0xE3 	//LCD正常模式启动
#define		LCD_OFF		0x02	//关闭LCD显示
#define		LCD_ON		0x03	//打开LCD显示
#define		SYS_EN		0x01	//打开系统时钟
#define       SYS_DIS         0x00    //关闭振荡器和LCD驱动
#define		RC_32K		0x18	//片内RC时钟使能

/***********************************************
Function :LCD_GpioInit
Discription:LCD管脚初始化
Parameter: 空
************************************************/
void LCD_GpioInit( void )
{
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE );

	GPIO_InitStructure.GPIO_Pin = LCD_B_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( LCD_B_Port, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = LCD_B_CS_PIN|LCD_B_WR_PIN|LCD_B_RD_PIN|LCD_B_Data_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init( LCD_B_Port, &GPIO_InitStructure );

	 GPIO_ResetBits( LCD_B_Port, LCD_B_LED_PIN);
	 GPIO_SetBits( LCD_B_Port, LCD_B_CS_PIN|LCD_B_WR_PIN|LCD_B_RD_PIN|LCD_B_Data_PIN );
}









//通信方式都是串口通信，这里是模拟IIC的通讯方式写入数据，HT1623指令配置根据自己需求添加修改*/


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
		delay_us(2);
		//delay_us(TIM_Delay);
		WR_High;
		data <<= 1;
		delay_us(TIM_Delay);
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
		delay_us(2);
		//delay_us(TIM_Delay);
		WR_High;
		data >>= 1;
		delay_us(TIM_Delay);
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


//写半个字节
void Write_1623HalfByte(u8 SEG,u8 dat)
{
    CS_Low;
    HT1623_SendBit_H(0xa0,3);  //写入标志码"101"
    HT1623_SendBit_H(SEG<<2,7); //写入 7 位 addr
    HT1623_SendBit_L(dat,4);
	
    CS_High;
}
/***********************************************
Function :void W1623_byte(UINT8 SEG,UINT8 dat)
Discription:写SEG脚上所有的位，SEG(0~48)
Parameter: SEG 要写入的地址
		   dat 要写入的数据
************************************************/
void W1623_byte(uint8_t SEG, uint8_t dat)
{
	uint8_t i, addr;
	addr = SEG * 2;
	for (i = 0; i < 2; i++)
	{
		Write_1623HalfByte(addr, dat);
		addr += 1;
		dat >>= 4;
	}
}

/***********************************************
Function :void W1623_success(UINT8 SEG,UINT8 cnt,volatile UINT8 *p)
Discription:连续写单元 SEG(0~48)
Parameter: SEG 要写入的起始地址
		   cnt 要写入的数量
		   *p 要写入的数据指针
************************************************/
void W1623_success(uint8_t SEG, uint8_t cnt, volatile uint8_t *p)//HT1623_Disp_SomeRam
{
	uint8_t i, addr;
	addr = SEG;
	CS_Low;
	HT1623_SendBit_H(0xa0, 3);  //写入标志码"101"
	HT1623_SendBit_H(addr << 2, 7); //写入 7 位 addr
	for (i = 0; i < cnt; i++)
	{
		HT1623_SendBit_L(*p, 4);
		HT1623_SendBit_L(*p >> 4, 4);
		p++;
	}
	CS_High;
}

/*------------------------------------------------------------*/
void HT1623_Read_Bit(void)
{
    RD_Low;
    delay_us(TIM_Delay);
    RD_High;
    delay_us(TIM_Delay);
}

unsigned char HT1623_ReadData_Lcd(void)
{
    unsigned char i, sdata = 0;

    // 配置数据引脚为输入模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LCD_B_Data_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);
		delay_us(TIM_Delay); // 确保时序稳定
    for (i = 0; i < 8; i++)
    {
        sdata >>= 1;
        HT1623_Read_Bit();
        if (GPIO_ReadInputDataBit(LCD_B_Port, LCD_B_Data_PIN))
            sdata |= 0x80;
    }
    // 恢复数据引脚为输出模式
    GPIO_InitStructure.GPIO_Pin = LCD_B_Data_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);

    return sdata;
}
// 读取LCD地址address的数据
unsigned char HT1623_ReadByte(u8 address)
{
    unsigned char data;

    CS_Low;
    HT1623_SendBit_H(0xC0, 3);  // 发送读取命令标志码"110"
    HT1623_SendBit_H(address << 2, 7); // 发送7位地址
    delay_us(TIM_Delay); // 确保时序稳定
    data = HT1623_ReadData_Lcd();
    CS_High;

    return data;
}

/**
 * @brief 从 LCD 读取数据，进行修改并写回
 * @param addr  要读取和修改的地址
 * @param value 要修改的值
 * @param opr   操作类型（1 表示或操作，0 表示异或操作）
 */
void HT1623_ReadData_From_Lcd(u8 addr, u8 value, u8 opr)
{
    volatile u8 byte;
    u32 p;
    u8 point;

    CS_Low;

    // 计算地址点
    point = addr;
    addr += point;

    // 发送读-修改-写命令
    HT1623_SendBit_H(0xA0, 3); // 命令码 "101"
    HT1623_SendBit_H(addr << 2, 7); // 7 位地址

    // 等待片刻确保时序
    delay_us(TIM_Delay); 

    // 从 HT1623 读取数据
    byte = HT1623_ReadData_Lcd();

    // 根据操作类型修改数据
    p = byte;
    if (opr)
        p |= value;
    else
        p ^= value;

    // 将修改后的数据写回 HT1623
    HT1623_SendBit_L(p, 8);

    delay_us(TIM_Delay); // 确保时序稳定

    // 结束片选信号
		CS_High;

}



/*-------------------------------------------------------------*/
/***********************************************
Function :void disp_renew(void)
Discription:显示更新,所有8x32段全部刷新
Parameter: 空
************************************************/
void disp_renew(void)
{
	W1623_success(0, 48, LCD_BUF);
}

/***********************************************
Function :void dispON(UINT8 com,UINT8 SEG)
Discription:打开某段显示
Parameter: com COM值
		   SEG SEG值
************************************************/
void dispON(uint8_t com, uint8_t SEG)
{
	LCD_BUF[SEG] |= (1 << com);
	W1623_byte(SEG, LCD_BUF[SEG]);     //去掉注释后，写完就马上显示
}

/***********************************************
Function :void dispOFF(UINT8 com,UINT8 SEG)
Discription:关闭某段显示
Parameter: com COM值
		   SEG SEG值
************************************************/
void dispOFF(uint8_t com, uint8_t SEG)
{
	LCD_BUF[SEG] &= ~(1 << com);
	//W1623_byte(SEG, LCD_BUF[SEG]);    //去掉注释后，写完就马上显示
}

/***********************************************
Function :void cleandisp(void)
Discription:清屏
Parameter: 空
************************************************/
void cleandisp(void)
{
	uint8_t i;
	CS_Low;     //清屏幕
	HT1623_SendBit_H(0xa0, 3);  //写入标志码"101"
	HT1623_SendBit_H(0, 7); //写入 7 位 addr，可能是写入 6 位 addr
	for (i = 0; i < 48; i++) //连续写入数据
	{
		HT1623_SendBit_L(0, 4);
		HT1623_SendBit_L(0, 4);
	}
	CS_High;
	for (i = 0; i < 48; i++)
	{
		LCD_BUF[i] = 0x00;    //清空显存
	}
}




/***********************************************
Function :void disp_All(void)
Discription:全显
Parameter: 空
************************************************/
void disp_All(void)
{
	uint8_t i;
	CS_Low;     //全显示屏幕
	HT1623_SendBit_H(0xa0, 3);  //写入标志码"101"
	HT1623_SendBit_H(0, 7); //写入 7 位 addr，可能是6位
	for (i = 0; i < 48; i++) //连续写入数据
	{
		HT1623_SendBit_L(0xff, 4);
		HT1623_SendBit_L(0xff, 4);
	}
	CS_High;
	for (i = 0; i < 48; i++)
	{
		LCD_BUF[i] = 0xff;    //填充显存
	}
}

/***********************************************
Function :void LCD_Init(void)
Discription:LCD初始化
Parameter: 空
************************************************/
void LCD_Init(void)
{
	//Set_Backlight_Brightness(900);
	GPIO_SetBits(GPIOB, GPIO_Pin_3); // 开背光
	SendCmd(SYS_EN);  //打开系统振荡器
	//SendCmd(RC_32K );
	SendCmd(LCD_ON);  //打开LCD偏压发生器
	//SendCmd(LCD_NORMAL  );
}

/***********************************************
Function :void LCD_DISP(void)
Discription:显示刷新
Parameter: 空
************************************************/
void LCD_DISP(void)
{
	disp_renew();
}

/***********************************************
Function :void LCD_CLOSE(void)
Discription:关闭LCD
Parameter: 空
************************************************/
void LCD_CLOSE(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_3); // 关背光
	SendCmd(SYS_DIS);  //关闭系统振荡器
	SendCmd(LCD_OFF);  //关闭LCD偏压发生器
}

/***********************************************
Function :void lcd_clear1(void)
Discription:清显示缓冲区1
Parameter: 空
************************************************/
void lcd_clear1(void)
{
	uint8_t i;
	for (i = 0; i < 40; i++)
		LCD_BUF[i] = 0;
	LCD_BUF[40] = 0;
	LCD_BUF[41] &= 0x7f;
}

/***********************************************
Function :void lcd_clear2(void)
Discription:清显示缓冲区2
Parameter: 空
************************************************/
void lcd_clear2(void)
{
	uint8_t i;
	for (i = 0; i < 40; i++)
		LCD_BUF[i] = 0;
	LCD_BUF[40] = 0;
	LCD_BUF[41] &= 0x7f;
}


void  One_Backlight(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//打开时钟
	GPIO_InitStruct.GPIO_Mode 	=  GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
}













