#include "adc.h"
#include "delay.h"
#include "usart.h"
//��������Ǵ洢��RAM�����ڴ��еģ����ڴ洢DMA��ADC-DR�а��˳�����ADCת��ֵ
//��4��ͨ��ƽ��ֵAD_TotalValue[40]���浽ADC_Value[4]����
uint16_t AD_TotalValue[40];
uint16_t ADC_TempValue[4];
uint16_t ADC_Value[4];
extern float ADValue_offset[4];
extern int initial_value;
float tempADC_Value[4];
void ADC_Init_t(void)
{
	GPIO_InitTypeDef GPIOA_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//����IO��Ϊģ������ģʽ,��ģʽ��ADC��ר��ģʽ
	//��ģʽ��IO������Ч�ģ���ֹIO�ڵ����������ģ���ѹ��ɸ���
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_InitStructure);
	//���ϴ��������꣬IO�ھͱ�����Ϊģ�������������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	
	//����ADCʱ��ΪRCC��6��Ƶ��12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//ѡ������������ͨ��
		//ѡ��ͨ��0�������1������ʱ��Ϊ55.5��ADCCLK����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
		//��д������ͨ��������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);	
	
	
	//���γ���Ĵ����õ��ǵ���ת����ɨ��ģʽ
	//����ת��ģʽ����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//ɨ��ģʽ����
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	//ͨ����Ŀ���ã�ָ���ڡ�ɨ��ģʽ�����ܹ���Ҫɨ��ǰ���ٸ�ͨ������ɨ��ģʽ�£�д�κ�ֵ��ֻ������1��Ч���ѣ�
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	//����λ���룬ѡ���Ҷ��룬����ȡ��12λ������16λ�Ĵ�����ռ��12λ,���������ת�������ľ���ʵ�ʶ�ȡֵ
		//��ѡ������룬���൱�����Ҷ���Ļ���������4λ��ռ�Ĵ����ĸ�12λ
		//��ʱ��ȡ��������ʵ����ֵ��2��4�η�������8��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//�ⲿ����Դѡ�񣬼�ѡ�񴥷�ת����Դͷ����������������������������ⲿ��������ADC_ExternalTrigConv_None
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	//����ADCΪ��������ģʽ����ADC1��ADC2��ת�����Եģ��ò���������ֵ����˫ADCģʽ������ص�
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_Init(ADC1, &ADC_InitStructure);
	//����ADC���þ������
	
	//�����жϺͿ��ſ�������������������
	
	/***************����DMA*****************/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//Ҫ����������ַ��ע�⣬�����ַҲ����Ĵ�����ַ��ʵ�������������軹�ǼĴ������ǼĴ�����
		//�˴�DR��ADCת����ɺ�洢���������ݵĵط�
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
	//�������⴫�����ݵ����ݿ�ȣ�����ȡDR�Ĵ����ĵ�16λ���ݣ��ǰ���ֵĴ�С
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//�������ݰ��˺��Ƿ�ִ�е�ַ�������˴�����������ʼ����DR����һ���ط�ȡ���ݼ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//Ҫ����ļĴ�����ַ��ע�⣬�Ĵ�����ַҲ���������ַ��ʵ�������������軹�ǼĴ������ǼĴ�����
	//DMA_PeripheralBaseAddr��DMA_InitStructure.DMA_MemoryBaseAddr
	//����ֻ�Ǵ����վ�����ֶ���
		//��ADCת�����ݰ��˵�RAM�����ڴ�������н��д洢
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_TotalValue;
	//�Ĵ��������ݿ�ȣ�ͬDR�Ĵ���
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//�Ĵ������ݰ��˺��Ƿ�ִ�е�ַ��������Ҫ������ÿ���һ������Ųһ���洢��λ��
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//���ݴ��䷽��ָ������վ���ַ��Դ�˻���Ŀ�ĵأ�������ѡ��ΪԴ�ˣ������ݴ�����վ�㴫�䵽�Ĵ���վ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//���ݴ��������������16λ��ȡֵ��ΧΪ0~65535������ÿ����Ҫ����4������
	DMA_InitStructure.DMA_BufferSize = 40;//4
	//ѡ���Ƿ�Ϊ�Ĵ������Ĵ���������ת�ˣ���ѡ�����������Ӳ���������Ĵ������Ĵ�����������������������������һֱ������������������ô����ظ�������
	//����ѡ��Ӳ����������ADC���һ��ͨ��ת�˺�����DMA������DMA���ˣ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//��ADC��DMA��������ͨ������ADC��һ��ͨ��ת����ɺ�ͻ�����DMA����
	ADC_DMACmd(ADC1, ENABLE);
	//����������Ƿ��Զ���װ�����ڱ��������������������ѡ�������װѭ��ģʽ��
	//ѡ��ѭ��ģʽ������������Ϊ0ʱDMA�������Զ���װ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//DMA�������ȼ�,��ΪDMA������ϵ����ͨ��ֻ��1�������Ե��ж��DMAͨ����ת������ʱ
	//��Ҫ�����ȼ���������ͨ����ʹ��Ȩ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	//ѡ��DMA1��ͨ��1�����ڱ����������������ѡ���κε�ͨ������Դ��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	
	//��ʼ���������ú�DMA���ϣ�����û�а��˴����źţ�Ҳ�޷���ʼ���ˣ���ȴ�һ�����˴����ź�
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	//����ADC��Դ
	ADC_Cmd(ADC1, ENABLE);
	
	//������Դ�󣬸����ֲ�Ľ��飬���ǻ����ADC����У׼
	//��λУ׼��������ʼ��λУ׼
	ADC_ResetCalibration(ADC1);
	//��λУ׼��ɱ�־���������У׼����0��δ���У׼ʱΪ1��
		//���û��У׼�������ѭ����һֱ�ȴ�ֱ��У׼���
	while(ADC_GetResetCalibrationStatus(ADC1));
	//��ʼУ׼����������У׼
	ADC_StartCalibration(ADC1);
	//�ȴ�У׼��ɺ���
		//whileѭ��ԭ��ͬ�ϸ�while
	while(ADC_GetCalibrationStatus(ADC1));
	//����ADC��ʼת����һ��������ADC�ڴ������±�������ֹ�ؽ�������ת��
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
}
#if 0
void ADC_GetAverageValues(void) {
    uint32_t sum[4] = {0, 0, 0, 0};
    
    // ���
    for (int i = 0; i < 40; i++) {
        sum[i % 4] += AD_TotalValue[i];
    }
    
    // ����ƽ��ֵ
    for (int i = 0; i < 4; i++) {
        ADC_Value[i] = sum[i] / 10;
    }
}
#endif

