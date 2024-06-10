#include "led.h"
#include "delay.h"
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	 
  	
 GPIO_ResetBits(GPIOA,GPIO_Pin_0); //��ʼ����
 GPIO_ResetBits(GPIOA,GPIO_Pin_1); //��ʼ����
 GPIO_ResetBits(GPIOA,GPIO_Pin_2); //��ʼ����
}

void blink(void)
{
	LED_R_ON;
	delay_ms(50);
	LED_R_OFF;
	delay_ms(50);
	
	LED_R_ON;
	delay_ms(50);
	LED_R_OFF;
	delay_ms(50);
}

void LED_ALL_ON(void)
{
	LED_R_ON;
	LED_Y_ON;
	LED_G_ON;
}

void LED_ALL_OFF(void)
{
	LED_R_OFF;
	LED_Y_OFF;
	LED_G_OFF;
}
