 //说明：hour_32u单位为0.1小时
#include "HT46R065.h"
#pragma 	vector 		ext_int		@ 0x04 
#pragma 	vector 		tmr0_int	@ 0x08
#pragma 	vector 		tmr1_int	@ 0x0c  
#pragma 	vector 		ad_int		@ 0x10
#pragma 	vector 		base0_int	@ 0x14

#define		dat		_pc3
#define		wr		_pc5
#define		cs		_pc4
 
#define		stop    _pb0  
#define		right   _pb1 
#define		left    _pb2
#define		up		_pb3
#define		down    _pb4

#define		beep    _pc1
#define		sw1    	_pc6			//sw1=1选择扫地车,				sw1=0即短接选择四轮车
#define		sw2    	_pc7			//sw2=1显示公司名和电话号码,	sw2=0即短接去掉公司名和电话号码
#define		sw3    	_pa2			//sw3=1选择用48V电池,			sw3=0即短接选择用72V电池	，此功能暂时不用

bit			f_500ms,f_flash,f_adflag,f_poweroff,f_save,f_saodiche,f_telephone,f_vlow;
unsigned char j,k,cnt500ms,adnumv,adnumi,lcdtemp,mode,cnt5s;
unsigned int  adsumi_16u,adaveri_16u,min_16u,current_16u,adibak_16u,voltage_16u,voltagebak_16u,step1_16u,step2_16u,step3_16u;
unsigned char	lcd[9],lcdt[5];
unsigned long	hour_32u,adsumv_32u,adaverv_32u;
const unsigned char dspT[10]={0xfa,0x0a,0xbc,0x9e,0x4e,0xd6,0xf6,0x8a,0xfe,0xde};		//(7)A F E D B G C DP(0)
const unsigned char dspA[10]={0x5f,0x50,0x3d,0x79,0x72,0x6b,0x6f,0x51,0x7f,0x7b};
#define bias 		0x52	//4com 3bias
#define sysen		0x02
#define lcdon 		0x06
#define lcdoff		0x04

#define	SDA	_pc2
#define	SCK	_pb5
#define	WRITEADDRESS (unsigned char)0xa0 
#define	READADDRESS (unsigned char)0xa1
#define IICDATAINPUT()	_pcc2 = 1;
#define IICDATAOUTPUT()	_pcc2 = 0;
#define IICDATA	_pc2
#define IICCLK	_pb5
#define ACTERROR 1
#define ACTNOERROR 0

unsigned char IICWriteByteAt(unsigned char Address, unsigned char Data);
unsigned char IICReadByteAt(unsigned char Address, unsigned char *Data);
void IICStart(void);
void IICStop(void); 
void IICTxAct(void);
void IICTxNoAct(void); 
unsigned char IICCRCAct(void);
void IICWriteByte(unsigned char Data);
unsigned char IICReadByte(void);
unsigned char IICWriteByteAt(unsigned char Address, unsigned char Data);
unsigned char IICReadByteAt(unsigned char Address, unsigned char *Data);
void delay1(unsigned char i)
	{
		while (i--); 
	}
		
void sendaddr_1621(unsigned char data,unsigned char cnt);
void senddata_1621(unsigned char data,unsigned char cnt);
void sendcmd(unsigned char command);
void write_1621(unsigned char addr,unsigned char data);
void writeall_1621(unsigned char addr,unsigned char *p,unsigned char cnt);


