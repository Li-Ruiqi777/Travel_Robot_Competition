#include "motor.h"
//////////////////////////////////////////////////////////////////////////////////	 
//X  M1		����    PA6(ǰ)  PA7(��)
//Y  M2   ����    PB0(ǰ)  PB1(��)
//////////////////////////////////////////////////////////////////////////////////  
void MOTOR_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܶ˿�ʱ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA
	GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//����JTAG ���� SWD
}   	  

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 

	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}

void motor(int32_t comparex,int32_t comparey)
{
	Limit_PWM(comparex,comparey,1000);//����޷�
	
	if(comparex >= 0)          //M1_pwm>=0ʱ�������ת
	{
		TIM3->CCR3=comparex; 
		TIM3->CCR4=0;
	}
	else   										//M1_pwm<0ʱ�������ת��M1_pwmȡ����ֵ
	{
		TIM3->CCR3=0; 
		TIM3->CCR4=abs(comparex);
	}
	
	if(comparey >= 0)          //M2_pwm>=0ʱ�������ת
	{
		TIM3->CCR1=0; 
		TIM3->CCR2=comparey; 
	}
	else    									//M2_pwm<0ʱ�������ת��M2_pwmȡ����ֵ
	{
		TIM3->CCR1=abs(comparey); 
		TIM3->CCR2=0; 
	}
	
}


void Limit_PWM(int32_t comparex,int32_t comparey,int32_t limit)
{
	if(abs(comparex>=limit))//����޷�
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