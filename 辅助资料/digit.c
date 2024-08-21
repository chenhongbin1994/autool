void Digital_tube_display(float dispaly_num)
{
  uint8_t Ram_Temp_2=0;
  if(dispaly_num  < 0)//????????????ж?
  {
    Icon_S7_On;//?????-??????
  }
  else
  {
    Ram_Temp_2  = ReadDataFromHT1621B(SEG7);
    Ram_Temp_2  = Ram_Temp_2  & 0X07;//0X08??????-????????
    WriteDisplayDatatoHT1621(SEG7, Ram_Temp_2);
  }
  
  if(dispaly_num  < 0)//???????
  {
    dispaly_num = dispaly_num*(-1);
  }
  
  /*??λ??????С?????*/
  if((dispaly_num>=1000)&&(dispaly_num<10000))//????1000С??10000
    {
      /*??1λ*/
      Digital_tube_Bit_Display((uint32_t)dispaly_num%10000/1000,1);
      /*??2λ*/
      Digital_tube_Bit_Display((uint32_t)dispaly_num%1000/100,2);
      /*??3λ*/
      Digital_tube_Bit_Display((uint32_t)dispaly_num%100/10,3);
      /*??4λ*/
      Digital_tube_Bit_Display((uint32_t)dispaly_num%10/1,4);
    }
  else if((dispaly_num>=100)&&(dispaly_num<1000))//???????100??С??1000,1λС??
    {
      /*??1λ*/
      Digital_tube_Bit_Display((uint32_t)dispaly_num%1000/100,1); // Icon_SEG6_Off;
      /*??2λ*/
      Digital_tube_Bit_Display((uint32_t)dispaly_num%100/10,2);
      /*??3λ*/
      Digital_tube_Bit_Display((uint32_t)dispaly_num%10/1,3);
      /*??4λ*/
      Digital_tube_Bit_Display((uint32_t)(dispaly_num*10)%10,4);
      /*???P3?????SEG??RAM?е?????*/
      Ram_Temp_2  = ReadDataFromHT1621B(1);
      /*??С??????????RAM??*/
      Ram_Temp_2  =  Ram_Temp_2 | 0X08;
      /*??RAM_tempд??RAM*/
      WriteDisplayDatatoHT1621(1, Ram_Temp_2);
    }
  else if((dispaly_num>=10)&&(dispaly_num<100))//??????????10??С??100??2λС??
    {
      /*??1λ*/
      Digital_tube_Bit_Display((uint32_t)(dispaly_num*100)/1000,1);
      /*??2λ*/
      Digital_tube_Bit_Display((uint32_t)(dispaly_num*100)%1000/100,2);
      /*??3λ*/
      Digital_tube_Bit_Display((uint32_t)(dispaly_num*100)%100/10,3);
      /*??4λ*/
      Digital_tube_Bit_Display((uint32_t)(dispaly_num*100)%10,4);
      /*???P2?????SEG3??RAM?е?????*/
      Ram_Temp_2  = ReadDataFromHT1621B(3);
      /*??С??????????RAM?
	  
	  uint8_t ReadDataFromHT1621B(uint8_t addr)
{
  GPIO_InitTypeDef PA7_InitStruct = {0};

	LCD_CS_LOW ;  //????CS??  CS????? WR??Ч
  WriteDatatoHT1621(0XC0,3);//д????????110    0xC0 ?????3BIT
	WriteDatatoHT1621(addr<<2,6);  //д??6bit???????
	sdata = 0;
  
  LCD_WR_HIGH;//????WR??
  /*????PA7 LCD_DATA_Pin?????????*/
  PA7_InitStruct.Pin = LCD_DATA_Pin;
  PA7_InitStruct.Mode = GPIO_MODE_INPUT;
  PA7_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &PA7_InitStruct);
  for(i_cnt=0;i_cnt<4;i_cnt++)
  {
      /*????????*/
      LCD_RD_LOW;
      delay_xns(180);
      LCD_RD_HIGH;
      if(HAL_GPIO_ReadPin(GPIOA,LCD_DATA_Pin))
      {
        sdata |= 0x01; 
      }
      delay_xns(170); 
      if(i_cnt  <3)
      sdata=sdata<<1;
  }
//  sdata = sdata>>4;//??4λ??λ??????λ

  PA7_InitStruct.Pin = LCD_DATA_Pin;
  PA7_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  PA7_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &PA7_InitStruct);
  // GPIOA->MODER = (GPIOA->MODER)|0xffff7fff;// set LCD_DATA(PA7) to output 
//  WriteDatatoHT1621(0,1);
  LCD_CS_HIGH;// ????CS ???? 
  
	return sdata;
}


uint8_t ReadDataFromHT1621B(uint8_t addr)
{
  GPIO_InitTypeDef PA7_InitStruct = {0};

	LCD_CS_LOW ;  //????CS??  CS????? WR??Ч
  WriteDatatoHT1621(0XC0,3);//д????????110    0xC0 ?????3BIT
	WriteDatatoHT1621(addr<<2,6);  //д??6bit???????
	sdata = 0;
  
  LCD_WR_HIGH;//????WR??
  /*????PA7 LCD_DATA_Pin?????????*/
  PA7_InitStruct.Pin = LCD_DATA_Pin;
  PA7_InitStruct.Mode = GPIO_MODE_INPUT;
  PA7_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &PA7_InitStruct);
  for(i_cnt=0;i_cnt<4;i_cnt++)
  {
      /*????????*/
      LCD_RD_LOW;
      delay_xns(180);
      LCD_RD_HIGH;
      if(HAL_GPIO_ReadPin(GPIOA,LCD_DATA_Pin))
      {
        sdata |= 0x01; 
      }
      delay_xns(170); 
      if(i_cnt  <3)
      sdata=sdata<<1;
  }