void ext_int   (void){} 
void ad_int    (void){}	 
void tmr1_int  (void){}
void base0_int (void){}
void tmr0_int  (void)		//4ms
	{ 			 
		cnt500ms++;
		if(cnt500ms>=125)		//0.5s
			{
				cnt500ms=0;
				f_500ms=1;
				f_flash=~f_flash; 
				if(min_16u<720)			//6min即0.1hour
					{
						min_16u++;
					}
				else
					{
						min_16u=0;
						if(hour_32u<999999)
							{ 
								hour_32u++;
							}
						else
							{
								hour_32u=0;
								min_16u=0;
							}
					}  
			} 
		f_adflag=~f_adflag;
		if(f_adflag==0)
			{
		 		_acsr=0x01;_adcr=0x10;_start=0;_start=1;_start=0;		//an0 
		 		while(_eocb);
		 		adsumv_32u+=(((unsigned int)_adrh << 4) + (_adrl >> 4));
		 		adnumv++;
		 		if(_adrh<60)		//电源电压低于25V认为电源关闭
		 			{
		 				if(cnt5s>60)
		 					{
		 						f_poweroff=1;
		 					} 
		 				else
		 					{
		 						f_poweroff=0;
		 						f_save=0;
		 					}
		 			} 
		 		_adcr=0; 
		 		if(adnumv==21)				//转换21次
		 		    {  
		 		        adaverv_32u=adsumv_32u;
		 		        adsumv_32u=0; 
		 		        adnumv=0;
		 		    }
		 	}
		else  
			{
		 		_acsr=0x01;_adcr=0x11;_start=0;_start=1;_start=0;			//an1
		 		while(_eocb);
		 		adsumi_16u+=(((unsigned int)_adrh << 4) + (_adrl >> 4));
		 		adnumi++;
		 		_adcr=0;
		 		if(adnumi==8)
		 		    {
		 		        adsumi_16u>>=3;
		 		        adaveri_16u=adsumi_16u;
		 		        adsumi_16u=0;
		 		        adnumi=0; 
		 		    }
		 	} 
	}
void	init()
    {
		_ctrl0=0;
		_ctrl1=0xf5;		//双边沿触发  ftb=fsys/2^13 wdt enable		
		_pa=0xe7; 
		_pac=0xe7;
		_papu=0x04;
		_pbpu=0x3f; 
		_pbc=0x1f;
		_pb=0x3f;
		_pcpu=0xfe;
		_pcc=0xc0;
		_pc=0x0c;
		_intc0=0x04;		//t0e
		_intc1=0x00; 		 
		_tmr0c=0x86;		//tmrc=tm1 tm0 t0s(1:LXT) ton te psc2 psc1 psc0 fint=fsys/64,定时器模式,ton=0
		_tmr0=6;
		_tmr1c=0x90;
		_tmr1=6;	 		 
		_wdts=0x07;	
    } 			
void ram_clr();		    
//;************************************************************************
//;所有ram寄存器复位清0 
//;************************************************************************
void	ram_clr()
    {
        for(_mp0=0x40;_mp0<=0x9f;_mp0++)
        {
           _iar0=0;
        }
    }
