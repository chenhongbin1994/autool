#include "digit.h"
#include "display.h"
#include "LCD_HT1623.h"
#include "usart.h"
#include "includes.h"
#include "key_handler.h"


// extern int settings_mode;
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
void Group1_digitron(u8 TIMEsegment_map1,u8 SEG1,u8 SEG2)
{
    // for(int i=5;i<10;i++)UpdateReadModifyWriteDisplay(i,0x0f,0);
    //UpdateReadModifyWriteDisplay(10,0x07,0);
    // for(int i=16;i<20;i++)UpdateReadModifyWriteDisplay(i,0x0f,0);
    
    switch(TIMEsegment_map1)
    {
        case 0: UpdateReadModifyWriteDisplay(SEG1,0x0f,1);UpdateReadModifyWriteDisplay(SEG2,0x05,1); break;
        case 1: UpdateReadModifyWriteDisplay(SEG1,0x06,1); break;
        case 2: UpdateReadModifyWriteDisplay(SEG1,0x0b,1);UpdateReadModifyWriteDisplay(SEG2,0x06,1); break;
        case 3: UpdateReadModifyWriteDisplay(SEG1,0x0f,1);UpdateReadModifyWriteDisplay(SEG2,0x02,1); break;
        case 4: UpdateReadModifyWriteDisplay(SEG1,0x06,1);UpdateReadModifyWriteDisplay(SEG2,0x03,1); break;
        case 5: UpdateReadModifyWriteDisplay(SEG1,0x0d,1);UpdateReadModifyWriteDisplay(SEG2,0x03,1); break;
        case 6: UpdateReadModifyWriteDisplay(SEG1,0x0d,1);UpdateReadModifyWriteDisplay(SEG2,0x07,1); break;
        case 7: UpdateReadModifyWriteDisplay(SEG1,0x07,1); break;
        case 8: UpdateReadModifyWriteDisplay(SEG1,0x0f,1);UpdateReadModifyWriteDisplay(SEG2,0x07,1); break;
        case 9: UpdateReadModifyWriteDisplay(SEG1,0x0f,1);UpdateReadModifyWriteDisplay(SEG2,0x03,1); break;
    }
}
void Group2_digitron(u8 TIMEsegment_map2,u8 SEG1,u8 SEG2)
{
    // for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
    // for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
    switch(TIMEsegment_map2)
    {
        case 0: UpdateReadModifyWriteDisplay(SEG1,0xf0,1);UpdateReadModifyWriteDisplay(SEG2,0x50,1); break;
        case 1: UpdateReadModifyWriteDisplay(SEG1,0x60,1); break;
        case 2: UpdateReadModifyWriteDisplay(SEG1,0xb0,1);UpdateReadModifyWriteDisplay(SEG2,0x60,1); break;
        case 3: UpdateReadModifyWriteDisplay(SEG1,0xf0,1);UpdateReadModifyWriteDisplay(SEG2,0x20,1); break;
        case 4: UpdateReadModifyWriteDisplay(SEG1,0x60,1);UpdateReadModifyWriteDisplay(SEG2,0x30,1); break;
        case 5: UpdateReadModifyWriteDisplay(SEG1,0xd0,1);UpdateReadModifyWriteDisplay(SEG2,0x30,1); break;
        case 6: UpdateReadModifyWriteDisplay(SEG1,0xd0,1);UpdateReadModifyWriteDisplay(SEG2,0x70,1); break;
        case 7: UpdateReadModifyWriteDisplay(SEG1,0x70,1); break;
        case 8: UpdateReadModifyWriteDisplay(SEG1,0xf0,1);UpdateReadModifyWriteDisplay(SEG2,0x70,1); break;
        case 9: UpdateReadModifyWriteDisplay(SEG1,0xf0,1);UpdateReadModifyWriteDisplay(SEG2,0x30,1); break;
    }
}


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

