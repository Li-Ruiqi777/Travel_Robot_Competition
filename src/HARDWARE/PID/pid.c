#include "pid.h"
#include "motor.h"
#include "delay.h"
#include "tim.h"
#include "task.h"
float error=0;
int adjust=0;
/* 全局变量*/
int sum1=0;	
float left_pwm=0,right_pwm=0;		
float error1=0; 
uint8_t G_L,G_R;

/* 多次采样GL,返回多数结果 */
void Read_GD_L_Data(void)
{
	uint8_t i;
	uint8_t y=0,w=0;
	uint8_t D[3]={0};
	for(i = 0;i < 3;i++) //采集5次数据
	{
		D[i] = GL;
		delay_us(40);
	}
	for(i = 0;i < 3;i++) 
	{
		if(D[i] == 1) w++;
		else y++;
	}
	if(y > w) G_L = 0;  //由于采集5个数据所以不存在相等的情况
	else G_L = 1;
}

/* 多次采样GR,返回多数结果 */
void Read_GD_R_Data(void)
{
	uint8_t i;
	uint8_t y=0,w=0;
	uint8_t D[5]={0};
	for(i = 0;i < 5;i++) //采集5次数据
	{
		D[i] = GR;
		delay_us(40);
	}
	for(i = 0;i < 5;i++) 
	{
		if(D[i] == 1) w++;
		else y++;
	}
	if(y > w) G_R = 0;  //由于采集5个数据所以不存在相等的情况
	else G_R = 1;
}

/* 读各个传感器的值 */
void Read_Digital_Data()
{
	E1;E2;E3;E4;E5;E6;E7;E8;
	EL;ER;
//	GL;GR;
	Read_GD_L_Data();	Read_GD_R_Data();
	S1;S2;S3;S4;
	
  sum1=E1+E2+E3+E4+E5+E6+E7+E8;
}

/*************************************
*函数名称：Hui_Error_return
*函数功能：根据灰度状态返回一个偏差，用于速度PID计算
*参数：
*说明：	灰度黑色返回1，白色返回0
**************************************/
float Hui_Error_return(void)
{
	Read_Digital_Data();
	
	if(flag.pid_flag==Straight_Quick)//#############用来快速直线寻迹#############
	{
		//无偏差
		if(E4==0&&E5==0) {error=0;}//1110 0111
		//0.5级偏差
		else if(E4==1&&E5==0){error=-0.5;}//1111 0111 车头左偏为负数  Change=0.5*Kp*speed
		else if(E4==0&&E5==1){error=0.5;} //1110 1111 右偏为正数      Change>speed时轮子才会反转
		
		//1级偏差
		else if(E5==0&&E6==0){error=-1;}//1111 0011 车头左偏为负数  Change=1*Kp*speed
		else if(E3==0&&E4==0){error=1;} //1100 1111 右偏为正数
		
		//1.5级偏差
		else if(E5==1&&E6==0){error=-1.5;}//1111 1011 车头左偏为负数  Change=1.5*Kp*speed
		else if(E3==0&&E4==1){error=1.5;} //1101 1111 右偏为正数
		
		//2级偏差
		else if(E6==0&&E7==0){error=-2;}//1111 1001 车头左偏为负数  Change=2*Kp*speed
		else if(E2==0&&E3==0){error=2;} //1001 1111 右偏为正数
		
		//2.5级偏差
		else if(E6==1&&E7==0){error=-2.5;}//1111 1101 车头左偏为负数  Change=2.5*Kp*speed
		else if(E2==0&&E3==1){error=2.5;} //1011 1111 右偏为正数
		
		//3级偏差
		else if(E7==0&&E8==0){error=-3;}//1111 1100 车头左偏为负数  Change=3*Kp*speed
		else if(E1==0&&E2==0){error=3;} //0011 1111 右偏为正数
		
		//3.5级偏差
		else if(E7==1&&E8==0){error=-3.5;}//1111 1110 车头左偏为负数  Change=3.5*Kp*speed
		else if(E1==0&&E2==1){error=3.5;} //0111 1111 右偏为正数
		
		else
		error=0;	
	}

	else if(flag.pid_flag==S_Curve)//#############用来走曲线#############
	{
		//无偏差
		if(E4==0&&E5==0) {error=0;}//1110 0111
		//0.5级偏差
		else if(E4==1&&E5==0){error=-0.5;}//1111 0111 车头左偏为负数  Change=0.5*Kp*speed
		else if(E4==0&&E5==1){error=0.5;} //1110 1111 右偏为正数      Change>speed时轮子才会反转
		
		//1级偏差
		else if(E5==0&&E6==0){error=-1;}//1111 0011 车头左偏为负数  Change=1*Kp*speed
		else if(E3==0&&E4==0){error=1;} //1100 1111 右偏为正数
		
		//1.5级偏差
		else if(E5==1&&E6==0){error=-1.5;}//1111 1011 车头左偏为负数  Change=1.5*Kp*speed
		else if(E3==0&&E4==1){error=1.5;} //1101 1111 右偏为正数
		
		//2级偏差
		else if(E6==0&&E7==0){error=-2;}//1111 1001 车头左偏为负数  Change=2*Kp*speed
		else if(E2==0&&E3==0){error=2;} //1001 1111 右偏为正数
		
		//2.5级偏差
		else if(E6==1&&E7==0){error=-3;}//1111 1101 车头左偏为负数  Change=3*Kp*speed
		else if(E2==0&&E3==1){error=3;} //1011 1111 右偏为正数
		
		//3级偏差
		else if(E7==0&&E8==0){error=-3.5;}//1111 1100 车头左偏为负数  Change=3.5*Kp*speed
		else if(E1==0&&E2==0){error=3.5;} //0011 1111 右偏为正数
		
		//3.5级偏差
		else if(E7==1&&E8==0){error=-4.5;}//1111 1110 车头左偏为负数  Change=4.5*Kp*speed
		else if(E1==0&&E2==1){error=4.5;} //0111 1111 右偏为正数
		
		else
		error=0;
	}
	
	else if(flag.pid_flag==Straight_Slow)//#############用来慢速走直线#############
	{
		//无偏差
		if(E4==0&&E5==0) {error=0;}//1110 0111
		//0.5级偏差
		else if(E4==1&&E5==0){error=-0.5;}//1111 0111 车头左偏为负数  Change=0.5*Kp*speed
		else if(E4==0&&E5==1){error=0.5;} //1110 1111 右偏为正数      Change>speed时轮子才会反转
		
		//1级偏差
		else if(E5==0&&E6==0){error=-1;}//1111 0011 车头左偏为负数  Change=1*Kp*speed
		else if(E3==0&&E4==0){error=1;} //1100 1111 右偏为正数
			
		else
		error=0;	
	}
	
	return error;
}

