#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
#include "iap.h"

iapfun jump2app; 
u16 iapbuf[1024];   
//appxaddr:Ӧ�ó������ʼ��ַ
//appbuf:Ӧ�ó���CODE.
//appsize:Ӧ�ó����С(�ֽ�).

void iap_write_appbin(u32 appxaddr, u8 *appbuf, u32 appsize)
{
    u16 i = 0;
    u16 temp;
    u32 fwaddr = appxaddr; // ��ǰд��ĵ�ַ
    u8 *dfu = appbuf;

    for (u32 t = 0; t < appsize; t += 2)
    {
        temp = (u16)dfu[1] << 8;
        temp += (u16)dfu[0];
        dfu += 2; // ƫ��2���ֽ�
        iapbuf[i++] = temp;

        if (i == 1024)
        {
            i = 0;
            STMFLASH_Write(fwaddr, iapbuf, 1024);
            fwaddr += 2048; // ƫ��2048�ֽ�
        }
    }

    if (i) STMFLASH_Write(fwaddr, iapbuf, i); // д��ʣ������
}



//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void iap_load_app(u32 appxaddr)
{
#if 0
	/* ��������ʱ�ӵ�Ĭ��״̬��ʹ��HSIʱ�� */
    RCC_DeInit();
	/* �ر�ȫ���ж� */
	INTX_DISABLE();

	/* �رյδ�ʱ������λ��Ĭ��ֵ */
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	/* ��������ʱ�ӵ�Ĭ��״̬��ʹ��HSIʱ�� */
//	HAL_RCC_DeInit();

	/* �ر������жϣ���������жϹ����־ */
	for (int i = 0; i < 8; i++)
	{
		NVIC->ICER[i]=0xFFFFFFFF;
		NVIC->ICPR[i]=0xFFFFFFFF;
	}	

	/* ʹ��ȫ���ж� */
	INTX_ENABLE();
#endif 
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{ 
		SCB->VTOR = 0x08010000;
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(vu32*)appxaddr);					//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		jump2app();									//��ת��APP.
	}
}		 