// void Clear_RMP_DigitalTubeDisplay(void)
// {
//   //刷新转速数码段
//     int i;
//     for(i=5;i<10;i++) {
//     UpdateReadModifyWriteDisplay(i,0x0f,0);
//     }
//     UpdateReadModifyWriteDisplay(10,0x0e,0);
//     for(i=16;i<19;i++) {
//     UpdateReadModifyWriteDisplay(i,0x0f,0);
//     }
// }
void Clear_Clock_Display(void)//清除时钟数码段
{
     UpdateReadModifyWriteDisplay(11,Screen_Data_Time,0);//TIME图标显示   
     UpdateReadModifyWriteDisplay(10,Group2_digitron_TIME_colon_S32,0);//冒号1显示   
     UpdateReadModifyWriteDisplay(22,Group2_digitron_TIME_colon_S38,0);//冒号2显示
     for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
     for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
}
void Clear_Group1dig(void)
{
    for(int i=5;i<10;i++)UpdateReadModifyWriteDisplay(i,0x0f,0);
    UpdateReadModifyWriteDisplay(10,0x07,0);
    for(int i=16;i<20;i++)UpdateReadModifyWriteDisplay(i,0x0f,0);
}
void Clear_Group2dig(void)
{
    for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
    for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
}

/*-------------------------------------------刷新函数--------------------------------------------------*/
void Digital_tube_Bit_Display(int num, uint8_t position)//将 num 参数类型从无符号整数（uint32_t）修改为有符号整数（int32_t），并处理负值情况。
{
	uint8_t segment_data;//TIMEsegment_data;

     if (num == -1) {
        segment_data = 0x00; // 清除显示内容
    } else {
    if (num > 9) return; // 处理非法输入
    segment_data = segment_map[num]; // 从映射表中获取段码
    //TIMEsegment_data = TIMEsegment_map[num]; // 从映射表中获取段码
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
        //MAX与MIN比较数码段显示
    }
    switch (position){
 
        case 21: Group2_digitron(num,7,8); break; // 万位
        case 22: Group2_digitron(num,5,6); break; // 千位
        case 23: Group2_digitron(num,17,16); break; // 百位
        case 24: Group2_digitron(num,19,18); break; // 十位        
        case 25: Group2_digitron(num,21,20); break; // 个位
        
        //转速显示数码段
        case 26: Group1_digitron(num, 9,10); break; // 万位	
        case 27: Group1_digitron(num, 7,8); break;       // 千位
        case 28: Group1_digitron(num, 5,6); break; // 百位
        case 29: Group1_digitron(num, 17,16); break; // 十位
        case 30: Group1_digitron(num, 19,18); break; // 个位
        default:break; // 处理非法位置
    
    }
}
#if 0
    switch (position)//MAX与MIN比较数码段显示
    {
		case 21: W1623_Lowerbyte(7, TIMEsegment_data); break; // 万位
        case 22: W1623_Lowerbyte(5, TIMEsegment_data); break; // 千位
        case 23: W1623_TIMELowerbyte(17, TIMEsegment_data); break; // 百位
        case 24: W1623_TIMELowerbyte(19, TIMEsegment_data); break; // 十位
        case 25: W1623_TIMELowerbyte(21, TIMEsegment_data); break; // 个位
         default:break; // 处理非法位置
    }
    switch (position)//转速显示数码段
    {
		case 26: W1623_byte(9, TIMEsegment_data); break; // 万位	
        case 27: W1623_byte(7, TIMEsegment_data); break;       // 千位
        case 28: W1623_byte(5, TIMEsegment_data); break; // 百位
        case 29: W1623_RPMbyte(17, TIMEsegment_data); break; // 十位
        case 30: W1623_RPMbyte(19, TIMEsegment_data); break; // 个位
         default:				
				break; // 处理非法位置
    }
}
#endif

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
				UpdateReadModifyWriteDisplay(SEG_addr2,mercury_data1,1);
    } else if (AD_MercuryValue >= 100 && AD_MercuryValue < 382) {
        W1623_bothSeg_byte(SEG_addr1, Mercury_1_Data_Grid1 + Mercury_1_Data_Grid2 + Mercury_1_Data_Grid3 + Mercury_1_Data_Grid4 + Mercury_1_Data_Grid5 + Mercury_1_Data_Grid6 + Mercury_1_Data_Grid7 + Mercury_1_Data_Grid8);
        UpdateReadModifyWriteDisplay(SEG_addr2,mercury_data1+mercury_data2,1);
    }     
}

