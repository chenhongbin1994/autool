#include "stm32f10x.h"

#define SHORT_PRESS_THRESHOLD  50    // 短按阈值（毫秒）
#define LONG_PRESS_THRESHOLD   1000  // 长按阈值（毫秒）
#define DOUBLE_CLICK_DELAY    300    // 双击延迟（毫秒）

typedef enum {
    BUTTON_IDLE,
    BUTTON_PRESSED,
    BUTTON_SHORT_PRESSED,
    BUTTON_LONG_PRESSED,
    BUTTON_DOUBLE_CLICKED
} ButtonState;

volatile uint32_t button1StartTime = 0;
volatile uint32_t button2StartTime = 0;
volatile uint32_t button3StartTime = 0;
volatile uint32_t button4StartTime = 0;
volatile uint32_t button5StartTime = 0;
volatile uint32_t button6StartTime = 0;
volatile ButtonState button1State = BUTTON_IDLE;
volatile ButtonState button2State = BUTTON_IDLE;
volatile ButtonState button3State = BUTTON_IDLE;
volatile ButtonState button4State = BUTTON_IDLE;
volatile ButtonState button5State = BUTTON_IDLE;
volatile ButtonState button6State = BUTTON_IDLE;

void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        if (button1State == BUTTON_IDLE) {
            button1StartTime = HAL_GetTick();
            button1State = BUTTON_PRESSED;
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
        if (button2State == BUTTON_IDLE) {
            button2StartTime = HAL_GetTick();
            button2State = BUTTON_PRESSED;
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

// Implement similar handlers for other buttons

void checkButtonState(void) {
    uint32_t currentTime = HAL_GetTick();

    // Button 1
    if (button1State == BUTTON_PRESSED && currentTime - button1StartTime >= SHORT_PRESS_THRESHOLD) {
        button1State = BUTTON_SHORT_PRESSED;
        // 执行按键一的短按操作
    } else if (button1State == BUTTON_PRESSED && currentTime - button1StartTime >= LONG_PRESS_THRESHOLD) {
        button1State = BUTTON_LONG_PRESSED;
        // 执行按键一的长按操作
    }

    // Implement similar logic for other buttons
}

int main(void) {
    // 初始化 HAL 库
    HAL_Init();

    // 初始化按键 GPIO 和外部中断
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    // 初始化按键 1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 初始化按键 2
    // 实现类似的初始化过程

    while (1) {
        checkButtonState();

        switch (button1State) {
            case BUTTON_SHORT_PRESSED:
                // 执行按键一的短按操作
                break;
            case BUTTON_LONG_PRESSED:
                // 执行按键一的长按操作
                break;
            default:
                break;
        }

        // Implement similar switch-case blocks for other buttons

        HAL_Delay(10); // 适当延迟，降低 CPU 占用
    }
}
