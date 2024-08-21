#include "digit.h"
#include "display.h"
#include "LCD_HT1623.h"
#include "usart.h"
#include "includes.h"
#include "key_handler.h"


extern int settings_mode;
extern Settings current_settings;

// 数码管段映射，作用于四个缸压力值数码段
const uint8_t segment_map[] = {
        Group6_digitron_Data_A + Group6_digitron_Data_B + Group6_digitron_Data_C + Group6_digitron_Data_D + Group6_digitron_Data_F + Group6_digitron_Data_E, // 0
        Group6_digitron_Data_B + Group6_digitron_Data_C, // 1
        Group6_digitron_Data_D + Group6_digitron_Data_G + Group6_digitron_Data_E + Group6_digitron_Data_A + Group6_digitron_Data_B,		//2
		Group6_digitron_Data_G + Group6_digitron_Data_D + Group6_digitron_Data_A + Group6_digitron_Data_B + Group6_digitron_Data_C,        //3                    		
		Group6_digitron_Data_C + Group6_digitron_Data_B + Group6_digitron_Data_F +Group6_digitron_Data_G,    		        //4
		Group6_digitron_Data_A + Group6_digitron_Data_C + Group6_digitron_Data_F + Group6_digitron_Data_D + Group6_digitron_Data_G,        //5
		Group6_digitron_Data_A + Group6_digitron_Data_C + Group6_digitron_Data_F + Group6_digitron_Data_G + Group6_digitron_Data_E + Group6_digitron_Data_D,   //6
		Group6_digitron_Data_A + Group6_digitron_Data_B + Group6_digitron_Data_C,			                     //7
		Group6_digitron_Data_F + Group6_digitron_Data_G + Group6_digitron_Data_E + Group6_digitron_Data_D + Group6_digitron_Data_A + Group6_digitron_Data_B + Group6_digitron_Data_C,   //8
		Group6_digitron_Data_A + Group6_digitron_Data_B + Group6_digitron_Data_C + Group6_digitron_Data_D + Group6_digitron_Data_F + Group6_digitron_Data_G,    //9		        
		SEGOK_OFF                         			//清显示
};
// 数码管段映射，作用于TIME时钟
const uint8_t TIMEsegment_map[] = { //6,7,8数码管
        Group2_digitron_Data_A + Group2_digitron_Data_B + Group2_digitron_Data_C + Group2_digitron_Data_D + Group2_digitron_Data_F + Group2_digitron_Data_E, // 0
        Group2_digitron_Data_B + Group2_digitron_Data_C, // 
        Group2_digitron_Data_D + Group2_digitron_Data_G + Group2_digitron_Data_E + Group2_digitron_Data_A + Group2_digitron_Data_B,		//2
		Group2_digitron_Data_G + Group2_digitron_Data_D + Group2_digitron_Data_A + Group2_digitron_Data_B + Group2_digitron_Data_C,        //3                    		
		Group2_digitron_Data_C + Group2_digitron_Data_B + Group2_digitron_Data_F + Group2_digitron_Data_G,    		        //4
		Group2_digitron_Data_A + Group2_digitron_Data_C + Group2_digitron_Data_F + Group2_digitron_Data_D + Group2_digitron_Data_G,        //5
		Group2_digitron_Data_A + Group2_digitron_Data_C + Group2_digitron_Data_F + Group2_digitron_Data_G + Group2_digitron_Data_E + Group2_digitron_Data_D,   //6
		Group2_digitron_Data_A + Group2_digitron_Data_B + Group2_digitron_Data_C,			                     //7
		Group2_digitron_Data_F + Group2_digitron_Data_G + Group2_digitron_Data_E + Group2_digitron_Data_D + Group2_digitron_Data_A + Group2_digitron_Data_B + Group2_digitron_Data_C,   //8
		Group2_digitron_Data_A + Group2_digitron_Data_B + Group2_digitron_Data_C + Group2_digitron_Data_D + Group2_digitron_Data_F + Group2_digitron_Data_G,    //9		        
		SEGOK_OFF                         			//清显示
};
/*-------------------------------------------刷新函数--------------------------------------------------*/
void ClearDigitalTubeDisplay(void)//清除四缸数码段，起刷新作用
{
    for (uint8_t i = 1; i <= 20; i++) {
        Digital_tube_Bit_Display(-1, i);
    }
}

