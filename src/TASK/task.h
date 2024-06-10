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

/* ·��ѡ�� */
//#define __Routine1
//#define __Routine2
#define __Routine3

#define _MPU_READ while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0)
	
/* �ٶȳ����ĺ궨�� */
//#define Rotation_pwm	400   //��תһ��ʱ���ٶ�
//#define Road_pwm   		450  	//·���ٶ�
//#define Bridge_pwm 		400   //�����ٶ�
//#define Bumps_pwm			600		//�����ٴ����ٶ�

#define Origin_Speed      500   //��ʼ�ٶ�
#define Road_Speed_H  	  950   //ƽ�ؿ��ٶ�
#define Road_Speed_MAX  	1000  //ƽ�ؿ��ٶ�
#define Road_Speed_L  	  550   //ƽ�����ٶ�
#define Mountain_Speed  	450   //����ɽ�ٶ�
#define Rotate_Speed  	  500   //ת���ٶ�
#define Down_Platform  	  450   //�����ٶ�
#define Up_Platform  	    500   //�����ٶ�

/* ʱ�䳣���ĺ궨�� */
#define Base_delay 				0.1   //������ʱ
#define Rotation_delay 		0.1   //��ת��ʱ
#define Bevel_delay1			0.3		//��б̨��Եת���м���߷���


/*ö������������ʽ������ short��ushort��int��uint��long �� ulong ������Ϊ��Ӧ�Ļ������͡�
û����ʽ�������������͵�ö��������ζ������Ӧ�Ļ��������� (int)*/

/* ·�ߵ�ö�� */
typedef enum
{
	_origin = 1,

}ROAD_TYPE;

/* ��־λ�ṹ�� */
typedef struct _flag {
	int 				MPU_flag;  					//6050��ȡflag
	PID_TYPE  	pid_flag; 					//pidѭ��flag
	int 				timer_flag;					//��ʱ��1flag
	int 				timer8_flag;					//��ʱ��8flag
	AD_TYPE  		adjust_flag;				//ɫ�����flag
}flag_ST;

/* ��״̬ö�� */
typedef enum {
	 _open   = 0,
	 _closed = 1
}Door_State;

/* �Žṹ�� */
typedef struct {
	Door_State		D1;
	Door_State		D2;
	Door_State		D3;
	Door_State		D4;
}Door_TYPE;

extern flag_ST flag;
extern Door_TYPE Door;

/* ·����غ��� */
void origin(void);
void up_bridge(void);
void go_bridge(void);
void go_bridge_new(void);
void rotation(void);
void right_turn1(void);
void bumps_3(void);//���ٴ�
void bumps_2(void);//���ٴ�
void mountains(void);//����ɽ
void mountains1(void);
void mountains_new(void);//����ɽ

void platform3(void);
void platform7(void);
void platform8(void);

//#############����#############
void node1_p0(void);
void node1_p3(void);
void rt_node1_d1(void);
void rt_node1_d2(void);

void node2_d1(void);
void node2_d2(void);
void node2_d3(void);

void node3_n1(void);
//############# The Final #############

void seesaw(void);//���ΰ�

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
/* ��4�� */
void rt_node3_d4(void);
void node4_d3(void);
/* ��3�� */
void rt_node3_d3(void);
void node5_p7(void);
void node4_p8(void);
void p7_node2(void);

#ifdef __Routine3
/* ��һȦ */
void jingdian1_2(void);
void jingdian2_4(void);
void jingdian4_7(void);
void jingdian7_8(void);

void return1_D4(void);
void return1_D3(void);
void return1_D1(void);
void return2_D4(void);
/* �ڶ�Ȧ */
void jingdian2_3(void);
void jingdian4_5(void);
void jingdian3_5(void);
void jingdian5_7(void);
void jingdian7_8(void);

/* ���� */
void jingdian2_4_new(void);
void jingdian4_7_D3(void);
void jingdian4_3();
void jingdian3_7();
#endif


#endif