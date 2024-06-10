#include "usart.h"
#include "delay.h"
#include "led.h"
#include "exti.h"
#include "pid.h"
#include "task.h"

/* 按键初始化 */
void KEY_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	 GPIO_Init(GPIOD,&GPIO_InitStructure);

}

/* 外部中断初始化 */
void EXTIX_Init(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		
	//GPIOE.8
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource8);
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOE.9
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	EXTI_Init(&EXTI_InitStructure);

	//GPIOE.10
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource10);
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOE.11
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource11);
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);

	//GPIOE.8和GPIOE.9
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =4; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_Init(&NVIC_InitStructure);
	
	//GPIOE.10和GPIOE.11
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =4; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_Init(&NVIC_InitStructure);
}


//外部中断服务程序
void EXTI9_5_IRQHandler(void)
{
	/* KEY1 */
	if(EXTI_GetITStatus(EXTI_Line8)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line8); 
	}
	
	/* KEY2 */
	else if(EXTI_GetITStatus(EXTI_Line9)==SET)
	{
		forward_mid(500,Straight_Quick,1);
		EXTI_ClearITPendingBit(EXTI_Line9); 
	}
}

//外部中断服务程序
void EXTI15_10_IRQHandler(void)
{
	/* KEY3 */
	if(EXTI_GetITStatus(EXTI_Line10)==SET)
	{
		forward_mid_light(500,Straight_Quick,1,3);
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
	
	/* KEY4 */
	else if(EXTI_GetITStatus(EXTI_Line11)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line11);
	} 
}