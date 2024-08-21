#include "HT1623.h"

void HT1623_SendBit(unsigned char data,unsigned char cnt)    
{   
  unsigned char i;   
     
  for(i =0; i <cnt; i ++)   
  {   
		HAL_GPIO_WritePin(GPIO_WR,GPIO_PIN_WR,GPIO_PIN_RESET);  
    if(data&0x80) 
			HAL_GPIO_WritePin(GPIO_DATA,GPIO_PIN_DATA,GPIO_PIN_SET);
		else  
			HAL_GPIO_WritePin(GPIO_DATA,GPIO_PIN_DATA,GPIO_PIN_RESET) ;
		
		HAL_GPIO_WritePin(GPIO_WR,GPIO_PIN_WR,GPIO_PIN_SET);  		   
    data<<=1;   
  }   
}   
void HT1623_SendDataBit(unsigned char data,unsigned char cnt)    
{   
  unsigned char i;   
  for(i =0; i <cnt; i ++)   
  {   
		HAL_GPIO_WritePin(GPIO_WR,GPIO_PIN_WR,GPIO_PIN_RESET);  
    if(data&0x01) 
			HAL_GPIO_WritePin(GPIO_DATA,GPIO_PIN_DATA,GPIO_PIN_SET);
		else  
			HAL_GPIO_WritePin(GPIO_DATA,GPIO_PIN_DATA,GPIO_PIN_RESET) ; 
		HAL_GPIO_WritePin(GPIO_WR,GPIO_PIN_WR,GPIO_PIN_SET);  		   
    data>>=1;   
  }   
}   
void HT1623_SendCmd(unsigned char command)   
{   
	HAL_GPIO_WritePin(GPIO_CS,GPIO_PIN_CS,GPIO_PIN_RESET);
  HT1623_SendBit(0x80,3);     //д??????"100"   
  HT1623_SendBit(command,9);  //д??9 λ????,?????8 λ?command ????,???1 λ????   
	HAL_GPIO_WritePin(GPIO_CS,GPIO_PIN_CS,GPIO_PIN_SET);
}  
void HT1623_Write(unsigned char addr,unsigned char data)   
{   
  HAL_GPIO_WritePin(GPIO_CS,GPIO_PIN_CS,GPIO_PIN_RESET);   
  HT1623_SendBit(0xa0,3);     //3位"101"   
  HT1623_SendBit(addr<<1,7);  //7位7 λaddr   
  HT1623_SendDataBit(data,4); //4位data ???4 λ   
  HAL_GPIO_WritePin(GPIO_CS,GPIO_PIN_CS,GPIO_PIN_SET);  
}   
void HT1623_WriteAll(unsigned char addr, unsigned char *p, unsigned char cnt)   
{   
  unsigned char i;   
     
  HAL_GPIO_WritePin(GPIO_CS,GPIO_PIN_CS,GPIO_PIN_RESET);      
  HT1623_SendBit(0xa0,3);     //д??????"101"   
  HT1623_SendBit(addr<<1,7);  //д??7 λaddr   
  for(i =0; i <cnt; i ++)     //????д??????   
  {   
    HT1623_SendDataBit(*p++,8);   
       
  }   
  HAL_GPIO_WritePin(GPIO_CS,GPIO_PIN_CS,GPIO_PIN_SET);  
}      
void HT1623_Init(void)   
{   
//  HT1623_SendCmd(0xE3); //LCD普通模式
	HT1623_SendCmd(0x29); //LCD偏置1/3 4COMS
//	HT1623_SendCmd(0x18);//使用内部振荡器
//	HT1623_SendCmd(0x00);//关闭系统时钟和 LCD 偏置发生器 
	HT1623_SendCmd(0x01);//打开系统时钟 
//	HT1623_SendCmd(0x02);//关闭 LCD 偏置发生器 
	HT1623_SendCmd(0x03);//打开 LCD 偏置发生器  
   
} 


//封装
void Clear()					//清屏函数
{
   unsigned int  i;
   for(i=2;i<74;i++) 
   HT1623_Write(i,0x00);  
}
void Full()				 	//全显示函数
{
   unsigned int  i;
   for(i=2;i<74;i++) 		
   HT1623_Write(i,0xff);  
} 