/*************************************
*函数名称：go_forward
*函数功能：以自定义速度寻迹
*参数：initial_speed：初始速度
			 mode：寻迹模式选择.0是关闭,参考pid_enum
*说明：	
**************************************/
PID pid_f={0,0,0,0,0,0,0,0};
void go_forward(int initial_speed,PID_TYPE pid_mode)
{
	float change = 0;
	flag.pid_flag = pid_mode;
	/* PID参数初始化 */
	switch(flag.pid_flag)
	{
		case Straight_Quick:  pid_f.kp = 0.30 * initial_speed;  pid_f.ki = 0;pid_f.kd = 0;  break;
		case S_Curve			 :	pid_f.kp = 0.50 * initial_speed;  pid_f.ki = 0;pid_f.kd = 0;  break;
		case Straight_Slow :	pid_f.kp = 0.30 * initial_speed;  pid_f.ki = 0;pid_f.kd = 0;  break;
		default: break;
	}

	/* 开启寻迹 */
	if(flag.pid_flag!=0)
	{
		error1=Hui_Error_return();
		pid_f.Now_err = error1;
		pid_f.Sum_err += pid_f.Now_err;
		if(pid_f.Sum_err >= MAX_sumERR) {pid_f.Sum_err = MAX_sumERR;}//积分限幅
		pid_f.Diff_err = pid_f.Now_err - pid_f.Last_err; 
		pid_f.Last_err = pid_f.Now_err;
		/* PID结果计算 */
		change = pid_f.kp * pid_f.Now_err
					 + pid_f.ki * pid_f.Sum_err 
					 + pid_f.kd * pid_f.Diff_err;
	}
	/* 关闭寻迹 */
	else if(flag.pid_flag==0)
	{
		error1=0;
		pid_f.Now_err = 0;
		pid_f.Last_err = 0;
		pid_f.Sum_err = 0;
		pid_f.Diff_err = 0;
		change = 0;
	}
	
  left_pwm  = initial_speed - change;
  right_pwm = initial_speed + change;
	
	motor(left_pwm,right_pwm); 

}


