#include "task.h"
/* �޸�·��ͨ���ĸ��������ڵ�Road_flag���� */
#ifdef __Routine2
/*��·����ƽ̨3��4��5*/
int k=0;

void origin(void)
{
	Read_Digital_Data();
	//motor(0,0);
	//while(!G1);//�ȴ��ƿ����� 
	
	go_open(500,500,0.5);//�����ܵ�������
	TIM1_ON();

	while(1)	//��ʼѰ��
	{
		go_forward(700,Straight_Quick);
	  _MPU_READ;
//		if(abs(roll)>15&&_second>=2.5) 
		if(sum1==8&&_second>=2.0)
		{
			TIM1_OFF();
			break;
		}
	}
	flag.Road_flag=_on_bridge;
}

void up_bridge(void)
{
//	Read_Digital_Data();
//	_MPU_READ;
//	while(abs(roll)>15)//������
//	{
//		_MPU_READ;
//		go_adjust(550,AD_UpBridge);//������£���ɫ�����----------------------------
//	}
////	stop(1);
//	flag.Road_flag=_on_bridge;
}

void on_bridge(void)
{
	Read_Digital_Data();
	_MPU_READ;

	while(1)//��ƽ����
	{
		Read_Digital_Data();
		_MPU_READ;
		go_adjust(650,AD_OnBridge);
		if(sum1<=6)//��⵽����
			break;
	}

	flag.Road_flag=_platform2;
}

void down_bridge(void)
{
//	Read_Digital_Data();
//	mpu_dmp_get_data(&pitch,&roll,&yaw);
//	while(abs(roll)>15)//������
//	{
//		_MPU_READ;
//		motor(200,200);//�������£���ɫ�����
//	}
//	
//	//stop(0.2);
//	flag.Road_flag=_platform2;
}

/*************************************
*�������ƣ�platform2
*�������ܣ���ƽ̨2����תһȦ
*��һ״̬��_right_turn1
**************************************/
void platform2(void)
{
	int upflag=0;
	TIM1_ON();
	while(1)
	{
		go_forward(700,Straight_Quick);//��ƽ��Ѱ��ֱ���ߵ�ƽ̨2��
		_MPU_READ;
		if(abs(roll)>15 && _second>0.5)//��������
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//�Ѿ��ߵ���ƽ̨2��
		{
			go_open(500,500,0.2);
			stop(0.2); 
			TIM1_OFF();
			break;
		}
	}
	blink();
	_MPU_READ;
	turn_right(450,175);//��ƽ̨����תһȦ170
	
	flag.Road_flag=_right_turn1;
}

/*************************************
*�������ƣ�right_turn1
*�������ܣ���ƽ̨2,�ߵ��ֲ�㴦����ת
*��һ״̬��_mountains	
**************************************/
void right_turn1(void)
{
	Read_Digital_Data();
	go_open(500,500,0.5);//�����ܵ�������
	
	forward_mid(700,Straight_Quick,1);
	turn_until_line(500,-500,0.2);
	
	flag.Road_flag=_mountains;
}

/*************************************
*�������ƣ�mountains
*�������ܣ���������ɽ��ͣ�ڷֲ�㴦
*��һ״̬��_platform4	
**************************************/
void mountains(void)//����ɽ
{
	forward_mid(500,Straight_Quick,1);
	flag.Road_flag=_platform4;
}

/*************************************
*�������ƣ�platform4
*�������ܣ�ֱ����ƽ̨4����ת
*��һ״̬��_platform3	
**************************************/
void platform4(void)
{
	int upflag=0;
	Read_Digital_Data();

	forward_mid(800,Straight_Quick,1);//���ߵ�node3
	while(1)
	{
		go_forward(750,Straight_Quick);//��ƽ��Ѱ��ֱ���ߵ�ƽ̨��
		_MPU_READ;
		if(abs(roll)>15)//��������
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//�Ѿ��ߵ���ƽ̨��
		{
			go_open(300,300,0.4);
			stop(0.2); 
			break;
		}
	}
	
	_MPU_READ;
	turn_right(400,175);//��ƽ̨����תһȦ170
	
	flag.Road_flag=_platform3;
}

/*************************************
*�������ƣ�platform3
*�������ܣ�����ƽ̨4,����3���ֲ��ߵ�node1,Ȼ����ƽ̨3,Ȼ����ת
*��һ״̬��_node1_p3	
**************************************/
void platform3(void)
{
	int upflag=0;
	Read_Digital_Data();
	forward_mid(800,Straight_Quick,3);//���ߵ�node1
	while(1)
	{
		go_forward(800,Straight_Quick);//��ƽ��Ѱ��ֱ���ߵ�ƽ̨��
		_MPU_READ;
		if(abs(roll)>15)//��������
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//�Ѿ��ߵ���ƽ̨��
		{
			go_open(300,300,0.2);
			stop(0.2); 
			break;
		}
	}
	
	_MPU_READ;
	turn_right(400,175);//��ƽ̨����תһȦ170
	
	flag.Road_flag=_node1_p3;
}

