#include "tim.h"
#include "task.h"
#include "led.h"

void TIM1_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;               //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;            //预分频系数
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;           //时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);               //使能定时器中断
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;        //使能按键所在的外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;        //响应优先级1
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
	if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update)==SET)//1ms定时中断
	{  
		if(flag.timer_flag==0)	//清空时间
		{
			_ms=0;
			_second=0;
		}
		
		else if(flag.timer_flag==1)	//开始计时
		{
			_ms++;
			if(_ms==10)
			{
				_second +=0.01;
				_ms=0;
			}
		}
	}    
	
  TIM_ClearITPendingBit(TIM1,TIM_IT_Update); //清除定时器1中断标志位	 
} 

void TIM8_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;               //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;            //预分频系数
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;           //时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);               //使能定时器中断
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM8_UP_IRQn;        //使能按键所在的外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;        //响应优先级0
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
	if(TIM_GetFlagStatus(TIM8,TIM_FLAG_Update)==SET)//50ms定时中断
	{  
		if(flag.timer8_flag==0)	//清空时间
		{
			_second8 = 0;
		}
		
		else if(flag.timer8_flag==1)	//开始计时
		{
			_second8 += 0.05;
		}
	} 
			
	TIM_ClearITPendingBit(TIM8,TIM_IT_Update); //清除定时器8中断标志位	
} 

/*************************************
*函数名称：Accelerate_Start
*函数功能：用户设定接下来加速的参数
*参数：origin_speed：加速的初始速度(直接给数字)
			 period：加速的持续时间，需要是0.05的倍数
			 times：加速周期的次数
*说明：	放在while1前面
**************************************/
void Accelerate_Start(float period,int times,int origin_speed)
{
	ACC_Handler.times  = times;
	ACC_Handler.period = period;
	ACC_Handler.origin_speed = origin_speed;
	*(ACC_Handler.speed) = origin_speed;//给Car_speed赋值
}

/*************************************
*函数名称：Accelerate_Manage
*函数功能：改变当前速度
*说明：	放在TIM8中断处理函数内
				用的话就先用Accelerate_Start给Car_speed赋值一个初速度，并开启。
        然后go_forward(Car_speed)
**************************************/
void Accelerate_Manage(void)
{
	if(ACC_Handler.times>0)
	{
		if(*(ACC_Handler.speed)<Speed_Limit)
		{
			*(ACC_Handler.speed) += 20;//指针指向Car_speed
			/*每秒加速：change*20  */
		}
		if(_second8 >= ACC_Handler.period)
		{
			ACC_Handler.times--;
			*(ACC_Handler.speed) = ACC_Handler.origin_speed;//速度重置
			_second8=0;//重置时间，开始下一个加速周期
		}
	}
	
	else 
		*(ACC_Handler.speed) = ACC_Handler.origin_speed;
}

/*************************************
*函数名称：Accelerate_OFF
*函数功能：关闭加速功能
*说明：	放在任务函数的末尾
				防止到下一个任务了还在继续加速
**************************************/
void Accelerate_OFF(void)
{
	ACC_Handler.times					= 0;
	ACC_Handler.period 				= 0;
	*(ACC_Handler.speed)  		= ACC_Handler.origin_speed;//速度重置
	ACC_Handler.origin_speed 	= 0;
}