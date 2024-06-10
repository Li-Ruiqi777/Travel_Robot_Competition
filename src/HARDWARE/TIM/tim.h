#ifndef __TIM_H
#define __TIM_H
#include "sys.h"
#include "stm32f10x_tim.h"
#include "led.h"
#include "mpu6050.h"//MPU6050������
#include "inv_mpu.h"//������������
#include "inv_mpu_dmp_motion_driver.h" //DMP��̬�����

extern float pitch,roll,yaw; 		//ŷ����:�����ǣ�ƫ���ǣ���ת��
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����  angular acceleration
extern short gyrox,gyroy,gyroz;	//������ԭʼ����  gyroscope
extern float  _ms,_second;			//���ڶ�ʱ��1
extern float  _second8;					//���ڶ�ʱ��8
extern int Car_speed;
#define Speed_Limit 800

void TIM1_Init(u16 arr,u16 psc);  
void TIM1_UP_IRQHandler(void);

void TIM1_ON(void);
void TIM1_OFF(void);

void TIM8_Init(u16 arr,u16 psc);  
void TIM8_UP_IRQHandler(void);

void TIM8_ON(void);
void TIM8_OFF(void);

typedef struct  {
	float period;					//���ٳ���ʱ��
	int 	times;				//���ٹ��̵Ĵ���
	int   origin_speed;		//���ʼ�ٶ�
	int*  speed;						//��ǰ�ٶ�
}Accelerate;

extern Accelerate ACC_Handler;
void Accelerate_Start(float period,int frequency,int origin_speed);
void Accelerate_OFF(void);
void Accelerate_Manage(void);

#endif