void main()
{
     init();
	 ram_clr();  
	 sendcmd(lcdoff);	//关闭LCD显示
	 sendcmd(bias);		//设置偏压和占空比
	 sendcmd(sysen);	//打开系统振荡器 
//------------------------------------------------------	  
	 for(j=0;j<=31;j++) 				//清液晶屏  
		 {
		 	write_1621((j<<2),0x00);
		 	_clrwdt();
		 	_delay(100);
		 }     
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	 
	 _clrwdt();
	 IICReadByteAt(5,&k);		//上电读IIC到min_16u 低位放低字节
	 _clrwdt();
	 min_16u=k;
	 min_16u<<=8;
	 _delay(1000);
	 _clrwdt();
	 IICReadByteAt(4,&k);
	 _clrwdt();
	 min_16u+=k;
	 _delay(1000);
	 _clrwdt();
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 	for(j=0;j<4;j++)			//上电读IIC到hour_32u 低位放低字节
		{ 
			IICReadByteAt((j),&k); 
			_clrwdt();
			_delay(1000);
			_clrwdt();
			hour_32u+=(((unsigned long)k)<<(j<<3)); 
		} 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
	if(hour_32u>999999)
		{
			hour_32u=0;
			min_16u=0;			//否则第一次会显示0000.1hour 
		}  
	 f_poweroff=0;  
	 _t0on=1;
	 _emi=1; 
	 sendcmd(lcdon); 
	 cnt5s=0;  
	 for(j=0;j<100;j++)
	 	{
	 		_delay(5000);
	 		_clrwdt();
		} 
	 f_saodiche=1;
	 if(!sw1)				//判断是扫地车还是四轮车
	 	{
	 		_delay(5000);
	 		_clrwdt();
	 		_delay(5000);
	 		_clrwdt();
	 		if(!sw1)
	 			{
	 				f_saodiche=0;
	 			}
	 	} 
	 f_telephone=1;			//判断是否显示公司名和电话号码
	 if(!sw2)
	 	{
	 		_delay(5000);
	 		_clrwdt();
	 		_delay(5000);
	 		_clrwdt();
	 		if(!sw2)
	 			{
	 				f_telephone=0;
	 			}
	 	} 
	 //voltage_16u=(unsigned int)((adaverv_32u*50)>>12); 	//判断电源是48V还是72V		电压>60V则认为是72V电池
	 	if(adaverv_32u>49152)			//电压>60V则认为是72V电池  60/21/5*4096*21
	 		{
	 			step1_16u=740;
	 			step2_16u=720;
	 			step3_16u=680;
	 		}					
	 	else
	 		{
	 			step1_16u=480;
	 			step2_16u=460;
	 			step3_16u=420;
	 		}
     while(1)                                                
	     {   
	     	_clrwdt();
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  	 
			if(f_poweroff)					//掉电保存
	     		{
	     			if(!f_save)
	     				{
	     					f_save=1;
	     					for(j=0;j<4;j++)			 
								{  
									k=hour_32u>>(j<<3); 
									_clrwdt();
									IICWriteByteAt(j,k);
									_delay(2000);
									_clrwdt();
								} 
			     			 k=min_16u;
							 _clrwdt();
							 IICWriteByteAt(4,k);
							 _delay(2000);
							 _clrwdt(); 
							  k=min_16u>>8;
							 _clrwdt();
							 IICWriteByteAt(5,k);
							 _delay(2000); 
							 _clrwdt();
							 
						}
	     		} 
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    	 
	     	_clrwdt();  
	     	if(f_500ms)			
	     		{ 
	     			_clrwdt();
	     			f_500ms=0;
	     			if(cnt5s<100)
	     				{ 
	     					cnt5s++;
	     				}
//**********************************************************************
//-------------------   转向灯扫描显示  -----------------------
//**********************************************************************     				     			
	     			if((_pb&0x1f)==0x1f)
	     				{
	     					lcdt[0]&=0xfb; 
	     					lcdt[1]&=0xf0;
	     					lcdt[2]&=0xfb;
	     				} 
	     			else
	     				{ 
					     	if(!stop)
					     		{
					     			lcdt[1]|=0x03;
					     		}
					     	else
					     		{
					     			lcdt[1]&=0xfc;
					     		}
					     	if(!up)
					     		{
					     			lcdt[1]|=0x08;
					     		}
					     	else
					     		{
					     			lcdt[1]&=0xf7;
					     		}
					     	if(!down)
					     		{
					     			lcdt[1]|=0x04;
					     		}
					     	else
					     		{
					     			lcdt[1]&=0xfb;
					     		} 
					     	if(!left)
					     		{
					     			lcdt[0]|=0x04;
					     		}
					     	else
					     		{
					     			lcdt[0]&=0xfb;
					     		}
					     	if(!right)
					     		{
					     			lcdt[2]|=0x04;
					     		}
					     	else
					     		{
					     			lcdt[2]&=0xfb;
					     		}
					    }  
//**********************************************************************
//---------------------  里程显示  --------------------------------------
//**********************************************************************					     					    					    
					lcdtemp=hour_32u/100000; 
					if(lcdtemp>9)
						{
							lcdtemp=9;
						}
					lcd[0]=dspT[lcdtemp];
					_clrwdt();
					lcdtemp=hour_32u/10000%10;
					lcd[1]=dspT[lcdtemp];
					_clrwdt();
					lcdtemp=hour_32u/1000%10;
					lcd[2]=dspT[lcdtemp];
					_clrwdt();
					lcdtemp=hour_32u/100%10;
					lcd[3]=dspT[lcdtemp];
					_clrwdt();
					lcdtemp=hour_32u/10%10;
					lcd[4]=dspT[lcdtemp];
					_clrwdt();
					lcdtemp=hour_32u%10;
					lcd[5]=dspT[lcdtemp];
					_clrwdt();
					
					lcd[4]|=0x01;		//D5 ON
					lcd[5]|=0x01;		//D6 ON
//**********************************************************************
//-------------------电流显示  300A--75MV 电流放大33倍----------------- 
//-----I=adaveri_16u*300*1000*5/75/33/4096=adaveri_16u*625/4224(A)-----
//**********************************************************************
					if((adibak_16u>(adaveri_16u+4))||(adaveri_16u>(adibak_16u+4)))
						{
							adibak_16u=adaveri_16u;
						}
					current_16u=(unsigned int)(((unsigned long)adibak_16u)*625/4224);
					if(current_16u<2)
						{
							current_16u=0;
						}
					if(current_16u>500)
						{
							current_16u=500;
						}
					lcdtemp=current_16u/100;
					lcd[8]=dspA[lcdtemp];
					lcdtemp=current_16u/10%10;
					lcd[7]=dspA[lcdtemp];
					lcdtemp=current_16u%10;
					lcd[6]=dspA[lcdtemp];
					lcd[6]|=0x80;		//D7 ON
					lcdt[2]|=0x02;		//T11 ON
//**********************************************************************
//----------------------  电量显示    -----------------------------------
//**********************************************************************	
					voltage_16u=(unsigned int)((adaverv_32u*50)>>12); 	//电压=ADV*50/4096，精确到0.1V
					if((voltagebak_16u>(voltage_16u+5))||(voltage_16u>(voltagebak_16u+5)))
						{
							voltagebak_16u=voltage_16u;
						}	
					lcd[0]|=0x01;						//D1 ON	
					lcdt[0]|=0x01;		 
					if(voltagebak_16u>=step1_16u)		//>=48v  
						{ 
							f_vlow=0;
							lcdt[0]&=0xfd;
							lcd[1]|=0x01;		//D2 ON
							lcd[2]|=0x01;		//D3 ON
							lcd[3]|=0x01;		//D4 ON
						}
					else if(voltagebak_16u>=step2_16u)	//>=46v
						{
							f_vlow=0;
							lcdt[0]&=0xfd;
							lcd[1]|=0x01;		//D2 ON
							lcd[2]|=0x01;		//D3 ON 
						} 
					else if(voltagebak_16u>=step3_16u)	//>=42v
						{
							f_vlow=0;
							lcdt[0]&=0xfd;
							lcd[1]|=0x01;		//D2 ON 
						} 
					else 						//低于42V欠压报警
						{  
							f_vlow=1;
							if(lcdt[0]&0x02)	//电池 T3 闪烁
								{
									lcdt[0]&=0xfd;
								}
							else
								{
									lcdt[0]|=0x02;		
								}  
						}  	 
					if(f_flash&&f_vlow)			//低电压报警或打转向灯报警
						{ 
							beep=1; 
						}
					else 
						{
							beep=0;
						}					 	  
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------其他显示----------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
					mode++; 
					if(mode>15)
						{
							mode=0;
						} 
					switch(mode)				//扫地车 T16 T14 T19 T13 D9 T18   // 四轮车 T19 T14 T13 T18 
						{
							case 0:	 
										lcdt[3]&=0xfe;		//T16 OFF
										lcdt[3]&=0xfb;		//T14 OFF
										lcdt[4]&=0xfd;		//T19 OFF
										lcdt[3]&=0xf7;		//T13 OFF
										lcd[8] &=0x7f;		//D9  OFF
										lcdt[4]&=0xfb;		//T18 OFF 
										break;										
							case 1:
										if(f_saodiche)
											{
												lcdt[3]|=0x01;		//T16 ON  
												lcdt[4]&=0xfd;		//T19 OFF 
												lcd[8] &=0x7f;		//D9  OFF 
											}
										else
											{
												lcdt[4]|=0x02;		//T19 ON 
											}
										lcdt[3]&=0xfb;		//T14 OFF  
										lcdt[4]&=0xfb;		//T18 OFF
										lcdt[3]&=0xf7;		//T13 OFF
										break;	
							case 2:	
										if(f_saodiche)
											{
												lcdt[3]|=0x01;		//T16 ON 
												lcdt[4]&=0xfd;		//T19 OFF 
												lcd[8] &=0x7f;		//D9  OFF 
											}
										else
											{
												lcdt[4]|=0x02;		//T19 ON 
												 
											}
										lcdt[3]|=0x04;		//T14 ON 
										lcdt[4]&=0xfb;		//T18 OFF
										lcdt[3]&=0xf7;		//T13 OFF
										break;	
							case 3:
										if(f_saodiche)
											{
												lcdt[3]|=0x01;		//T16 ON 
												lcd[8] &=0x7f;		//D9  OFF
												lcdt[4]&=0xfb;		//T18 OFF
											}
										else
											{ 
												lcdt[4]|=0x04;		//T18 ON 
											}
										lcdt[3]&=0xf7;		//T13 OFF
										lcdt[4]|=0x02;		//T19 ON 
										lcdt[3]|=0x04;		//T14 ON 
										break;
							case 4:
										if(f_saodiche)
											{
												lcdt[3]|=0x01;		//T16 ON 
												lcd[8] &=0x7f;		//D9  OFF
												lcdt[4]&=0xfb;		//T18 OFF
											}
										else
											{ 
												lcdt[4]|=0x04;		//T18 ON  
											}
										lcdt[4]|=0x02;		//T19 ON 
										lcdt[3]|=0x04;		//T14 ON 
										lcdt[3]|=0x08;		//T13 ON	
										break;		
							case 5:
										if(f_saodiche)
											{
												lcdt[3]|=0x01;		//T16 ON
												lcd[8] |=0x80;		//D9  ON
												lcdt[4]&=0xfb;		//T18 OFF
											}
										else
											{  
												lcdt[4]|=0x04;		//T18 ON  
											} 
										lcdt[3]|=0x04;		//T14 ON
										lcdt[4]|=0x02;		//T19 ON
										lcdt[3]|=0x08;		//T13 ON
										break;	 		
							default:
										if(f_saodiche)
											{
												lcdt[3]|=0x01;		//T16 ON   
												lcd[8] |=0x80;		//D9  ON 	
											} 
										lcdt[4]|=0x02;		//T19 ON 
										lcdt[3]|=0x04;		//T14 ON  
										lcdt[4]|=0x04;		//T18 ON 
										lcdt[3]|=0x08;		//T13 ON 
										break; 
						}  
					if(f_telephone)						//显示公司名和电话
						{
							lcdt[0]|=0x08;			//显示T1 	公司名
							lcdt[4]|=0x01;			//T20 ON	注意事项
							lcdt[4]|=0x08;			//T17  ON	销售热线
							lcdt[3]|=0x02;			//T15  ON	横线
							lcdt[2]|=0x08;			//T9  ON	服务热线
						}
					else							//不显示公司名和电话
						{
							lcdt[0]&=0xf7;			//T1   OFF	去掉显示公司名
							lcdt[4]|=0x01;			//T20  ON	注意事项
							lcdt[4]&=0xf7;			//T17  OFF	去掉销售热线
							lcdt[3]|=0x02;			//T15  ON	横线
							lcdt[2]&=0xf7;			//T9   OFF	去掉服务热线
						}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
			        write_1621(32,lcd[0]>>4); 
			        write_1621(28,lcd[0]); 
			        write_1621(24,lcd[1]>>4);
			        write_1621(20,lcd[1]);
			        write_1621(16,lcd[2]>>4);
			        write_1621(12,lcd[2]);
			        write_1621(8,lcd[3]>>4);
			        write_1621(4,lcd[3]);
			        write_1621(0,lcd[4]>>4);
			        write_1621(88,lcd[4]);
			        write_1621(84,lcd[5]>>4);
			        write_1621(80,lcd[5]);
			        _clrwdt();
			        
			        write_1621(68,lcd[6]>>4);
			        write_1621(64,lcd[6]);
			        write_1621(60,lcd[7]>>4);
			        write_1621(56,lcd[7]); 
			        write_1621(40,lcd[8]>>4); 
			        write_1621(44,lcd[8]); 
			        _clrwdt();
			        
			        write_1621(36,lcdt[0]); 
			        write_1621(76,lcdt[1]);
			        write_1621(72,lcdt[2]);
			        write_1621(48,lcdt[3]);
			        write_1621(52,lcdt[4]); 
			        _clrwdt();
			    }
		 }
}    

