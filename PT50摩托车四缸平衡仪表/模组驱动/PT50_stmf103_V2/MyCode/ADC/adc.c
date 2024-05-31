 #include "adc.h"
 #include "delay.h"

	   
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc1_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

//	//PA2 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//DISABLE����ͨ��ģʽ��ENABLE��ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//DISABLE��ģ��ת�������ڵ���ת��ģʽ��ENABLE����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 3;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  

//ch:ͨ��ֵ 0~3
//��ȡ����ADCֵ
u16 ADC1_Mid_GetValue(u8 channel)   //ch:ѡ��ͨ����ADC_Channel_0
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

// ��ȡָ��ͨ����ƽ��ADCֵ
u16 ADC1_Mid_GetAverageValue(u8 channel,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=ADC1_Mid_GetValue(channel);
		delay_ms(5);
	}
	return temp_val/times;
} 

/*
3.3V ����:(0.2~2.7V)
ѹ��=(���ֵ-1.45)/K

         K ֵ VS ѹ������
���� (kPa)        3.3��V��    5��V��
-100~100             0.0125        0.02
*/
float ADC1_Mid_MapValue(float OutputValue, float PositivePressure, float K_Value) 
{
   return (OutputValue/4096*3.3 - PositivePressure) / K_Value;
}

#if 1
/*--------------------------------��Դ��ѹ����----------------------------------*/
void Adc2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef  ADC_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2|RCC_APB2Periph_GPIOB, ENABLE);//��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCʱ�ӷ�Ƶ
	
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AIN;	//ģ������
    GPIO_InitStruct.GPIO_Pin  =GPIO_Pin_0;     	//��������	PB0	ϵͳ����(6V)������
    GPIO_Init(GPIOB, &GPIO_InitStruct);         //��ʼ��
	
//	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AIN;	//ģ������
//    GPIO_InitStruct.GPIO_Pin  =GPIO_Pin_4;     	//��������	PC4 Ŧ�۵�ز�����
//    GPIO_Init(GPIOC, &GPIO_InitStruct);         //��ʼ��

	ADC_InitStruct.ADC_ContinuousConvMode= DISABLE;//����ת��
	ADC_InitStruct.ADC_DataAlign         = ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStruct.ADC_Mode              = ADC_Mode_Independent;//����ģʽ
	ADC_InitStruct.ADC_ScanConvMode      = DISABLE;//��ɨ��
	ADC_InitStruct.ADC_NbrOfChannel      = 1;//��ͨ���л�
	ADC_InitStruct.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None;//���
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC2, ENABLE);
	ADC_ResetCalibration(ADC2);//��λУ׼
	while(ADC_GetResetCalibrationStatus(ADC2));//�ȴ���λ���
	ADC_StartCalibration(ADC2);  //����У׼
	while(ADC_GetCalibrationStatus(ADC2));//�ȴ�У׼����
}


u16 ADC2_Mid_GetValue(u8 channel)
{
    ADC_RegularChannelConfig(ADC2, channel, 1, ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);//�������ת��
	ADC_Cmd(ADC2, ENABLE);
    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));//�ȴ�ת������
	return ADC_GetConversionValue(ADC2);
}

/*--------------------------------��Դ��ѹ����----------------------------------*/
#endif





















