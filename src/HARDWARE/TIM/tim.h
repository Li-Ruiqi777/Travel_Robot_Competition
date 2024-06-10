#ifndef __TIM_H
#define __TIM_H
#include "sys.h"
#include "stm32f10x_tim.h"
#include "led.h"
#include "mpu6050.h"//MPU6050驱动库
#include "inv_mpu.h"//陀螺仪驱动库
#include "inv_mpu_dmp_motion_driver.h" //DMP姿态解读库

extern float pitch,roll,yaw; 		//欧拉角:俯仰角，偏航角，滚转角
extern short aacx,aacy,aacz;		//加速度传感器原始数据  angular acceleration
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据  gyroscope
extern float  _ms,_second;			//用于定时器1
extern float  _second8;					//用于定时器8
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
	float period;					//加速持续时间
	int 	times;				//加速过程的次数
	int   origin_speed;		//存初始速度
	int*  speed;						//当前速度
}Accelerate;

extern Accelerate ACC_Handler;
void Accelerate_Start(float period,int frequency,int origin_speed);
void Accelerate_OFF(void);
void Accelerate_Manage(void);

#endif