void ClearMercuryDisplay(void)//清除四缸汞柱格数，起刷新作用
{
    for (uint8_t i = 0; i <= 4; i++) {
        UpdateReadModifyWriteDisplay( i,0xff,0);
    }

         UpdateReadModifyWriteDisplay(12,0xff,0);	 //数码管编码汞柱编号刷新
         UpdateReadModifyWriteDisplay(23,Mercury_4_Data_K4,0);	 //4号汞柱编号刷新
         UpdateReadModifyWriteDisplay(0,0xff,0);	 //4号汞柱格数刷新
         ClearDigitalTubeDisplay(); // 每次切换单位之前清除显示内容
}

/*-------------------------------------------刷新函数--------------------------------------------------*/
void Digital_tube_Bit_Display(int num, uint8_t position)//将 num 参数类型从无符号整数（uint32_t）修改为有符号整数（int32_t），并处理负值情况。
{
	uint8_t segment_data,TIMEsegment_data;

     if (num == -1) {
        segment_data = 0x00; // 清除显示内容
    } else {
    if (num > 9) return; // 处理非法输入
    segment_data = segment_map[num]; // 从映射表中获取段码
    TIMEsegment_data = TIMEsegment_map[num]; // 从映射表中获取段码
    }
		switch (position)//1-4号缸
    {	
        //1号缸
        case 1: W1623_LowerbyteMyriabit(D42, segment_data); break; // 万位		
        case 2: W1623_Lowerbyte(D40, segment_data); break; // 千位
        case 3: W1623_Lowerbyte(D38, segment_data); break; // 百位
        case 4: W1623_Lowerbyte(D36, segment_data); break; // 十位
        case 5: W1623_Lowerbyte(D34, segment_data); break; // 个位
        //2号缸
        case 6: W1623_byteMyriabit(D42, segment_data); break; // 万位
        case 7: W1623_byte(D40, segment_data); break; // 千位
        case 8: W1623_byte(D38, segment_data); break; // 百位
        case 9: W1623_byte(D36, segment_data); break; // 十位
        case 10: W1623_byte(D34, segment_data); break; // 个位
        //3号缸
        case 11: W1623_Lowerbyte(D32, segment_data); break; // 万位
        case 12: W1623_Lowerbyte(D30, segment_data); break; // 千位
        case 13: W1623_Lowerbyte(D28, segment_data); break; // 百位
        case 14: W1623_Lowerbyte(D26, segment_data); break; // 十位
        case 15: W1623_Lowerbyte(D24, segment_data); break; // 个位
        //4号缸
		case 16: W1623_byte(D32, segment_data); break; // 万位	
        case 17: W1623_byte(D30, segment_data); break; // 千位
        case 18: W1623_byte(D28, segment_data); break; // 百位
        case 19: W1623_byte(D26, segment_data); break; // 十位
        case 20: W1623_byte(D24, segment_data); break; // 个位
         default:break; // 处理非法位置
    }
#if 1
    switch (position)//MAX与MIN比较数码段显示
    {
		case 21: W1623_Lowerbyte(7, TIMEsegment_data); break; // 万位
        case 22: W1623_Lowerbyte(5, TIMEsegment_data); break; // 千位
        case 23: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // 百位
        case 24: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // 十位
        case 25: W1623_TIMELowerbyte(21, TIMEsegment_data); break; // 个位
         default:break; // 处理非法位置
    }
#endif	

#if 0
    switch (position)//转速显示数码段
    {
		case 26: W1623_TIMELowerbyte(9, TIMEsegment_data); break; // 万位	
        case 27: W1623_Lowerbyte(7, TIMEsegment_data); break;       // 千位
        case 28: W1623_TIMELowerbyte(5, TIMEsegment_data); break; // 百位
        case 29: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // 十位
        case 30: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // 个位
         default:				
				break; // 处理非法位置
    }
#endif	

}