void UpdateDecimalPoint(u8 addr, u8 highByte, u8 lowByte, u8 highMask, u8 lowMask)
{
    switch (addr) {
        case 1:
            UpdateReadModifyWriteDisplay(highByte, highMask, 1); // 1号缸小数点
            break;
        case 6:
            UpdateReadModifyWriteDisplay(highByte, lowMask, 1); // 2号缸小数点
            break;
        case 11:
            UpdateReadModifyWriteDisplay(lowByte, highMask, 1); // 3号缸小数点
            break;
        case 16:
            UpdateReadModifyWriteDisplay(lowByte, lowMask, 1); // 4号缸小数点
            break;
    }
}
// 添加全局变量用于存储压力偏移值
float pressure_offset[4] = {0.0, 0.0, 0.0, 0.0};
u8 decimal_points = 0; // 默认没有小数点
extern int in_submode;
extern int Calibration_offset;
// 数码管显示函数
void Digital_tube_display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,float display_num,u16 AD_MercuryValue)//待优化，只需一个地址参数追踪即可
{   
    mercury_display(addr_1,AD_MercuryValue);//汞柱显示   
   switch (addr_1) {
        case 1:
            UpdateReadModifyWriteDisplay(12, 0x08, 1); // 写入缸号1
            if (display_num < 0)
            {
                display_num = display_num*(-1);// 转换为正数display_num = display_num*(-1);
				UpdateReadModifyWriteDisplay(D13,0x40,1);			
            }else{
                UpdateReadModifyWriteDisplay(D13,0x40,0);	 // 清除负号段码所有位		
            }	

            break;
        case 6:
            UpdateReadModifyWriteDisplay(12, 0x04, 1); // 写入缸号2
            if (display_num < 0)
            {
                display_num = display_num*(-1);// 转换为正数display_num = display_num*(-1);
				UpdateReadModifyWriteDisplay(D13,0x04,1);			
            }else{
                UpdateReadModifyWriteDisplay(D13,0x04,0);	 // 清除负号段码所有位		
            }
            break;
        case 11:
            UpdateReadModifyWriteDisplay(12, 0x02, 1); // 写入缸号3
            if (display_num < 0)
            {
                display_num = display_num*(-1);// 转换为正数display_num = display_num*(-1);
				UpdateReadModifyWriteDisplay(D33,0x40,1);			
            }else{
                UpdateReadModifyWriteDisplay(D33,0x40,0);	 // 清除负号段码所有位		
            }
            break;
        case 16:
            UpdateReadModifyWriteDisplay(12, 0x01, 1); // 写入缸号4
            if (display_num < 0)
            {
                display_num = display_num*(-1);// 转换为正数display_num = display_num*(-1);
				UpdateReadModifyWriteDisplay(D33,0x04,1);			
            }else{
                UpdateReadModifyWriteDisplay(D33,0x04,0);	 // 清除负号段码所有位		
            }
            break;
    }
    // if (display_num < 0) {
    //     display_num = -display_num; // 转换为正数
    // }

    int integer_part = (int)display_num;
      
    // 显示数字和小数点
    if (integer_part >= 10000) {
        Digital_tube_Bit_Display((uint32_t)integer_part % 100000 / 10000, addr_1);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10000 / 1000, addr_2);    
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3);     
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);     
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);
         if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);   
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 1000) { 
        Digital_tube_Bit_Display((uint32_t)integer_part % 10000 / 1000, addr_2);
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3);
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);   
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 100&& integer_part < 1000) {
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3); 
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);   
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 10&& integer_part < 100) { 
#if 0   //p=0校准后开启归0，历史数据需同步，可加入单位限制
        if (Calibration_offset == 1) {
            integer_part = 0;
        }
#endif

        // 当整数部分为0时，确保显示0和小数部分         
        Digital_tube_Bit_Display((uint32_t)(integer_part)%100/10,addr_4);
        Digital_tube_Bit_Display((uint32_t)(integer_part)%10,addr_5);         
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1); 
        }
        else if (decimal_points == 2) {
            Digital_tube_Bit_Display(0, addr_3); // 显示0
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }    
    } else if (integer_part >= 0&& integer_part < 10) {
#if 1  //p=0校准后开启归0，历史数据需同步
        if (Calibration_offset == 1) {
            integer_part = 0;
        }
#endif
        // 当整数部分为0时，确保显示0和小数部分
        Digital_tube_Bit_Display((uint32_t)(integer_part)%10,addr_5); 
        if (decimal_points == 1) {
            Digital_tube_Bit_Display(0, addr_4); // 显示0
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1); 
        } else if (decimal_points == 2) {
            Digital_tube_Bit_Display(0, addr_3); // 显示0
            Digital_tube_Bit_Display(0, addr_4); // 显示0
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    }
}

