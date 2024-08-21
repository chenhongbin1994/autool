#include "adc.h"
#include "delay.h"
#include "usart.h"
//这个数组是存储在RAM运行内存中的，用于存储DMA从ADC-DR中搬运出来的ADC转换值
//求4个通道平均值AD_TotalValue[40]，存到ADC_Value[4]里面
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
	
	//配置IO口为模拟输入模式,该模式是ADC的专属模式
	//该模式下IO口是无效的，防止IO口的输入输出对模拟电压造成干扰
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_InitStructure);
	//以上代码配置完，IO口就被配置为模拟输入的引脚了
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	
	//配置ADC时钟为RCC的6分频即12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//选择规则组的输入通道
		//选择通道0，排序第1，采用时间为55.5个ADCCLK周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
		//若写入其他通道进序列
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);	
	
	
	//本次程序的代码用的是单次转换，扫描模式
	//连续转换模式配置
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//扫描模式配置
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	//通道数目配置，指定在【扫描模式】下总共需要扫描前多少个通道（非扫描模式下，写任何值都只有序列1有效而已）
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	//数据位对齐，选择右对齐，即读取的12位数据在16位寄存器中占后12位,这种情况下转换出来的就是实际读取值
		//若选择左对齐，则相当于在右对齐的基础上左移4位，占寄存器的高12位
		//此时读取的数据是实际数值的2的4次方倍，即8倍
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//外部触发源选择，即选择触发转换的源头，本程序我们用软件触发，不需外部触发，填ADC_ExternalTrigConv_None
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	//配置ADC为独立工作模式，即ADC1和ADC2各转换各自的，该参数的其他值则是双ADC模式配置相关的
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_Init(ADC1, &ADC_InitStructure);
	//至此ADC配置就完成了
	
	//若需中断和看门口则可以在下面继续配置
	
	/***************配置DMA*****************/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//要运输的外设地址（注意，外设地址也可填寄存器地址，实际上无论是外设还是寄存器都是寄存器）
		//此处DR是ADC转换完成后存储规则组数据的地方
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
	//外设向外传输数据的数据宽度，我们取DR寄存器的低16位数据，是半个字的大小
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//外设数据搬运后是否执行地址自增，此处无需自增，始终在DR的这一个地方取数据即可
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//要运输的寄存器地址（注意，寄存器地址也可填外设地址，实际上无论是外设还是寄存器都是寄存器）
	//DMA_PeripheralBaseAddr、DMA_InitStructure.DMA_MemoryBaseAddr
	//他们只是传输的站点名字而已
		//将ADC转换数据搬运到RAM运行内存的数组中进行存储
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_TotalValue;
	//寄存器的数据宽度，同DR寄存器
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//寄存器数据搬运后是否执行地址自增，需要自增，每获得一个数据挪一个存储的位置
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//数据传输方向，指定外设站点地址是源端还是目的地，本程序选择为源端，即数据从外设站点传输到寄存器站点
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//数据传输计数器，其是16位，取值范围为0~65535，这里每次需要搬运4个数据
	DMA_InitStructure.DMA_BufferSize = 40;//4
	//选择是否为寄存器到寄存器的数据转运，即选择软件触发或硬件触发，寄存器到寄存器就是软件触发（软件触发条件下一直会有软件触发，无须用代码重复触发）
	//这里选择硬件触发，由ADC完成一个通道转运后申请DMA（触发DMA搬运）
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//打开ADC对DMA搬运申请通道，当ADC的一个通道转换完成后就会申请DMA搬运
	ADC_DMACmd(ADC1, ENABLE);
	//传输计数器是否自动重装，由于本程序是软件触发，不可选择这个重装循环模式，
	//选择循环模式，当计数器减为0时DMA计数器自动重装
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//DMA请求优先级,因为DMA对外联系的总通道只有1个，所以当有多个DMA通道有转运需求时
	//需要有优先级来分配总通道的使用权限
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	//选择DMA1，通道1，由于本程序是软件触发，选择任何的通道都开源）
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	
	//初始化函数调用后，DMA马上，但若没有搬运触发信号，也无法开始搬运，需等待一个搬运触发信号
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	//开启ADC电源
	ADC_Cmd(ADC1, ENABLE);
	
	//开启电源后，根据手册的建议，我们还需对ADC进行校准
	//复位校准函数，开始复位校准
	ADC_ResetCalibration(ADC1);
	//复位校准完成标志函数（完成校准返回0，未完成校准时为1）
		//如果没有校准完成则在循环中一直等待直到校准完成
	while(ADC_GetResetCalibrationStatus(ADC1));
	//开始校准函数，启动校准
	ADC_StartCalibration(ADC1);
	//等待校准完成函数
		//while循环原理同上个while
	while(ADC_GetCalibrationStatus(ADC1));
	//触发ADC开始转换，一经触发，ADC在此配置下便永无休止地进行连续转换
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
}
#if 0
void ADC_GetAverageValues(void) {
    uint32_t sum[4] = {0, 0, 0, 0};
    
    // 求和
    for (int i = 0; i < 40; i++) {
        sum[i % 4] += AD_TotalValue[i];
    }
    
    // 计算平均值
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
    
    // 找到每个通道的最大值和最小值，并计算总和
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
    
    // 去掉最大值和最小值后重新计算总和
    for (int i = 0; i < 4; i++) {
        sum[i] -= max[i];
        sum[i] -= min[i];
        count[i] -= 2;  // 去掉两个极值后的有效样本数
        if (count[i] > 0) {
            ADC_Value[i] = sum[i] / count[i];
        } else {
            ADC_Value[i] = 0;  // 防止除以0的情况
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


//得到压力值
float ADC1_MapValue(float OutputValue, float PositivePressure, float K_Value) 
{

    return (((OutputValue/4096*3.3 - PositivePressure) / K_Value)*10)+10.6;//基本单位原本是KPa加*10变成HPa,插电池电源 +0.37是校0
	
}

/*--------------------------------电源电压管理----------------------------------*/
void ADC2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  ADC_InitTypeDef  ADC_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2|RCC_APB2Periph_GPIOB, ENABLE);//开时钟
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC时钟分频

  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AIN;	//模拟输入
  GPIO_InitStruct.GPIO_Pin  =GPIO_Pin_5;     	//设置引脚	PB0	系统供电(6V)采样脚
  GPIO_Init(GPIOA, &GPIO_InitStruct);         //初始化

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

u16 ADC2_GetValue(u8 channel)//ch5
{
  ADC_RegularChannelConfig(ADC2, channel, 1, ADC_SampleTime_239Cycles5);
  ADC_SoftwareStartConvCmd(ADC2, ENABLE);//启动软件转换
  ADC_Cmd(ADC2, ENABLE);
  while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));//等待转换结束
  return ADC_GetConversionValue(ADC2);
}
/*************************************************************************
函数功能：读取ADC1的通道x的值进行10次平均滤波
入口参数1：Channel：采集的通道：0~17 
入口参数2：
返回值：返回平均滤波值
说明：最大值不超过12位--4095
*************************************************************************/
u16 Get_ADC2_ChannelAverage(u8 Channel)
{
		int i;
		u32 sum=0;
		for(i=0;i<10;i++)   //采集10次
		{
			sum+=ADC2_GetValue(Channel);
		}
		sum/=10;  //求平均

		return   sum;   //返回平均滤波值
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
/*--------------------------------电源电压管理----------------------------------*/
