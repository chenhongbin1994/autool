
#include "ht1621.h"
#include "common.h"


u8 tmr_cnt1;
bit flg_100ms;

void sys_init(void)
{
	_pac = 0x00;
	_pa = 0x00;
	
	_pcc = 0x00;
	_pc = 0x00;
		 
	//¶¨Ê±¡¢ÖÐ¶Ï
	_tmr0c=0x87;	//4M/128
	_tmr0=255-156;	//5ms
	
	_t0e=1;
	_emi=1;
	_t0on=1;
	
	_wdts=0x07;
	_clrwdt();
	
}


void main(void)
{
	sys_init();
	
	init_1621();
	
	while (1)
	{
		_clrwdt();
		
	
		if (flg_100ms)
		{
			flg_100ms = 0;
			
			clr_1621();
		
		}		

	}
}


#pragma vector tm0_isr @ 0x08
void tm0_isr(void)	//4ms
{	

	if (25 <= ++tmr_cnt1)
	{
		tmr_cnt1 = 0;
		flg_100ms =1;
	}


}	
	