void node1_p0(void)
{
	
}

/*************************************
*�������ƣ�node1_p3
*�������ܣ�����ƽ̨3,����1���ֲ��ߵ�node1,Ȼ����ת����1�ķ���
*��һ״̬��_node2_d1	
**************************************/
void node1_p3(void)
{
	go_open(500,500,1);
	forward_mid_light(500,Straight_Quick,1,3);//���ߵ�node1
	turn_until_line(400,-400,0.4);//ת����1����
	flag.Road_flag=_node2_d1;
}

/*************************************
*�������ƣ�node2_d1
*�������ܣ��趨һ��ʱ������1��ȥ,�ڴ�ʱ���ڼ�����Ƿ�����
					 ��1����������1���ֲ��ߵ�node2,����ת�����ΰ巽��
					 ��1�رգ���ͷ,ת��node1����
*��һ״̬��_seesaw1 		(��1��)
					 _rt_node1_d1 (��1��)
**************************************/
void node2_d1(void)
{
	go_closed(550,Straight_Quick,2,DT_1);
//	stop(1);
	//�ſ�
	if(Door.D1==_open){
		forward_mid(800,Straight_Quick,1);//�ߵ�node2
		turn_until_line(500,-500,0.2);//ת�����ΰ巽��	
		flag.Road_flag=_seesaw1;
		}
	
	//�Ź�
	else if(Door.D1==_closed){
		turn_until_line(-500,500,0.4);//ת��node1����		
		flag.Road_flag=_rt_node1_d1;
		}
}

/*************************************
*�������ƣ�rt_node1_d1
*�������ܣ�����1����ֱ�߾���һ���ֲ��߷��ص�node1,��ת����2����
*��һ״̬��_node2_d2	
**************************************/
void rt_node1_d1(void)
{
	forward_mid(450,Straight_Quick,1);//�ߵ�node1
	go_open(500,500,0.15);
	turn_until_line(500,-500,0.3);
	turn_until_line(500,-500,0.2);//ת����2����,ת2������׼ȷ��		
	flag.Road_flag=_node2_d2;
}

/*************************************
*�������ƣ�node2_d2
*�������ܣ��趨һ��ʱ������2��ȥ,�ڴ�ʱ���ڼ�����Ƿ�����
					 ��2�������Ⱦ���һ���ֲ�㵽�����м�,Ȼ��ת��node2����,�پ���һ���ֲ�㵽node2,��ת�����ΰ巽��			
					 ��2�رգ���ͷ,ת��node1����
*��һ״̬��_seesaw1 		(��2��)
					 _rt_node1_d2 (��2��)
**************************************/
void node2_d2(void)
{
	go_closed(450,Straight_Quick,2,DT_2);
	//�ſ�
	if(Door.D2==_open){
		forward_mid(450,Straight_Quick,1);//�ߵ��ֲ��
		turn_until_line(500,-500,0.4);//ת�����ΰ巽��	
//		forward_mid(450,Straight_Quick,1);//�ߵ�node2
		forward_mid_light(450,Straight_Quick,1,4);
		go_open(500,500,0.1);
		turn_until_line(500,-500,0.2);//ת�����ΰ巽��	
		flag.Road_flag=_seesaw1;
		}
	
	//�Ź�
	else if(Door.D2==_closed){
		turn_until_line(-500,500,0.4);//ת��node1����		
		flag.Road_flag=_rt_node1_d2;
		}
}

/*************************************
*�������ƣ�rt_node1_d2
*�������ܣ�����2����ֱ�߾���һ���ֲ��߷��ص�node1,��ת��node3����
*��һ״̬��_node3_n1	
**************************************/
void rt_node1_d2(void)
{
	forward_mid(450,Straight_Quick,1);//�ߵ�node1
		go_open(500,500,0.15);
	turn_until_line(500,-500,0.4);//ת��node3����		
	flag.Road_flag=_node3_n1;
}

/*************************************
*�������ƣ�node3_n1
*�������ܣ���node1����ֱ�߾���2���ֲ��߷��ص�node3,��ת����3����
*��һ״̬��_node2_d3	
**************************************/
void node3_n1(void)
{
//	forward_mid(550,Straight_Quick,1);//�ߵ�node3
//	go_closed(550,Straight_Quick,0.5,DT_Disable);
//	forward_mid(550,Straight_Quick,1);//�ߵ�node3

	forward_mid(750,Straight_Quick,2);//�ߵ�node3
	turn_until_line(500,-500,0.2);//ת��node3����	
	turn_until_line(500,-500,0.2);//ת��node3����		

	flag.Road_flag=_node2_d3;
}