/* 寻迹向后走 */
PID pid_b={0,0,0,0,0,0,0,0};
void go_back(int initial_speed)
{		
  if(flag.pid_flag==1) {error1=Hui_Error_return();}/* 开启寻迹 */
	else {error1=0;}/* 关闭寻迹 */

  left_pwm  = initial_speed - error1 * initial_speed;
  right_pwm = initial_speed + error1 * initial_speed;
  motor(-right_pwm,-left_pwm); 
}


/* 右转指定角度 */
void turn_right(int speed,float angle)
{
	float ang_last;
	float ang_now;
	float sum;
	flag.MPU_flag=1;	//开启陀螺仪
//	angle=angle*0.9;	//陀螺仪自身所带误差
	_MPU_READ;
	ang_last=abs(yaw);
	
	while(sum<angle)
	{
		_MPU_READ;
		ang_now=abs(yaw);
		sum = sum + abs(ang_now-ang_last);
		motor(speed,-speed);
		ang_last=ang_now;
		delay_ms(1);
	}
	flag.MPU_flag=0;	//关闭陀螺仪
	stop(Rotation_delay);//停止一段时间
}

/* 左转指定角度 */
void turn_left(int speed,float angle)
{
	float ang_last;
	float ang_now;
	float sum;
	flag.MPU_flag=1;	//开启陀螺仪
//	angle=angle*0.9;	//陀螺仪自身所带误差
	_MPU_READ;
	ang_last=abs(yaw);

	while(sum<angle)
	{
		_MPU_READ;
		ang_now=abs(yaw);
		sum = sum + abs(ang_now-ang_last);
		motor(-speed,speed);
		ang_last=ang_now;
		delay_ms(1);
	}
	flag.MPU_flag=0;	//关闭陀螺仪
	stop(Rotation_delay);//停止一段时间
}

/* 停止一段时间 */
void stop(float target_s)
{
  error1=0;  
	TIM1_ON();
	while(_second < target_s)
  {
		motor(0,0);
	}
	TIM1_OFF();//关闭定时器1
}

void go_adjust(int initial_speed,AD_TYPE ad_mode)//靠色标传感器调整
{
	flag.adjust_flag = ad_mode;
	Read_Digital_Data();
	if(flag.adjust_flag == AD_UpBridge)//###############上桥
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed-5,initial_speed);
		}
		else if(S1 == 0)//左偏
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//右偏
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
	
	else if(flag.adjust_flag == AD_OnBridge)//###############桥上
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed-5,initial_speed);
		}
		else if(S1 == 0)//左偏
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//右偏
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
	
	else if(flag.adjust_flag == AD_DownBridge)//###############下桥
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed,initial_speed);
		}
		else if(S1 == 0)//左偏
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//右偏
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
	
	else if(flag.adjust_flag == AD_Seesaw)//###############上跷跷板
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed,initial_speed);
		}
		else if(S1 == 0)//左偏
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//右偏
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
}
//--------------------------------------------------------------------

/* 左/右转直到车中线到白线 */
void turn_until_line(int L_speed,int R_speed,float time)//用于分叉时转到另一根线上
{
	TIM1_ON();
	while(1)
	{
		Read_Digital_Data();
		motor(L_speed,R_speed);
		if( (E4==0||E5==0) && (_second>=time) )
		{
			stop(Base_delay);
			break;
		}
	}
	TIM1_OFF();
}

/* 右转自定义时间 */
void right_time(int L_speed,int R_speed,float time)
{
	TIM1_ON();
	while(_second < time)
	{
		motor(L_speed,R_speed);
	}
	TIM1_OFF();
}

/* 左转自定义时间 */
void left_time(int L_speed,int R_speed,float time)
{
	TIM1_ON();
	while(_second < time)
	{
		motor(L_speed,R_speed);
	}
	TIM1_OFF();
}

/* 开环跑自定义时间 */
void go_open(int L_speed,int R_speed,float time)
{
	TIM1_ON();
	while(_second < time)
	{
		motor(L_speed,R_speed);
	}
	TIM1_OFF();
}

/* 寻迹跑自定义时间,同时检测门的状态 */
void go_closed(int initial_speed,PID_TYPE pid_mode,float time)
{
	TIM1_ON();
	while(_second <= time)
	{
		go_forward(initial_speed,pid_mode);
	}
	
	TIM1_OFF();
}

/* 寻迹直到灰度全到白线并停止 */
void forward_head(int initial_speed,PID_TYPE pid_mode)
{
	while(sum1>=5)//超过3个灯亮就停止
	{
		go_forward(initial_speed,pid_mode);
	}
}

