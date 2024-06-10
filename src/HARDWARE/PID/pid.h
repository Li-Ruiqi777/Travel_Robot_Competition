#ifndef __PID__H
#define __PID__H

#include "sys.h"
#include "sensor.h"
#include "mpu6050.h"//MPU6050������
#include "inv_mpu.h"//������������
#include "inv_mpu_dmp_motion_driver.h" //DMP��̬�����

typedef struct {
	float setpoint;  //Ŀ���趨ֵ
	float Now_err;   //���嵱ǰ���
	float Sum_err;   //�����
	float Diff_err;  //΢���
	float Last_err;  //��һ�����
	float kp,ki,kd;  //������У�΢�֣����ֳ���
}PID;

/* PID��ģʽö�� */
typedef enum 
{
	Disable		   			 = 0,
	Straight_Quick  	 = 1,
	Straight_Slow   	 = 2,
	S_Curve				 		 = 3,
}PID_TYPE;

/* adjustģʽ��ö�� */
typedef enum  
{
	AD_Disable		   	 = 0,
	AD_UpBridge        = 1,
	AD_OnBridge        = 2,
	AD_DownBridge      = 3,
	AD_Seesaw          = 4,
}AD_TYPE;

/* Door_testģʽ��ö�� */
typedef enum  
{
	DT_Disable  = 0,
	DT_1        = 1,
	DT_2        = 2,
	DT_3      	= 3,
	DT_4        = 4,
}DT_TYPE;

#define MAX_sumERR 2000
extern float left_pwm,right_pwm;
extern int sum1,sum2;
extern float error1;
extern int k;
extern uint8_t G_L,G_R;

void Read_Digital_Data(void);
void Read_GD_L_Data(void);
void Read_GD_R_Data(void);
float Hui_Error_return(void);

/* С���Ķ��� */
void go_adjust(int initial_speed,AD_TYPE ad_mode);//��ɫ�괫��������

void forward_head(int initial_speed,PID_TYPE pid_mode);
void forward_mid(int initial_speed,PID_TYPE pid_mode,int num);
void forward_mid_light(int initial_speed,PID_TYPE pid_mode,int num,int _sum);
void forward_mid_light_L(int initial_speed,PID_TYPE pid_mode,int num,int _sum);
void forward_mid_light_R(int initial_speed,PID_TYPE pid_mode,int num,int _sum);

void go_forward(int initial_speed,PID_TYPE pid_mode);
void go_back(int initial_speed);
void go_open(int L_speed,int R_speed,float time);
void go_closed(int initial_speed,PID_TYPE pid_mode,float time);
void go_door(void);

void dash_dp(void);
void dash_op(void);
void dash(void);
void dash_big(void);
void down_platform(void);
void down_platform8(void);

void turn_right(int speed,float angle);
void turn_left (int speed,float angle);
void right2line(int speed,float mintime);
void left2line (int speed,float mintime);
void turn_until_line(int L_speed,int R_speed,float time);

void crash(int initial_speed);//ײ̨��ת180��
void platform(float time);//��ƽ̨����תһȦ
void platform_new(void);//��ƽ̨����תһȦ
void stop(float target_s);

void Door_Judege(uint8_t doornum);
#endif