/*************************************
*�������ƣ�node2_d3
*�������ܣ�����3�����Ⱦ���1���ֲ��ߵ���������,�پ���һ���ֲ��ߵ�node2����ת�����ΰ巽��
*��һ״̬��_seesaw1
**************************************/
void node2_d3(void)
{
	forward_mid(550,Straight_Quick,1);//�ߵ�node2
	forward_mid_light(450,Straight_Quick,1,4);
	go_open(500,500,0.1);
//	forward_mid(550,Straight_Quick,1);//�ߵ�node2
//	LED_R_ON;
//	go_open(500,500,0.15);
	turn_until_line(500,-500,0.2);//ת�����ΰ巽��	
	flag.Road_flag=_seesaw1;
}

/*************************************
*�������ƣ�seesaw1
*�������ܣ���ֱ��,�ڵ�һ���ֲ�㴦ת�����ΰ�1����,Ѱ�����ϰ�(�ϰ�ǰҪ��תһ��)��
					 �°��ǰ��һ���ֲ��,��ת��ƽ̨6�ķ���
*��һ״̬��_platform6
**************************************/
void seesaw1(void)//���ΰ�1
{
	forward_mid(800,Straight_Quick,1);
	turn_until_line(500,-500,0.5);
	go_closed(500,S_Curve,0.4,DT_Disable);
	go_open(350,500,0.3);
	while(1)
	{
		go_forward(450,S_Curve);
		if(sum1>=8)
			break;
	}
//	stop(10);
	go_open(-300,500,0.15);
	TIM1_ON();
	while(1)
	{
		Read_Digital_Data();
		go_adjust(500,AD_Seesaw);
		if(_second>=1.15)
		{
			TIM1_OFF();
			break;
		}
	}
	stop(1.5);//��������ȥ
	go_open(-100,500,0.4);//�ܵ�������
	forward_mid(450,Straight_Quick,1);
	turn_until_line(-500,500,0.3);//ת��ƽ̨6����
	
	flag.Road_flag=_platform6;
}

/*************************************
*�������ƣ�platform6
*�������ܣ�ֱ����ƽ̨6,��ת,��̨,ǰ��һ���ֲ�㲢ת����2�ķ���
*��һ״̬��_seesaw2
**************************************/
void platform6(void)//ֱ����ƽ̨6����ת����ȥ������������ת
{
	int upflag=0;
	Read_Digital_Data();
	while(1)
	{
		go_forward(450,Straight_Quick);//��ƽ��Ѱ��ֱ���ߵ�ƽ̨��
		_MPU_READ;
		if(abs(roll)>15)//��������
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//�Ѿ��ߵ���ƽ̨��
		{
			go_open(300,300,0.4);
			stop(0.2); 
			break;
		}
	}
	
	_MPU_READ;
	turn_right(500,175);//��ƽ̨����תһȦ170
	
	forward_mid(450,Straight_Quick,1);//�ߵ�Բ��
	turn_until_line(-500,500,0.3);//ת�����ΰ巽��
	
	flag.Road_flag=_seesaw2;
}

/*************************************
*�������ƣ�seesaw2
*�������ܣ�Ѱ�����ϰ�(�ϰ�ǰҪ��תһ��)��
					 �°��ǰ��һ���������ֲ�㵽node2
*��һ״̬��_platform6
**************************************/
void seesaw2(void)//���ΰ�2
{
	while(1)
	{
		go_forward(450,S_Curve);
		if(sum1>=8)
			break;
	}
	go_open(-300,500,0.14);
	//�Ҷȵ����ΰ�
	//go_open(100,500,0.3);//�����ΰ�ƫ����,����ֱ�ӵ���ȥ��
	TIM1_ON();
	while(1)
	{
		Read_Digital_Data();
		go_adjust(500,AD_Seesaw);
		if(_second>=1.12)
		{
			TIM1_OFF();
			break;
		}
	}
	stop(1.5);//��������ȥ
	go_open(-100,500,0.4);//�ܵ�������
	
	flag.Road_flag=_up_bevel_edge;
}

void up_bevel_edge(void)//��б̨
{
	forward_mid(450,Straight_Quick,2);
}

void down_bevel_edge(void)//��б̨
{
	flag.Road_flag=_crash1;
}

void platform5(void)
{
	
}

void bumps(void)
{
	Read_Digital_Data();

}

void crash(int initial_speed)//ײ̨��ת180��
{
	/* ���ɹ����еĺ���ʹ��,�����ǵ������ڵ� */
	Read_Digital_Data();
	while(1)
	{
		go_forward(initial_speed,Straight_Quick);
		if(G1==0)
		{
			stop(1);
			break;
		}	
	}
	turn_until_line(500,-500,0.4);//����ͷ
//	flag.Road_flag=_crash2;
}



void return1(void)
{
	int upflag=0;

	stop(50);
	flag.Road_flag=20;
}
#endif
