#ifndef __TASK_H
#define __TASK_H
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart3.h"
#include "pid.h"
#include "motor.h"
#include "led.h"
#include "tim.h"

/* 路线选择 */
//#define __Routine1
//#define __Routine2
#define __Routine3

#define _MPU_READ while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0)
	
/* 速度常量的宏定义 */
//#define Rotation_pwm	400   //自转一周时的速度
//#define Road_pwm   		450  	//路面速度
//#define Bridge_pwm 		400   //过桥速度
//#define Bumps_pwm			600		//过减速带的速度

#define Origin_Speed      500   //起始速度
#define Road_Speed_H  	  950   //平地快速度
#define Road_Speed_MAX  	1000  //平地快速度
#define Road_Speed_L  	  550   //平地慢速度
#define Mountain_Speed  	450   //梯形山速度
#define Rotate_Speed  	  500   //转弯速度
#define Down_Platform  	  450   //下坡速度
#define Up_Platform  	    500   //上坡速度

/* 时间常量的宏定义 */
#define Base_delay 				0.1   //基本延时
#define Rotation_delay 		0.1   //自转延时
#define Bevel_delay1			0.3		//从斜台边缘转到中间白线方向


/*枚举声明可以显式地声明 short、ushort、int、uint、long 或 ulong 类型作为对应的基础类型。
没有显式地声明基础类型的枚举声明意味着所对应的基础类型是 (int)*/

/* 路线的枚举 */
typedef enum
{
	_origin = 1,

}ROAD_TYPE;

/* 标志位结构体 */
typedef struct _flag {
	int 				MPU_flag;  					//6050读取flag
	PID_TYPE  	pid_flag; 					//pid循迹flag
	int 				timer_flag;					//定时器1flag
	int 				timer8_flag;					//定时器8flag
	AD_TYPE  		adjust_flag;				//色标调整flag
}flag_ST;

/* 门状态枚举 */
typedef enum {
	 _open   = 0,
	 _closed = 1
}Door_State;

/* 门结构体 */
typedef struct {
	Door_State		D1;
	Door_State		D2;
	Door_State		D3;
	Door_State		D4;
}Door_TYPE;

extern flag_ST flag;
extern Door_TYPE Door;

/* 路线相关函数 */
void origin(void);
void up_bridge(void);
void go_bridge(void);
void go_bridge_new(void);
void rotation(void);
void right_turn1(void);
void bumps_3(void);//减速带
void bumps_2(void);//减速带
void mountains(void);//梯形山
void mountains1(void);
void mountains_new(void);//梯形山

void platform3(void);
void platform7(void);
void platform8(void);

//#############走门#############
void node1_p0(void);
void node1_p3(void);
void rt_node1_d1(void);
void rt_node1_d2(void);

void node2_d1(void);
void node2_d2(void);
void node2_d3(void);

void node3_n1(void);
//############# The Final #############

void seesaw(void);//跷跷板

void bevel_1_3(void);
void bevel_1_4(void);

void bevel_2_3(void);
void bevel_2_4(void);

void bevel_3_1(void);
void bevel_3_2(void);

void bevel_4_1(void);
void bevel_4_2(void);

void bevel_1_mid(void);
void bevel_4_mid(void);

void bevel_mid_1(void);
void bevel_mid_4(void);

//#############   PLANC  #############
void node3_p4(void);
void node4_d4(void);
void node4_p5(void);
void node2_node3(void);
void p7_p5(void);
/* 门4关 */
void rt_node3_d4(void);
void node4_d3(void);
/* 门3关 */
void rt_node3_d3(void);
void node5_p7(void);
void node4_p8(void);
void p7_node2(void);

#ifdef __Routine3
/* 第一圈 */
void jingdian1_2(void);
void jingdian2_4(void);
void jingdian4_7(void);
void jingdian7_8(void);

void return1_D4(void);
void return1_D3(void);
void return1_D1(void);
void return2_D4(void);
/* 第二圈 */
void jingdian2_3(void);
void jingdian4_5(void);
void jingdian3_5(void);
void jingdian5_7(void);
void jingdian7_8(void);

/* 决赛 */
void jingdian2_4_new(void);
void jingdian4_7_D3(void);
void jingdian4_3();
void jingdian3_7();
#endif


#endif