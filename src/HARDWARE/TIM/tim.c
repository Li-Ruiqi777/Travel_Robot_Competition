#include "tim.h"
#include "task.h"
#include "led.h"

void TIM1_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;               //��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;            //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;           //ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);               //ʹ�ܶ�ʱ���ж�
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;        //��Ӧ���ȼ�1
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM1,ENABLE);
}

void TIM1_ON(void)
{
	flag.timer_flag=1;
	_second=0;
}
void TIM1_OFF(void)
{
	flag.timer_flag=0;
	_second=0;
}

void TIM1_UP_IRQHandler(void)  
{    
	if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update)==SET)//1ms��ʱ�ж�
	{  
		if(flag.timer_flag==0)	//���ʱ��
		{
			_ms=0;
			_second=0;
		}
		
		else if(flag.timer_flag==1)	//��ʼ��ʱ
		{
			_ms++;
			if(_ms==10)
			{
				_second +=0.01;
				_ms=0;
			}
		}
	}    
	
  TIM_ClearITPendingBit(TIM1,TIM_IT_Update); //�����ʱ��1�жϱ�־λ	 
} 

void TIM8_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;               //��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;            //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;           //ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);               //ʹ�ܶ�ʱ���ж�
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM8_UP_IRQn;        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;        //��Ӧ���ȼ�0
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM8,ENABLE);
}

void TIM8_ON(void)
{
	flag.timer8_flag=1;
//	_second=0;
}
void TIM8_OFF(void)
{
	flag.timer8_flag=0;
	_second8 = 0;
}

void TIM8_UP_IRQHandler(void)  
{ 
	if(TIM_GetFlagStatus(TIM8,TIM_FLAG_Update)==SET)//50ms��ʱ�ж�
	{  
		if(flag.timer8_flag==0)	//���ʱ��
		{
			_second8 = 0;
		}
		
		else if(flag.timer8_flag==1)	//��ʼ��ʱ
		{
			_second8 += 0.05;
		}
	} 
			
	TIM_ClearITPendingBit(TIM8,TIM_IT_Update); //�����ʱ��8�жϱ�־λ	
} 

/*************************************
*�������ƣ�Accelerate_Start
*�������ܣ��û��趨���������ٵĲ���
*������origin_speed�����ٵĳ�ʼ�ٶ�(ֱ�Ӹ�����)
			 period�����ٵĳ���ʱ�䣬��Ҫ��0.05�ı���
			 times���������ڵĴ���
*˵����	����while1ǰ��
**************************************/
void Accelerate_Start(float period,int times,int origin_speed)
{
	ACC_Handler.times  = times;
	ACC_Handler.period = period;
	ACC_Handler.origin_speed = origin_speed;
	*(ACC_Handler.speed) = origin_speed;//��Car_speed��ֵ
}

/*************************************
*�������ƣ�Accelerate_Manage
*�������ܣ��ı䵱ǰ�ٶ�
*˵����	����TIM8�жϴ�������
				�õĻ�������Accelerate_Start��Car_speed��ֵһ�����ٶȣ���������
        Ȼ��go_forward(Car_speed)
**************************************/
void Accelerate_Manage(void)
{
	if(ACC_Handler.times>0)
	{
		if(*(ACC_Handler.speed)<Speed_Limit)
		{
			*(ACC_Handler.speed) += 20;//ָ��ָ��Car_speed
			/*ÿ����٣�change*20  */
		}
		if(_second8 >= ACC_Handler.period)
		{
			ACC_Handler.times--;
			*(ACC_Handler.speed) = ACC_Handler.origin_speed;//�ٶ�����
			_second8=0;//����ʱ�䣬��ʼ��һ����������
		}
	}
	
	else 
		*(ACC_Handler.speed) = ACC_Handler.origin_speed;
}

/*************************************
*�������ƣ�Accelerate_OFF
*�������ܣ��رռ��ٹ���
*˵����	������������ĩβ
				��ֹ����һ�������˻��ڼ�������
**************************************/
void Accelerate_OFF(void)
{
	ACC_Handler.times					= 0;
	ACC_Handler.period 				= 0;
	*(ACC_Handler.speed)  		= ACC_Handler.origin_speed;//�ٶ�����
	ACC_Handler.origin_speed 	= 0;
}