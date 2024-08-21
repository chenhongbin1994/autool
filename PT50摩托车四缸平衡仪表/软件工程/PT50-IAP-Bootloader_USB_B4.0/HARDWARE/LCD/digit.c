#include "digit.h"
#include "display.h"
#include "LCD_HT1623.h"
#include "usart.h"
#include "key_handler.h"

#if 0
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
    switch (position)//MAX��MIN�Ƚ��������ʾ
    {
		case 21: W1623_Lowerbyte(7, TIMEsegment_data); break; // ��λ
        case 22: W1623_Lowerbyte(5, TIMEsegment_data); break; // ǧλ
        case 23: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // ��λ
        case 24: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // ʮλ
        case 25: W1623_TIMELowerbyte(21, TIMEsegment_data); break; // ��λ
         default:break; // ����Ƿ�λ��
    }
    switch (position)//ת����ʾ�����
    {
		case 26: W1623_byte(9, TIMEsegment_data); break; // ��λ	
        case 27: W1623_byte(7, TIMEsegment_data); break;       // ǧλ
        case 28: W1623_byte(5, TIMEsegment_data); break; // ��λ
        case 29: W1623_RPMbyte(17, TIMEsegment_data); break; // ʮλ
        case 30: W1623_RPMbyte(19, TIMEsegment_data); break; // ��λ
         default:				
				break; // ����Ƿ�λ��
    }
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

void UpdateDecimalPoint(u8 addr, u8 highByte, u8 lowByte, u8 highMask, u8 lowMask)
{
    switch (addr) {
        case 1:
            UpdateReadModifyWriteDisplay(highByte, highMask, 1); // 1�Ÿ�С����
            break;
        case 6:
            UpdateReadModifyWriteDisplay(highByte, lowMask, 1); // 2�Ÿ�С����
            break;
        case 11:
            UpdateReadModifyWriteDisplay(lowByte, highMask, 1); // 3�Ÿ�С����
            break;
        case 16:
            UpdateReadModifyWriteDisplay(lowByte, lowMask, 1); // 4�Ÿ�С����
            break;
    }
}
// ���ȫ�ֱ������ڴ洢ѹ��ƫ��ֵ
float pressure_offset[4] = {0.0, 0.0, 0.0, 0.0};
//float ADValue_offset[4] = {1784.0, 1784.0, 1784.0,1784.0};
float ADValue_offset[4] = {0, 0, 0, 0};
u8 decimal_points = 0; // Ĭ��û��С����
extern int in_submode;
// �������ʾ����
void Digital_tube_display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,float display_num,u16 AD_MercuryValue)//���Ż���ֻ��һ����ַ����׷�ټ���
{
    
	if(!settings_mode){
    mercury_display(addr_1,AD_MercuryValue);//������ʾ
    }
    // Ӧ��У׼ƫ��ֵ
    //��������������Ӱ�������С��ֵ�����ݻ���10
    //display_num -= pressure_offset[addr_1 / 5]; // ÿ5����ַһ�飬�ֱ��Ӧ�ĸ׵�ƫ��ֵ
    
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
    }
    if (display_num < 0) {
        display_num = -display_num; // ת��Ϊ����
    }
    // UpdateReadModifyWriteDisplay(35,0x11,0);
    // UpdateReadModifyWriteDisplay(25,0x11,0);
    // UpdateReadModifyWriteDisplay(37,0x11,0);
    // UpdateReadModifyWriteDisplay(27,0x11,0);
    int integer_part = (int)display_num;
    int fraction_part = (int)((display_num - integer_part) * 10);
      
    // ��ʾ���ֺ�С����
    if (integer_part >= 10000) {
        Digital_tube_Bit_Display((uint32_t)integer_part % 100000 / 10000, addr_1);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10000 / 1000, addr_2);    
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3);     
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);     
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);
    } else if (integer_part >= 1000) { 
        Digital_tube_Bit_Display((uint32_t)integer_part % 10000 / 1000, addr_2);
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3);
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // ��ʾһλС����
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);   
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // ��ʾ��λС����
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 100&& integer_part < 1000) {
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3); 
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);   
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // ��ʾһλС����
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // ��ʾ��λС����
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 10&& integer_part < 100) { 
        // ����������Ϊ0ʱ��ȷ����ʾ0��С������         
        Digital_tube_Bit_Display((uint32_t)(integer_part)%100/10,addr_4);
        Digital_tube_Bit_Display((uint32_t)(integer_part)%10,addr_5);         
        if (decimal_points == 1) {
            Digital_tube_Bit_Display(0, addr_4); // ��ʾ0
            Digital_tube_Bit_Display((uint32_t)(fraction_part), addr_5); // ��ʾС������ 
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // ��ʾһλС����

            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1); 
        }
        else if (decimal_points == 2) {
            // Digital_tube_Bit_Display(0%1000/100, addr_3); // ��ʾ0            
            // Digital_tube_Bit_Display((uint32_t)(fraction_part%100/10 ), addr_4); // ��ʾС�����ֵĵ�һλ
            // Digital_tube_Bit_Display((uint32_t)(fraction_part%10 ), addr_5); // ��ʾС�����ֵĵڶ�λ 
            Digital_tube_Bit_Display(0, addr_3); // ��ʾ0
            Digital_tube_Bit_Display((uint32_t)(fraction_part / 10), addr_4); // ��ʾС�����ֵĵ�һλ
            Digital_tube_Bit_Display((uint32_t)(fraction_part % 10), addr_5); // ��ʾС�����ֵĵڶ�λ
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // ��ʾ��λС����

            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }    
    } else if (integer_part >= 0&& integer_part < 10) {
        // ����������Ϊ0ʱ��ȷ����ʾ0��С������
        Digital_tube_Bit_Display((uint32_t)(integer_part)%10,addr_5); 
        if (decimal_points == 1) {
            Digital_tube_Bit_Display(0, addr_4); // ��ʾ0
            Digital_tube_Bit_Display((uint32_t)(fraction_part), addr_5); // ��ʾС������
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // ��ʾһλС����

            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1); 
        } else if (decimal_points == 2) {
            // Digital_tube_Bit_Display(0%1000/100, addr_3); // ��ʾ0        
            // Digital_tube_Bit_Display((uint32_t)(fraction_part%100/10 ), addr_4); // ��ʾС�����ֵĵ�һλ
            // Digital_tube_Bit_Display((uint32_t)(fraction_part%10 ), addr_5); // ��ʾС�����ֵĵڶ�λ
            Digital_tube_Bit_Display(0, addr_3); // ��ʾ0
            Digital_tube_Bit_Display((uint32_t)(fraction_part / 10), addr_4); // ��ʾС�����ֵĵ�һλ
            Digital_tube_Bit_Display((uint32_t)(fraction_part % 10), addr_5); // ��ʾС�����ֵĵڶ�λ
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // ��ʾ��λС����

            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    }
}
/*-----------------------------------�������Ż�------------------------------------*/
extern u8   Timing_Switch_5min,MinAuto,SecondAuto; 
extern u8 calibration_flag;//P=0
void Dsp_RUN_Mode(void);