//*******************************************************************************************************  
//----------------1621子程序-------------------------------
//*******************************************************************************************************  
void sendaddr_1621(unsigned char data,unsigned char cnt)		//data的高cnt位写入HT1621，高位在前
	{
		unsigned char i; 
		for(i =0; i <cnt; i ++)
			{
				if((data&0x80)==0) 
					dat=0;
				else 
					dat=1; 
				wr=0;
				_nop();
				wr=1; 
				data<<=1;
			} 
	}
//-----------------------------------------------------------------------------------------------------------
void senddata_1621(unsigned char data,unsigned char cnt)	//data的低cnt位写入HT1621，低位在前
	{
		unsigned char i; 
		for(i =0; i <cnt; i ++)
			{
				if((data&0x01)==0) 
					dat=0;
				else 
					dat=1; 
				wr=0;
				_nop();
				wr=1; 
				data>>=1;
			} 
	}
//-----------------------------------------------------------------------------------------------------------
void sendcmd(unsigned char command)
	{ 
		cs=0;
		sendaddr_1621(0x80,4);			//写入标志码"100"和9位command命令，由于
		sendaddr_1621(command,8); 		//没有使有到更改时钟输出等命令，为了编程方便
		cs=1;						//直接将command的最高位写"0"
	}
//-----------------------------------------------------------------------------------------------------------
void write_1621(unsigned char addr,unsigned char data)
	{ 
		cs=0;
		sendaddr_1621(0xa0,3);			//写入标志码"101"
		sendaddr_1621(addr,6);			//写入addr的高6位
		senddata_1621(data,4);		//写入data的低4位
		cs=1; 
	}
