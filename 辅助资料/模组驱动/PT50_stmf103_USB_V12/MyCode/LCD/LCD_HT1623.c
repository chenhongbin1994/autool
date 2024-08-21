/*
 * @Author: hong 944278386@qq.com
 * @Date: 2024-05-15 11:54:58
 * @LastEditors: ChenHongBin 944278386@qq.com
 * @LastEditTime: 2024-06-11 18:18:11
 * @FilePath: \USERc:\Users\IBM\Desktop\�ĸ�ƽ���Ǳ�\ģ������\STM32F103coding - V3\MyCode\LCD\HT61666_LCD.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "LCD_HT1623.h"
#include "delay.h"
#include "timer.h"

#define TIM_Delay  4  //��λ΢��
volatile u8 LCD_BUF[48];
/* ����ܽ�������Ҫ����ʵ����������޸ĵĸ��¹ܽź�д������ */
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

#define		LCD_NORMAL	0xE3 	//LCD����ģʽ����
#define		LCD_OFF		0x02	//�ر�LCD��ʾ
#define		LCD_ON		0x03	//��LCD��ʾ
#define		SYS_EN		0x01	//��ϵͳʱ��
#define       SYS_DIS         0x00    //�ر�������LCD����
#define		RC_32K		0x18	//Ƭ��RCʱ��ʹ��

/***********************************************
Function :LCD_GpioInit
Discription:LCD�ܽų�ʼ��
Parameter: ��
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









//ͨ�ŷ�ʽ���Ǵ���ͨ�ţ�������ģ��IIC��ͨѶ��ʽд�����ݣ�HT1623ָ�����ø����Լ���������޸�*/


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
		delay_us(2);
		//delay_us(TIM_Delay);
		WR_High;
		data <<= 1;
		delay_us(TIM_Delay);
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
		delay_us(2);
		//delay_us(TIM_Delay);
		WR_High;
		data >>= 1;
		delay_us(TIM_Delay);
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


//д����ֽ�
void Write_1623HalfByte(u8 SEG,u8 dat)
{
    CS_Low;
    HT1623_SendBit_H(0xa0,3);  //д���־��"101"
    HT1623_SendBit_H(SEG<<2,7); //д�� 7 λ addr
    HT1623_SendBit_L(dat,4);
	
    CS_High;
}
/***********************************************
Function :void W1623_byte(UINT8 SEG,UINT8 dat)
Discription:дSEG�������е�λ��SEG(0~48)
Parameter: SEG Ҫд��ĵ�ַ
		   dat Ҫд�������
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
Discription:����д��Ԫ SEG(0~48)
Parameter: SEG Ҫд�����ʼ��ַ
		   cnt Ҫд�������
		   *p Ҫд�������ָ��
************************************************/
void W1623_success(uint8_t SEG, uint8_t cnt, volatile uint8_t *p)//HT1623_Disp_SomeRam
{
	uint8_t i, addr;
	addr = SEG;
	CS_Low;
	HT1623_SendBit_H(0xa0, 3);  //д���־��"101"
	HT1623_SendBit_H(addr << 2, 7); //д�� 7 λ addr
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

    // ������������Ϊ����ģʽ
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LCD_B_Data_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);
		delay_us(TIM_Delay); // ȷ��ʱ���ȶ�
    for (i = 0; i < 8; i++)
    {
        sdata >>= 1;
        HT1623_Read_Bit();
        if (GPIO_ReadInputDataBit(LCD_B_Port, LCD_B_Data_PIN))
            sdata |= 0x80;
    }
    // �ָ���������Ϊ���ģʽ
    GPIO_InitStructure.GPIO_Pin = LCD_B_Data_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);

    return sdata;
}
// ��ȡLCD��ַaddress������
unsigned char HT1623_ReadByte(u8 address)
{
    unsigned char data;

    CS_Low;
    HT1623_SendBit_H(0xC0, 3);  // ���Ͷ�ȡ�����־��"110"
    HT1623_SendBit_H(address << 2, 7); // ����7λ��ַ
    delay_us(TIM_Delay); // ȷ��ʱ���ȶ�
    data = HT1623_ReadData_Lcd();
    CS_High;

    return data;
}

/**
 * @brief �� LCD ��ȡ���ݣ������޸Ĳ�д��
 * @param addr  Ҫ��ȡ���޸ĵĵ�ַ
 * @param value Ҫ�޸ĵ�ֵ
 * @param opr   �������ͣ�1 ��ʾ�������0 ��ʾ��������
 */
