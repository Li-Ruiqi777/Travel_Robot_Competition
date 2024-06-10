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
Door_TYPE Door={_open,_open,_open,_open};//��ʼ���ŵ�״̬

float pitch=0,roll=0,yaw=0;
flag_ST flag = {0,Disable,0,0,AD_Disable}; //��־λ�ṹ��:MPU--PID---timer1---adjust
uint8_t quanshu = 1;//Ȧ��
int f1,f2,f3,f4;

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  //�ж����ȼ����麯��
	uart_init(115200);		//����1��ʼ��Ϊ115200
  USART3_Init(115200);	//����3��ʼ��Ϊ115200
	LED_Init();
	LED_ALL_ON();
	KEY_Init();   				//��ʼ���밴�����ӵ�Ӳ���ӿ�
	EXTIX_Init();					//�ⲿ�жϳ�ʼ��
	MOTOR_GPIO_Init();
	Sensors_GPIO_Init();	//��ʼ������������
	TIM3_PWM_Init(1199,5);//10000(HZ)

	while(MPU_Init())//��ʼ��MPU6050
	{
		
	}		
	while(mpu_dmp_init()) //��ʼ��mpu_dmp��
 	{	
		
	}
	
	LED_ALL_OFF();
	TIM1_Init(999,71);//��ʱ��1��1msһ���ж�
	TIM8_Init(499,7199);//��ʱ��8��50msһ���ж�
	
  while(1)
	{
		/******************* ����ר�� *******************/
//		mountains_new();
//		platform_new();
//		stop(5);

//		platform_new();		
//		platform3();
//		platform7();
//		platform8();
//		stop(5);
		
//		bumps_3();//���ٴ�
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

		/******************* ����ר�� *******************/
		
		
#ifdef __Routine3

		jingdian1_2();
		
		if(Door.D4==_closed && Door.D3==_closed)//�ڶ�Ȧ���ֶ�����
		{
			jingdian2_4();/* ����1 */
			jingdian4_3();
			jingdian3_7();
			jingdian7_8();
			return1_D1();/**** �ؼ� ****/
		}
		
		else if(Door.D4==_closed && Door.D3==_open)//�ڶ�Ȧ���ֶ�����
		{
			jingdian2_4();/* ����3 */
			jingdian4_7_D3();
			jingdian7_8();
			return1_D3();/**** �ؼ� ****/
		}
		
		else if(Door.D4==_open)//��һȦ������4�ǿ���
		{
			jingdian2_4();
			jingdian4_7();
			jingdian7_8();
			
			/**** �ؼ� ****/
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