//-----------------------------------------------------------------------------------------------------------
void writeall_1621(unsigned char addr,unsigned char *p,unsigned char cnt)
	{
		unsigned char i; 
		cs=0;
		sendaddr_1621(0xa0,3);			//写入标志码"101"
		sendaddr_1621(addr,6);			//写入addr的高6位
		for(i =0; i <cnt; i ++,p++)		//连续写入数据
			{
				senddata_1621(*p,8);
			}
		cs=1; 
	}
//******************************************************************************************************* 
   
/*********************************************************
* IIC Bus Start: void IICStart(void)
* By	: Wang Kuo
* Date	: 2009-1-13 17:35
*********************************************************/
void IICStart(void)
{
	IICCLK = 0;
	delay1(35);
	IICDATA = 1;
	delay1(35);
	IICCLK = 1;
	delay1(35);
	IICDATA = 0;
	delay1(35);
	IICCLK = 0;
	delay1(35);
}

/*********************************************************
* IIC Bus Stop: void IICStop(void)
* By	: Wang Kuo
* Date	: 2009-1-14 9:37
*********************************************************/
void IICStop(void)
{
	IICCLK = 0;
	delay1(35);
	IICDATA = 0;
	delay1(35);
	IICCLK = 1;
	delay1(35);
	IICDATA = 1;
	delay1(35);
}
   
