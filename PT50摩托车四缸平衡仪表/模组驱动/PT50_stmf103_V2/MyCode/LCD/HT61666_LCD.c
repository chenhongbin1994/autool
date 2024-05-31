/*
 * @Author: hong 944278386@qq.com
 * @Date: 2024-05-15 11:54:58
 * @LastEditors: hong 944278386@qq.com
 * @LastEditTime: 2024-05-17 14:56:19
 * @FilePath: \USERc:\Users\IBM\Desktop\�ĸ�ƽ���Ǳ�\ģ������\STM32F103coding - V3\MyCode\LCD\HT61666_LCD.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "HT61666_LCD.h"


/* ����ܽ�������Ҫ����ʵ����������޸ĵĸ��¹ܽź�д������ */
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

#define		LCD_NORMAL	0xE3 	//LCD����ģʽ����
#define		LCD_OFF		0x02	//�ر�LCD��ʾ
#define		LCD_ON		0x03	//��LCD��ʾ
#define		SYS_EN		0x01	//��ϵͳʱ��
#define		RC_32K		0x18	//Ƭ��RCʱ��ʹ��

static uint8_t CS0_Src[32] = {0}; //Դ���� LCD��ʾ���ݶ�Ӧ32λ��������λ

/* �豸��� 	��Ӧ����ͼ�����ֵ			    0    1    2    3    4    5    6    7    8    9    ��    -   F */
static const uint8_t CS0_DevId_Num[13] = {0xEF,0x25,0xBB,0xB7,0x75,0xD7,0xDF,0xAD,0xFF,0xF7,0x80,0x11,0x59};

/***********************************************
Function :LCD_GpioInit
Discription:LCD�ܽų�ʼ��
Parameter: ��
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


/*ͨ�ŷ�ʽ���Ǵ���ͨ�ţ�������ģ��IIC��ͨѶ��ʽд�����ݣ�HT1623ָ�����ø����Լ���������޸�*/
/***********************************************
Function :LCD_Delay
Discription:��ʱ
Parameter: ��
************************************************/
void LCD_Delay( )
{
	uint8_t i = 0;

	for( i = 0; i < 5; i++ );
}

/***********************************************
Function :void HT1623_SendBit_H(u8 data,u8 bit)
Discription:��bitλд��HT1623
Parameter: data Ҫд������� 
 		   bitҪд���λ��
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
Discription:��bitλд��HT1623
Parameter: data Ҫд������� 
		   bitҪд���λ��
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
Discription:��������
Parameter: command ����
************************************************/
void SendCmd( u8 command )
{
	CS_Low;
	HT1623_SendBit_H( 0x80,3 );        //д���־��"100"
	HT1623_SendBit_H( command,9 );     //д��9 λ����,����ǰ8 λΪcommand ����,���1 λ����
	CS_High;
}

/***********************************************
Function :void Write_1623Byte(u8 SEG,u8 dat)
Discription:д��HT1623����
Parameter: SEG Ҫд��ĵ�ַ  
		   datҪд�������
************************************************/
void  Write_1623Byte( u8 SEG,u8 dat )
{
	u8 addr;
	addr = SEG;                     
	CS_Low;
	HT1623_SendBit_H( 0xa0,3 );        //д���־��"101" 
	HT1623_SendBit_H( addr<<2,6 );     //д��7 λaddr    32

	/* ���������λд���Ƿ�������4COM��Ļʹ��ʱ��д����,��Ȼ��Ҳ���Ը�дΪ8λд�� */
	HT1623_SendBit_L( dat<<1,8 );      //д��data �ĵ�4 λ
	HT1623_SendBit_H( dat,8 );		   //д��data �ĸ�4 λ

	CS_High;
}

/***********************************************
Function :void HT1623_INIT(void)
Discription:HT1623��ʼ��
Parameter:
************************************************/
void HT1623_INIT( void )
{
	/* ��������Ҫ�����Լ���������ӻ�������� ���DataSheet */
	SendCmd( SYS_EN );        //��ϵͳʱ��
	SendCmd( RC_32K );        //Ƭ��RCʱ��
	SendCmd( LCD_ON );        //ʹ��LCD��ʾ
	SendCmd( LCD_NORMAL );    //LCD��������
}

/***********************************************
Function :void DisPlay_Init(void)
Discription:��ʾ��ʼ��
Parameter:
************************************************/
void DisPlay_Init( void )
{
	LCD_GpioInit(); //LCD GPIO��ʼ��
	HT1623_INIT();	//HT1623��ʼ��
}

/***********************************************
Function :void LCD_Clear_All(void)
Discription:����
Parameter:
************************************************/
void LCD_Clear_All( void )
{
	u8  i;

	for( i=0; i<32; i++ )
	{
		CS0_Src[i] = 0x00;    //ȫ��
		Write_1623Byte( i,CS0_Src[i] );//д������
	}
}

/***********************************************
Function :void LCD_Display_All(void)
Discription:��ʾ����
Parameter:
************************************************/
void LCD_Display_All( void )
{
	u8  i;

	for( i=0; i<32; i++ )
	{
		CS0_Src[i] = 0xFF;    //ȫ��
		Write_1623Byte( i,CS0_Src[i] );//д������
	}
}




/*----------------------------��������������----------------------------*/
/***********************************************
Function :uint8_t LCD_DeviceID(uint8_t *pData)
Discription: �豸����,���ݳ�����λ
Parameter: pData ��λ�豸����
************************************************/
uint8_t LCD_DeviceID( uint8_t *pData )
{
	uint8_t addr = 0,i = 0;

	while( i < 6 )
	{
		if( pData[i] < '0' | pData[i] > '9' )
			return 1;//ԭ����

		i++;
	}

	for( i = 0; i < 6; i++ )
	{
		CS0_Src[i] = CS0_DevId_Num[( pData[i]-0x30 )]; //0~5 ��λ�豸����
		Write_1623Byte( i,CS0_Src[i] );
	}

	return 0;
}

/***********************************************
Function :void DisPlay_Task(void)
Discription: ��Ļ��ʾ��������ʹ�õ���RTOSд������
Parameter: 
************************************************/
void DisPlay_Task( void *pvParameters )
{
	static u8 Dvice_Init_Flag = 0; 
	uint8_t id[6] = "123456";

	if( Dvice_Init_Flag == 0 )
	{
		Dvice_Init_Flag = 1;

		/* ��ʼ������ */
		DisPlay_Init();

		/* ���� */
		LCD_Clear_All();

		/* ȫ����ʾ */
		LCD_Display_All();

		/* ���� */
		LCD_Clear_All();
	}
	
	while(1)
	{
		/* �豸ID */
		LCD_DeviceID( id );
		delay_ms(200);
		//vTaskDelay( 200 );
	}
}












