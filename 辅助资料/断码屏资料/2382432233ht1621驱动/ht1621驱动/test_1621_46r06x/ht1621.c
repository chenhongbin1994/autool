#include "common.h"
#include "ht1621.h"


#define		dat		_pc3
#define		wr		_pc5
#define		cs		_pc4


void SendBit_1621(uchar data,uchar cnt)		//data的高cnt位写入HT1621，高位在前
{
	uchar i;
	for(i =0; i <cnt; i ++)
	{
		if((data&0x80)==0) dat=0;
		else dat=1;
		wr=0;
		_nop();
		_nop();
		wr=1;
		data<<=1;
	}
}

void SendDataBit_1621(uchar data,uchar cnt)	//data的低cnt位写入HT1621，低位在前
{
	uchar i;
	for(i =0; i <cnt; i ++)
	{
		if((data&0x01)==0) dat=0;
		else dat=1;
		wr=0;
		_nop();
		_nop();
		wr=1;
		data>>=1;
	}
} 

void SendCmd(uchar command)
{
	cs=0;
	SendBit_1621(0x80,4);			//写入标志码"100"和9位command命令，由于
	SendBit_1621(command,8); 		//没有使有到更改时钟输出等命令，为了编程方便
	cs=1;					//直接将command的最高位写"0"
}

void Write_1621(uchar addr,uchar data)
{
	addr <<= 2;

	cs=0;
	SendBit_1621(0xa0,3);			//写入标志码"101"
	SendBit_1621(addr,6);			//写入addr的高6位
	SendDataBit_1621(data,4);		//写入data的低4位
	cs=1;
}

void WriteAll_1621(uchar addr,uchar *p,uchar cnt)  //连续写入cnt个数据
{
	uchar i;
	addr <<= 2;
	
	cs=0;
	SendBit_1621(0xa0,3);			//写入标志码"101"
	SendBit_1621(addr,6);			//写入addr的高6位
	for(i =0; i <cnt; i ++,p++)		//连续写入数据
	{
		SendDataBit_1621(*p,8);
	}
	cs=1;
}

void init_1621(void)
{
	uchar seg;
	
	SendCmd(BIAS);	//设置偏压和占空比
	SendCmd(SYSEN);	//打开系统振荡器
	SendCmd(LCDON);	//打开LCD偏压发生器

  	for(seg =0; seg <32; seg++)	//清屏
	{
		Write_1621(seg,0x00);
	} 
}

void clr_1621(void)
{
	uchar seg;
	for(seg =0; seg <32; seg++)	//清屏
	{
		Write_1621(seg,0x55);
	}
}