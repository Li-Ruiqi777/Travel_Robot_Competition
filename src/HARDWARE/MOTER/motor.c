#include "motor.h"
//////////////////////////////////////////////////////////////////////////////////	 
//X  M1		左轮    PA6(前)  PA7(后)
//Y  M2   右轮    PB0(前)  PB1(后)
//////////////////////////////////////////////////////////////////////////////////  
void MOTOR_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//使能端口时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA
	GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//禁用JTAG 启用 SWD
}   	  

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 

	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}

void motor(int32_t comparex,int32_t comparey)
{
	Limit_PWM(comparex,comparey,1000);//电机限幅
	
	if(comparex >= 0)          //M1_pwm>=0时，电机正转
	{
		TIM3->CCR3=comparex; 
		TIM3->CCR4=0;
	}
	else   										//M1_pwm<0时，电机反转，M1_pwm取绝对值
	{
		TIM3->CCR3=0; 
		TIM3->CCR4=abs(comparex);
	}
	
	if(comparey >= 0)          //M2_pwm>=0时，电机正转
	{
		TIM3->CCR1=0; 
		TIM3->CCR2=comparey; 
	}
	else    									//M2_pwm<0时，电机反转，M2_pwm取绝对值
	{
		TIM3->CCR1=abs(comparey); 
		TIM3->CCR2=0; 
	}
	
}


void Limit_PWM(int32_t comparex,int32_t comparey,int32_t limit)
{
	if(abs(comparex>=limit))//电机限幅
	{
		if(comparex<0) {comparex= -limit;}
		else {comparex = limit;}
	}
  if(abs(comparey>=limit))
	{
		if(comparey<0) {comparey= - limit;}
		else {comparey=limit;}
	}
}