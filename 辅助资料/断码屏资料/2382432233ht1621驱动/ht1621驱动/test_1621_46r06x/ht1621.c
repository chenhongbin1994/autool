#include "common.h"
#include "ht1621.h"


#define		dat		_pc3
#define		wr		_pc5
#define		cs		_pc4


void SendBit_1621(uchar data,uchar cnt)		//data�ĸ�cntλд��HT1621����λ��ǰ
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

void SendDataBit_1621(uchar data,uchar cnt)	//data�ĵ�cntλд��HT1621����λ��ǰ
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
	SendBit_1621(0x80,4);			//д���־��"100"��9λcommand�������
	SendBit_1621(command,8); 		//û��ʹ�е�����ʱ����������Ϊ�˱�̷���
	cs=1;					//ֱ�ӽ�command�����λд"0"
}

void Write_1621(uchar addr,uchar data)
{
	addr <<= 2;

	cs=0;
	SendBit_1621(0xa0,3);			//д���־��"101"
	SendBit_1621(addr,6);			//д��addr�ĸ�6λ
	SendDataBit_1621(data,4);		//д��data�ĵ�4λ
	cs=1;
}

void WriteAll_1621(uchar addr,uchar *p,uchar cnt)  //����д��cnt������
{
	uchar i;
	addr <<= 2;
	
	cs=0;
	SendBit_1621(0xa0,3);			//д���־��"101"
	SendBit_1621(addr,6);			//д��addr�ĸ�6λ
	for(i =0; i <cnt; i ++,p++)		//����д������
	{
		SendDataBit_1621(*p,8);
	}
	cs=1;
}

void init_1621(void)
{
	uchar seg;
	
	SendCmd(BIAS);	//����ƫѹ��ռ�ձ�
	SendCmd(SYSEN);	//��ϵͳ����
	SendCmd(LCDON);	//��LCDƫѹ������

  	for(seg =0; seg <32; seg++)	//����
	{
		Write_1621(seg,0x00);
	} 
}

void clr_1621(void)
{
	uchar seg;
	for(seg =0; seg <32; seg++)	//����
	{
		Write_1621(seg,0x55);
	}
}