void mercury_display(u8 addr_1, u16 AD_MercuryValue)//进度条格数按AD值来判断
{    

     uint8_t SEG_addr1,SEG_addr2;
     u16 mercury_data1,mercury_data2;
     
/*-------------------------------------------------汞柱显示判断----------------------------------------------*/       
   if(addr_1==1)
   {
       UpdateReadModifyWriteDisplay(12,Mercury_1_Data_K1,1);	 //1号汞柱
       SEG_addr1 = 3;SEG_addr2 = 4;
       mercury_data1 = Mercury_1_Data_Grid9;mercury_data2 = Mercury_1_Data_Grid10;
   }
     if(addr_1==6)
    {
        UpdateReadModifyWriteDisplay(12,Mercury_2_Data_K2,1);	 //2号汞柱
        SEG_addr1 = 2;SEG_addr2 = 4;
        mercury_data1 = Mercury_2_Data_Grid9;mercury_data2 = Mercury_2_Data_Grid10;
    }
    
     if(addr_1==11)
   {
       UpdateReadModifyWriteDisplay(12,Mercury_3_Data_K3,1);	 //3号汞柱
       SEG_addr1 = 1;SEG_addr2 = 4;
       mercury_data1 = Mercury_3_Data_Grid9;mercury_data2 = Mercury_3_Data_Grid10;
   }
    if(addr_1==16)
   {
       UpdateReadModifyWriteDisplay(23,Mercury_4_Data_K4,1);	 //4号汞柱
       SEG_addr1 = 0;SEG_addr2 = 4;
       mercury_data1 = Mercury_4_Data_Grid9;mercury_data2 = Mercury_4_Data_Grid10;
   }
   //刷新汞柱
    UpdateReadModifyWriteDisplay(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6 + Mercury_1_Data_Grid7 + Mercury_1_Data_Grid8,0);
    UpdateReadModifyWriteDisplay(SEG_addr2,mercury_data1+mercury_data2,0);//清9格跟10格显示，
/*-------------------------------------------------格数按AD值来判断----------------------------------------------*/
   if (AD_MercuryValue >= 1638 && AD_MercuryValue < 1900) {        
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1); // 第一格
    } else if (AD_MercuryValue >= 1481 && AD_MercuryValue < 1638) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2);      
    } else if (AD_MercuryValue >= 1324 && AD_MercuryValue < 1481) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3);       
    } else if (AD_MercuryValue >= 1167 && AD_MercuryValue < 1324) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4);
    } else if (AD_MercuryValue >= 1010 && AD_MercuryValue < 1167) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5);       
    } else if (AD_MercuryValue >= 853 && AD_MercuryValue < 1010) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6);           
    } else if (AD_MercuryValue >= 696 && AD_MercuryValue < 853) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6 + Mercury_1_Data_Grid7);
    } else if (AD_MercuryValue >= 593 && AD_MercuryValue < 696) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6 + Mercury_1_Data_Grid7 + Mercury_1_Data_Grid8);        
    } else if (AD_MercuryValue >= 382 && AD_MercuryValue < 593) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6 + Mercury_1_Data_Grid7 + Mercury_1_Data_Grid8);
    } else if (AD_MercuryValue >= 100 && AD_MercuryValue < 382) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6 + Mercury_1_Data_Grid7 + Mercury_1_Data_Grid8);
        UpdateReadModifyWriteDisplay(SEG_addr2,mercury_data1+mercury_data2,1);
    }
      
}

// void UpdateDecimalPoint(u8 addr, u8 highByte, u8 lowByte, u8 highMask, u8 lowMask)
// {
//     switch (addr) {
//         case 1:
//             UpdateReadModifyWriteDisplay(highByte, highMask, 1); // 1号缸小数点
//             break;
//         case 6:
//             UpdateReadModifyWriteDisplay(highByte, lowMask, 1); // 2号缸小数点
//             break;
//         case 11:
//             UpdateReadModifyWriteDisplay(lowByte, highMask, 1); // 3号缸小数点
//             break;
//         case 16:
//             UpdateReadModifyWriteDisplay(lowByte, lowMask, 1); // 4号缸小数点
//             break;
//     }
// }

