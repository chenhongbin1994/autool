#include "digit.h"
#include "display.h"
#include "LCD_HT1623.h"
#include "usart.h"
#include "includes.h"
#include "key_handler.h"


extern int settings_mode;
extern Settings current_settings;

// ����ܶ�ӳ�䣬�������ĸ���ѹ��ֵ�����
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
		SEGOK_OFF                         			//����ʾ
};
// ����ܶ�ӳ�䣬������TIMEʱ��
const uint8_t TIMEsegment_map[] = { //6,7,8�����
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
		SEGOK_OFF                         			//����ʾ
};
/*-------------------------------------------ˢ�º���--------------------------------------------------*/
void ClearDigitalTubeDisplay(void)//����ĸ�����Σ���ˢ������
{
    for (uint8_t i = 1; i <= 20; i++) {
        Digital_tube_Bit_Display(-1, i);
    }
}

void ClearMercuryDisplay(void)//����ĸ׹�����������ˢ������
{
    for (uint8_t i = 0; i <= 4; i++) {
        UpdateReadModifyWriteDisplay( i,0xff,0);
    }

         UpdateReadModifyWriteDisplay(12,0xff,0);	 //����ܱ��빯�����ˢ��
         UpdateReadModifyWriteDisplay(23,Mercury_4_Data_K4,0);	 //4�Ź������ˢ��
         UpdateReadModifyWriteDisplay(0,0xff,0);	 //4�Ź�������ˢ��
         ClearDigitalTubeDisplay(); // ÿ���л���λ֮ǰ�����ʾ����
}

/*-------------------------------------------ˢ�º���--------------------------------------------------*/
void Digital_tube_Bit_Display(int num, uint8_t position)//�� num �������ʹ��޷���������uint32_t���޸�Ϊ�з���������int32_t����������ֵ�����
{
	uint8_t segment_data,TIMEsegment_data;

     if (num == -1) {
        segment_data = 0x00; // �����ʾ����
    } else {
    if (num > 9) return; // ����Ƿ�����
    segment_data = segment_map[num]; // ��ӳ����л�ȡ����
    TIMEsegment_data = TIMEsegment_map[num]; // ��ӳ����л�ȡ����
    }
		switch (position)//1-4�Ÿ�
    {	
        //1�Ÿ�
        case 1: W1623_LowerbyteMyriabit(D42, segment_data); break; // ��λ		
        case 2: W1623_Lowerbyte(D40, segment_data); break; // ǧλ
        case 3: W1623_Lowerbyte(D38, segment_data); break; // ��λ
        case 4: W1623_Lowerbyte(D36, segment_data); break; // ʮλ
        case 5: W1623_Lowerbyte(D34, segment_data); break; // ��λ
        //2�Ÿ�
        case 6: W1623_byteMyriabit(D42, segment_data); break; // ��λ
        case 7: W1623_byte(D40, segment_data); break; // ǧλ
        case 8: W1623_byte(D38, segment_data); break; // ��λ
        case 9: W1623_byte(D36, segment_data); break; // ʮλ
        case 10: W1623_byte(D34, segment_data); break; // ��λ
        //3�Ÿ�
        case 11: W1623_Lowerbyte(D32, segment_data); break; // ��λ
        case 12: W1623_Lowerbyte(D30, segment_data); break; // ǧλ
        case 13: W1623_Lowerbyte(D28, segment_data); break; // ��λ
        case 14: W1623_Lowerbyte(D26, segment_data); break; // ʮλ
        case 15: W1623_Lowerbyte(D24, segment_data); break; // ��λ
        //4�Ÿ�
		case 16: W1623_byte(D32, segment_data); break; // ��λ	
        case 17: W1623_byte(D30, segment_data); break; // ǧλ
        case 18: W1623_byte(D28, segment_data); break; // ��λ
        case 19: W1623_byte(D26, segment_data); break; // ʮλ
        case 20: W1623_byte(D24, segment_data); break; // ��λ
         default:break; // ����Ƿ�λ��
    }
#if 1
    switch (position)//MAX��MIN�Ƚ��������ʾ
    {
		case 21: W1623_Lowerbyte(7, TIMEsegment_data); break; // ��λ
        case 22: W1623_Lowerbyte(5, TIMEsegment_data); break; // ǧλ
        case 23: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // ��λ
        case 24: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // ʮλ
        case 25: W1623_TIMELowerbyte(21, TIMEsegment_data); break; // ��λ
         default:break; // ����Ƿ�λ��
    }
#endif	

#if 0
    switch (position)//ת����ʾ�����
    {
		case 26: W1623_TIMELowerbyte(9, TIMEsegment_data); break; // ��λ	
        case 27: W1623_Lowerbyte(7, TIMEsegment_data); break;       // ǧλ
        case 28: W1623_TIMELowerbyte(5, TIMEsegment_data); break; // ��λ
        case 29: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // ʮλ
        case 30: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // ��λ
         default:				
				break; // ����Ƿ�λ��
    }
#endif	

}

