#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
#include "iap.h"

iapfun jump2app; 
u16 iapbuf[1024];   
//appxaddr:应用程序的起始地址
//appbuf:应用程序CODE.
//appsize:应用程序大小(字节).

void iap_write_appbin(u32 appxaddr, u8 *appbuf, u32 appsize)
{
    u16 i = 0;
    u16 temp;
    u32 fwaddr = appxaddr; // 当前写入的地址
    u8 *dfu = appbuf;

    for (u32 t = 0; t < appsize; t += 2)
    {
        temp = (u16)dfu[1] << 8;
        temp += (u16)dfu[0];
        dfu += 2; // 偏移2个字节
        iapbuf[i++] = temp;

        if (i == 1024)
        {
            i = 0;
            STMFLASH_Write(fwaddr, iapbuf, 1024);
            fwaddr += 2048; // 偏移2048字节
        }
    }

    if (i) STMFLASH_Write(fwaddr, iapbuf, i); // 写入剩余数据
}



//跳转到应用程序段
//appxaddr:用户代码起始地址.
void iap_load_app(u32 appxaddr)
{
#if 0
	/* 设置所有时钟到默认状态，使用HSI时钟 */
    RCC_DeInit();
	/* 关闭全局中断 */
	INTX_DISABLE();

	/* 关闭滴答定时器，复位到默认值 */
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	/* 设置所有时钟到默认状态，使用HSI时钟 */
//	HAL_RCC_DeInit();

	/* 关闭所有中断，清除所有中断挂起标志 */
	for (int i = 0; i < 8; i++)
	{
		NVIC->ICER[i]=0xFFFFFFFF;
		NVIC->ICPR[i]=0xFFFFFFFF;
	}	

	/* 使能全局中断 */
	INTX_ENABLE();
#endif 
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		SCB->VTOR = 0x08010000;
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(vu32*)appxaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		jump2app();									//跳转到APP.
	}
}		 














