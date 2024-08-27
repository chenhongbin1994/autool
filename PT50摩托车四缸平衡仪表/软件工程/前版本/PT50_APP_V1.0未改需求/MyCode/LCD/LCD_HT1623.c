/*
 * @Author: hong 944278386@qq.com
 * @Date: 2024-05-15 11:54:58
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-13 16:11:24
 * @FilePath: \USERc:\Users\IBM\Desktop\�ĸ�ƽ���Ǳ�\ģ������\STM32F103coding - V3\MyCode\LCD\HT61666_LCD.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "LCD_HT1623.h"
#include "delay.h"
#include "timer.h"
#include "key_handler.h"

#define TIM_Delay  4  //��λ΢��4
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
#define		LCD_OFF			0x02	//�ر�LCD��ʾ
#define		LCD_ON			0x03	//��LCD��ʾ
#define		SYS_EN			0x01	//��ϵͳʱ��
#define   SYS_DIS     0x00    //�ر�������LCD����
#define		RC_32K			0x18	//Ƭ��RCʱ��ʹ��

/***********************************************
Function :LCD_GpioInit
Discription:LCD�ܽų�ʼ��
Parameter: ��
************************************************/
void LCD_GpioInit( void )
{
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE );	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LCD_B_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( LCD_B_Port, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = LCD_B_CS_PIN|LCD_B_WR_PIN|LCD_B_RD_PIN|LCD_B_Data_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( LCD_B_Port, &GPIO_InitStructure );

	 GPIO_ResetBits( LCD_B_Port, LCD_B_LED_PIN);
	 GPIO_SetBits( LCD_B_Port, LCD_B_CS_PIN|LCD_B_WR_PIN|LCD_B_RD_PIN|LCD_B_Data_PIN );
}









//ͨ�ŷ�ʽ���Ǵ���ͨ�ţ�������ģ��SPI��ͨѶ��ʽд�����ݣ�HT1623ָ�����ø����Լ���������޸�*/


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
Function :void Write_1623HalfByte(u8 SEG,u8 dat)
Discription:д��SEG����ǰ4λ
Parameter: SEG Ҫд��ĵ�ַ  
		   datҪд�������
************************************************/


//д����ֽ��ϰ벿��
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
Discription:��д��SEG����ǰ4λ��SEG+1д4��λ
Parameter: SEG Ҫд��ĵ�ַ
		   dat Ҫд�������
************************************************/
void W1623_byte(uint8_t SEG, uint8_t dat)
{
	uint8_t i, addr;
	addr = SEG ;
	for (i = 0; i < 2; i++)
	{
		Write_1623HalfByte(addr, dat);
		addr += 1;
		dat >>= 4;
	}
}
void W1623_RPMbyte(uint8_t SEG, uint8_t dat)//ת�������4,5��
{
	uint8_t i, addr;
	addr = SEG ;
	for (i = 0; i < 2; i++)
	{
		Write_1623HalfByte(addr, dat);
		addr -= 1;
		dat >>= 4;
	}
}


void W1623_byteMyriabit(uint8_t SEG, uint8_t dat)//����2��SEGд����λ�����ƶ��Ÿ�(��λ�������
{
	uint8_t i, addr;
	addr = SEG ;
	for (i = 0; i < 2; i++)
	{
		Write_1623HalfByte(addr, dat);
		addr -= 29;
		dat >>= 4;
	}
}


/***********************************************
ֻд�°��ֽ�,1�Ÿ׺�3�Ÿ���Ҫ
************************************************/
//д����ֽ��°벿��
void Write_1623LowerHalfByte(u8 SEG,u8 dat)
{
    CS_Low;
    HT1623_SendBit_H(0xa0,3);  //д���־��"101"
    HT1623_SendBit_H(SEG<<2,7); //д�� 7 λ addr
    HT1623_SendBit_L(dat<<4,8);
	
    CS_High;
}
void W1623_Lowerbyte(uint8_t SEG, uint8_t dat)//����2��SEGд����λ������һ�Ÿ׺Ͷ��Ÿ������
{
	uint8_t i, addr;
	addr = SEG ;
	for (i = 0; i < 2; i++)
	{
		Write_1623LowerHalfByte(addr, dat);
		addr += 1;
		dat >>= 4;
	}
}

void W1623_LowerbyteMyriabit(uint8_t SEG, uint8_t dat)//����2��SEGд����λ������һ�Ÿ�(��λ�������
{
	uint8_t i, addr;
	addr = SEG ;
	for (i = 0; i < 2; i++)
	{
		Write_1623LowerHalfByte(addr, dat);
		addr -= 29;
		dat >>= 4;
	}
}