void ADC_GetAverageValues(void) {
    uint32_t sum[4] = {0, 0, 0, 0};
    uint16_t max[4] = {0, 0, 0, 0};
    uint16_t min[4] = {65535, 65535, 65535, 65535};
    uint16_t count[4] = {0, 0, 0, 0};
    
    // �ҵ�ÿ��ͨ�������ֵ����Сֵ���������ܺ�
    for (int i = 0; i < 40; i++) {
        int channel = i % 4;
        uint16_t value = AD_TotalValue[i];
        sum[channel] += value;
        if (value > max[channel]) {
            max[channel] = value;
        }
        if (value < min[channel]) {
            min[channel] = value;
        }
        count[channel]++;
    }
    
    // ȥ�����ֵ����Сֵ�����¼����ܺ�
    for (int i = 0; i < 4; i++) {
        sum[i] -= max[i];
        sum[i] -= min[i];
        count[i] -= 2;  // ȥ��������ֵ�����Ч������
        if (count[i] > 0) {
            ADC_Value[i] = sum[i] / count[i];
        } else {
            ADC_Value[i] = 0;  // ��ֹ����0�����
        }
    }
}

void ADC1_GetValue(void)
{
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	ADC_GetAverageValues();	    
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
		 
	   for (int i = 0; i < 4; i++) {
		 ADC_Value[i] = initial_value + ADC_Value[i] - ADValue_offset[i];
        
		 }

	}


//�õ�ѹ��ֵ
float ADC1_MapValue(float OutputValue, float PositivePressure, float K_Value) 
{

    return (((OutputValue/4096*3.3 - PositivePressure) / K_Value)*10)+10.6;//������λԭ����KPa��*10���HPa,���ص�Դ +0.37��У0
	
}

/*--------------------------------��Դ��ѹ����----------------------------------*/
void ADC2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  ADC_InitTypeDef  ADC_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2|RCC_APB2Periph_GPIOB, ENABLE);//��ʱ��
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCʱ�ӷ�Ƶ

  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AIN;	//ģ������
  GPIO_InitStruct.GPIO_Pin  =GPIO_Pin_5;     	//��������	PB0	ϵͳ����(6V)������
  GPIO_Init(GPIOA, &GPIO_InitStruct);         //��ʼ��

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

u16 ADC2_GetValue(u8 channel)//ch5
{
  ADC_RegularChannelConfig(ADC2, channel, 1, ADC_SampleTime_239Cycles5);
  ADC_SoftwareStartConvCmd(ADC2, ENABLE);//�������ת��
  ADC_Cmd(ADC2, ENABLE);
  while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));//�ȴ�ת������
  return ADC_GetConversionValue(ADC2);
}
/*************************************************************************
�������ܣ���ȡADC1��ͨ��x��ֵ����10��ƽ���˲�
��ڲ���1��Channel���ɼ���ͨ����0~17 
��ڲ���2��
����ֵ������ƽ���˲�ֵ
˵�������ֵ������12λ--4095
*************************************************************************/
u16 Get_ADC2_ChannelAverage(u8 Channel)
{
		int i;
		u32 sum=0;
		for(i=0;i<10;i++)   //�ɼ�10��
		{
			sum+=ADC2_GetValue(Channel);
		}
		sum/=10;  //��ƽ��

		return   sum;   //����ƽ���˲�ֵ
}

#if 0
float ADC2_array_sort(uint16_t *ACD2_array, uint8_t Array_size)
{
    float return_value;
    uint16_t array_temp[16];
    uint32_t temp_array;
    uint8_t i, j;

    for (i = 0; i < Array_size; i++)
        array_temp[i] = ACD2_array[i];

    for (i = 0; i < Array_size; i++)
    {
        for (j = 0; j < (Array_size - 1); j++)
        {
            if (array_temp[j] > array_temp[1 + j])
            {
                temp_array = array_temp[j];
                array_temp[j] = array_temp[1 + j];
                array_temp[1 + j] = temp_array;
            }
        }
    }
}
#endif 
/*--------------------------------��Դ��ѹ����----------------------------------*/