/******************************************************
*函数名称：forward_mid
*函数功能：寻迹直到灰度全到白线(3个以上检测到),在车身到白线时停止
*参数		 ：num：需要走过的分叉白线的个数
******************************************************/
void forward_mid(int initial_speed,PID_TYPE pid_mode,int num)
{
	int line=0;
	int num_remain = num;//还剩余要走白线的数量
	TIM1_ON();
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* 判断车头 */
		if(sum1<=5 && _second >0.3)
		{
			line=1;
			TIM1_OFF();
		}
		
		/* 判断车身 */
		if(line==1 && (EL==0||ER==0) ){
			line=0;
			num_remain--;			
		}
		
		if(num_remain==0){
			TIM1_OFF();
			break;
		}
	}

}

/******************************************************
*函数名称：forward_mid_light
*函数功能：寻迹直到灰度全到白线(自己设定几个以上检测到),在车身到白线时停止
					 用于走到横的白线。
*参数		 ：num：需要走过的分叉白线的个数
					_sum：8-判定车头到白线的灯的个数
*******************************************************/
void forward_mid_light(int initial_speed,PID_TYPE pid_mode,int num,int _sum)
{
	int line=0;
	int passed_flag=0;
	int num_remain = num;//还剩余要走白线的数量
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* 判断车头 */
		if(passed_flag == 0)
		{
			if(sum1<=_sum)
				line=1;
		}
		else if(passed_flag > 0) //第二个分叉线必须在第一个过后0.5s后才会被判定,以免一个分叉线判断多次
		{
			if(sum1<=_sum && _second >=0.18)//0.5
			{
				line=1;
				TIM1_OFF();
			}
		}
		
		/* 判断车身 */
		if(line==1 && (EL==0||ER==0) )
		{
			line=0;
			num_remain--;			
			passed_flag++;
			TIM1_ON();	//经过一个分叉线后开始计时
		}
		
		if(num_remain==0)
		{
			TIM1_OFF();
			break;
		}
	}

}

/******************************************************
*函数名称：forward_mid_light_L
*函数功能：寻迹直到灰度全到白线(自己设定几个以上检测到),在车身到白线时停止
					 用于走到横的白线。
*参数		 ：num：需要走过的分叉白线的个数
					_sum：8-判定车头到白线的灯的个数
*******************************************************/
void forward_mid_light_L(int initial_speed,PID_TYPE pid_mode,int num,int _sum)
{
	int line=0;
	int passed_flag=0;
	int num_remain = num;//还剩余要走白线的数量
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* 判断车头 */
		if(passed_flag == 0)
		{
			if(sum1<=_sum)
				line=1;
		}
		else if(passed_flag > 0) //第二个分叉线必须在第一个过后0.5s后才会被判定,以免一个分叉线判断多次
		{
			if(sum1<=_sum && _second >0.5)
			{
				line=1;
				TIM1_OFF();
			}
		}
		
		/* 判断车身 */
		if(line==1 && EL==0 )
		{
			line=0;
			num_remain--;			
			passed_flag++;
			TIM1_ON();	//经过一个分叉线后开始计时
		}
		
		if(num_remain==0)
		{
			TIM1_OFF();
			break;
		}
	}

	//stop(0.3);
}

void forward_mid_light_R(int initial_speed,PID_TYPE pid_mode,int num,int _sum)
{
	int line=0;
	int passed_flag=0;
	int num_remain = num;//还剩余要走白线的数量
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* 判断车头 */
		if(passed_flag == 0)
		{
			if(sum1<=_sum)
				line=1;
		}
		else if(passed_flag > 0) //第二个分叉线必须在第一个过后0.5s后才会被判定,以免一个分叉线判断多次
		{
			if(sum1<=_sum && _second >0.5)
			{
				line=1;
				TIM1_OFF();
			}
		}
		
		/* 判断车身 */
		if(line==1 && ER==0 )
		{
			line=0;
			num_remain--;			
			passed_flag++;
			TIM1_ON();	//经过一个分叉线后开始计时
		}
		
		if(num_remain==0)
		{
			TIM1_OFF();
			break;
		}
	}

	//stop(0.3);
}
/******************************************************
*函数名称：platform
*函数功能：先快速走段距离,然后慢速上平台并自转一圈
*说明    ：靠ROLL角识别
******************************************************/
void platform(float time)
{
	int upflag=0;
	
	if(time>0)
		go_closed(Road_Speed_H,Straight_Quick,time);
	//stop(1);
	TIM1_ON();
	while(1)
	{
		go_forward(Down_Platform,Straight_Quick);//在平地慢速寻迹直到走到平台上
		_MPU_READ;
		if(abs(roll)>15 && _second>0.5)//到上坡了
			upflag=1;

		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//已经走到了平台上
		{
			dash_op();
			stop(0.2); 
			TIM1_OFF();
			break;
		}
	}
	//blink();
	_MPU_READ;
	turn_right(550,165);//在平台上自转一圈170
}