void W1623_TIMELowerbyte(uint8_t SEG, uint8_t dat)//����MINMAX�����
{
	uint8_t i, addr;
	addr = SEG ;
	for (i = 0; i < 2; i++)
	{
		Write_1623LowerHalfByte(addr, dat);
		addr -= 1;
		dat >>= 4;
	}
}


/***********************************************
Function :void W1623_bothSeg_byte(uint8_t SEG, uint8_t dat)
Discription:дSEG�������е�λ��SEG(0~48)
Parameter: SEG Ҫд��ĵ�ַ
		   dat Ҫд�������
************************************************/
void W1623_bothSeg_byte(uint8_t SEG, uint8_t dat)
{
	 CS_Low;
    HT1623_SendBit_H(0xa0,3);  //д���־��"101"
    HT1623_SendBit_H(SEG<<2,7); //д�� 7 λ addr
    HT1623_SendBit_L(dat,8);	
    CS_High;
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
		//addr += 1;
		p++;
	}
	CS_High;
}

/*------------------------------���޸�д------------------------------*/
void HT1623_Read_Bit(void)
{
    RD_Low;
    delay_us(TIM_Delay);
    RD_High;
    delay_us(TIM_Delay);
}

unsigned char HT1623_ReadData_Lcd(void)
{
	
    unsigned char  i, sdata = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LCD_B_Data_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�Ƿ�ѡ����
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);
    // ������������Ϊ����ģʽ
    
	delay_us(TIM_Delay); // ȷ��ʱ���ȶ�
    for (i = 0; i < 8; i++)
    {
        sdata >>= 1;
        HT1623_Read_Bit();
        if (GPIO_ReadInputDataBit(LCD_B_Port, LCD_B_Data_PIN))
            sdata |= 0x80;
    }
		//sdata >>= 4;
    // �ָ���������Ϊ���ģʽ
     
    GPIO_InitStructure.GPIO_Pin = LCD_B_Data_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�������л�Ĭ��ģ������,���ܻᵼ�������������㣬���ŵ�ƽ�޷��ﵽԤ�ڵĸ�/�͵�ƽ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);
#ifdef HT1623_PIN_LEVEL
    GPIO_ResetBits(LCD_B_Port, LCD_B_Data_PIN);
#else    
    GPIO_SetBits(LCD_B_Port, LCD_B_Data_PIN);
#endif
    return ((unsigned char)sdata);
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
/*-------------------------------------4bit------------------------------------*/

/**
 * @brief �� LCD ��ȡ���ݣ������޸Ĳ�д��
 * @param addr  Ҫ��ȡ���޸ĵĵ�ַ
 * @param mask Ҫ�޸ĵ�ֵ
 * @param opr   �������ͣ�1 ��ʾ�������0 ��ʾ�������
 */
void UpdateReadModifyWriteDisplay(uint8_t address, uint8_t mask, uint8_t opr) {
	
		uint8_t ram_temp;
		
    ram_temp = HT1623_ReadByte(address);
		  // ���ݲ��������޸�����
#if 0
    if (opr)
        ram_temp |= mask;// �����ض�λ
    else
        ram_temp ^= mask;// �����ض�λ,��ͬram_temp &=  ~mask;
#endif
#if 1
    if (opr)
        ram_temp |=  mask;// �����ض�λ
    else
        ram_temp &=  ~mask;// �����ض�λ
#endif 
    W1623_bothSeg_byte(address, ram_temp); // ���޸ĺ��ֵд��
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
Parameter: com+1 COMֵ(+1��
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
extern Settings current_settings;
void LCD_Init(void)
{	
	
	LCD_GpioInit(  );		
	SendCmd(SYS_EN);  //��ϵͳ����
	//SendCmd(RC_32K );
	SendCmd(LCD_ON);  //��LCDƫѹ������
	//SendCmd(LCD_NORMAL  );
	cleandisp();//������һЩ���ܿ��ܲ�������������Ŀǰ�ǵ�����
	GPIO_SetBits(LCD_B_Port, LCD_B_LED_PIN);UpdateReadModifyWriteDisplay(15,Screen_Data_LED,1); // �������Լ�ͼ��
	if(current_settings.buzzer_enabled == 1)
		UpdateReadModifyWriteDisplay(15,Screen_Data_BUZZER,1);//����������ͼ��
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









