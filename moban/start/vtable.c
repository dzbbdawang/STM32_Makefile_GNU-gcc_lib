/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_vector.c
* Author             : MCD Application Team
* Version            : V1.0
* Date               : 10/08/2007
* Description        : This file contains the vector table for STM32F10x.
*                      After Reset the Cortex-M3 processor is in Thread mode,
*                      priority is Privileged, and the Stack is set to Main.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

void NMIException(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void HardFaultException(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void MemManageException(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void BusFaultException(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void UsageFaultException(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DebugMonitor(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void SVCHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void PendSVC(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void SysTickHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));

/* Peripherals handlers */

void WWDG_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void PVD_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TAMPER_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void RTC_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void FLASH_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void RCC_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void EXTI0_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void EXTI1_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void EXTI2_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void EXTI3_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void EXTI4_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DMAChannel1_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DMAChannel2_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DMAChannel3_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DMAChannel4_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DMAChannel5_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DMAChannel6_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void DMAChannel7_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void ADC_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void USB_HP_CAN_TX_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void USB_LP_CAN_RX0_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void CAN_RX1_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void CAN_SCE_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void EXTI9_5_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TIM1_BRK_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TIM1_UP_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TIM1_TRG_COM_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TIM1_CC_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TIM2_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TIM3_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void TIM4_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void I2C1_EV_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void I2C1_ER_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void I2C2_EV_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void I2C2_ER_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void SPI1_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void SPI2_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void USART1_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void USART2_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void USART3_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void EXTI15_10_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void RTCAlarm_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));
void USBWakeUp_IRQHandler(void) __attribute__ ((weak, alias("IntDefaultHandler")));


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern unsigned long _etext;
extern unsigned long _sidata;		/* start address for the initialization values
                                   of the .data section. defined in linker script */
extern unsigned long _sdata;		/* start address for the .data section. defined
                                   in linker script */
extern unsigned long _edata;		/* end address for the .data section. defined in
                                   linker script */

extern unsigned long _sbss;			/* start address for the .bss section. defined
                                   in linker script */
extern unsigned long _ebss;			/* end address for the .bss section. defined in
                                   linker script */

extern void _estack;		/* init value for the stack pointer. defined in linker script */



/* Private typedef -----------------------------------------------------------*/
/* function prototypes -------------------------------------------------------*/
void Reset_Handler(void) __attribute__((__interrupt__));
extern int main(void);


/*******************************************************************************
*
* Cortex M3的最小向量表。注意必须正确放置以确保它最终位于物理地址
* 0x0000.0000。
*
*******************************************************************************/


/*__attribute__ ((section(".vectors"), used))//定义向量表*/
void (* const gVectors[])(void) = 
{
  (void (*)(void))((unsigned long)&_estack), // The initial stack pointer
  Reset_Handler,             // The reset handler
  NMIException,
  HardFaultException,
  MemManageException,
  BusFaultException,
  UsageFaultException,
  0, 0, 0, 0,            // 
  SVCHandler,
  DebugMonitor,
  0,                      //
  PendSVC,
  SysTickHandler,
  WWDG_IRQHandler,
  PVD_IRQHandler,
  TAMPER_IRQHandler,
  RTC_IRQHandler,
  FLASH_IRQHandler,
  RCC_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  DMAChannel1_IRQHandler,
  DMAChannel2_IRQHandler,
  DMAChannel3_IRQHandler,
  DMAChannel4_IRQHandler,
  DMAChannel5_IRQHandler,
  DMAChannel6_IRQHandler,
  DMAChannel7_IRQHandler,
  ADC_IRQHandler,
  USB_HP_CAN_TX_IRQHandler,
  USB_LP_CAN_RX0_IRQHandler,
  CAN_RX1_IRQHandler,
  CAN_SCE_IRQHandler,
  EXTI9_5_IRQHandler,//
  TIM1_BRK_IRQHandler,
  TIM1_UP_IRQHandler,
  TIM1_TRG_COM_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ER_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ER_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  EXTI15_10_IRQHandler,
  RTCAlarm_IRQHandler,
  USBWakeUp_IRQHandler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (unsigned short)0xF108F85F //this is a workaround for boot in RAM mode.
};

/*******************************************************************************
* 函数名称  : Reset_Handler
* 描述      : 这是处理器在复位事件后首次开始执行时调用的代码。
*             只执行绝对必要的设置，之后调用应用程序提供的main()例程。
* 输入      :
* 输出      :
* 返回      :
*******************************************************************************/
void ResetHandler(void)
{
    unsigned long *pulSrc, *pulDest;
    SystemInit();
    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pulSrc = &_sidata;
    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    //
    // Zero fill the bss segment.
    //
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    //
    // Call the application's entry point.
    //
    main();
}


void IntDefaultHandler(void)
{
   for(;;);
}
/****************** (C) COPYRIGHT 2007 STMicroelectronics  *****END OF FILE****/