void display_nb(unsigned char nb1,unsigned char nb2)//nb1 第几位数字  nb2 数字显示几( nb1 范围1-12  12个位置；nb2范围0-10  10为清空)
{
	unsigned int i=1;
	switch(nb1) 
			  {
					case 1:	i=8;break;
					case 2:	i=12;break;
					case 3:	i=16;break;
					case 4:	i=20;break;
					case 5:	i=24;break;
					case 6:	i=28;break;
					case 7:	i=66;break;
					case 8:	i=62;break;
					case 9:	i=58;break;
					case 10:i=52;break;
					case 11:i=48;break;
					case 12:i=44;break;					
			  }
	if(nb1>=1&&nb1<=6)
	{		
		switch(nb2) 
			  {
			    case 0:	HT1623_Write(i,0x0f);HT1623_Write(i+1,0x0f);HT1623_Write(i+2,0x0a);break;
					case 1:	HT1623_Write(i,0x00);HT1623_Write(i+1,0x00);HT1623_Write(i+2,0x0a);break;
					case 2:	HT1623_Write(i,0x0a);HT1623_Write(i+1,0x0f);HT1623_Write(i+2,0x07);break;
					case 3:	HT1623_Write(i,0x02);HT1623_Write(i+1,0x0f);HT1623_Write(i+2,0x0f);break;
					case 4:	HT1623_Write(i,0x04);HT1623_Write(i+1,0x00);HT1623_Write(i+2,0x0f);break;
					case 5:	HT1623_Write(i,0x07);HT1623_Write(i+1,0x0f);HT1623_Write(i+2,0x0C);break;
					case 6:	HT1623_Write(i,0x0f);HT1623_Write(i+1,0x0f);HT1623_Write(i+2,0x0C);break;
					case 7:	HT1623_Write(i,0x02);HT1623_Write(i+1,0x00);HT1623_Write(i+2,0x0a);break;
					case 8:	HT1623_Write(i,0x0f);HT1623_Write(i+1,0x0f);HT1623_Write(i+2,0x0F);break;
					case 9:	HT1623_Write(i,0x06);HT1623_Write(i+1,0x0f);HT1623_Write(i+2,0x0F);break;	
					case 10:HT1623_Write(i,0x00);HT1623_Write(i+1,0x00);HT1623_Write(i+2,0x00);break;	//写空白					
			  }
	}
	else
	{
		switch(nb2) 
			  {
			    case 0:	HT1623_Write(i,0x0a);HT1623_Write(i+2,0x0f);HT1623_Write(i+3,0x0f);break;
					case 1:	HT1623_Write(i,0x0a);HT1623_Write(i+2,0x00);HT1623_Write(i+3,0x00);break;
					case 2:	HT1623_Write(i,0x0c);HT1623_Write(i+2,0x06);HT1623_Write(i+3,0x0f);break;
					case 3:	HT1623_Write(i,0x0f);HT1623_Write(i+2,0x02);HT1623_Write(i+3,0x0f);break;
					case 4:	HT1623_Write(i,0x0f);HT1623_Write(i+2,0x08);HT1623_Write(i+3,0x00);break;
					case 5:	HT1623_Write(i,0x06);HT1623_Write(i+2,0x0a);HT1623_Write(i+3,0x0f);break;
					case 6:	HT1623_Write(i,0x06);HT1623_Write(i+2,0x0f);HT1623_Write(i+3,0x0f);break;
					case 7:	HT1623_Write(i,0x0a);HT1623_Write(i+2,0x00);HT1623_Write(i+3,0x0f);break;
					case 8:	HT1623_Write(i,0x0f);HT1623_Write(i+2,0x0f);HT1623_Write(i+3,0x0f);break;
					case 9:	HT1623_Write(i,0x0f);HT1623_Write(i+2,0x0a);HT1623_Write(i+3,0x0f);break;
					case 10:HT1623_Write(i,0x00);HT1623_Write(i+2,0x00);HT1623_Write(i+3,0x00);break;//写空白
				}
	}
}
void display_point(unsigned char nb,unsigned char enable)//nb  第几个点    enable 使能（nb  范围0-13 ）
{
	if(enable)
	{
		switch(nb) 
		{
			case 0:	HT1623_Write(31,0xf);break;
			case 1:	HT1623_Write(11,0xf);break;
			case 2:	HT1623_Write(15,0xf);break;
			case 3:	HT1623_Write(19,0xf);break;
			case 4:	HT1623_Write(23,0xf);break;
			case 5:	HT1623_Write(27,0xf);break;
			case 6:	HT1623_Write( 5,0xf);break;
			case 7:	HT1623_Write(67,0xf);break;
			case 8:	HT1623_Write(63,0xf);break;
			case 9:	HT1623_Write(59,0xf);break;
			case 10:HT1623_Write(53,0xf);break;
			case 11:HT1623_Write(49,0xf);break;	
			case 12:HT1623_Write( 3,0xf);break;
			case 13:HT1623_Write(45,0xf);break;					
		}
	}
	else
	{
		switch(nb) 
		{
			case 0:	HT1623_Write(31,0x00);break;
			case 1:	HT1623_Write(11,0x00);break;
			case 2:	HT1623_Write(15,0x00);break;
			case 3:	HT1623_Write(19,0x00);break;
			case 4:	HT1623_Write(23,0x00);break;
			case 5:	HT1623_Write(27,0x00);break;
			case 6:	HT1623_Write( 5,0x00);break;
			case 7:	HT1623_Write(67,0x00);break;
			case 8:	HT1623_Write(63,0x00);break;
			case 9:	HT1623_Write(59,0x00);break;
			case 10:HT1623_Write(53,0x00);break;
			case 11:HT1623_Write(49,0x00);break;	
			case 12:HT1623_Write( 3,0x00);break;
			case 13:HT1623_Write(45,0x00);break;
		}
	}
}
void display_piece(unsigned char nb,unsigned char enable)//nb  第几个块    enable 使能（nb  范围1-89 ）
{
	if(enable)
	{
		switch(nb)
		{
			case 1: HT1623_Write(2,0x8);break;
			case 2: HT1623_Write(2,0x4);break;
			case 3: HT1623_Write(2,0x2);break;
			case 4: HT1623_Write(2,0xc);break;
			case 5: HT1623_Write(2,0xa);break;
			case 6: HT1623_Write(2,0x6);break;
			case 7: HT1623_Write(2,0xe);break;
			case 8: HT1623_Write(4,0x8);break;
			case 9: HT1623_Write(4,0x4);break;
			case 10:HT1623_Write(4,0x2);break;
			case 11:HT1623_Write(4,0xc);break;
			case 12:HT1623_Write(4,0xa);break;
			case 13:HT1623_Write(4,0x6);break;
			case 14:HT1623_Write(4,0xe);break;
			case 15:HT1623_Write(6,0x8);break;
			case 16:HT1623_Write(6,0x4);break;
			case 17:HT1623_Write(6,0x2);break;
			case 18:HT1623_Write(6,0xc);break;
			case 19:HT1623_Write(6,0xa);break;
			case 20:HT1623_Write(6,0x6);break;
			case 21:HT1623_Write(6,0xe);break;
			case 22:HT1623_Write(32,0x8);break;
			case 23:HT1623_Write(32,0x4);break;
			case 24:HT1623_Write(32,0x2);break;
			case 25:HT1623_Write(32,0xc);break;
			case 26:HT1623_Write(32,0xa);break;
			case 27:HT1623_Write(32,0x6);break;
			case 28:HT1623_Write(32,0xe);break;
			case 29:HT1623_Write(34,0x8);break;
			case 30:HT1623_Write(34,0x4);break;
			case 31:HT1623_Write(34,0x2);break;
			case 32:HT1623_Write(34,0xc);break;
			case 33:HT1623_Write(34,0xa);break;
			case 34:HT1623_Write(34,0x6);break;
			case 35:HT1623_Write(34,0xe);break;
			case 36:HT1623_Write(36,0x8);break;
			case 37:HT1623_Write(36,0x4);break;
			case 38:HT1623_Write(36,0x2);break;
			case 39:HT1623_Write(36,0xc);break;
			case 40:HT1623_Write(36,0xa);break;
			case 41:HT1623_Write(36,0x6);break;
			case 42:HT1623_Write(36,0xe);break;
			case 43:HT1623_Write(40,0x8);break;
			case 44:HT1623_Write(40,0x4);break;
			case 45:HT1623_Write(40,0x2);break;
			case 46:HT1623_Write(40,0xc);break;
			case 47:HT1623_Write(40,0xa);break;
			case 48:HT1623_Write(40,0x6);break;
			case 49:HT1623_Write(40,0xe);break;
			case 50:HT1623_Write(42,0x8);break;
			case 51:HT1623_Write(42,0x4);break;
			case 52:HT1623_Write(42,0x2);break;
			case 53:HT1623_Write(42,0xc);break;
			case 54:HT1623_Write(42,0xa);break;
			case 55:HT1623_Write(42,0x6);break;
			case 56:HT1623_Write(42,0xe);break;
			case 57:HT1623_Write(56,0x8);break;
			case 58:HT1623_Write(56,0x4);break;
			case 59:HT1623_Write(56,0x2);break;
			case 60:HT1623_Write(56,0xc);break;
			case 61:HT1623_Write(56,0xa);break;
			case 62:HT1623_Write(56,0x6);break;
			case 63:HT1623_Write(56,0xe);break;
			case 64:HT1623_Write(70,0x8);break;
			case 65:HT1623_Write(70,0x4);break;
			case 66:HT1623_Write(70,0x2);break;
			case 67:HT1623_Write(70,0xc);break;
			case 68:HT1623_Write(70,0xa);break;
			case 69:HT1623_Write(70,0x6);break;
			case 70:HT1623_Write(70,0xe);break;
			case 71:HT1623_Write(72,0x8);break;
			case 72:HT1623_Write(72,0x4);break;
			case 73:HT1623_Write(72,0x2);break;
			case 74:HT1623_Write(72,0xc);break;
			case 75:HT1623_Write(72,0xa);break;
			case 76:HT1623_Write(72,0x6);break;
			case 77:HT1623_Write(72,0xe);break;
			case 78:HT1623_Write(7,0xf);break;
			case 79:HT1623_Write(33,0xf);break;
			case 80:HT1623_Write(35,0xf);break;
			case 81:HT1623_Write(37,0xf);break;
			case 82:HT1623_Write(38,0x4);break;
			case 83:HT1623_Write(38,0x2);break;
			case 84:HT1623_Write(38,0xe);break;
			case 85:HT1623_Write(41,0xf);break;
			case 86:HT1623_Write(43,0xf);break;
			case 87:HT1623_Write(57,0xf);break;
			case 88:HT1623_Write(71,0xf);break;
			case 89:HT1623_Write(73,0xf);break;
		}
	}
	else
	{
		switch(nb)
		{
			case 1: HT1623_Write(2,0x0);break;
			case 2: HT1623_Write(2,0x0);break;
			case 3: HT1623_Write(2,0x0);break;
			case 4: HT1623_Write(2,0x0);break;
			case 5: HT1623_Write(2,0x0);break;
			case 6: HT1623_Write(2,0x0);break;
			case 7: HT1623_Write(2,0x0);break;
			case 8: HT1623_Write(4,0x0);break;
			case 9: HT1623_Write(4,0x0);break;
			case 10:HT1623_Write(4,0x0);break;
			case 11:HT1623_Write(4,0x0);break;
			case 12:HT1623_Write(4,0x0);break;
			case 13:HT1623_Write(4,0x0);break;
			case 14:HT1623_Write(4,0x0);break;
			case 15:HT1623_Write(6,0x0);break;
			case 16:HT1623_Write(6,0x0);break;
			case 17:HT1623_Write(6,0x0);break;
			case 18:HT1623_Write(6,0x0);break;
			case 19:HT1623_Write(6,0x0);break;
			case 20:HT1623_Write(6,0x0);break;
			case 21:HT1623_Write(6,0x0);break;
			case 22:HT1623_Write(32,0x0);break;
			case 23:HT1623_Write(32,0x0);break;
			case 24:HT1623_Write(32,0x0);break;
			case 25:HT1623_Write(32,0x0);break;
			case 26:HT1623_Write(32,0x0);break;
			case 27:HT1623_Write(32,0x0);break;
			case 28:HT1623_Write(32,0x0);break;
			case 29:HT1623_Write(34,0x0);break;
			case 30:HT1623_Write(34,0x0);break;
			case 31:HT1623_Write(34,0x0);break;
			case 32:HT1623_Write(34,0x0);break;
			case 33:HT1623_Write(34,0x0);break;
			case 34:HT1623_Write(34,0x0);break;
			case 35:HT1623_Write(34,0x0);break;
			case 36:HT1623_Write(36,0x0);break;
			case 37:HT1623_Write(36,0x0);break;
			case 38:HT1623_Write(36,0x0);break;
			case 39:HT1623_Write(36,0x0);break;
			case 40:HT1623_Write(36,0x0);break;
			case 41:HT1623_Write(36,0x0);break;
			case 42:HT1623_Write(36,0x0);break;
			case 43:HT1623_Write(40,0x0);break;
			case 44:HT1623_Write(40,0x0);break;
			case 45:HT1623_Write(40,0x0);break;
			case 46:HT1623_Write(40,0x0);break;
			case 47:HT1623_Write(40,0x0);break;
			case 48:HT1623_Write(40,0x0);break;
			case 49:HT1623_Write(40,0x0);break;
			case 50:HT1623_Write(42,0x0);break;
			case 51:HT1623_Write(42,0x0);break;
			case 52:HT1623_Write(42,0x0);break;
			case 53:HT1623_Write(42,0x0);break;
			case 54:HT1623_Write(42,0x0);break;
			case 55:HT1623_Write(42,0x0);break;
			case 56:HT1623_Write(42,0x0);break;
			case 57:HT1623_Write(56,0x0);break;
			case 58:HT1623_Write(56,0x0);break;
			case 59:HT1623_Write(56,0x0);break;
			case 60:HT1623_Write(56,0x0);break;
			case 61:HT1623_Write(56,0x0);break;
			case 62:HT1623_Write(56,0x0);break;
			case 63:HT1623_Write(56,0x0);break;
			case 64:HT1623_Write(70,0x0);break;
			case 65:HT1623_Write(70,0x0);break;
			case 66:HT1623_Write(70,0x0);break;
			case 67:HT1623_Write(70,0x0);break;
			case 68:HT1623_Write(70,0x0);break;
			case 69:HT1623_Write(70,0x0);break;
			case 70:HT1623_Write(70,0x0);break;
			case 71:HT1623_Write(72,0x0);break;
			case 72:HT1623_Write(72,0x0);break;
			case 73:HT1623_Write(72,0x0);break;
			case 74:HT1623_Write(72,0x0);break;
			case 75:HT1623_Write(72,0x0);break;
			case 76:HT1623_Write(72,0x0);break;
			case 77:HT1623_Write(72,0x0);break;
			case 78:HT1623_Write(7,0x0);break;
			case 79:HT1623_Write(33,0x0);break;
			case 80:HT1623_Write(35,0x0);break;
			case 81:HT1623_Write(37,0x0);break;
			case 82:HT1623_Write(38,0x0);break;
			case 83:HT1623_Write(38,0x0);break;
			case 84:HT1623_Write(38,0x0);break;
			case 85:HT1623_Write(41,0x0);break;
			case 86:HT1623_Write(43,0x0);break;
			case 87:HT1623_Write(57,0x0);break;
			case 88:HT1623_Write(71,0x0);break;
			case 89:HT1623_Write(73,0x0);break;
		}
	}
}
void display_time(unsigned char hour,unsigned char min,unsigned char sec)
{
	unsigned char time[6];
	time[0]=hour/10;
	time[1]=hour%10;
	time[2]=min/10;
	time[3]=min%10;
	time[4]=sec/10;
	time[5]=sec%10;
	display_point(2,1);
	display_point(6,1);
	display_point(0,1);
	display_point(4,1);
	display_nb(1,time[0]);display_nb(2,time[1]);
	display_nb(3,time[2]);display_nb(4,time[3]);
	display_nb(5,time[4]);display_nb(6,time[5]);	
}
void display_money(uint32_t money,unsigned char enable)
{
	if(enable)
	{
		unsigned char money1[6];
		money1[0]=(unsigned char)(money/100000);
		money1[1]=(unsigned char)(money/10000%10);
		money1[2]=(unsigned char)(money/1000%10);
		money1[3]=(unsigned char)(money/100%10);
		money1[4]=(unsigned char)(money/10%10);
		money1[5]=(unsigned char)(money%10);
		if(money<100)
		{
			display_nb(7 ,10);
			display_nb(8 ,10);
			display_nb(9 ,10);
			display_nb(10,0);
			display_nb(11,money1[4]);
			display_nb(12,money1[5]);
			display_point(10,1);
			display_piece(S22,1);
		}else if (money>=100&&money<1000)
		{
			display_nb(7 ,10);
			display_nb(8 ,10);
			display_nb(9 ,10);
			display_nb(10,money1[3]);
			display_nb(11,money1[4]);
			display_nb(12,money1[5]);
			display_point(10,1);
			display_piece(S22,1);
		}else if (money>=1000&&money<10000)
		{
			display_nb(7 ,10);
			display_nb(8 ,10);
			display_nb(9 ,money1[2]);
			display_nb(10,money1[3]);
			display_nb(11,money1[4]);
			display_nb(12,money1[5]);
			display_point(10,1);
			display_piece(S22,1);
		}else if (money>=10000&&money<100000)
		{
			display_nb(7 ,10);
			display_nb(8 ,money1[1]);
			display_nb(9 ,money1[2]);
			display_nb(10,money1[3]);
			display_nb(11,money1[4]);
			display_nb(12,money1[5]);
			display_point(10,1);
			display_piece(S22,1);
		}else if (money>=100000&&money<1000000)
		{
			display_nb(7 ,money1[0]);
			display_nb(8 ,money1[1]);
			display_nb(9 ,money1[2]);
			display_nb(10,money1[3]);
			display_nb(11,money1[4]);
			display_nb(12,money1[5]);
			display_point(10,1);
			display_piece(S22,1);
		}
	}
	else
	{
		display_nb(7 ,10);display_nb(8 ,10);
		display_nb(9 ,10);display_nb(10,10);
		display_nb(11,10);display_nb(12,10);
		display_point(10,0);
		display_piece(S22,0);
	}
}
void display_top(unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e,unsigned char f,unsigned char g,unsigned char h)
{
	unsigned char j;
	j=c*2*2*2+b*2*2+a*2;
	HT1623_Write(32,j);
	if(d==1)
		HT1623_Write(33,0xf);
	else if(d==0)
		HT1623_Write(33,0x0);
	if(e==1)
		HT1623_Write(35,0xf);
	else if(e==0)
		HT1623_Write(35,0x0);
	j=f*2*2*2+g*2*2+h*2;
	HT1623_Write(34,j);	
}
void display_left(unsigned char a1,unsigned char a2,unsigned char a3,unsigned char a4,unsigned char a5,unsigned char a6,unsigned char a7,unsigned char a8,unsigned char a9,unsigned char a10)
{
	unsigned char j;
	j=a2*2*2*2+a1*2*2+a6*2;
	HT1623_Write(4,j);
	j=a5*2*2*2+a4*2*2+a3*2;
	HT1623_Write(2,j);
	j=a9*2*2*2+a8*2*2+a7*2;
	HT1623_Write(6,j);
	if(a10==1)
		HT1623_Write(7,0xf);
	else if(a10==0)
		HT1623_Write(7,0x0);	
}
void display_right(unsigned char a1,unsigned char a2,unsigned char a3,unsigned char a4)
{
	unsigned char j;
	j=a3*2*2*2+a2*2*2+a1*2;
	HT1623_Write(36,j);
	if(a4==1)
		HT1623_Write(37,0xf);
	else if(a4==0)
		HT1623_Write(37,0x0);
}
void display_under(unsigned char nb,unsigned char enable)
{
	if(enable)
	{
		display_piece(T2,0);
		display_piece(T4,0);
		display_piece(T6,0);
		display_piece(T9,0);
		display_piece(T11,0);
		display_piece(T14,0);
		display_piece(T16,0);
		display_piece(T18,0);
		display_piece(T20,0);
		display_piece(T22,0);
		display_piece(T13,0);
		display_piece(T5,0);
		display_piece(T7,0);
		display_piece(T8,0);
		display_piece(T10,0);
		display_piece(T11,0);
		display_piece(T12,0);
		display_piece(T13,0);
		display_piece(T15,0);
		display_piece(T17,0);
		display_piece(T19,0);
		display_piece(T1,1);
		display_piece(nb,1);
	}
	else
	{
		display_piece(T1,0);
		display_piece(T2,0);
		display_piece(T4,0);
		display_piece(T6,0);
		display_piece(T9,0);
		display_piece(T11,0);
		display_piece(T14,0);
		display_piece(T16,0);
		display_piece(T18,0);
		display_piece(T20,0);
		display_piece(T22,0);
		display_piece(T13,0);
		display_piece(T5,0);
		display_piece(T7,0);
		display_piece(T8,0);
		display_piece(T10,0);
		display_piece(T11,0);
		display_piece(T12,0);
		display_piece(T13,0);
		display_piece(T15,0);
		display_piece(T17,0);
		display_piece(T19,0);
	}
}