/*-----------------------------------测试需优化------------------------------------*/
extern u8   Timing_Switch_5min,MinAuto,SecondAuto; 
extern u8 calibration_flag;//P=0
void Dsp_RUN_Mode(void);

float pressure[4];
// 处理并显示压力值
void ProcessAndDisplayPressureValues( float PositivePressure, float K_Value)
 {
    
    // 将ADC值映射到压力值   
    ADC1_GetValue();
    for (int i = 0; i < 4; i++) {
        pressure[i] = ADC1_MapValue((float)(ADC_Value[i] ), PositivePressure, K_Value);//- pressure_offset[i];       
    }
#if 0
    // 打印压力值
    printf("-----------------------PressureValue---------------------- \r\n");
    for (int i = 0; i < 4; i++) {
        printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], pressure[i]);
    }
#endif   
#if 1 
    //INTX_DISABLE();//关闭所有中断
    SettingsUint_display();
    //Switching2T4T_display();
    //INTX_ENABLE();//开启所有中断
#endif
    SwitcUint(pressure);
    Dsp_RUN_Mode();
    
	//delay_ms(500);
}


float convertedPressure[4];
//extern u8 Zero_flag;

void Dsp_RUN_Mode(void)
{  

        //INTX_DISABLE();//关闭所有中断
        if (current_settings.sensor_count == MODE_CH1) {
        
            ClearDigitalTubeDisplay(); 
            Digital_tube_display(1, 2, 3, 4, 5, convertedPressure[3], ADC_Value[3]);//1号缸                 
        }      
        else if (current_settings.sensor_count == MODE_CH2) {

            ClearDigitalTubeDisplay(); 
            Digital_tube_display(1, 2, 3, 4, 5, convertedPressure[3], ADC_Value[3]);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, convertedPressure[2], ADC_Value[2]);//2号缸
             
        }
        else if (current_settings.sensor_count == MODE_CH3) {

            ClearDigitalTubeDisplay(); 
            Digital_tube_display(1, 2, 3, 4, 5, convertedPressure[3], ADC_Value[3]);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, convertedPressure[2], ADC_Value[2]);//2号缸
            Digital_tube_display(11, 12, 13, 14, 15, convertedPressure[1], ADC_Value[1]);//3号缸 
        }
        else if (current_settings.sensor_count == MODE_CH4) {

            ClearDigitalTubeDisplay(); 
            Digital_tube_display(1, 2, 3, 4, 5, convertedPressure[3], ADC_Value[3]);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, convertedPressure[2], ADC_Value[2]);//2号缸
            Digital_tube_display(11, 12, 13, 14, 15, convertedPressure[1], ADC_Value[1]);//3号缸
            Digital_tube_display(16, 17, 18, 19, 20, convertedPressure[0], ADC_Value[0]);//4号缸
        }
        //INTX_ENABLE();//开启所有中断
}
/*-----------------------------------测试需优化------------------------------------*/
void SwitcUint(float* inputPressure)//单位换算
{
    //printf("================================Pressure==============================\r\n");
    switch(current_settings.current_unit)
    {
        case 0: // kPa   需要2位小数点
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_K+Switching_Unit_Data_pa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 10;//0.1*100
                //printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);
                //convertedPressure[i] = convertedPressure[i]*100;
               
            }
            decimal_points = 2;
            break;

        case 1: // mmHg   1小数点
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 7.50062;//0.750062
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);
            }
            decimal_points = 1; 
            break;

        case 2: // Torr    1小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 7.50062;
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

            }
            decimal_points = 1; 
            break; 

        case 3: // mbar    1小数点
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 10;
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);
                
            }
            decimal_points = 1; 
            break;

        case 4: // inHg    2小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 2.95301;//0.0295301*100
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);               
            }
            decimal_points = 2; 
            break;

        case 5: // inH2O    1小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 4.01463;//0.401463
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

            }
            decimal_points = 1; 
            break;

        case 6: // mmH2O    无小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 10.1972;
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

            }
            decimal_points = 0; 
            break;

        case 7: // psi  需要2个小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i] * 1.45038;//0.0145038*100                
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);

                
            }
            decimal_points = 2; 
            break;

        case 8: // hPa  1小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);
            for (int i = 0; i < 4; i++) {
                convertedPressure[i] = inputPressure[i]*10;
                printf("Pressure %d: AD_Value= %d, 压力= %.2f HPa\r\n", i, ADC_Value[i], convertedPressure[i]);               
            }
            decimal_points = 1; 
            break;
    }
}
void SwitchingNumberCylinders(void)
{
    //UpdateReadModifyWriteDisplay(12, 0x0f, 0); 
    //UpdateReadModifyWriteDisplay(12,Mercury_1_Data_K1+Mercury_2_Data_K2+Mercury_3_Data_K3,0);	
    //UpdateReadModifyWriteDisplay(23,Mercury_4_Data_K4,0);	 
    ClearDigitalTubeDisplay(); 
    ClearMercuryDisplay();
    switch (current_settings.sensor_count) {
        case MODE_CH1:
            printf("当前模式: ch1\n");
            //UpdateReadModifyWriteDisplay(12, 0x08, 1); // 写入缸号1          
            //UpdateReadModifyWriteDisplay(12,Mercury_1_Data_K1,1);	 //1号汞柱
            Digital_tube_display(1, 2, 3, 4, 5, 0, 1900);//1号缸
          
            break;
        case MODE_CH2:
            printf("当前模式: ch2\n");
            //UpdateReadModifyWriteDisplay(12, 0x0c, 1); // 写入缸号1      
            //UpdateReadModifyWriteDisplay(12,Mercury_1_Data_K1+Mercury_2_Data_K2,1);	 //1号汞柱
            Digital_tube_display(1, 2, 3, 4, 5, 0, 1900);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, 0, 1900);//2号缸
            break;
        case MODE_CH3:
            printf("当前模式: ch3\n");
            //UpdateReadModifyWriteDisplay(12, 0x0e, 1); // 写入缸号1          
            //UpdateReadModifyWriteDisplay(12,Mercury_1_Data_K1+Mercury_2_Data_K2+Mercury_3_Data_K3,1);	 //1/2/3号汞柱 

            Digital_tube_display(1, 2, 3, 4, 5, 0, 1900);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, 0, 1900);//2号缸
            Digital_tube_display(11, 12, 13, 14, 15, 0, 1900);//3号缸         
            break;
        case MODE_CH4:
            printf("当前模式: ch4\n");
            //UpdateReadModifyWriteDisplay(12, 0x0f, 1); // 写入缸号1
            //UpdateReadModifyWriteDisplay(12,Mercury_1_Data_K1+Mercury_2_Data_K2+Mercury_3_Data_K3,1);	 //1/2/3号汞柱
            //UpdateReadModifyWriteDisplay(23,Mercury_4_Data_K4,1);	 //4号汞柱

            Digital_tube_display(1, 2, 3, 4, 5, 0, 1900);//1号缸
            Digital_tube_display(6, 7, 8, 9, 10, 0, 1900);//2号缸
            Digital_tube_display(11, 12, 13, 14, 15, 0, 1900);//3号缸
            Digital_tube_display(16, 17, 18, 19, 20, 0, 1900);//4号缸 
            break;
    }
}

