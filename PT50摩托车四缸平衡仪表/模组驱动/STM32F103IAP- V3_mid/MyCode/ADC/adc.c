 #include "adc.h"
 #include "delay.h"

	   
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc1_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

//	//PA2 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//DISABLE：单通道模式；ENABLE多通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//DISABLE：模数转换工作在单次转换模式；ENABLE连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 3;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  

//ch:通道值 0~3
//获取单次ADC值
u16 ADC1_Mid_GetValue(u8 channel)   //ch:选择通道如ADC_Channel_0
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

// 获取指定通道的平均ADC值
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
3.3V 供电:(0.2~2.7V)
压力=(输出值-1.45)/K

         K 值 VS 压力量程
量程 (kPa)        3.3（V）    5（V）
-100~100             0.0125        0.02
*/
float ADC1_Mid_MapValue(float OutputValue, float PositivePressure, float K_Value) 
{
   return (OutputValue/4096*3.3 - PositivePressure) / K_Value;
}

#if 1
/*--------------------------------电源电压管理----------------------------------*/
void Adc2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef  ADC_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2|RCC_APB2Periph_GPIOB, ENABLE);//开时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC时钟分频
	
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AIN;	//模拟输入
    GPIO_InitStruct.GPIO_Pin  =GPIO_Pin_0;     	//设置引脚	PB0	系统供电(6V)采样脚
    GPIO_Init(GPIOB, &GPIO_InitStruct);         //初始化
	
//	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AIN;	//模拟输入
//    GPIO_InitStruct.GPIO_Pin  =GPIO_Pin_4;     	//设置引脚	PC4 纽扣电池采样脚
//    GPIO_Init(GPIOC, &GPIO_InitStruct);         //初始化

	ADC_InitStruct.ADC_ContinuousConvMode= DISABLE;//单次转换
	ADC_InitStruct.ADC_DataAlign         = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_Mode              = ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_ScanConvMode      = DISABLE;//非扫描
	ADC_InitStruct.ADC_NbrOfChannel      = 1;//单通道切换
	ADC_InitStruct.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None;//软件
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC2, ENABLE);
	ADC_ResetCalibration(ADC2);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC2));//等待复位完成
	ADC_StartCalibration(ADC2);  //开启校准
	while(ADC_GetCalibrationStatus(ADC2));//等待校准结束
}


u16 ADC2_Mid_GetValue(u8 channel)
{
    ADC_RegularChannelConfig(ADC2, channel, 1, ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);//启动软件转换
	ADC_Cmd(ADC2, ENABLE);
    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));//等待转换结束
	return ADC_GetConversionValue(ADC2);
}

/*--------------------------------电源电压管理----------------------------------*/
#endif





















