#include "stm32f10x.h" // 确保包含正确的头文件
#include "stm32f10x_gpio.h" // 添加 GPIO 相关的头文件
#include "stm32f10x_rcc.h" // 添加 RCC 相关的头文件
#include "stm32f10x_tim.h" // 添加定时器相关的头文件

// 使用PA5端口接收中断输入，然后点亮PB5(低电平点亮，默认高电平)

// 定义LED引脚
#define LED_PIN GPIO_Pin_5
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_CLK RCC_APB2Periph_GPIOB

// 定义中断输入引脚
#define INPUT_PIN GPIO_Pin_5
#define INPUT_GPIO_PORT GPIOA
#define INPUT_GPIO_CLK RCC_APB2Periph_GPIOA

void GPIO_Configuration(void);
void EXTI_Configuration(void);
void NVIC_Configuration(void);

int main(void)
{
    // 初始化系统时钟
    SystemInit();
    
    // 配置GPIO
    GPIO_Configuration();
    
    // 配置外部中断
    EXTI_Configuration();
    
    // 配置NVIC
    NVIC_Configuration();
    
    while(1)
    {
        // 主循环
    }
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能LED和输入引脚的时钟
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK | INPUT_GPIO_CLK, ENABLE);
    
    // 配置LED引脚
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
    
    // 默认LED为高电平（熄灭状态）
    GPIO_SetBits(LED_GPIO_PORT, LED_PIN);
    
    // 配置输入引脚
    GPIO_InitStructure.GPIO_Pin = INPUT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(INPUT_GPIO_PORT, &GPIO_InitStructure);
}

void EXTI_Configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    
    // 将GPIOA Pin5连接到中断线5
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
    
    // 配置EXTI线5
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

// 中断服务函数
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        // 翻转LED状态
        GPIO_WriteBit(LED_GPIO_PORT, LED_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(LED_GPIO_PORT, LED_PIN)));
        
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
}
