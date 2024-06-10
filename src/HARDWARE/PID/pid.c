#include "pid.h"
#include "motor.h"
#include "delay.h"
#include "tim.h"
#include "task.h"
float error=0;
int adjust=0;
/* ȫ�ֱ���*/
int sum1=0;	
float left_pwm=0,right_pwm=0;		
float error1=0; 
uint8_t G_L,G_R;

/* ��β���GL,���ض������ */
void Read_GD_L_Data(void)
{
	uint8_t i;
	uint8_t y=0,w=0;
	uint8_t D[3]={0};
	for(i = 0;i < 3;i++) //�ɼ�5������
	{
		D[i] = GL;
		delay_us(40);
	}
	for(i = 0;i < 3;i++) 
	{
		if(D[i] == 1) w++;
		else y++;
	}
	if(y > w) G_L = 0;  //���ڲɼ�5���������Բ�������ȵ����
	else G_L = 1;
}

/* ��β���GR,���ض������ */
void Read_GD_R_Data(void)
{
	uint8_t i;
	uint8_t y=0,w=0;
	uint8_t D[5]={0};
	for(i = 0;i < 5;i++) //�ɼ�5������
	{
		D[i] = GR;
		delay_us(40);
	}
	for(i = 0;i < 5;i++) 
	{
		if(D[i] == 1) w++;
		else y++;
	}
	if(y > w) G_R = 0;  //���ڲɼ�5���������Բ�������ȵ����
	else G_R = 1;
}