/*********************************************************
* Send an Act to IIC Bus: void IICTxAct(void)
* By	: Wang Kuo
* Date	: 2009-1-14 9:39
*********************************************************/
void IICTxAct(void)
{
	IICCLK = 0;
	delay1(35);
	IICDATA = 0;
	delay1(35);
	IICCLK = 1;
	delay1(35);
	IICCLK = 0;
	delay1(35);
	IICDATA = 1;
	delay1(35);
}

/*********************************************************
* Send an No Act to IIC Bus:void IICTxNoAct(void)
* By	: Wang Kuo
* Date	: 2009-1-14 9:44
*********************************************************/
void IICTxNoAct(void)
{
	IICCLK = 0;
	delay1(35);
	IICDATA = 1;
	delay1(35);
	IICCLK = 1;
	delay1(35);
}

/*********************************************************
* CRC Act signal on IIC Bus: unsigned char IICCRCAct(void)
* By	: Wang Kuo
* Date	: 2009-1-14 9:45
*********************************************************/
unsigned char IICCRCAct(void)
{
	unsigned char Temp = 0;
	IICDATAINPUT();
	IICCLK = 0;
	delay1(35);
	IICCLK = 1;
	delay1(35);
	while(IICDATA)		//等待应答
	{
		Temp ++;
		if(Temp == 255) break;
	}
	IICCLK = 0;
	IICDATAOUTPUT();	//IICDATADIR = OUTPUT;
	delay1(35);
	if(Temp < 255)
		return ACTNOERROR;
	else
		return ACTERROR;
}