extern uint16_t ADC_Value[4];
float pressure[4];

// ������ʾѹ��ֵ
void ProcessAndDisplayPressureValues( float PositivePressure, float K_Value)
 {
    int i;
    // ��ADCֵӳ�䵽ѹ��ֵ   
    for (i = 0; i < 4; i++) {
        pressure[i] = ADC1_MapValue((float)(ADC_Value[i] ), PositivePressure, K_Value);//- pressure_offset[i];       
    }
#if 1
    // ��ӡѹ��ֵ
    printf("-----------------------PressureValue---------------------- \r\n");
    for (i = 0; i < 4; i++) {
        printf("Pressure %d: AD_Value= %d, ѹ��= %.2f HPa\r\n", i, ADC_Value[i], pressure[i]);
    }
#endif 
     //UpdateReadModifyWriteDisplay(15, Screen_Data_2T+Screen_Data_4T, 0);   //2T
 #if 1    //2Tͼ���Ӱ������ͬSEG���д�룬��Ҫ��취��λ�÷�
     //2T,4T����ģʽ��ʾ�л�
    if(current_settings.sensor_count==0){
         UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);   //2T
         UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 1);   //4T
    }else{          
         //UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   //4T
         UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 1);   //2T
    }
    delay_ms(50);//����ʱ���Ա���2Tͼ���Ӱ������ͬSEG���д��
#endif
    Dsp_RUN_Mode();
    
	delay_ms(500);
}


float convertedPressure[4];
extern u8 Zero_flag;