/* ��������������ֵ */
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
*�������ƣ�Hui_Error_return
*�������ܣ����ݻҶ�״̬����һ��ƫ������ٶ�PID����
*������
*˵����	�ҶȺ�ɫ����1����ɫ����0
**************************************/
float Hui_Error_return(void)
{
	Read_Digital_Data();
	
	if(flag.pid_flag==Straight_Quick)//#############��������ֱ��Ѱ��#############
	{
		//��ƫ��
		if(E4==0&&E5==0) {error=0;}//1110 0111
		//0.5��ƫ��
		else if(E4==1&&E5==0){error=-0.5;}//1111 0111 ��ͷ��ƫΪ����  Change=0.5*Kp*speed
		else if(E4==0&&E5==1){error=0.5;} //1110 1111 ��ƫΪ����      Change>speedʱ���ӲŻᷴת
		
		//1��ƫ��
		else if(E5==0&&E6==0){error=-1;}//1111 0011 ��ͷ��ƫΪ����  Change=1*Kp*speed
		else if(E3==0&&E4==0){error=1;} //1100 1111 ��ƫΪ����
		
		//1.5��ƫ��
		else if(E5==1&&E6==0){error=-1.5;}//1111 1011 ��ͷ��ƫΪ����  Change=1.5*Kp*speed
		else if(E3==0&&E4==1){error=1.5;} //1101 1111 ��ƫΪ����
		
		//2��ƫ��
		else if(E6==0&&E7==0){error=-2;}//1111 1001 ��ͷ��ƫΪ����  Change=2*Kp*speed
		else if(E2==0&&E3==0){error=2;} //1001 1111 ��ƫΪ����
		
		//2.5��ƫ��
		else if(E6==1&&E7==0){error=-2.5;}//1111 1101 ��ͷ��ƫΪ����  Change=2.5*Kp*speed
		else if(E2==0&&E3==1){error=2.5;} //1011 1111 ��ƫΪ����
		
		//3��ƫ��
		else if(E7==0&&E8==0){error=-3;}//1111 1100 ��ͷ��ƫΪ����  Change=3*Kp*speed
		else if(E1==0&&E2==0){error=3;} //0011 1111 ��ƫΪ����
		
		//3.5��ƫ��
		else if(E7==1&&E8==0){error=-3.5;}//1111 1110 ��ͷ��ƫΪ����  Change=3.5*Kp*speed
		else if(E1==0&&E2==1){error=3.5;} //0111 1111 ��ƫΪ����
		
		else
		error=0;	
	}

	else if(flag.pid_flag==S_Curve)//#############����������#############
	{
		//��ƫ��
		if(E4==0&&E5==0) {error=0;}//1110 0111
		//0.5��ƫ��
		else if(E4==1&&E5==0){error=-0.5;}//1111 0111 ��ͷ��ƫΪ����  Change=0.5*Kp*speed
		else if(E4==0&&E5==1){error=0.5;} //1110 1111 ��ƫΪ����      Change>speedʱ���ӲŻᷴת
		
		//1��ƫ��
		else if(E5==0&&E6==0){error=-1;}//1111 0011 ��ͷ��ƫΪ����  Change=1*Kp*speed
		else if(E3==0&&E4==0){error=1;} //1100 1111 ��ƫΪ����
		
		//1.5��ƫ��
		else if(E5==1&&E6==0){error=-1.5;}//1111 1011 ��ͷ��ƫΪ����  Change=1.5*Kp*speed
		else if(E3==0&&E4==1){error=1.5;} //1101 1111 ��ƫΪ����
		
		//2��ƫ��
		else if(E6==0&&E7==0){error=-2;}//1111 1001 ��ͷ��ƫΪ����  Change=2*Kp*speed
		else if(E2==0&&E3==0){error=2;} //1001 1111 ��ƫΪ����
		
		//2.5��ƫ��
		else if(E6==1&&E7==0){error=-3;}//1111 1101 ��ͷ��ƫΪ����  Change=3*Kp*speed
		else if(E2==0&&E3==1){error=3;} //1011 1111 ��ƫΪ����
		
		//3��ƫ��
		else if(E7==0&&E8==0){error=-3.5;}//1111 1100 ��ͷ��ƫΪ����  Change=3.5*Kp*speed
		else if(E1==0&&E2==0){error=3.5;} //0011 1111 ��ƫΪ����
		
		//3.5��ƫ��
		else if(E7==1&&E8==0){error=-4.5;}//1111 1110 ��ͷ��ƫΪ����  Change=4.5*Kp*speed
		else if(E1==0&&E2==1){error=4.5;} //0111 1111 ��ƫΪ����
		
		else
		error=0;
	}
	
	else if(flag.pid_flag==Straight_Slow)//#############����������ֱ��#############
	{
		//��ƫ��
		if(E4==0&&E5==0) {error=0;}//1110 0111
		//0.5��ƫ��
		else if(E4==1&&E5==0){error=-0.5;}//1111 0111 ��ͷ��ƫΪ����  Change=0.5*Kp*speed
		else if(E4==0&&E5==1){error=0.5;} //1110 1111 ��ƫΪ����      Change>speedʱ���ӲŻᷴת
		
		//1��ƫ��
		else if(E5==0&&E6==0){error=-1;}//1111 0011 ��ͷ��ƫΪ����  Change=1*Kp*speed
		else if(E3==0&&E4==0){error=1;} //1100 1111 ��ƫΪ����
			
		else
		error=0;	
	}
	
	return error;
}