void mercury_display(u8 addr_1, u16 AD_MercuryValue)//������������ADֵ���ж�
{    

     uint8_t SEG_addr1,SEG_addr2;
     u16 mercury_data1,mercury_data2;
     
/*-------------------------------------------------������ʾ�ж�----------------------------------------------*/       
   if(addr_1==1)
   {
       UpdateReadModifyWriteDisplay(12,Mercury_1_Data_K1,1);	 //1�Ź���
       SEG_addr1 = 3;SEG_addr2 = 4;
       mercury_data1 = Mercury_1_Data_Grid9;mercury_data2 = Mercury_1_Data_Grid10;
   }
     if(addr_1==6)
    {
        UpdateReadModifyWriteDisplay(12,Mercury_2_Data_K2,1);	 //2�Ź���
        SEG_addr1 = 2;SEG_addr2 = 4;
        mercury_data1 = Mercury_2_Data_Grid9;mercury_data2 = Mercury_2_Data_Grid10;
    }
    
     if(addr_1==11)
   {
       UpdateReadModifyWriteDisplay(12,Mercury_3_Data_K3,1);	 //3�Ź���
       SEG_addr1 = 1;SEG_addr2 = 4;
       mercury_data1 = Mercury_3_Data_Grid9;mercury_data2 = Mercury_3_Data_Grid10;
   }
    if(addr_1==16)
   {
       UpdateReadModifyWriteDisplay(23,Mercury_4_Data_K4,1);	 //4�Ź���
       SEG_addr1 = 0;SEG_addr2 = 4;
       mercury_data1 = Mercury_4_Data_Grid9;mercury_data2 = Mercury_4_Data_Grid10;
   }
   //ˢ�¹���
    UpdateReadModifyWriteDisplay(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6 + Mercury_1_Data_Grid7 + Mercury_1_Data_Grid8,0);
    UpdateReadModifyWriteDisplay(SEG_addr2,mercury_data1+mercury_data2,0);//��9���10����ʾ��
/*-------------------------------------------------������ADֵ���ж�----------------------------------------------*/
   if (AD_MercuryValue >= 1638 && AD_MercuryValue < 1900) {        
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1); // ��һ��
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
//             UpdateReadModifyWriteDisplay(highByte, highMask, 1); // 1�Ÿ�С����
//             break;
//         case 6:
//             UpdateReadModifyWriteDisplay(highByte, lowMask, 1); // 2�Ÿ�С����
//             break;
//         case 11:
//             UpdateReadModifyWriteDisplay(lowByte, highMask, 1); // 3�Ÿ�С����
//             break;
//         case 16:
//             UpdateReadModifyWriteDisplay(lowByte, lowMask, 1); // 4�Ÿ�С����
//             break;
//     }
// }

// �������ʾ����
void Digital_tube_display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,float display_num,u16 AD_MercuryValue)//���Ż���ֻ��һ����ַ����׷�ټ���
{
	if(!settings_mode){
    mercury_display(addr_1,AD_MercuryValue);//������ʾ
    }
   switch (addr_1) {
        case 1:
            UpdateReadModifyWriteDisplay(12, 0x08, 1); // д��׺�1
            
            break;
        case 6:
            UpdateReadModifyWriteDisplay(12, 0x04, 1); // д��׺�2
            break;
        case 11:
            UpdateReadModifyWriteDisplay(12, 0x02, 1); // д��׺�3
            break;
        case 16:
            UpdateReadModifyWriteDisplay(12, 0x01, 1); // д��׺�4
            break;
        case 21:
            UpdateReadModifyWriteDisplay(11, Screen_Data_MIN + Screen_Data_MAX, 1); // MIN��MAXͼ����ʾ
            break;
    }

    if (display_num < 0) {
        display_num = -display_num; // ת��Ϊ����
    }
    if (display_num >= 10000 && display_num < 100000)//����10000����ʾ����
    {
      Digital_tube_Bit_Display((uint32_t)display_num%100000/10000,addr_1);
      Digital_tube_Bit_Display((uint32_t)display_num%10000/1000,addr_2);    
      Digital_tube_Bit_Display((uint32_t)display_num%1000/100,addr_3);     
      Digital_tube_Bit_Display((uint32_t)display_num%100/10,addr_4);     
      Digital_tube_Bit_Display((uint32_t)display_num%10/1,addr_5);
        
    }
    else if (display_num >= 1000 && display_num < 10000)//����10000����ʾ����
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
      //Digital_tube_Bit_Display((uint32_t)(display_num*10)%10,addr_5);//һλС����
 
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
/*-----------------------------------�������Ż�------------------------------------*/
void Dsp_RUN_Mode(void);

extern uint16_t ADC_Value[4];
float pressure[4];

//u8 Rec_Data_Display;

// ������ʾѹ��ֵ
void ProcessAndDisplayPressureValues( float PositivePressure, float K_Value)
 {
    int i;
	//float pressure[4];
	
    // ��ADCֵӳ�䵽ѹ��ֵ   
    for (i = 0; i < 4; i++) {
        pressure[i] = ADC1_MapValue((float)ADC_Value[i], PositivePressure, K_Value);
    }
  
#if 0
    // ��ӡѹ��ֵ
    printf("-----------------------PressureValue---------------------- \r\n");
    for (i = 0; i < 4; i++) {
        printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], pressure[i]);
    }