/******************************************************
*函数名称：platform_new
*函数功能：先快速走到上坡处,然后慢速上平台并自转一圈
*说明    ：靠光电识别
******************************************************/
void platform_new(void)//上平台并自转一圈
{
	TIM1_OFF();
	/* 平地 */
	while(1)
	{
		go_forward(Road_Speed_H,Straight_Quick);//在平地快速寻迹直到走到平台上
		Read_Digital_Data();

		if(GL==0)
			break;//到上坡了
	}
	
	/* 上坡 */
	TIM1_ON();
	while(1)
	{
		_MPU_READ;
		go_forward(Up_Platform,Straight_Slow);//在平地慢速寻迹直到走到平台上
		if(sum1<=4 && _second > 0.4)	//已经走到了平台上
		{
			TIM1_OFF();
			break;
		}
	}
	dash_op();
	stop(Base_delay);

	_MPU_READ;
	_MPU_READ;
	turn_right(550,165);//在平台上自转一圈170
}

/******************************************************
*函数名称：platform7
*函数功能：先快速走到上坡处,然后慢速上平台并自转一圈
*说明    ：
******************************************************/
void platform7(void)//上平台并自转一圈
{
	float roll_ref;
	while(1)
	{
		go_forward(Road_Speed_H,Straight_Quick);//在平地快速寻迹直到走到平台上
		Read_Digital_Data();

		if(GL == 0)
			break;//到上坡了
	}

	TIM1_ON();
	while(1)
	{
		_MPU_READ;
		go_forward(Up_Platform,Straight_Quick);//在平地慢速寻迹直到走到平台
		
		if(sum1<=4 && _second >2.2)
		{
			TIM1_OFF();
			break;
		}
	}
	go_open(Origin_Speed,Origin_Speed,0.12);
	stop(Base_delay);

	_MPU_READ;
	turn_right(550,165);//在平台上自转一圈170

	go_closed(300,Straight_Quick,0.9);
}

/******************************************************
*函数名称：platform8
*函数功能：先快速走到上坡处,然后慢速上平台并自转一圈
*说明    ：
******************************************************/
void platform8(void)//上平台并自转一圈
{
	while(1)
	{
		go_forward(Road_Speed_H,Straight_Quick);//在平地快速寻迹直到走到平台上
		Read_Digital_Data();

		if(GL==0)
			break;//到上坡了
	}
	TIM1_ON();
	while(1)
	{
		_MPU_READ;
		go_forward(Up_Platform,Straight_Quick);//在平地慢速寻迹直到走到平台上
		if(sum1<=2 && _second >2.5)	//已经走到了平台上
		{
			TIM1_OFF();
			break;
		}
	}
	//dash_op();
	go_open(Origin_Speed,Origin_Speed,0.20);
	stop(Base_delay);

	_MPU_READ;
	turn_right(550,167);//在平台上自转一圈170

//	stop(3);
	/* 保险程序 */
	TIM1_ON();
	while(1)
	{
		Read_Digital_Data();
		motor(300,300);
		if(sum1 != 8 && _second > 0.3)
		{
			if(E1 ==0 && E8==0)
			{
				stop(0.1);
				go_open(-300,-300,0.2);
				go_open(300,-300,0.07);
			}
			
			else if(E1 ==0 || E2==0)
			{
				right_time(-300,300,0.12);//0.15
			}
			
			else if(E7 ==0 || E8==0)
			{
				right_time(300,-300,0.12);//0.15
			}
			
			break;
		}

	}
	TIM1_OFF();
	go_closed(300,Straight_Quick,0.4);
}

/******************************************************
*函数名称：crash
*函数功能：撞台并转180度
*说明    ：
******************************************************/
void crash(int initial_speed)
{
	Read_Digital_Data();
	while(1)
	{
		go_forward(initial_speed,Straight_Quick);
		if(GR==0)
		{
			stop(0.5);
			break;
		}	
	}
	turn_until_line(500,-500,0.4);//掉个头
}