// 数码管显示函数
void Digital_tube_display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,float display_num,u16 AD_MercuryValue)//待优化，只需一个地址参数追踪即可
{
	if(!settings_mode){
    mercury_display(addr_1,AD_MercuryValue);//汞柱显示
    }
   switch (addr_1) {
        case 1:
            UpdateReadModifyWriteDisplay(12, 0x08, 1); // 写入缸号1
            
            break;
        case 6:
            UpdateReadModifyWriteDisplay(12, 0x04, 1); // 写入缸号2
            break;
        case 11:
            UpdateReadModifyWriteDisplay(12, 0x02, 1); // 写入缸号3
            break;
        case 16:
            UpdateReadModifyWriteDisplay(12, 0x01, 1); // 写入缸号4
            break;
        case 21:
            UpdateReadModifyWriteDisplay(11, Screen_Data_MIN + Screen_Data_MAX, 1); // MIN与MAX图标显示
            break;
    }

    if (display_num < 0) {
        display_num = -display_num; // 转换为正数
    }
    if (display_num >= 10000 && display_num < 100000)//超过10000则显示不了
    {
      Digital_tube_Bit_Display((uint32_t)display_num%100000/10000,addr_1);
      Digital_tube_Bit_Display((uint32_t)display_num%10000/1000,addr_2);    
      Digital_tube_Bit_Display((uint32_t)display_num%1000/100,addr_3);     
      Digital_tube_Bit_Display((uint32_t)display_num%100/10,addr_4);     
      Digital_tube_Bit_Display((uint32_t)display_num%10/1,addr_5);
        
    }
    else if (display_num >= 1000 && display_num < 10000)//超过10000则显示不了
    {
        
      Digital_tube_Bit_Display((uint32_t)display_num%10000/1000,addr_2);
      Digital_tube_Bit_Display((uint32_t)display_num%1000/100,addr_3);
      Digital_tube_Bit_Display((uint32_t)display_num%100/10,addr_4);
      Digital_tube_Bit_Display((uint32_t)display_num%10/1,addr_5);
       
    }
    else if (display_num >= 100 && display_num < 1000)
    {
      Digital_tube_Bit_Display((uint32_t)display_num%1000/100,addr_3); 
      Digital_tube_Bit_Display((uint32_t)display_num%100/10,addr_4);
      Digital_tube_Bit_Display((uint32_t)display_num%10/1,addr_5);
      //Digital_tube_Bit_Display((uint32_t)(display_num*10)%10,addr_5);//一位小数点
 
    //UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01);
    }
    else if (display_num >= 10 && display_num < 100)
    {
    
      Digital_tube_Bit_Display((uint32_t)(display_num)%100/10,addr_4);
      Digital_tube_Bit_Display((uint32_t)(display_num)%10,addr_5);
    //UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01);
    }
		else if (display_num >= 0 && display_num < 10)
    {
    
      Digital_tube_Bit_Display((uint32_t)(display_num*100)%10,addr_5);
       //UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); 
    }
}
/*-----------------------------------测试需优化------------------------------------*/
void Dsp_RUN_Mode(void);

extern uint16_t ADC_Value[4];
float pressure[4];

//u8 Rec_Data_Display;

// 处理并显示压力值
void ProcessAndDisplayPressureValues( float PositivePressure, float K_Value)
 {
    int i;
	//float pressure[4];
	
    // 将ADC值映射到压力值   
    for (i = 0; i < 4; i++) {
        pressure[i] = ADC1_MapValue((float)ADC_Value[i], PositivePressure, K_Value);
    }
  
#if 0
    // 打印压力值
    printf("-----------------------PressureValue---------------------- \r\n");
    for (i = 0; i < 4; i++) {
        printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], pressure[i]);
    }