void HT1623_ReadData_From_Lcd(u8 addr, u8 value, u8 opr)
{
    volatile u8 byte;
    u32 p;
    u8 point;

    CS_Low;

    // �����ַ��
    point = addr;
    addr += point;

    // ���Ͷ�-�޸�-д����
    HT1623_SendBit_H(0xA0, 3); // ������ "101"
    HT1623_SendBit_H(addr << 2, 7); // 7 λ��ַ

    // �ȴ�Ƭ��ȷ��ʱ��
    delay_us(TIM_Delay); 

    // �� HT1623 ��ȡ����
    byte = HT1623_ReadData_Lcd();

    // ���ݲ��������޸�����
    p = byte;
    if (opr)
        p |= value;
    else
        p ^= value;

    // ���޸ĺ������д�� HT1623
    HT1623_SendBit_L(p, 8);

    delay_us(TIM_Delay); // ȷ��ʱ���ȶ�

    // ����Ƭѡ�ź�
		CS_High;

}



/*-------------------------------------------------------------*/
/***********************************************
Function :void disp_renew(void)
Discription:��ʾ����,����8x32��ȫ��ˢ��
Parameter: ��
************************************************/
void disp_renew(void)
{
	W1623_success(0, 48, LCD_BUF);
}

/***********************************************
Function :void dispON(UINT8 com,UINT8 SEG)
Discription:��ĳ����ʾ
Parameter: com COMֵ
		   SEG SEGֵ
************************************************/
void dispON(uint8_t com, uint8_t SEG)
{
	LCD_BUF[SEG] |= (1 << com);
	W1623_byte(SEG, LCD_BUF[SEG]);     //ȥ��ע�ͺ�д���������ʾ
}

/***********************************************
Function :void dispOFF(UINT8 com,UINT8 SEG)
Discription:�ر�ĳ����ʾ
Parameter: com COMֵ
		   SEG SEGֵ
************************************************/
void dispOFF(uint8_t com, uint8_t SEG)
{
	LCD_BUF[SEG] &= ~(1 << com);
	//W1623_byte(SEG, LCD_BUF[SEG]);    //ȥ��ע�ͺ�д���������ʾ
}

/***********************************************
Function :void cleandisp(void)
Discription:����
Parameter: ��
************************************************/
void cleandisp(void)
{
	uint8_t i;
	CS_Low;     //����Ļ
	HT1623_SendBit_H(0xa0, 3);  //д���־��"101"
	HT1623_SendBit_H(0, 7); //д�� 7 λ addr��������д�� 6 λ addr
	for (i = 0; i < 48; i++) //����д������
	{
		HT1623_SendBit_L(0, 4);
		HT1623_SendBit_L(0, 4);
	}
	CS_High;
	for (i = 0; i < 48; i++)
	{
		LCD_BUF[i] = 0x00;    //����Դ�
	}
}




/***********************************************
Function :void disp_All(void)
Discription:ȫ��
Parameter: ��
************************************************/
void disp_All(void)
{
	uint8_t i;
	CS_Low;     //ȫ��ʾ��Ļ
	HT1623_SendBit_H(0xa0, 3);  //д���־��"101"
	HT1623_SendBit_H(0, 7); //д�� 7 λ addr��������6λ
	for (i = 0; i < 48; i++) //����д������
	{
		HT1623_SendBit_L(0xff, 4);
		HT1623_SendBit_L(0xff, 4);
	}
	CS_High;
	for (i = 0; i < 48; i++)
	{
		LCD_BUF[i] = 0xff;    //����Դ�
	}
}

/***********************************************
Function :void LCD_Init(void)
Discription:LCD��ʼ��
Parameter: ��
************************************************/
void LCD_Init(void)
{
	//Set_Backlight_Brightness(900);
	GPIO_SetBits(GPIOB, GPIO_Pin_3); // ������
	SendCmd(SYS_EN);  //��ϵͳ����
	//SendCmd(RC_32K );
	SendCmd(LCD_ON);  //��LCDƫѹ������
	//SendCmd(LCD_NORMAL  );
}

/***********************************************
Function :void LCD_DISP(void)
Discription:��ʾˢ��
Parameter: ��
************************************************/
void LCD_DISP(void)
{
	disp_renew();
}

/***********************************************
Function :void LCD_CLOSE(void)
Discription:�ر�LCD
Parameter: ��
************************************************/
void LCD_CLOSE(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_3); // �ر���
	SendCmd(SYS_DIS);  //�ر�ϵͳ����
	SendCmd(LCD_OFF);  //�ر�LCDƫѹ������
}

/***********************************************
Function :void lcd_clear1(void)
Discription:����ʾ������1
Parameter: ��
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
Discription:����ʾ������2
Parameter: ��
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//��ʱ��
	GPIO_InitStruct.GPIO_Mode 	=  GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
}













