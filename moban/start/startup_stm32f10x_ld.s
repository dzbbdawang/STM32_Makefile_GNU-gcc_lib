@ ******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
@ File Name          : startup_stm32f10x_ld.s
@ Author             : MCD Application Team
@ Version            : V3.5.0
@ Date               : 11-March-2011
@ Description        : STM32F10x Low Density Devices vector table for GNU toolchain.
@                      This module performs:
@                      - Set the initial SP
@                      - Set the initial PC == Reset_Handler
@                      - Set the vector table entries with the exceptions ISR address
@                      - Configure the clock system
@                      - Branches to __main in the C library (which eventually
@                        calls main()).
@                      After Reset the CortexM3 processor is in Thread mode,
@                      priority is Privileged, and the Stack is set to Main.
@ <<< Use Configuration Wizard in Context Menu >>>   
@ *******************************************************************************

@ Amount of memory (in bytes) allocated for Stack
@ Tailor this value to your application needs
@ <h> Stack Configuration
@   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
@ </h>

Stack_Size      = 0x00000400

                .section .stack
                .align 3
                .space   Stack_Size
                .global __initial_sp
__initial_sp:

@ <h> Heap Configuration
@   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
@ </h>

Heap_Size       = 0x00000200

                .section .heap
                .align 3
                .space   Heap_Size
                .global  __heap_base
                .global  __heap_limit

@ Vector Table Mapped to Address 0 at Reset
                .section .isr_vector,"a",%progbits
                .align 3
                .global  __Vectors
                .global  __Vectors_End
                .global  __Vectors_Size

__Vectors:
                .word    __initial_sp              @ Top of Stack
                .word    ResetHandler             @ Reset Handler
                .word    NMI_Handler               @ NMI Handler
                .word    HardFault_Handler         @ Hard Fault Handler
                .word    MemManage_Handler         @ MPU Fault Handler
                .word    BusFault_Handler          @ Bus Fault Handler
                .word    UsageFault_Handler        @ Usage Fault Handler
                .word    0                         @ Reserved
                .word    0                         @ Reserved
                .word    0                         @ Reserved
                .word    0                         @ Reserved
                .word    SVC_Handler               @ SVCall Handler
                .word    DebugMon_Handler          @ Debug Monitor Handler
                .word    0                         @ Reserved
                .word    PendSV_Handler            @ PendSV Handler
                .word    SysTick_Handler           @ SysTick Handler

                @ External Interrupts
                .word     WWDG_IRQHandler           @ Window Watchdog
                .word     PVD_IRQHandler            @ PVD through EXTI Line detect
                .word     TAMPER_IRQHandler         @ Tamper
                .word     RTC_IRQHandler            @ RTC
                .word     FLASH_IRQHandler          @ Flash
                .word     RCC_IRQHandler            @ RCC
                .word     EXTI0_IRQHandler          @ EXTI Line 0
                .word     EXTI1_IRQHandler          @ EXTI Line 1
                .word     EXTI2_IRQHandler          @ EXTI Line 2
                .word     EXTI3_IRQHandler          @ EXTI Line 3
                .word     EXTI4_IRQHandler          @ EXTI Line 4
                .word     DMA1_Channel1_IRQHandler  @ DMA1 Channel 1
                .word     DMA1_Channel2_IRQHandler  @ DMA1 Channel 2
                .word     DMA1_Channel3_IRQHandler  @ DMA1 Channel 3
                .word     DMA1_Channel4_IRQHandler  @ DMA1 Channel 4
                .word     DMA1_Channel5_IRQHandler  @ DMA1 Channel 5
                .word     DMA1_Channel6_IRQHandler  @ DMA1 Channel 6
                .word     DMA1_Channel7_IRQHandler  @ DMA1 Channel 7
                .word     ADC1_2_IRQHandler         @ ADC1 & ADC2
                .word     USB_HP_CAN1_TX_IRQHandler @ USB High Priority or CAN1 TX
                .word     USB_LP_CAN1_RX0_IRQHandler @ USB Low  Priority or CAN1 RX0
                .word     CAN1_RX1_IRQHandler       @ CAN1 RX1
                .word     CAN1_SCE_IRQHandler       @ CAN1 SCE
                .word     EXTI9_5_IRQHandler        @ EXTI Line 9..5
                .word     TIM1_BRK_IRQHandler       @ TIM1 Break
                .word     TIM1_UP_IRQHandler        @ TIM1 Update
                .word     TIM1_TRG_COM_IRQHandler   @ TIM1 Trigger and Commutation
                .word     TIM1_CC_IRQHandler        @ TIM1 Capture Compare
                .word     TIM2_IRQHandler           @ TIM2
                .word     TIM3_IRQHandler           @ TIM3
                .word     0                         @ Reserved
                .word     I2C1_EV_IRQHandler        @ I2C1 Event
                .word     I2C1_ER_IRQHandler        @ I2C1 Error
                .word     0                         @ Reserved
                .word     0                         @ Reserved
                .word     SPI1_IRQHandler           @ SPI1
                .word     0                         @ Reserved
                .word     USART1_IRQHandler         @ USART1
                .word     USART2_IRQHandler         @ USART2
                .word     0                         @ Reserved
                .word     EXTI15_10_IRQHandler      @ EXTI Line 15..10
                .word     RTCAlarm_IRQHandler       @ RTC Alarm through EXTI Line
                .word     USBWakeUp_IRQHandler      @ USB Wakeup from suspend

