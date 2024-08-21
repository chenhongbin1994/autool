#include "lcd.h"


static void nop(void)//
{
  u8 i;
  for(i=0;i<90;i++)
	;
}
//��1625�����������ַ��д��3λID�����A6A5A4A3A2A1A0��λ��ַ
static void SendBit_1625(u8 mdata,u8 cnt)   //mdata�ĸ�cntλд��HT1625����λ��ǰ
{
  u8 i;
  for(i=0;i<cnt;i++)
  { 
	LWR_L;
    if((mdata&0x80)==0)
      LDA_L;
    else
      LDA_H;	
	nop();
    LWR_H;
    nop();	
    mdata<<=1;
  }
}

//��1625�������ݣ�д��D0D1D2D3..cntλ���ݵ�RAM
static void SendDataBit_1625(u8 mdata,u8 cnt)   //mdata�ĵ�cntλд��HT1625����λ��ǰ
{
  u8 i;
  for(i=0;i<cnt;i++)
  {	
	LWR_L;
     if((mdata&0x01)==0x00)
       LDA_L;
     else
       LDA_H; 	 
     nop();
     LWR_H;
	 nop();
     mdata>>=1;
  }
}

//��һ����ַ
u8 Read_1625(u8 addr,u8 cnt)
{
  u8 rd=0x00,i=0;
  LCS_L;
  SendBit_1625(0xc0,3);			//��������110��������ģʽ
//  SendBit_1625(addr<<1,7);
//  //��������ݷ���RD�ĵ���λ
//  for(i=0;i<cnt;i++)
//  {
//    if(LDA)
//       rd|=0x08;
//    else
//       rd&=0xf7;
//     LRD_L;
//     nop();//
//     LRD_H;
//    nop();//
//     rd = rd>>1;		//rd>>1;
//  } 
//  if(LDA)
//     rd|=0x08;
//  else
//     rd&=0xf7;
//  LCS=1;
  return rd;
}

//��1625�������������
void SendCmd(u8 command)
{
  LCS_L;
  SendBit_1625(0x80,3);			//��������100����������ģʽ
  SendBit_1625(command,9);		//jjk��� ������������9   ������command���͸�1625
  LCS_H;
}

//LCD��ʼ������HT1625д������
void LCD_init(void)
{  
	//LCD�˿ڳ�ʼ������������������ݷ���
	  LCS_H;LWR_H;LDA_H;LRD_H;nop();	  
	  SendCmd(0x01);		//����2��0x01����ϵͳ����SYS_EN
	  SendCmd(0x03);		//����3��0x03����LCD��ʾ	LCD_ON  
	  SendCmd(0x18);		//����1��0x18��ʹ��Ƭ��RC����RC_32K
}  

//дһ����ַ
void Write_1625(u8 addr,u8 mdata)
{  
  LCS_L;
  SendBit_1625(0xa0,3);			//����дģʽ
  SendBit_1625(addr,7);			//д��A6A5A4A3A2A1A0��λ��ַ
  SendDataBit_1625(mdata,4);	//д��D0D1D2D3���ݵ�RAM
  LCS_H;
}

//��һ��ַ������д��
void WriteAll_1625(u8 addr,u8 *p,u8 cnt)		//��ʼ��ַ������ָ�룬�����ֽ���
{
  u8 i;
  LCS_L;
  SendBit_1625(0xa0,3);		//����дģʽ
  SendBit_1625(addr,7);		//д��A6A5A4A3A2A1A0��λ��ַ
  for(i=0;i<cnt;i++,p++)	//����д��cnt���ֽ�����
  {
    SendDataBit_1625(*p,8);
  }
  LCS_H;
}

//����&ȫ����ʾ
void full_or_clear (u8 F_C)	//1��ȫ�ԣ�0������
{
  u8 i,p;
  if(F_C)
    p=0xff;
  else
    p=0x00;
  LCS_L;
  SendBit_1625(0xa0,3);		//����дģʽ
  SendBit_1625(0x00,7);		//��ַ0000H
  for(i=0;i<64;i++)
  {
    SendDataBit_1625(p,8);	//��ȫ�Ի���������д��1625
  }
  LCS_H;
}