#endif 
    Dsp_RUN_Mode();
    
    //Digital_tube_display(21, 22, 23, 24, 25, -8532, ADC_Value[0]);//最大最小值的显示数码段
	delay_ms(500);
}
float convertedPressure[4];
extern u8 Zero_flag;
void Dsp_RUN_Mode(void)
{
    //float convertedPressure[4];  
    UpdateReadModifyWriteDisplay(22, 0x3f, 0); // 清除显示内容     
    UpdateReadModifyWriteDisplay(23, 0x3f, 0); // 清除显示内容  
    
    //printf("%d  , %d  ",current_settings.current_unit,current_settings.sensor_count);
    switch(current_settings.current_unit)
    {
        case 0: // Pa
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_pa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 100;
            }
            break;

        case 1: // kPa   需要1个小数点
            UpdateReadModifyWriteDisplay(22, 0x30, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.1;
            }
            break;

        case 2: // mmHg
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.750062;
            }
            break;

        case 3: // Torr    这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.750062;
            }
            break;

        case 4: // mbar
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i];
            }
            break;

        case 5: // inHg
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.0295301;
            }
            break;

        case 6: // inH2O    这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.401463;
            }
            break;

        case 7: // mmH2O    这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 10.1972;
            }
            break;

        case 8: // psi  需要2个小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.0145038;
            }
            break;

        case 9: // hPa
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i];
            }
            break;
    }
    
        //检查 Rec_Data_Display_Num 是否为非零值。如果为非零值，则表示我们需要使用存储在数组 DATA_ADC1、DATA_ADC2 和 DATA_ADC_DIF 中的历史记录数据来进行显示。				
        // 显示转换后的压力值
        
        
        if (current_settings.sensor_count == 0) {
            UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);   //2T
            UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 1);   //4T
            if(!settings_mode){
            ClearDigitalTubeDisplay(); 
            if(Zero_flag ==1){
                    //Zero_flag = 0;
                    Dig_Zero(); 
                    
  
                }
            Digital_tube_display(1, 2, 3, 4, 5, convertedPressure[0], ADC_Value[0]);
            Digital_tube_display(6, 7, 8, 9, 10, convertedPressure[1], ADC_Value[1]);
            if(Zero_flag ==1){
                    Zero_flag = 0;
                    ADC_Value[2] = 1800; 
                    ADC_Value[3] = 1800;
            }
            Digital_tube_display(11, 12, 13, 14, 15, convertedPressure[2], ADC_Value[2]);
            Digital_tube_display(16, 17, 18, 19, 20, convertedPressure[3], ADC_Value[3]);
            }
        }
      
        if (current_settings.sensor_count == 1) {
             UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   //4T
             UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 1);   //2T
            if(!settings_mode){
            ClearDigitalTubeDisplay(); 
            if(Zero_flag ==1){
                    Zero_flag = 0;
                    Dig_Zero(); 
                }
            Digital_tube_display(1, 2, 3, 4, 5, convertedPressure[0], ADC_Value[0]);
            Digital_tube_display(6, 7, 8, 9, 10, convertedPressure[1], ADC_Value[1]);
             }

        }

 

}



/*-----------------------------------测试需优化------------------------------------*/

/*----------------------------------电子时钟显示模块-------------------------------------*/
extern u8 Second,Minute,Hour;//秒、分、时
// 电子时钟处理时间值
void TIME_Digital_tube_Bit_Display(uint32_t Timnum, uint8_t Timposition)
{
	uint8_t TIMEsegment_data;
    if (Timnum > 9) return; // 处理非法输入

    TIMEsegment_data = TIMEsegment_map[Timnum]; // 从映射表中获取段码

    switch (Timposition)//时间，电子时钟
    {			
        case 1: W1623_Lowerbyte(9, TIMEsegment_data); break; // 时十位
        case 2: W1623_Lowerbyte(7, TIMEsegment_data); break; // 时个位
        case 3: W1623_Lowerbyte(5, TIMEsegment_data); break; // 分十位
        case 4: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // 分个位
        case 5: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // 秒十位
        case 6: W1623_TIMELowerbyte(21, TIMEsegment_data); break; // 秒个位
        default:break; // 处理非法位置
    }
}

//电子时钟 处理并显示时间值
void Clock_Display(void)//时间，电子时钟
{
    UpdateReadModifyWriteDisplay(11,Screen_Data_Time,1);//TIME图标显示   
    TIME_Digital_tube_Bit_Display(Hour / 10, 1);   
    TIME_Digital_tube_Bit_Display(Hour % 10, 2);
    UpdateReadModifyWriteDisplay(10,Group2_digitron_TIME_colon_S32,1);//冒号1显示   
    TIME_Digital_tube_Bit_Display(Minute / 10, 3);
    TIME_Digital_tube_Bit_Display(Minute % 10, 4);
    UpdateReadModifyWriteDisplay(22,Group2_digitron_TIME_colon_S38,1);//冒号2显示
    TIME_Digital_tube_Bit_Display(Second / 10, 5);
    TIME_Digital_tube_Bit_Display(Second % 10, 6);

}
/*----------------------------------电子时钟显示模块-------------------------------------*/