/*----------------------------------电子时钟显示模块-------------------------------------*/
extern u8 Second,Minute,Hour;//秒、分、时
// 电子时钟处理时间值
void TIME_Digital_tube_Bit_Display(uint32_t Timnum, uint8_t Timposition)
{
	//uint8_t TIMEsegment_data;
    if (Timnum > 9) return; // 处理非法输入

    //TIMEsegment_data = TIMEsegment_map[Timnum]; // 从映射表中获取段码
    switch (Timposition)//时间，电子时钟
    {			
        case 1: Group2_digitron(Timnum,9,10); break; // 时十位
        case 2: Group2_digitron(Timnum,7,8); break; // 时个位
        case 3: Group2_digitron(Timnum,5,6); break; // 分十位
        case 4: Group2_digitron(Timnum,17,16); break; // 分个位
        case 5: Group2_digitron(Timnum,19,18); break; // 秒十位
        case 6: Group2_digitron(Timnum,21,20); break; // 秒个位
        default:break; // 处理非法位置
    }
#if 0
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
#endif
}
//电子时钟 处理并显示时间值
void Clock_Display(void)//时间，电子时钟
{
     for(int i=5;i<11;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
     for(int i=16;i<22;i++)UpdateReadModifyWriteDisplay(i,0xf0,0);
    UpdateReadModifyWriteDisplay(11,Screen_Data_Time,1);//TIME图标显示   
    TIME_Digital_tube_Bit_Display(Hour / 10, 1);   
    TIME_Digital_tube_Bit_Display(Hour % 10, 2);
    UpdateReadModifyWriteDisplay(10,Group2_digitron_TIME_colon_S32,1);//冒号1显示   
    TIME_Digital_tube_Bit_Display(Minute / 10, 3);
    TIME_Digital_tube_Bit_Display(Minute % 10, 4);
    UpdateReadModifyWriteDisplay(22,Group2_digitron_TIME_colon_S38,1);//冒号2显示
    TIME_Digital_tube_Bit_Display(Second / 10, 5);
    TIME_Digital_tube_Bit_Display(Second % 10, 6);
    //if(current_settings.sensor_count == 0)UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 1);     //4T图标，因为受6号断码管影响会关掉4T图标，所以重新打开
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
 
    UpdateReadModifyWriteDisplay(14,Battery_Data_S5+Battery_Data_S1+Battery_Data_S2+Battery_Data_S3+Battery_Data_S4,0); //刷新电池个数显示 
/*----------------------------------------显示-------------------------------------------*/
        if(Adc_Data<1800)//低于4V
		{
			UpdateReadModifyWriteDisplay(14,Battery_Data_S5,1);  
            delay_ms(200);
            UpdateReadModifyWriteDisplay(14,Battery_Data_S5,0); 
            delay_ms(200);
            UpdateReadModifyWriteDisplay(14,Battery_Data_S5,1);  
            delay_ms(200);
            UpdateReadModifyWriteDisplay(14,Battery_Data_S5,0); 
            delay_ms(200);
            UpdateReadModifyWriteDisplay(14,Battery_Data_S5,1);
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

extern int history_index;  // 当前记录的索引
extern int total_records;  // 总记录数
/*----------------------------------P=0-------------------------------------*/
void	Dig_Zero(void)
{
    
	//四缸压力值、汞柱、时间 = 0；
    Second =0-1;Minute=0;Hour=0;//0-1这样才能归0
    //ADC_Value[0] = 1800;ADC_Value[1] = 1800; ADC_Value[2] = 1800; ADC_Value[3] = 1800;  //应该是1783 
    //convertedPressure[0] = 0;convertedPressure[1] = 0;convertedPressure[2] = 0;convertedPressure[3] = 0;
    // 清除所有历史记录
    //history_index = 0;total_records = 0;         //SaveCurrentHistoryIndexToFlash();// 清除所有历史记录
    //delay_ms(50);
}
extern int ProgressBar;
//P = 0 自动校0,压力归零
// 校准函数，记录当前压力值作为偏移量
void Calibration(void){
    //UpdateReadModifyWriteDisplay(15,Screen_Data_S23,1);
    switch(ProgressBar){
        case 1:UpdateReadModifyWriteDisplay(15,Screen_Data_S23,1);delay_ms(100);      break;
        case 2:UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_1,1);delay_ms(100); break;
        case 3:UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_2,1);delay_ms(100); break;            
        case 4:UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_3,1);delay_ms(100); break;            
        case 5:UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_4,1);delay_ms(100); break;  
        case 6:UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_5,1);delay_ms(100); break;
        case 7:UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_6,1);delay_ms(100); break;
        case 8:UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_7,1);delay_ms(100); break;
        case 9:UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_8,1);delay_ms(100); break;
        case 10:
                UpdateReadModifyWriteDisplay(15,Screen_Data_S23,0);
                UpdateReadModifyWriteDisplay(20,ProgressBlock_Data_1+ProgressBlock_Data_2+ProgressBlock_Data_3+ProgressBlock_Data_4,0);
                UpdateReadModifyWriteDisplay(21,ProgressBlock_Data_5+ProgressBlock_Data_6+ProgressBlock_Data_7+ProgressBlock_Data_8,0);
        break;
        default:break; // 处理非法位置
    }
}
   
