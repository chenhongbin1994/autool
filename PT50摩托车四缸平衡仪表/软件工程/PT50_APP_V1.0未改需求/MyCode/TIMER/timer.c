/*
 * @Author: ChenHongBin 944278386@qq.com
 * @Date: 2024-06-19 15:44:42
 * @LastEditors: ChenHongBin chenhongbin@cnautool.com
 * @LastEditTime: 2024-08-18 19:44:41
 * @FilePath: \Projectc:\Users\IBM\Desktop\PT50_stmf103_ADC_V14cs\MyCode\TIMER\timer.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE 
 */
#include "timer.h"
#include "usart.h"
#include "stdio.h"
#include "key.h"
#include "includes.h"
#include "key_handler.h"
u8 Second,Minute,Hour;
u8 SecondAuto;//AUTO���ػ�
u32 count,Battery_time;
u32 P_0_cnt = 0;
uint32_t Long_press_cnt ;
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
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���TIMx�����жϱ�־ 
      
    KeyHandler_Process();// �������¼�,�����ﰴ����Ӧ���������ǳ���ʱ���

    count++;
    
    if(count == 100)
    {
        count = 0;
        
        //Flag_o5s_Disp = 1;
        Flag_1s = !Flag_1s;
        if(Flag_1s == 0){
          Flag_o5s_Disp = 1;
          Clock_flag = 1;
        //Clock();
        }
    }
    
    //Battery_time++; //
    // if(Battery_time == 1000)//5Supdata
    // {
    //   Battery_time = 0; 
    //   Battery_ADCflag = 1;
    // }
    
     MinAuto++;
    if(MinAuto ==200)
    {
      MinAuto = 0;
       SecondAuto++;  
       if(SecondAuto ==60){                    //��60���1
        SecondAuto = 0;                       //������
        Timing_Switch_5min++;   
        Battery_ADCflag++;
        }           //��+1
    }

		 // ��ȡÿ��������״̬
        KEY_ReadStateMachine(&Key0Cfg);//����״̬��
        KEY_ReadStateMachine(&Key1Cfg);
        KEY_ReadStateMachine(&Key2Cfg);
        KEY_ReadStateMachine(&Key3Cfg);
        KEY_ReadStateMachine(&Key4Cfg);
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
		
		//P=0 ��������
    if((GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN_5) == 0))
    {
      P_0_cnt ++;
    }
    else
    {
      P_0_cnt = 0;
    }

    
			
	}
}

void Clock(void)                          //ʱ�ӳ���(��+1����+1��ʱ+1)
{
    Second++;                             //��+1
      if(Second ==60){                    //��60���1
        Second = 0;                       //������
        Minute++;
       
          if(Minute == 60){
            Minute =0;            
            Hour++;
            if(Hour == 24)Hour=0;
          }
      }
      Clock_Display();
}



#if 1
// ��ʼ��TIM2ͨ��2��ΪPWM���
void TIM2_Backlight_PWM_Init(void)
{
 
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); // �޸�: ����RCC_APB2Periph_AFIO
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//��֪���ע��Ϊ�ο�������������
  GPIO_InitStruct.GPIO_Mode 	=  GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;;
  GPIO_Init(GPIOB,&GPIO_InitStruct);
  GPIO_ResetBits( GPIOB, GPIO_Pin_3);

  // ����TIM2������ʱ��
  TIM_TimeBaseStructure.TIM_Period = 999; // ��������
  TIM_TimeBaseStructure.TIM_Prescaler = 71; // Ԥ��Ƶϵ��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  // ����TIM2ͨ��2ΪPWMģʽ
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0; // ��ʼռ�ձ�Ϊ0���رձ��⣩
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  // 6��ʹ��ARR��Ԥװ�ؼĴ���
   TIM_ARRPreloadConfig(TIM2, ENABLE);
   TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

  // ʹ��TIM2
  TIM_Cmd(TIM2, ENABLE);
	
}

// ����PWMռ�ձȣ��������ȣ�
void Set_Backlight_Brightness(uint16_t brightness)
{
  // ����������0��1000֮��
  if (brightness > 1000)
    brightness = 1000;

  // ����TIM2ͨ��2�Ĳ���ȽϼĴ���ֵ
  TIM_SetCompare2(TIM2, brightness);
	
	 // ���������Ϣ
  //printf("Set Backlight Brightness: %d\n", brightness);
}
#endif

#if 0  //EPMת��
//��ʱ��2ͨ��1���벶������

TIM_ICInitTypeDef  TIM1_ICInitStructure;

void TIM1_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
	
	//��ʼ����ʱ��1 TIM1	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM1���벶�����
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM1_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM1,ENABLE ); 	//ʹ�ܶ�ʱ��5
   


}

u8  TIM1CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM1CH1_CAPTURE_VAL;	//���벶��ֵ
 
//��ʱ��1�жϷ������	 
void TIM1_IRQHandler(void)
{ 

 	if((TIM1CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM1CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM1CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM1CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM1CH1_CAPTURE_VAL=0XFFFF;
				}else TIM1CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM1CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM1CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM1CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);
		   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM1CH1_CAPTURE_STA=0;			//���
				TIM1CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM1CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
 
}
#endif




// extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
// extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
//  int main(void)
//  {		
//  	u32 temp=0; 
// 	delay_init();	    	 //��ʱ������ʼ��	  
// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
// 	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
//  	LED_Init();			     //LED�˿ڳ�ʼ��
 
//  	TIM3_PWM_Init(899,0); 		//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
//  	TIM5_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
//    	while(1)
// 	{
//  		delay_ms(10);
// 		TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);

// 		if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
//  		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
// 		{
// 			temp=TIM5CH1_CAPTURE_STA&0X3F;
// 			temp*=65536;//���ʱ���ܺ�
// 			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
// 			printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
// 			TIM5CH1_CAPTURE_STA=0;//������һ�β���
// 		}
// 	}
//  }