/******************************************************
*函数名称：right2line
*函数功能：右转转到车中线到白线上
*说明    ：
******************************************************/
void right2line(int speed,float mintime)
{
	turn_until_line(speed,-speed,mintime);
}

/******************************************************
*函数名称：left2line
*函数功能：左转转到车中线到白线上
*说明    ：
******************************************************/
void left2line (int speed,float mintime)
{
	turn_until_line(-speed,speed,mintime);
}

/******************************************************
*函数名称：dash_dp
*函数功能：下平台一开始开环跑至白线在开始寻迹
*说明    ：
******************************************************/
void dash_dp(void)
{
	go_open(Origin_Speed,Origin_Speed,0.2);//开环跑到白线上
}

/******************************************************
*函数名称：dash_op
*函数功能：上平台往前走一点再停车
*说明    ：
******************************************************/
void dash_op(void)
{
	go_open(Origin_Speed,Origin_Speed,0.13);
}

/******************************************************
*函数名称：dash
*函数功能：在平地上往前走一点
*说明    ：
******************************************************/
void dash(void)
{
	go_open(600,600,0.1);
}

/******************************************************
*函数名称：dash_big
*函数功能：在平地上往前走一点,node3处必须要往前走一点
*说明    ：
******************************************************/
void dash_big(void)
{
	go_open(Road_Speed_H,Road_Speed_H,0.35);
}

/******************************************************
*函数名称：down_platform
*函数功能：慢速下台直到完全走到平地上
*说明    ：
******************************************************/
void down_platform(void)
{
	dash_dp();
	while(1)
	{
		go_forward(Down_Platform,Straight_Quick);
		if(G_L == 0)
			break;
	}
	
	while(1)
	{
		go_forward(Down_Platform,Straight_Quick);
		if(G_L == 1)
			break;
	}
}

/******************************************************
*函数名称：down_platform8
*函数功能：慢速下台直到完全走到平地上
*说明    ：只用于平台8
******************************************************/
void down_platform8(void)
{
	//dash_dp();
//	go_open(Origin_Speed,Origin_Speed,0.2);
	TIM1_ON();
	while(1)
	{
		go_forward(Down_Platform,Straight_Quick);
		if( (G_L == 0) && (_second > 3) ) 
			break;
	}
	
	while(1)
	{
		go_forward(Down_Platform,Straight_Quick);
		if(G_L == 1)
			break;
	}
}

/******************************************************
*函数名称：Door_Judege
*函数功能：判断门X是否开
*说明    ：如果到了门前光电仍为1,则强制退出判断并认为是开的
******************************************************/
void Door_Judege(uint8_t doornum)
{
	/* 先快速走一段 */
	if(doornum == 4)
		go_closed(750,Straight_Quick,0.4);
	
	else
		go_closed(750,Straight_Quick,0.5);
	
	/* 开始判断 */
	while(1)
	{
		go_forward(450,Straight_Quick);
		if(G_R == 0)
		{
			switch(doornum)
			{
				case 1 : Door.D1=_closed;  break;
				case 2 : Door.D2=_closed;  break;
				case 3 : Door.D3=_closed;  break;
				case 4 : Door.D4=_closed;  break;
				default : break;
			}
			stop(0.1);
			break;
		}
		
		/* 强制结束 */
		if(G_L == 0)
		{
			if(G_R == 0) /* 门关 */
			{
				switch(doornum)
				{
					case 1 : Door.D1=_closed;  break;
					case 2 : Door.D2=_closed;  break;
					case 3 : Door.D3=_closed;  break;
					case 4 : Door.D4=_closed;  break;
					default : break;
				}
				stop(0.1);
			}
			
			else /* 门开 */
			{
				switch(doornum)
				{
					case 1 : Door.D1=_open;  break;
					case 2 : Door.D2=_open;  break;
					case 3 : Door.D3=_open;  break;
					case 4 : Door.D4=_open;  break;
					default : break;
				}
				go_closed(550,Straight_Quick,1);//防止过门被识别成过白线了
			}
			
			break;
	  }
  } 
	
	
}

/******************************************************
*函数名称：go_door
*函数功能：过门(只用于回家时)
*说明    ：快速跑直到光电被挡住(说明到了门),然后定时走过门X
******************************************************/
void go_door(void)
{
	while(1)
	{
		go_forward(650,Straight_Quick);
		if(G_L==0)
		{
			go_closed(550,Straight_Quick,1.2);
			break;
		}
	}
}