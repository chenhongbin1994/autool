/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"


volatile uint32_t systemTicks = 0;
#if 0
#define size 10
char Usart1_data[size];
uint8_t ret=0;

extern uint8_t led_flag;
						 
uint8_t dma_flag=0;
#endif
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	systemTicks++;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
//编写中断服务函数
#if 0
void USART1_IRQHandler(void)  //串口控制中断
{
	uint8_t val;
	if(SET==USART_GetITStatus(USART1, USART_IT_RXNE)){
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART_SendData(USART1, USART_ReceiveData(USART1));
		Usart1_data[ret]=USART_ReceiveData(USART1);
		ret++;
		if((Usart1_data[0]!='o')&&(Usart1_data[0]!='c')){
			ret=0;
			memset(Usart1_data,0,sizeof(Usart1_data));
			}else{
				if(ret>3){
					if(0==strcmp("open",(const char *)Usart1_data)){
						LED_CTRL(Led_b, Led_open);
						ret=0;
			            memset(Usart1_data,0,sizeof(Usart1_data));
						}
					if(0==strcmp("close",(const char *)Usart1_data)){
						LED_CTRL(Led_b, Led_close);
						ret=0;
			            memset(Usart1_data,0,sizeof(Usart1_data));
						}
					}
				}
			if(ret>4){
				ret=0;
			    memset(Usart1_data,0,sizeof(Usart1_data));
				}

			
		}
		
		if(SET==USART_GetITStatus(USART1, USART_IT_IDLE)){
			//清除总线空闲标志位
			USART_ReceiveData(USART1);
			USART_SendData(USART1,'a');
			
	} 
}

void EXTI0_IRQHandler(void)
{
	if(SET==EXTI_GetITStatus(EXTI_Line0)){
		EXTI_ClearITPendingBit(EXTI_Line0);
		led_flag=~led_flag;
		}

}

void TIM6_IRQHandler(void)
{
	if(SET==TIM_GetITStatus(TIM6,TIM_IT_Update)){
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		led_flag=~led_flag;
		}


}


void DMA1_Channel2_IRQHandler(void)
{
	if(SET==DMA_GetITStatus(DMA1_IT_TC2)){
		DMA_ClearITPendingBit(DMA1_IT_TC2);
		dma_flag=1;
			
	}

}
#endif

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