void Dsp_RUN_Mode(void)
{
    UpdateReadModifyWriteDisplay(22, 0x3f, 0); // ˢ����ʾ����     
    UpdateReadModifyWriteDisplay(23, 0x3f, 0); // ˢ����ʾ����  
    
    switch(current_settings.current_unit)
    {
        case 0: // Pa
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_pa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 100;
                
            }
            decimal_points = 0; // ����ҪС����
            break;

        case 1: // kPa   ��Ҫ2λС����
            UpdateReadModifyWriteDisplay(22, 0x30, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.1;
                convertedPressure[i] = convertedPressure[i]*100;
                //printf("Pressure %d: ѹ��= %.2f HPa\r\n", i,  convertedPressure[i]);
            }
            decimal_points = 2;
            break;

        case 2: // mmHg   1С����
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.750062;
                convertedPressure[i] = convertedPressure[i]*10;
            }
            decimal_points = 1; 
            break;

        case 3: // Torr    1С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.750062;
                convertedPressure[i] = convertedPressure[i]*10;
            }
            decimal_points = 1; 
            break; 

        case 4: // mbar    1С����
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i];
                convertedPressure[i] = convertedPressure[i]*10;
            }
            decimal_points = 1; 
            break;

        case 5: // inHg    2С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.0295301;
                convertedPressure[i] = convertedPressure[i]*100;
            }
            decimal_points = 2; 
            break;

        case 6: // inH2O    1С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.401463;
                convertedPressure[i] = convertedPressure[i]*10;
            }
            decimal_points = 2; 
            break;

        case 7: // mmH2O    ��С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 10.1972;
            }
            decimal_points = 0; 
            break;

        case 8: // psi  ��Ҫ2��С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i] * 0.0145038;
                convertedPressure[i] = convertedPressure[i]*100;
            }
            decimal_points = 2; 
            break;

        case 9: // hPa  1С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = pressure[i];
                convertedPressure[i] = convertedPressure[i]*10;
                //printf("Pressure %d: ѹ��= %.2f HPa\r\n", i,  convertedPressure[i]);
            }
            decimal_points = 1; 
            break;
    }
       
        if (current_settings.sensor_count == 0) {
            if(!settings_mode){
            ClearDigitalTubeDisplay(); 
            if(Zero_flag ==1){
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
            //  UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   //4T
            //  UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 1);   //2T
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
//�ĸ�ѹ��ֵ��δ����ʱ������ֵ�������������P = 0����������������������ѹ����״̬�£�4��ѹ����Ȼ��3��Pa�ĸ���������P=0����ȥ��ǰ��ֵʹ֮Ϊ0����������ĸ�ʩ����20Kpaѹ���ٰ�P=0ʹ֮��0��������ѹ����״̬������ʾ��20KPa,�ٴγ�������ʹ֮��0

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

void Clear_Clock_Display(void)
{
     UpdateReadModifyWriteDisplay(11,Screen_Data_Time,0);//TIMEͼ����ʾ   
     UpdateReadModifyWriteDisplay(10,Group2_digitron_TIME_colon_S32,0);//ð��1��ʾ   
     UpdateReadModifyWriteDisplay(22,Group2_digitron_TIME_colon_S38,0);//ð��2��ʾ
     for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
     for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
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

extern int history_index;  // ��ǰ��¼������
extern int total_records;  // �ܼ�¼��
/*----------------------------------P=0-------------------------------------*/
void	Dig_Zero(void)
{
    
	//�ĸ�ѹ��ֵ��������ʱ�� = 0��
    Second =0-1;Minute=0;Hour=0;//0-1�������ܹ�0
    ADC_Value[0] = 1800;ADC_Value[1] = 1800; ADC_Value[2] = 1800; ADC_Value[3] = 1800;  //Ӧ����1783 
    convertedPressure[0] = 0;convertedPressure[1] = 0;convertedPressure[2] = 0;convertedPressure[3] = 0;
    // ���������ʷ��¼
    history_index = 0;total_records = 0;//SaveCurrentHistoryIndexToFlash();// ���������ʷ��¼
    delay_ms(50);
}

//P = 0 �Զ�У0,ѹ������
// У׼��������¼��ǰѹ��ֵ��Ϊƫ����
void Calibration(void){
    // ADC_GetAverageValues();	  
    //  for (int i = 0; i < 4; i++) {
    //     ADValue_offset[i] = ADC_Value[i]; // ��¼��ǰѹ��ֵ��Ϊƫ����
    // }
    printf("У׼��ɣ�ѹ��ƫ��ֵ�Ѽ�¼\n");
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


/*----------------------------------��ʷ��������-----------------------------------------*/
void NumHistoricalData_Display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,int HistoricalData_num)
{
#if 0  //ˢ��ת�������
    int i;
    for(i=5;i<10;i++) {
    UpdateReadModifyWriteDisplay(i,0x0f,0);
    }
    UpdateReadModifyWriteDisplay(10,0x0e,0);
    for(i=16;i<19;i++) {
    UpdateReadModifyWriteDisplay(i,0x0f,0);
    }
#endif
    if (HistoricalData_num >= 10000 && HistoricalData_num < 100000)//����10000����ʾ����
    {
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%100000/10000,addr_1);
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%10000/1000,addr_2);    
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%1000/100,addr_3);     
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%100/10,addr_4);     
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%10/1,addr_5);
        
    }
    else if (HistoricalData_num >= 1000 && HistoricalData_num < 10000)//����10000����ʾ����
    {
        
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%10000/1000,addr_2);
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%1000/100,addr_3);
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%100/10,addr_4);
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%10/1,addr_5);
       
    }
    else if (HistoricalData_num >= 100 && HistoricalData_num < 1000)
    {
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%1000/100,addr_3); 
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%100/10,addr_4);
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%10/1,addr_5);
    
    }
    else if (HistoricalData_num >= 10 && HistoricalData_num < 100)
    {
    
      Digital_tube_Bit_Display((uint32_t)(HistoricalData_num)%100/10,addr_4);
      Digital_tube_Bit_Display((uint32_t)(HistoricalData_num)%10,addr_5);
   
    }
		else if (HistoricalData_num >= 0 && HistoricalData_num < 10)
    {
    Digital_tube_Bit_Display((uint32_t)(HistoricalData_num)%10,addr_5);
      
    }

}