__Vectors_End:
__Vectors_Size  = __Vectors_End - __Vectors

                .section .text
                .thumb
                .align 3

@ Reset handler routine
                .global  Reset_Handler
                .weak    Reset_Handler
Reset_Handler:  
                .global  __main
                .global  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0

@ Dummy Exception Handlers (infinite loops which can be modified)
                .global  NMI_Handler
                .weak    NMI_Handler
NMI_Handler:
                B       .

                .global  HardFault_Handler
                .weak    HardFault_Handler
HardFault_Handler:
                B       .

                .global  MemManage_Handler
                .weak    MemManage_Handler
MemManage_Handler:
                B       .

                .global  BusFault_Handler
                .weak    BusFault_Handler
BusFault_Handler:
                B       .

                .global  UsageFault_Handler
                .weak    UsageFault_Handler
UsageFault_Handler:
                B       .

                .global  SVC_Handler
                .weak    SVC_Handler
SVC_Handler:
                B       .

                .global  DebugMon_Handler
                .weak    DebugMon_Handler
DebugMon_Handler:
                B       .

                .global  PendSV_Handler
                .weak    PendSV_Handler
PendSV_Handler:
                B       .

                .global  SysTick_Handler
                .weak    SysTick_Handler
SysTick_Handler:
                B       .

                .global  Default_Handler
Default_Handler:
                .weak    WWDG_IRQHandler
                .weak    PVD_IRQHandler
                .weak    TAMPER_IRQHandler
                .weak    RTC_IRQHandler
                .weak    FLASH_IRQHandler
                .weak    RCC_IRQHandler
                .weak    EXTI0_IRQHandler
                .weak    EXTI1_IRQHandler
                .weak    EXTI2_IRQHandler
                .weak    EXTI3_IRQHandler
                .weak    EXTI4_IRQHandler
                .weak    DMA1_Channel1_IRQHandler
                .weak    DMA1_Channel2_IRQHandler
                .weak    DMA1_Channel3_IRQHandler
                .weak    DMA1_Channel4_IRQHandler
                .weak    DMA1_Channel5_IRQHandler
                .weak    DMA1_Channel6_IRQHandler
                .weak    DMA1_Channel7_IRQHandler
                .weak    ADC1_2_IRQHandler
                .weak    USB_HP_CAN1_TX_IRQHandler
                .weak    USB_LP_CAN1_RX0_IRQHandler
                .weak    CAN1_RX1_IRQHandler
                .weak    CAN1_SCE_IRQHandler
                .weak    EXTI9_5_IRQHandler
                .weak    TIM1_BRK_IRQHandler
                .weak    TIM1_UP_IRQHandler
                .weak    TIM1_TRG_COM_IRQHandler
                .weak    TIM1_CC_IRQHandler
                .weak    TIM2_IRQHandler
                .weak    TIM3_IRQHandler
                .weak    I2C1_EV_IRQHandler
                .weak    I2C1_ER_IRQHandler
                .weak    SPI1_IRQHandler
                .weak    USART1_IRQHandler
                .weak    USART2_IRQHandler
                .weak    EXTI15_10_IRQHandler
                .weak    RTCAlarm_IRQHandler
                .weak    USBWakeUp_IRQHandler

WWDG_IRQHandler:
PVD_IRQHandler:
TAMPER_IRQHandler:
RTC_IRQHandler:
FLASH_IRQHandler:
RCC_IRQHandler:
EXTI0_IRQHandler:
EXTI1_IRQHandler:
EXTI2_IRQHandler:
EXTI3_IRQHandler:
EXTI4_IRQHandler:
DMA1_Channel1_IRQHandler:
DMA1_Channel2_IRQHandler:
DMA1_Channel3_IRQHandler:
DMA1_Channel4_IRQHandler:
DMA1_Channel5_IRQHandler:
DMA1_Channel6_IRQHandler:
DMA1_Channel7_IRQHandler:
ADC1_2_IRQHandler:
USB_HP_CAN1_TX_IRQHandler:
USB_LP_CAN1_RX0_IRQHandler:
CAN1_RX1_IRQHandler:
CAN1_SCE_IRQHandler:
EXTI9_5_IRQHandler:
TIM1_BRK_IRQHandler:
TIM1_UP_IRQHandler:
TIM1_TRG_COM_IRQHandler:
TIM1_CC_IRQHandler:
TIM2_IRQHandler:
TIM3_IRQHandler:
I2C1_EV_IRQHandler:
I2C1_ER_IRQHandler:
SPI1_IRQHandler:
USART1_IRQHandler:
USART2_IRQHandler:
EXTI15_10_IRQHandler:
RTCAlarm_IRQHandler:
USBWakeUp_IRQHandler:
                B       .

@ *******************************************************************************
@ User Stack and Heap initialization
@ *******************************************************************************
                .ifdef __MICROLIB
                
                .global  __initial_sp
                .global  __heap_base
                .global  __heap_limit
                
                .else
                
                .global  __use_two_region_memory
                .global  __user_initial_stackheap
                 
__user_initial_stackheap:

                LDR     R0, =Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, =(Heap_Mem + Heap_Size)
                LDR     R3, =Stack_Mem
                BX      LR

                .align 3

                .endif

@ ******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE*****