/*************************************
*�������ƣ�go_forward
*�������ܣ����Զ����ٶ�Ѱ��
*������initial_speed����ʼ�ٶ�
			 mode��Ѱ��ģʽѡ��.0�ǹر�,�ο�pid_enum
*˵����	
**************************************/
PID pid_f={0,0,0,0,0,0,0,0};
void go_forward(int initial_speed,PID_TYPE pid_mode)
{
	float change = 0;
	flag.pid_flag = pid_mode;
	/* PID������ʼ�� */
	switch(flag.pid_flag)
	{
		case Straight_Quick:  pid_f.kp = 0.30 * initial_speed;  pid_f.ki = 0;pid_f.kd = 0;  break;
		case S_Curve			 :	pid_f.kp = 0.50 * initial_speed;  pid_f.ki = 0;pid_f.kd = 0;  break;
		case Straight_Slow :	pid_f.kp = 0.30 * initial_speed;  pid_f.ki = 0;pid_f.kd = 0;  break;
		default: break;
	}

	/* ����Ѱ�� */
	if(flag.pid_flag!=0)
	{
		error1=Hui_Error_return();
		pid_f.Now_err = error1;
		pid_f.Sum_err += pid_f.Now_err;
		if(pid_f.Sum_err >= MAX_sumERR) {pid_f.Sum_err = MAX_sumERR;}//�����޷�
		pid_f.Diff_err = pid_f.Now_err - pid_f.Last_err; 
		pid_f.Last_err = pid_f.Now_err;
		/* PID������� */
		change = pid_f.kp * pid_f.Now_err
					 + pid_f.ki * pid_f.Sum_err 
					 + pid_f.kd * pid_f.Diff_err;
	}
	/* �ر�Ѱ�� */
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


/* Ѱ������� */
PID pid_b={0,0,0,0,0,0,0,0};
void go_back(int initial_speed)
{		
  if(flag.pid_flag==1) {error1=Hui_Error_return();}/* ����Ѱ�� */
	else {error1=0;}/* �ر�Ѱ�� */

  left_pwm  = initial_speed - error1 * initial_speed;
  right_pwm = initial_speed + error1 * initial_speed;
  motor(-right_pwm,-left_pwm); 
}


/* ��תָ���Ƕ� */
void turn_right(int speed,float angle)
{
	float ang_last;
	float ang_now;
	float sum;
	flag.MPU_flag=1;	//����������
//	angle=angle*0.9;	//�����������������
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
	flag.MPU_flag=0;	//�ر�������
	stop(Rotation_delay);//ֹͣһ��ʱ��
}

/* ��תָ���Ƕ� */
void turn_left(int speed,float angle)
{
	float ang_last;
	float ang_now;
	float sum;
	flag.MPU_flag=1;	//����������
//	angle=angle*0.9;	//�����������������
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
	flag.MPU_flag=0;	//�ر�������
	stop(Rotation_delay);//ֹͣһ��ʱ��
}

/* ֹͣһ��ʱ�� */
void stop(float target_s)
{
  error1=0;  
	TIM1_ON();
	while(_second < target_s)
  {
		motor(0,0);
	}
	TIM1_OFF();//�رն�ʱ��1
}

void go_adjust(int initial_speed,AD_TYPE ad_mode)//��ɫ�괫��������
{
	flag.adjust_flag = ad_mode;
	Read_Digital_Data();
	if(flag.adjust_flag == AD_UpBridge)//###############����
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed-5,initial_speed);
		}
		else if(S1 == 0)//��ƫ
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//��ƫ
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
	
	else if(flag.adjust_flag == AD_OnBridge)//###############����
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed-5,initial_speed);
		}
		else if(S1 == 0)//��ƫ
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//��ƫ
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
	
	else if(flag.adjust_flag == AD_DownBridge)//###############����
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed,initial_speed);
		}
		else if(S1 == 0)//��ƫ
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//��ƫ
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
	
	else if(flag.adjust_flag == AD_Seesaw)//###############�����ΰ�
	{
		if(S1 == 1&&S2 == 1)			  
		{
			motor(initial_speed,initial_speed);
		}
		else if(S1 == 0)//��ƫ
		{
			motor(initial_speed,-initial_speed);
			delay_ms(5);//10
		}
		else if(S2 == 0)//��ƫ
		{
			motor(-initial_speed,initial_speed);
			delay_ms(5);//10
		}
	}
}
//--------------------------------------------------------------------

/* ��/��תֱ�������ߵ����� */
void turn_until_line(int L_speed,int R_speed,float time)//���ڷֲ�ʱת����һ������
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

/* ��ת�Զ���ʱ�� */
void right_time(int L_speed,int R_speed,float time)
{
	TIM1_ON();
	while(_second < time)
	{
		motor(L_speed,R_speed);
	}
	TIM1_OFF();
}

/* ��ת�Զ���ʱ�� */
void left_time(int L_speed,int R_speed,float time)
{
	TIM1_ON();
	while(_second < time)
	{
		motor(L_speed,R_speed);
	}
	TIM1_OFF();
}

/* �������Զ���ʱ�� */
void go_open(int L_speed,int R_speed,float time)
{
	TIM1_ON();
	while(_second < time)
	{
		motor(L_speed,R_speed);
	}
	TIM1_OFF();
}