/*----------------------------------��ʷ��������-----------------------------------------*/
void SettingsUint(float display_value)
{
    float temp_value = 0;
    switch(current_settings.current_unit)
    {
        case 0: // Pa
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_pa, 1);
           
               temp_value = display_value * 100;
                      
            decimal_points = 0; // ����ҪС����
            break;

        case 1: // kPa   ��Ҫ2λС����
            UpdateReadModifyWriteDisplay(22, 0x30, 1);
           
                temp_value = display_value * 0.1;
                temp_value = temp_value*100;
                //printf("Pressure %d: ѹ��= %.2f HPa\r\n", i,  convertedPressure[i]);
            
            decimal_points = 2;
            break;

        case 2: // mmHg   1С����
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);
           
                temp_value = display_value * 0.750062;
                temp_value = temp_value*10;
            
            decimal_points = 1; 
            break;

        case 3: // Torr    1С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
           
                temp_value = display_value * 0.750062;
                temp_value = temp_value*10;
            
            decimal_points = 1; 
            break; 

        case 4: // mbar    1С����
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);
            
                temp_value = display_value;
                temp_value = temp_value*10;
            
            decimal_points = 1; 
            break;

        case 5: // inHg    2С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);
           
                temp_value = display_value * 0.0295301;
                temp_value = temp_value*100;
            
            decimal_points = 2; 
            break;

        case 6: // inH2O    1С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
            
                temp_value = display_value * 0.401463;
                temp_value = temp_value*10;
            
            decimal_points = 2; 
            break;

        case 7: // mmH2O    ��С����   �����λ�����ûҪ��
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
           
                temp_value = display_value * 10.1972;
            
            decimal_points = 0; 
            break;

        case 8: // psi  ��Ҫ2��С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);
            
                temp_value = display_value* 0.0145038;
                temp_value = temp_value*100;
            
            decimal_points = 2; 
            break;

        case 9: // hPa  1С����
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);
            
                temp_value = display_value;
                temp_value = temp_value*10;
                //printf("Pressure %d: ѹ��= %.2f HPa\r\n", i,  convertedPressure[i]);
            
            decimal_points = 1; 
            break;
    }
    Digital_tube_display(21, 22, 23, 24, 25, temp_value, ADC_Value[3]);//ADֵ��Ӧ�ó���
}


#endif