#endif 
    Dsp_RUN_Mode();
    
    //Digital_tube_display(21, 22, 23, 24, 25, -8532, ADC_Value[0]);//�����Сֵ����ʾ�����
	delay_ms(500);
}
float convertedPressure[4];
extern u8 Zero_flag;
void Dsp_RUN_Mode(void)
{
    //float convertedPressure[4];  
    UpdateReadModifyWriteDisplay(22, 0x3f, 0); // �����ʾ����     
    UpdateReadModifyWriteDisplay(23, 0x3f, 0); // �����ʾ����  
    
    //printf("%d  , %d  ",current_settings.current_unit,current_settings.sensor_count);
    switch(current_settings.current_unit)
    {
        case 0: // Pa
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_pa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 100;
            }
            break;

        case 1: // kPa   ��Ҫ1��С����
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

        case 3: // Torr    �����λ�����ûҪ��
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

        case 6: // inH2O    �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.401463;
            }
            break;

        case 7: // mmH2O    �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 10.1972;
            }
            break;

        case 8: // psi  ��Ҫ2��С����
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
    
        //��� Rec_Data_Display_Num �Ƿ�Ϊ����ֵ�����Ϊ����ֵ�����ʾ������Ҫʹ�ô洢������ DATA_ADC1��DATA_ADC2 �� DATA_ADC_DIF �е���ʷ��¼������������ʾ��				
        // ��ʾת�����ѹ��ֵ
        
        
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



/*-----------------------------------�������Ż�------------------------------------*/