/* Ѱ�����Զ���ʱ��,ͬʱ����ŵ�״̬ */
void go_closed(int initial_speed,PID_TYPE pid_mode,float time)
{
	TIM1_ON();
	while(_second <= time)
	{
		go_forward(initial_speed,pid_mode);
	}
	
	TIM1_OFF();
}

/* Ѱ��ֱ���Ҷ�ȫ�����߲�ֹͣ */
void forward_head(int initial_speed,PID_TYPE pid_mode)
{
	while(sum1>=5)//����3��������ֹͣ
	{
		go_forward(initial_speed,pid_mode);
	}
}

/******************************************************
*�������ƣ�forward_mid
*�������ܣ�Ѱ��ֱ���Ҷ�ȫ������(3�����ϼ�⵽),�ڳ�������ʱֹͣ
*����		 ��num����Ҫ�߹��ķֲ���ߵĸ���
******************************************************/
void forward_mid(int initial_speed,PID_TYPE pid_mode,int num)
{
	int line=0;
	int num_remain = num;//��ʣ��Ҫ�߰��ߵ�����
	TIM1_ON();
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* �жϳ�ͷ */
		if(sum1<=5 && _second >0.3)
		{
			line=1;
			TIM1_OFF();
		}
		
		/* �жϳ��� */
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
*�������ƣ�forward_mid_light
*�������ܣ�Ѱ��ֱ���Ҷ�ȫ������(�Լ��趨�������ϼ�⵽),�ڳ�������ʱֹͣ
					 �����ߵ���İ��ߡ�
*����		 ��num����Ҫ�߹��ķֲ���ߵĸ���
					_sum��8-�ж���ͷ�����ߵĵƵĸ���
*******************************************************/
void forward_mid_light(int initial_speed,PID_TYPE pid_mode,int num,int _sum)
{
	int line=0;
	int passed_flag=0;
	int num_remain = num;//��ʣ��Ҫ�߰��ߵ�����
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* �жϳ�ͷ */
		if(passed_flag == 0)
		{
			if(sum1<=_sum)
				line=1;
		}
		else if(passed_flag > 0) //�ڶ����ֲ��߱����ڵ�һ������0.5s��Żᱻ�ж�,����һ���ֲ����ж϶��
		{
			if(sum1<=_sum && _second >=0.18)//0.5
			{
				line=1;
				TIM1_OFF();
			}
		}
		
		/* �жϳ��� */
		if(line==1 && (EL==0||ER==0) )
		{
			line=0;
			num_remain--;			
			passed_flag++;
			TIM1_ON();	//����һ���ֲ��ߺ�ʼ��ʱ
		}
		
		if(num_remain==0)
		{
			TIM1_OFF();
			break;
		}
	}

}