//  sdata = sdata>>4;//??4λ??λ??????λ

  PA7_InitStruct.Pin = LCD_DATA_Pin;
  PA7_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  PA7_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &PA7_InitStruct);
  // GPIOA->MODER = (GPIOA->MODER)|0xffff7fff;// set LCD_DATA(PA7) to output 
//  WriteDatatoHT1621(0,1);
  LCD_CS_HIGH;// ????CS ???? 
  
	return sdata;
}




--------------------------------------------------------------------------------------------
#include "stm32f10x.h"
#include "LCD_HT1623.h"
#include "delay.h"
#include "timer.h"

// 数码管段映射，假设7段数码管
const uint8_t segment_map[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// 数码管位显示函数
void Digital_tube_Bit_Display(uint32_t num, uint8_t position)
{
    uint8_t segment_data;

    if (num > 9)
        return; // 处理非法输入

    segment_data = segment_map[num]; // 从映射表中获取段码

    switch (position)
    {
    case 1:
        Write_1623HalfByte(0, segment_data);
        break;
    case 2:
        Write_1623HalfByte(1, segment_data);
        break;
    case 3:
        Write_1623HalfByte(2, segment_data);
        break;
    case 4:
        Write_1623HalfByte(3, segment_data);
        break;
    default:
        break; // 处理非法位置
    }
}

// 数码管显示函数
void Digital_tube_display(float display_num)
{
    uint8_t Ram_Temp_2 = 0;

    // 处理负数情况
    if (display_num < 0)
    {
        dispON(7, 0); // 打开负号图标
    }
    else
    {
        Ram_Temp_2 = HT1623_ReadByte(7);
        Ram_Temp_2 &= 0x07; // 清除负号位
        Write_1623HalfByte(7, Ram_Temp_2);
    }

    if (display_num < 0)
    {
        display_num = -display_num; // 转换为正数
    }

    // 根据数值范围选择不同的显示方式
    if (display_num >= 1000 && display_num < 10000)
    {
        Digital_tube_Bit_Display((uint32_t)display_num % 10000 / 1000, 1);
        Digital_tube_Bit_Display((uint32_t)display_num % 1000 / 100, 2);
        Digital_tube_Bit_Display((uint32_t)display_num % 100 / 10, 3);
        Digital_tube_Bit_Display((uint32_t)display_num % 10, 4);
    }
    else if (display_num >= 100 && display_num < 1000)
    {
        Digital_tube_Bit_Display((uint32_t)display_num % 1000 / 100, 1);
        Digital_tube_Bit_Display((uint32_t)display_num % 100 / 10, 2);
        Digital_tube_Bit_Display((uint32_t)display_num % 10, 3);
        Digital_tube_Bit_Display((uint32_t)(display_num * 10) % 10, 4);

        Ram_Temp_2 = HT1623_ReadByte(1);
        Ram_Temp_2 |= 0x08; // 设置小数点位
        Write_1623HalfByte(1, Ram_Temp_2);
    }
    else if (display_num >= 10 && display_num < 100)
    {
        Digital_tube_Bit_Display((uint32_t)(display_num * 100) / 1000, 1);
        Digital_tube_Bit_Display((uint32_t)(display_num * 100) % 1000 / 100, 2);
        Digital_tube_Bit_Display((uint32_t)(display_num * 100) % 100 / 10, 3);
        Digital_tube_Bit_Display((uint32_t)(display_num * 100) % 10, 4);

        Ram_Temp_2 = HT1623_ReadByte(3);
        Ram_Temp_2 |= 0x08; // 设置小数点位
        Write_1623HalfByte(3, Ram_Temp_2);
    }
}

/***********************************************
Function :void LCD_GpioInit(void)
Description:LCD管脚初始化
Parameter: 空
************************************************/
void LCD_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LCD_B_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_B_CS_PIN | LCD_B_WR_PIN | LCD_B_RD_PIN | LCD_B_Data_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LCD_B_Port, &GPIO_InitStructure);

    GPIO_ResetBits(LCD_B_Port, LCD_B_LED_PIN);
    GPIO_SetBits(LCD_B_Port, LCD_B_CS_PIN | LCD_B_WR_PIN | LCD_B_RD_PIN | LCD_B_Data_PIN);
}

/***********************************************
Function :void SystemClock_Config(void)
Description:配置系统时钟
Parameter: 空
************************************************/
void SystemClock_Config(void)
{
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_WaitForHSEStartUp() == ERROR);

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1, ENABLE);
}

/***********************************************
Function :void MX_GPIO_Init(void)
Description:初始化 GPIO
Parameter: 空
************************************************/
void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/***********************************************
Function :void MX_SPI_Init(void)
Description:初始化 SPI
Parameter: 空
************************************************/
void MX_SPI_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

/***********************************************
Function :int main(void)
Description:主函数
Parameter: 空
************************************************/
int main(void)
{
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI_Init();
    LCD_GpioInit();
    LCD_Init();

    // 示例：显示 123.4
    Digital_tube_display(123.4f);

    while (1)
    {
        // 主循环
    }