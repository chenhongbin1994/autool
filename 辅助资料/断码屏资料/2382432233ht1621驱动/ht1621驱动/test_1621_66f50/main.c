
#include "ht1621.h"
#include "common.h"


u8 tmr_cnt1;

#pragma rambank0
bit flg_100ms;
#pragma norambank

void sys_init(void)
{	
	_papu = 0x00;
	_pac = 0x00;
	_pa = 0x00;
		 
	_pbpu = 0x00;
	_pbc = 0x00;
	_pb = 0x00;
	
	_pcpu = 0x00;
	_pcc = 0x00;
	_pc = 0x00;
	
	
	//clr ram
	#asm
	mov		a,80h
	mov		__mp0,a
	mov		a,128
	clr		__iar0
	inc		__mp0
	sdz		__acc
	jmp		$-3
	
	mov		a,01
	mov		__bp,a
	mov		a,80h
	mov		__mp0,a
	mov		a,128
	clr		__iar0
	inc		__mp0
	sdz		__acc
	jmp		$-3
	
	mov		a,02
	mov		__bp,a
	mov		a,80h
	mov		__mp0,a
	mov		a,128
	clr		__iar0
	inc		__mp0
	sdz		__acc
	jmp		$-3
	clr		__bp
	#endasm
	
	
	_cp0c = 0x08;		// DISABLE COMPARATOR
	_cp1c = 0x08;
	
	_tm0c0 = 0x30;		// 1/64 Fh
	_tm0c1 = 0xc1;
	_tm0al = 0xc1;		// 8M	7.69ms
	_tm0ah = 0x03;

	
	_t0on = 1;
	_mf0e = 1;		// ENABLE CTM INTERRUPT
	_t0ae = 1;		// ENABLE CTM CCRA COMPARE INTERRUPT
	_emi = 1;		// ENABLE EMI
	
	_acerl = 0x00;
	
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


#pragma vector tm0_isr @ 0x14
void tm0_isr(void)	//4ms
{	
	_t0af = 0;

	if (25 <= ++tmr_cnt1)
	{
		tmr_cnt1 = 0;
		flg_100ms =1;
	}


}	
	