#ifndef __PID__H
#define __PID__H

#include "sys.h"
#include "sensor.h"
#include "mpu6050.h"//MPU6050驱动库
#include "inv_mpu.h"//陀螺仪驱动库
#include "inv_mpu_dmp_motion_driver.h" //DMP姿态解读库

typedef struct {
	float setpoint;  //目标设定值
	float Now_err;   //定义当前误差
	float Sum_err;   //总误差
	float Diff_err;  //微误差
	float Last_err;  //上一次误差
	float kp,ki,kd;  //定义比列，微分，积分常数
}PID;

/* PID的模式枚举 */
typedef enum 
{
	Disable		   			 = 0,
	Straight_Quick  	 = 1,
	Straight_Slow   	 = 2,
	S_Curve				 		 = 3,
}PID_TYPE;

/* adjust模式的枚举 */
typedef enum  
{
	AD_Disable		   	 = 0,
	AD_UpBridge        = 1,
	AD_OnBridge        = 2,
	AD_DownBridge      = 3,
	AD_Seesaw          = 4,
}AD_TYPE;

/* Door_test模式的枚举 */
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

/* 小车的动作 */
void go_adjust(int initial_speed,AD_TYPE ad_mode);//靠色标传感器调整

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

void crash(int initial_speed);//撞台并转180度
void platform(float time);//上平台并自转一圈
void platform_new(void);//上平台并自转一圈
void stop(float target_s);

void Door_Judege(uint8_t doornum);
#endif