/*----------------------------------电源检测显示模块-------------------------------------*/
// 计算实际电池电压的函数
float calculateBatteryVoltage(int channel) {
    // 获取指定通道的ADC平均值
    int Adc_Data = Get_ADC2_ChannelAverage(channel);
    //printf("Adc_Data = %d\n", Adc_Data);
    // 计算分压后的电压，假设ADC参考电压为3.3V
    float Vout = (Adc_Data / 4095.0) * 3.3;    
    // 计算实际的电池电压
    float Vin = Vout * ((120.0 + 72.0) / 72.0); // R23 = 120K, R26 = 72K，Vin =Vout * ((120.0 + 72.0) / 72.0)
    // 输出计算结果
    // printf("ADC2_Channel%d = %d | %f\n", channel, Adc_Data, Vout);
    // printf("实际电压 = %.2f V\n", Vin);
    UpdateReadModifyWriteDisplay(14,Battery_Data_S5+Battery_Data_S1+Battery_Data_S2+Battery_Data_S3+Battery_Data_S4,0); //刷新电池个数显示 
/*----------------------------------------显示-------------------------------------------*/
        if(Adc_Data<1800)//低于4V
		{
			UpdateReadModifyWriteDisplay(14,Battery_Data_S5,1);  
            delay_ms(200);
            UpdateReadModifyWriteDisplay(14,Battery_Data_S5,0); 
            delay_ms(200);
		}
		if((Adc_Data>1800)&&(Adc_Data<2000))//4V
		{
           
			UpdateReadModifyWriteDisplay(14,Battery_Data_S5,1);  
		}
		if((Adc_Data>2000)&&(Adc_Data<2200))//4.5V
		{
            
			UpdateReadModifyWriteDisplay(14,Battery_Data_S5+Battery_Data_S1,1);  
		}
		if((Adc_Data>2200)&&(Adc_Data<2500))//5.0V
		{
            
			UpdateReadModifyWriteDisplay(14,Battery_Data_S5+Battery_Data_S1+Battery_Data_S2,1);  
		}
        if((Adc_Data>2500)&&(Adc_Data<2700))//5.5V
		{
             
			UpdateReadModifyWriteDisplay(14,Battery_Data_S5+Battery_Data_S1+Battery_Data_S2+Battery_Data_S3,1);  
		}
		if(Adc_Data>2700)//6.0V
		{
            
			UpdateReadModifyWriteDisplay(14,Battery_Data_S5+Battery_Data_S1+Battery_Data_S2+Battery_Data_S3+Battery_Data_S4,1);  
		}



    return Vin;
}


/*----------------------------------电源检测显示模块-------------------------------------*/


/*----------------------------------P=0-------------------------------------*/
void	Dig_Zero(void)
{
    
	//四缸压力值、汞柱、时间 = 0；
    Second =0;Minute=0;Hour=0;
    ADC_Value[0] = 1800;
    ADC_Value[1] = 1800; 
    ADC_Value[2] = 1800; 
    ADC_Value[3] = 1800;
    
    convertedPressure[0] = 0;convertedPressure[1] = 0;convertedPressure[2] = 0;convertedPressure[3] = 0;

}

//P = 0 自动校0,压力归零
void Calibration(void){
    UpdateReadModifyWriteDisplay(15,Screen_Data_S23,1);
    UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_1+ProgressBlock_Data_2,1);
    delay_ms(500);   
    UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_3+ProgressBlock_Data_4,1);
    delay_ms(500);   
    UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_5+ProgressBlock_Data_6,1);
    delay_ms(500);   
    UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_7+ProgressBlock_Data_8,1);
    delay_ms(500);  
    UpdateReadModifyWriteDisplay(15,Screen_Data_S23,0);
    UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_1+ProgressBlock_Data_2+ProgressBlock_Data_3+ProgressBlock_Data_4,0);
    UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_5+ProgressBlock_Data_6+ProgressBlock_Data_7+ProgressBlock_Data_8,0);
}


/*----------------------------------P=0-------------------------------------*/