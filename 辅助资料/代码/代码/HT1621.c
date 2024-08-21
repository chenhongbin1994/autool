#include "stm32f10x.h"

#define HT1621_PORT GPIOA
#define HT1621_DATA_PIN GPIO_Pin_0
#define HT1621_WR_PIN GPIO_Pin_1
#define HT1621_RD_PIN GPIO_Pin_2
#define HT1621_CS_PIN GPIO_Pin_3

void HT1621_Init(void);
void HT1621_WriteCmd(uint8_t cmd);
void HT1621_WriteData(uint8_t address, uint8_t data);
uint8_t HT1621_ReadData(uint8_t address);
void HT1621_Clear(void);
void HT1621_DisplayNumber(uint8_t number);

int main(void) {
    HT1621_Init();
    
    while (1) {
        // 在这里添加你的代码来控制显示内容
    }
}

void HT1621_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = HT1621_DATA_PIN | HT1621_WR_PIN | HT1621_RD_PIN | HT1621_CS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HT1621_PORT, &GPIO_InitStruct);

    // 初始化时钟信号
    GPIO_SetBits(HT1621_PORT, HT1621_WR_PIN);

    // 初始化片选信号
    GPIO_ResetBits(HT1621_PORT, HT1621_CS_PIN);

    // 初始化数据线
    GPIO_ResetBits(HT1621_PORT, HT1621_DATA_PIN);
    for (int i = 0; i < 4; i++) {
        GPIO_SetBits(HT1621_PORT, HT1621_WR_PIN);
    }

    // 初始化结束，释放片选信号
    GPIO_SetBits(HT1621_PORT, HT1621_CS_PIN);
}

void HT1621_WriteCmd(uint8_t cmd) {
    uint8_t i;

    // 传输命令
    GPIO_ResetBits(HT1621_PORT, HT1621_CS_PIN);
    for (i = 0; i < 4; i++) {
        if (cmd & 0x01) {
            GPIO_SetBits(HT1621_PORT, HT1621_DATA_PIN);
        } else {
            GPIO_ResetBits(HT1621_PORT, HT1621_DATA_PIN);
        }
        GPIO_ResetBits(HT1621_PORT, HT1621_WR_PIN);
        GPIO_SetBits(HT1621_PORT, HT1621_WR_PIN);
        cmd >>= 1;
    }
    GPIO_SetBits(HT1621_PORT, HT1621_CS_PIN);
}

void HT1621_WriteData(uint8_t address, uint8_t data) {
    uint8_t i;

    // 传输数据命令
    HT1621_WriteCmd(0b01000000 | (address & 0b00111111));

    // 传输数据
    for (i = 0; i < 4; i++) {
        if (data & 0x80) {
            GPIO_SetBits(HT1621_PORT, HT1621_DATA_PIN);
        } else {
            GPIO_ResetBits(HT1621_PORT, HT1621_DATA_PIN);
        }
        GPIO_ResetBits(HT1621_PORT, HT1621_WR_PIN);
        GPIO_SetBits(HT1621_PORT, HT1621_WR_PIN);
        data <<= 1;
    }
}

uint8_t HT1621_ReadData(uint8_t address) {
    uint8_t i, data = 0;

    // 读取数据命令
    HT1621_WriteCmd(0b11000000 | (address & 0b00111111));

    // 读取数据
    GPIO_ResetBits(HT1621_PORT, HT1621_CS_PIN);
    for (i = 0; i < 4; i++) {
        data <<= 1;
        if (GPIO_ReadInputDataBit(HT1621_PORT, HT1621_DATA_PIN)) {
            data |= 0x01;
        }
        GPIO_ResetBits(HT1621_PORT, HT1621_WR_PIN);
        GPIO_SetBits(HT1621_PORT, HT1621_WR_PIN);
    }
    GPIO_SetBits(HT1621_PORT, HT1621_CS_PIN);
    return data;
}

void HT1621_Clear(void) {
    for (uint8_t i = 0; i < 11; i++) {
        HT1621_WriteData(i * 2, 0);
    }
}

void HT1621_DisplayNumber(uint8_t number) {
    static const uint8_t digitPatterns[10] = {
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4F, // 3
        0x66, // 4
        0x6D, // 5
        0x7D, // 6
        0x07, // 7
        0x7F, // 8
        0x6F  // 9
    };

    if (number < 10) {
        HT1621_WriteData(0, digitPatterns[number]);
    }
}