/**********************************************************
* Write one Byte to IIC Bus: void IICWriteByte(unsigned char Data)
* By	: Wang Kuo
* Date	: 2009-1-14 10:04
**********************************************************/
void IICWriteByte(unsigned char Data)
{
	unsigned char Temp;
	for(Temp=0;Temp<8;Temp++)
	{
		if((Data & 0x80) != 0)
			IICDATA = 1;
		else
			IICDATA = 0;
		delay1(35);
		IICCLK = 1;
		delay1(35);
		IICCLK = 0;
		delay1(35);
		Data <<= 1;
	}
}

/*********************************************************
* Read one Byte from IIC Bus: unsigned char IICReadByte(void)
* By	: Wang Kuo
* Date	: 2009-1-14 10:08
*********************************************************/
unsigned char IICReadByte(void)
{
	unsigned char Temp,Data = 0;
	for(Temp=0; Temp<8; Temp++)
	{
		IICDATAINPUT();		//IICDATADIR = INPUT;         //切换为输入状态
		delay1(35);								/* 由于没加上拉电阻，49RA0内部只有200K的上拉，所以这里延时去掉的话 就读不对 */
		Data = Data << 1;
		if(IICDATA == 1)
			Data ++;
		IICCLK = 1;
		delay1(35);
		IICCLK = 0;
		delay1(35);
	}
	IICDATAOUTPUT();	//IICDATADIR = OUTPUT;
	delay1(35);
	return(Data);
}

/***********************************************************
* Write 8 Bytes Data to IIC Bus 
*   void IICWriteBytesAt(unsigned char Address, unsigned char *Data)
* By	: Wang Kuo
* Date	: 2009-1-14 11:09
***********************************************************/
unsigned char IICWriteByteAt(unsigned char Address, unsigned char Data)
{
	unsigned char i, i1;
	i1 = 0;
	IICStart();
	IICWriteByte(WRITEADDRESS);
	if(IICCRCAct() == ACTERROR)
		return	ACTERROR;
	IICWriteByte(Address);
	if(IICCRCAct() == ACTERROR)
		return	ACTERROR;

	IICWriteByte(Data);
	if(IICCRCAct() == ACTERROR)
		i1 = 1;
	IICStop();
	return i1;
} 

/***********************************************************
* Read 8 Bytes from IIC Bus:
* void IICReadBytesAt(unsigned char Address,unsigned char *Data)
* By	: Wang Kuo
* Date	: 2009-1-14 13:24
***********************************************************/
unsigned char IICReadByteAt(unsigned char Address, unsigned char *Data)
{
	unsigned char Temp, i;
	IICStart();
	IICWriteByte(WRITEADDRESS);
	if(IICCRCAct() == ACTERROR)
		return	ACTERROR;
	IICWriteByte(Address);
	if(IICCRCAct() == ACTERROR)
		return	ACTERROR;
	IICStart();
	IICWriteByte(READADDRESS);
	if(IICCRCAct() == ACTERROR)
		return	ACTERROR;

	*Data  = IICReadByte();
	IICTxNoAct();
	IICStop();
	return 0;
}