#include "delay.h"
#include "sys.h"
#include "exti.h"
#include "tim.h"
#include "task.h"
#include "sys.h"
#include "led.h"

float _ms=0;
float _second=0;
float _second8=0;
int Car_speed=0;
Accelerate ACC_Handler={0,0,0,&Car_speed};
Door_TYPE Door={_open,_open,_open,_open};//初始化门的状态

float pitch=0,roll=0,yaw=0;
flag_ST flag = {0,Disable,0,0,AD_Disable}; //标志位结构体:MPU--PID---timer1---adjust
uint8_t quanshu = 1;//圈数
int f1,f2,f3,f4;

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  //中断优先级分组函数
	uart_init(115200);		//串口1初始化为115200
  USART3_Init(115200);	//串口3初始化为115200
	LED_Init();
	LED_ALL_ON();
	KEY_Init();   				//初始化与按键连接的硬件接口
	EXTIX_Init();					//外部中断初始化
	MOTOR_GPIO_Init();
	Sensors_GPIO_Init();	//初始化各个传感器
	TIM3_PWM_Init(1199,5);//10000(HZ)

	while(MPU_Init())//初始化MPU6050
	{
		
	}		
	while(mpu_dmp_init()) //初始化mpu_dmp库
 	{	
		
	}
	
	LED_ALL_OFF();
	TIM1_Init(999,71);//定时器1：1ms一次中断
	TIM8_Init(499,7199);//定时器8：50ms一次中断
	
  while(1)
	{
		/******************* 调试专区 *******************/
//		mountains_new();
//		platform_new();
//		stop(5);

//		platform_new();		
//		platform3();
//		platform7();
//		platform8();
//		stop(5);
		
//		bumps_3();//减速带
//		platform7();
//		jingdian7_8();
//		down_platform8();
//		stop(5);
		
//		jingdian2_4();
//		jingdian4_7();
//		jingdian7_8();
//		return2_D4();

//    return1_D3();
//jingdian2_4();
//	bevel_1_3();

//	bumps_2();
//bevel_4_1();
//		stop(5);

		/******************* 调试专区 *******************/
		
		
#ifdef __Routine3

		jingdian1_2();
		
		if(Door.D4==_closed && Door.D3==_closed)//第二圈或手动控制
		{
			jingdian2_4();/* 走门1 */
			jingdian4_3();
			jingdian3_7();
			jingdian7_8();
			return1_D1();/**** 回家 ****/
		}
		
		else if(Door.D4==_closed && Door.D3==_open)//第二圈或手动控制
		{
			jingdian2_4();/* 走门3 */
			jingdian4_7_D3();
			jingdian7_8();
			return1_D3();/**** 回家 ****/
		}
		
		else if(Door.D4==_open)//第一圈或者门4是开的
		{
			jingdian2_4();
			jingdian4_7();
			jingdian7_8();
			
			/**** 回家 ****/
			if(Door.D4==_open)
				return2_D4();
			else if(Door.D4==_closed && Door.D3==_open)
				return1_D3();
			else 
				return1_D1();
		}
	
#endif

//Read_Digital_Data();
//		f1=G_L;
//		f2=G_R;
//		f3=EL;
//		f4=ER;
  }   
  
}