/*----------------------------------����ʱ����ʾģ��-------------------------------------*/
extern u8 Second,Minute,Hour;//�롢�֡�ʱ
// ����ʱ�Ӵ���ʱ��ֵ
void TIME_Digital_tube_Bit_Display(uint32_t Timnum, uint8_t Timposition)
{
	uint8_t TIMEsegment_data;
    if (Timnum > 9) return; // ����Ƿ�����

    TIMEsegment_data = TIMEsegment_map[Timnum]; // ��ӳ����л�ȡ����

    switch (Timposition)//ʱ�䣬����ʱ��
    {			
        case 1: W1623_Lowerbyte(9, TIMEsegment_data); break; // ʱʮλ
        case 2: W1623_Lowerbyte(7, TIMEsegment_data); break; // ʱ��λ
        case 3: W1623_Lowerbyte(5, TIMEsegment_data); break; // ��ʮλ
        case 4: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // �ָ�λ
        case 5: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // ��ʮλ
        case 6: W1623_TIMELowerbyte(21, TIMEsegment_data); break; // ���λ
        default:break; // ����Ƿ�λ��
    }
}

//����ʱ�� ������ʾʱ��ֵ
void Clock_Display(void)//ʱ�䣬����ʱ��
{
    UpdateReadModifyWriteDisplay(11,Screen_Data_Time,1);//TIMEͼ����ʾ   
    TIME_Digital_tube_Bit_Display(Hour / 10, 1);   
    TIME_Digital_tube_Bit_Display(Hour % 10, 2);
    UpdateReadModifyWriteDisplay(10,Group2_digitron_TIME_colon_S32,1);//ð��1��ʾ   
    TIME_Digital_tube_Bit_Display(Minute / 10, 3);
    TIME_Digital_tube_Bit_Display(Minute % 10, 4);
    UpdateReadModifyWriteDisplay(22,Group2_digitron_TIME_colon_S38,1);//ð��2��ʾ
    TIME_Digital_tube_Bit_Display(Second / 10, 5);
    TIME_Digital_tube_Bit_Display(Second % 10, 6);

}
/*----------------------------------����ʱ����ʾģ��-------------------------------------*/

/*----------------------------------��Դ�����ʾģ��-------------------------------------*/
// ����ʵ�ʵ�ص�ѹ�ĺ���
float calculateBatteryVoltage(int channel) {
    // ��ȡָ��ͨ����ADCƽ��ֵ
    int Adc_Data = Get_ADC2_ChannelAverage(channel);
    //printf("Adc_Data = %d\n", Adc_Data);
    // �����ѹ��ĵ�ѹ������ADC�ο���ѹΪ3.3V
    float Vout = (Adc_Data / 4095.0) * 3.3;    
    // ����ʵ�ʵĵ�ص�ѹ
    float Vin = Vout * ((120.0 + 72.0) / 72.0); // R23 = 120K, R26 = 72K��Vin =Vout * ((120.0 + 72.0) / 72.0)
    // ���������
    // printf("ADC2_Channel%d = %d | %f\n", channel, Adc_Data, Vout);
    // printf("ʵ�ʵ�ѹ = %.2f V\n", Vin);
    UpdateReadModifyWriteDisplay(14,Battery_Data_S5+Battery_Data_S1+Battery_Data_S2+Battery_Data_S3+Battery_Data_S4,0); //ˢ�µ�ظ�����ʾ 
/*----------------------------------------��ʾ-------------------------------------------*/
        if(Adc_Data<1800)//����4V
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


/*----------------------------------��Դ�����ʾģ��-------------------------------------*/


/*----------------------------------P=0-------------------------------------*/
void	Dig_Zero(void)
{
    
	//�ĸ�ѹ��ֵ��������ʱ�� = 0��
    Second =0;Minute=0;Hour=0;
    ADC_Value[0] = 1800;
    ADC_Value[1] = 1800; 
    ADC_Value[2] = 1800; 
    ADC_Value[3] = 1800;
    
    convertedPressure[0] = 0;convertedPressure[1] = 0;convertedPressure[2] = 0;convertedPressure[3] = 0;

}

//P = 0 �Զ�У0,ѹ������
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