/*----------------------------------P=0-------------------------------------*/


/*----------------------------------历史数据索引-----------------------------------------*/
void NumHistoricalData_Display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,int HistoricalData_num)
{
    //Clear_RMP_DigitalTubeDisplay();
    //Clear_Group1dig();
    //Switching2T4T_display();    //需重新添加2T4T，不然会被刷新
    if (HistoricalData_num >= 10000 && HistoricalData_num < 100000)//超过10000则显示不了
    {
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%100000/10000,addr_1);
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%10000/1000,addr_2);    
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%1000/100,addr_3);     
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%100/10,addr_4);     
      Digital_tube_Bit_Display((uint32_t)HistoricalData_num%10/1,addr_5);
        
    }
    else if (HistoricalData_num >= 1000 && HistoricalData_num < 10000)//超过10000则显示不了
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

/*----------------------------------历史数据MAXMINDIFF显示-----------------------------------------*/
void SettingsUint(float display_value)
{
    float temp_value = 0;
    switch(current_settings.current_unit)
    {
        case 0: // kPa   需要2位小数点
            UpdateReadModifyWriteDisplay(22, 0x30, 1);           
            temp_value = display_value * 0.1 *100;
            //temp_value = temp_value*100;           
            decimal_points = 2;
            break;

        case 1: // mmHg   1小数点
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);           
            temp_value = display_value * 7.50062;
            //temp_value = temp_value*10;            
            decimal_points = 1; 
            break;

        case 2: // Torr    1小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
           
                temp_value = display_value * 7.50062;
                //temp_value = temp_value*10;
            
            decimal_points = 1; 
            break; 

        case 3: // mbar    1小数点
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);           
            temp_value = display_value * 10;
            //temp_value = temp_value*10;           
            decimal_points = 1; 
            break;

        case 4: // inHg    2小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);           
            temp_value = display_value * 0.0295301;
            temp_value = temp_value*100;           
            decimal_points = 2; 
            break;

        case 5: // inH2O    1小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);           
            temp_value = display_value * 4.01463;
            //temp_value = temp_value*10;            
            decimal_points = 1; 
            break;

        case 6: // mmH2O    无小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);           
            temp_value = display_value * 10.1972;            
            decimal_points = 0; 
            break;

        case 7: // psi  需要2个小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);            
            temp_value = display_value* 0.0145038;
            temp_value = temp_value*100;            
            decimal_points = 2; 
            break;

        case 8: // hPa  1小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);            
            temp_value = display_value;
            temp_value = temp_value*10;                          
            decimal_points = 1; 
            break;
        default:break; // 处理非法位置
    }
    Digital_2tube_display(21, 22, 23, 24, 25, temp_value);//AD值不应该出现
   
}
void Digital_2tube_display(u8 addr_1,u8 addr_2,u8 addr_3,u8 addr_4,u8 addr_5,float display_num)//只显示压力值数码管
{
    // if (display_num < 0) {
    //     display_num = -display_num; // 转换为正数
    // }

    if (display_num < 0)
    {
        display_num = display_num*(-1);// 转换为正数display_num = display_num*(-1);
		UpdateReadModifyWriteDisplay(8,0x20,1);			
    }else{
        UpdateReadModifyWriteDisplay(8,0x20,0);	 // 清除负号段码所有位		
    }

    int integer_part = (int)display_num;   
      
    // 显示数字和小数点
    if (integer_part >= 10000) {
        Digital_tube_Bit_Display((uint32_t)integer_part % 100000 / 10000, addr_1);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10000 / 1000, addr_2);    
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3);     
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);     
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);
         if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);   
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 1000) { 
        Digital_tube_Bit_Display((uint32_t)integer_part % 10000 / 1000, addr_2);
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3);
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);   
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 100&& integer_part < 1000) {
        Digital_tube_Bit_Display((uint32_t)integer_part % 1000 / 100, addr_3); 
        Digital_tube_Bit_Display((uint32_t)integer_part % 100 / 10, addr_4);
        Digital_tube_Bit_Display((uint32_t)integer_part % 10, addr_5);   
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1);
        } else if (decimal_points == 2) {
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    } else if (integer_part >= 10&& integer_part < 100) { 
        // 当整数部分为0时，确保显示0和小数部分         
        Digital_tube_Bit_Display((uint32_t)(integer_part)%100/10,addr_4);
        Digital_tube_Bit_Display((uint32_t)(integer_part)%10,addr_5);         
        if (decimal_points == 1) {
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1); 
        }
        else if (decimal_points == 2) {
            Digital_tube_Bit_Display(0, addr_3); // 显示0
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }    
    } else if (integer_part >= 0&& integer_part < 10) {
#if 0  //p=0校准后开启归0，历史数据需同步
        if (Calibration_offset == 1) {
            integer_part = 0;
        }
#endif
        // 当整数部分为0时，确保显示0和小数部分
        Digital_tube_Bit_Display((uint32_t)(integer_part)%10,addr_5); 
        if (decimal_points == 1) {
            Digital_tube_Bit_Display(0, addr_4); // 显示0
            UpdateDecimalPoint(addr_1, 35, 25, 0x10, 0x01); // 显示一位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(20, 0x80, 1); 
        } else if (decimal_points == 2) {
            Digital_tube_Bit_Display(0, addr_3); // 显示0
            Digital_tube_Bit_Display(0, addr_4); // 显示0
            UpdateDecimalPoint(addr_1, 37, 27, 0x10, 0x01); // 显示两位小数点
            if(in_submode  == 1) UpdateReadModifyWriteDisplay(18, 0x80, 1); 
        }
    }
}
/*----------------------------------历史数据MAXMINDIFF显示-----------------------------------------*/

