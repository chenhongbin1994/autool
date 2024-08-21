
#include "timer.h"
#include "usart.h"
#include "stdio.h"
#include "key.h"
#include "includes.h"

u8 Second,Minute,Hour;
u8 SecondAuto;//AUTO���ػ�
u32 count,Battery_time;

volatile    u8   Flag_o5s_Disp,Flag_1s,flag_10ms,Battery_ADCflag,Clock_flag;//AutoONOFF_flag
volatile    u8   Timing_Switch_5min,MinAuto; 
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void TIM3_Int_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3, ENABLE);					 
}




extern KEY_Configure_TypeDef Key0Cfg;
extern KEY_Configure_TypeDef Key1Cfg;
extern KEY_Configure_TypeDef Key2Cfg;
extern KEY_Configure_TypeDef Key3Cfg;
extern KEY_Configure_TypeDef Key4Cfg;
extern KEY_Configure_TypeDef Key5Cfg;
                        
extern int history_index;  // ��ǰ��¼������
int powerON_cut;
extern int power_on;
uint32_t Long_press_cnt ;

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���TIMx�����жϱ�־ 
      
    KeyHandler_Process();// �������¼�,�����ﰴ����Ӧ���������ǳ���ʱ���

    count++;
   

		 // ��ȡÿ��������״̬
        KEY_ReadStateMachine(&Key0Cfg);//����״̬��
        //KEY_ReadStateMachine(&Key1Cfg);
        KEY_ReadStateMachine(&Key2Cfg);
        KEY_ReadStateMachine(&Key3Cfg);
        //KEY_ReadStateMachine(&Key4Cfg);
        KEY_ReadStateMachine(&Key5Cfg);
				
						//���������� ����
		if ((power_on ==0)&&(GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 1)){
			powerON_cut++;
		}
		else
		{
			powerON_cut =0;
		}
				if(powerON_cut	> 400)
		{
			power_on = 1;
			return;
		}
		
		
		//�ػ�
		if((power_on == 1)&& (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_0) == 1))
		{
			 Long_press_cnt ++;
		}
		else
		{
			Long_press_cnt =0;
		}
			
		if(Long_press_cnt	> 400)
		{
			Handle_Key0_Event( KEY_Event_LongPress);
			Long_press_cnt =	0;
		}
	}
}







