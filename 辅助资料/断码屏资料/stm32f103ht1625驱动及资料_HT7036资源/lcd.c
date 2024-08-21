#include "lcd.h"


static void nop(void)//
{
  u8 i;
  for(i=0;i<90;i++)
	;
}
//给1625发送命令与地址，写入3位ID命令或A6A5A4A3A2A1A0七位地址
static void SendBit_1625(u8 mdata,u8 cnt)   //mdata的高cnt位写入HT1625，高位在前
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

//给1625发送数据，写入D0D1D2D3..cnt位数据到RAM
static void SendDataBit_1625(u8 mdata,u8 cnt)   //mdata的低cnt位写入HT1625，低位在前
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

//读一个地址
u8 Read_1625(u8 addr,u8 cnt)
{
  u8 rd=0x00,i=0;
  LCS_L;
  SendBit_1625(0xc0,3);			//控制命令110，启动读模式
//  SendBit_1625(addr<<1,7);
//  //读入的数据放在RD的低四位
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

//给1625发送命令控制字
void SendCmd(u8 command)
{
  LCS_L;
  SendBit_1625(0x80,3);			//控制命令100，启动命令模式
  SendBit_1625(command,9);		//jjk命令处 数据数必须是9   将命令command发送给1625
  LCS_H;
}

//LCD初始化，向HT1625写入命令
void LCD_init(void)
{  
	//LCD端口初始化，定义控制引脚数据方向
	  LCS_H;LWR_H;LDA_H;LRD_H;nop();	  
	  SendCmd(0x01);		//命令2：0x01，打开系统晶振SYS_EN
	  SendCmd(0x03);		//命令3：0x03，开LCD显示	LCD_ON  
	  SendCmd(0x18);		//命令1：0x18，使用片上RC振荡器RC_32K
}  

//写一个地址
void Write_1625(u8 addr,u8 mdata)
{  
  LCS_L;
  SendBit_1625(0xa0,3);			//启动写模式
  SendBit_1625(addr,7);			//写入A6A5A4A3A2A1A0七位地址
  SendDataBit_1625(mdata,4);	//写入D0D1D2D3数据到RAM
  LCS_H;
}

//从一地址处连续写入
void WriteAll_1625(u8 addr,u8 *p,u8 cnt)		//起始地址，数组指针，数据字节数
{
  u8 i;
  LCS_L;
  SendBit_1625(0xa0,3);		//启动写模式
  SendBit_1625(addr,7);		//写入A6A5A4A3A2A1A0七位地址
  for(i=0;i<cnt;i++,p++)	//依次写入cnt个字节数据
  {
    SendDataBit_1625(*p,8);
  }
  LCS_H;
}

//清屏&全屏显示
void full_or_clear (u8 F_C)	//1：全显，0：清屏
{
  u8 i,p;
  if(F_C)
    p=0xff;
  else
    p=0x00;
  LCS_L;
  SendBit_1625(0xa0,3);		//启动写模式
  SendBit_1625(0x00,7);		//地址0000H
  for(i=0;i<64;i++)
  {
    SendDataBit_1625(p,8);	//将全显或清屏数据写入1625
  }
  LCS_H;
}