/*----------------------------------------设置模式显示---------------------------------------------*/
//单位选择
void SettingsUint_display(void)
{
    UpdateReadModifyWriteDisplay(22, 0x3f, 0); // 刷新显示内容     
    UpdateReadModifyWriteDisplay(23, 0x3f, 0); // 刷新显示内容  
    switch(current_settings.current_unit)
    {
        case 0: // kPa   需要2位小数点
            UpdateReadModifyWriteDisplay(22, 0x30, 1);
            break;

        case 1: // mmHg   1小数点
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_mmHg, 1);
            break;

        case 2: // Torr    1小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_Torr, 1);
            break; 

        case 3: // mbar    1小数点
            UpdateReadModifyWriteDisplay(22, Switching_Unit_Data_m + Switching_Unit_Data_bar, 1);
            break;

        case 4: // inHg    2小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inHg, 1);
            break;

        case 5: // inH2O    1小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_inH2O, 1);
          break;

        case 6: // mmH2O    无小数点   这个单位立项报告没要求
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_mmH2O, 1);
            break;

        case 7: // psi  需要2个小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_psi, 1);
            break;

        case 8: // hPa  1小数点
            UpdateReadModifyWriteDisplay(23, Switching_Unit_Data_hpa, 1);
            break;
         default:break; // 处理非法位置
    }
}

//冲程选择
void Switching2T4T_display(void)
{    
    UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 0);   
    UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 0);   
    if(current_settings.stroke2T4T_mode==0){
        UpdateReadModifyWriteDisplay(10, Screen_Data_4T, 1);   //4T

    }else{          
         UpdateReadModifyWriteDisplay(15, Screen_Data_2T, 1);   //2T

    }
    
}
//是否自动关机选择
void AUutoshutdownONOFF_display(void)
{    
    UpdateReadModifyWriteDisplay(11, Screen_Data_Auto+Screen_Data_on+Screen_Data_off, 0);   
    
    if(current_settings.auto_shutdown_enabled==0){
         UpdateReadModifyWriteDisplay(11, Screen_Data_Auto+Screen_Data_off, 0);   
         UpdateReadModifyWriteDisplay(11, Screen_Data_Auto+Screen_Data_off, 1);   //关闭自动关机
    }else{          
         UpdateReadModifyWriteDisplay(11, Screen_Data_Auto+Screen_Data_on, 1);  //开启自动关机

    }
    
}
/*----------------------------------------设置模式显示---------------------------------------------*/