/******************************************************
*�������ƣ�forward_mid_light_L
*�������ܣ�Ѱ��ֱ���Ҷ�ȫ������(�Լ��趨�������ϼ�⵽),�ڳ�������ʱֹͣ
					 �����ߵ���İ��ߡ�
*����		 ��num����Ҫ�߹��ķֲ���ߵĸ���
					_sum��8-�ж���ͷ�����ߵĵƵĸ���
*******************************************************/
void forward_mid_light_L(int initial_speed,PID_TYPE pid_mode,int num,int _sum)
{
	int line=0;
	int passed_flag=0;
	int num_remain = num;//��ʣ��Ҫ�߰��ߵ�����
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* �жϳ�ͷ */
		if(passed_flag == 0)
		{
			if(sum1<=_sum)
				line=1;
		}
		else if(passed_flag > 0) //�ڶ����ֲ��߱����ڵ�һ������0.5s��Żᱻ�ж�,����һ���ֲ����ж϶��
		{
			if(sum1<=_sum && _second >0.5)
			{
				line=1;
				TIM1_OFF();
			}
		}
		
		/* �жϳ��� */
		if(line==1 && EL==0 )
		{
			line=0;
			num_remain--;			
			passed_flag++;
			TIM1_ON();	//����һ���ֲ��ߺ�ʼ��ʱ
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
	int num_remain = num;//��ʣ��Ҫ�߰��ߵ�����
	while(1)
	{
		go_forward(initial_speed,pid_mode);
		/* �жϳ�ͷ */
		if(passed_flag == 0)
		{
			if(sum1<=_sum)
				line=1;
		}
		else if(passed_flag > 0) //�ڶ����ֲ��߱����ڵ�һ������0.5s��Żᱻ�ж�,����һ���ֲ����ж϶��
		{
			if(sum1<=_sum && _second >0.5)
			{
				line=1;
				TIM1_OFF();
			}
		}
		
		/* �жϳ��� */
		if(line==1 && ER==0 )
		{
			line=0;
			num_remain--;			
			passed_flag++;
			TIM1_ON();	//����һ���ֲ��ߺ�ʼ��ʱ
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
*�������ƣ�platform
*�������ܣ��ȿ����߶ξ���,Ȼ��������ƽ̨����תһȦ
*˵��    ����ROLL��ʶ��
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
		go_forward(Down_Platform,Straight_Quick);//��ƽ������Ѱ��ֱ���ߵ�ƽ̨��
		_MPU_READ;
		if(abs(roll)>15 && _second>0.5)//��������
			upflag=1;

		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//�Ѿ��ߵ���ƽ̨��
		{
			dash_op();
			stop(0.2); 
			TIM1_OFF();
			break;
		}
	}
	//blink();
	_MPU_READ;
	turn_right(550,165);//��ƽ̨����תһȦ170
}

/******************************************************
*�������ƣ�platform_new
*�������ܣ��ȿ����ߵ����´�,Ȼ��������ƽ̨����תһȦ
*˵��    �������ʶ��
******************************************************/
void platform_new(void)//��ƽ̨����תһȦ
{
	TIM1_OFF();
	/* ƽ�� */
	while(1)
	{
		go_forward(Road_Speed_H,Straight_Quick);//��ƽ�ؿ���Ѱ��ֱ���ߵ�ƽ̨��
		Read_Digital_Data();

		if(GL==0)
			break;//��������
	}
	
	/* ���� */
	TIM1_ON();
	while(1)
	{
		_MPU_READ;
		go_forward(Up_Platform,Straight_Slow);//��ƽ������Ѱ��ֱ���ߵ�ƽ̨��
		if(sum1<=4 && _second > 0.4)	//�Ѿ��ߵ���ƽ̨��
		{
			TIM1_OFF();
			break;
		}
	}
	dash_op();
	stop(Base_delay);

	_MPU_READ;
	_MPU_READ;
	turn_right(550,165);//��ƽ̨����תһȦ170
}

/******************************************************
*�������ƣ�platform7
*�������ܣ��ȿ����ߵ����´�,Ȼ��������ƽ̨����תһȦ
*˵��    ��
******************************************************/
void platform7(void)//��ƽ̨����תһȦ
{
	float roll_ref;
	while(1)
	{
		go_forward(Road_Speed_H,Straight_Quick);//��ƽ�ؿ���Ѱ��ֱ���ߵ�ƽ̨��
		Read_Digital_Data();

		if(GL == 0)
			break;//��������
	}

	TIM1_ON();
	while(1)
	{
		_MPU_READ;
		go_forward(Up_Platform,Straight_Quick);//��ƽ������Ѱ��ֱ���ߵ�ƽ̨
		
		if(sum1<=4 && _second >2.2)
		{
			TIM1_OFF();
			break;
		}
	}
	go_open(Origin_Speed,Origin_Speed,0.12);
	stop(Base_delay);

	_MPU_READ;
	turn_right(550,165);//��ƽ̨����תһȦ170

	go_closed(300,Straight_Quick,0.9);
}

/******************************************************
*�������ƣ�platform8
*�������ܣ��ȿ����ߵ����´�,Ȼ��������ƽ̨����תһȦ
*˵��    ��
******************************************************/
void platform8(void)//��ƽ̨����תһȦ
{
	while(1)
	{
		go_forward(Road_Speed_H,Straight_Quick);//��ƽ�ؿ���Ѱ��ֱ���ߵ�ƽ̨��
		Read_Digital_Data();

		if(GL==0)
			break;//��������
	}
	TIM1_ON();
	while(1)
	{
		_MPU_READ;
		go_forward(Up_Platform,Straight_Quick);//��ƽ������Ѱ��ֱ���ߵ�ƽ̨��
		if(sum1<=2 && _second >2.5)	//�Ѿ��ߵ���ƽ̨��
		{
			TIM1_OFF();
			break;
		}
	}
	//dash_op();
	go_open(Origin_Speed,Origin_Speed,0.20);
	stop(Base_delay);

	_MPU_READ;
	turn_right(550,167);//��ƽ̨����תһȦ170

//	stop(3);
	/* ���ճ��� */
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
*�������ƣ�crash
*�������ܣ�ײ̨��ת180��
*˵��    ��
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
	turn_until_line(500,-500,0.4);//����ͷ
}

/******************************************************
*�������ƣ�right2line
*�������ܣ���תת�������ߵ�������
*˵��    ��
******************************************************/
void right2line(int speed,float mintime)
{
	turn_until_line(speed,-speed,mintime);
}

/******************************************************
*�������ƣ�left2line
*�������ܣ���תת�������ߵ�������
*˵��    ��
******************************************************/
void left2line (int speed,float mintime)
{
	turn_until_line(-speed,speed,mintime);
}

/******************************************************
*�������ƣ�dash_dp
*�������ܣ���ƽ̨һ��ʼ�������������ڿ�ʼѰ��
*˵��    ��
******************************************************/
void dash_dp(void)
{
	go_open(Origin_Speed,Origin_Speed,0.2);//�����ܵ�������
}

/******************************************************
*�������ƣ�dash_op
*�������ܣ���ƽ̨��ǰ��һ����ͣ��
*˵��    ��
******************************************************/
void dash_op(void)
{
	go_open(Origin_Speed,Origin_Speed,0.13);
}

/******************************************************
*�������ƣ�dash
*�������ܣ���ƽ������ǰ��һ��
*˵��    ��
******************************************************/
void dash(void)
{
	go_open(600,600,0.1);
}

/******************************************************
*�������ƣ�dash_big
*�������ܣ���ƽ������ǰ��һ��,node3������Ҫ��ǰ��һ��
*˵��    ��
******************************************************/
void dash_big(void)
{
	go_open(Road_Speed_H,Road_Speed_H,0.35);
}

/******************************************************
*�������ƣ�down_platform
*�������ܣ�������ֱ̨����ȫ�ߵ�ƽ����
*˵��    ��
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
*�������ƣ�down_platform8
*�������ܣ�������ֱ̨����ȫ�ߵ�ƽ����
*˵��    ��ֻ����ƽ̨8
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
*�������ƣ�Door_Judege
*�������ܣ��ж���X�Ƿ�
*˵��    �����������ǰ�����Ϊ1,��ǿ���˳��жϲ���Ϊ�ǿ���
******************************************************/
void Door_Judege(uint8_t doornum)
{
	/* �ȿ�����һ�� */
	if(doornum == 4)
		go_closed(750,Straight_Quick,0.4);
	
	else
		go_closed(750,Straight_Quick,0.5);
	
	/* ��ʼ�ж� */
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
		
		/* ǿ�ƽ��� */
		if(G_L == 0)
		{
			if(G_R == 0) /* �Ź� */
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
			
			else /* �ſ� */
			{
				switch(doornum)
				{
					case 1 : Door.D1=_open;  break;
					case 2 : Door.D2=_open;  break;
					case 3 : Door.D3=_open;  break;
					case 4 : Door.D4=_open;  break;
					default : break;
				}
				go_closed(550,Straight_Quick,1);//��ֹ���ű�ʶ��ɹ�������
			}
			
			break;
	  }
  } 
	
	
}

/******************************************************
*�������ƣ�go_door
*�������ܣ�����(ֻ���ڻؼ�ʱ)
*˵��    ��������ֱ����类��ס(˵��������),Ȼ��ʱ�߹���X
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