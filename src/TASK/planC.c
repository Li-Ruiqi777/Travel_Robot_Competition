#include "task.h"
/* �޸�·��ͨ���ĸ��������ڵ�Road_flag���� */
#ifdef __Routine3
/*��·����ƽ̨3��4��5*/
int k=0;

void origin(void)
{
	Read_Digital_Data();
	/* �ȴ��ƿ����� */
	motor(0,0);
	while(!G_R)
	{
		Read_Digital_Data();
		motor(0,0);
	}
	
	down_platform();//�����ܵ�������
	TIM1_ON();

	while(1)	//��ʼѰ��
	{
		go_forward(Road_Speed_H,Straight_Quick);
		if( (sum1==8) && (_second>=0.8) && (G_L==0))//�������´�
		{
			TIM1_OFF();
			break;
		}
	}

}

/*************************************
*�������ƣ�go_bridge_new
*�������ܣ�����+����+����(�������)
*��һ״̬��
**************************************/
void go_bridge_new(void)
{
	Read_Digital_Data();
	TIM1_ON();
	/*  ������ */
	while(_second <1.2)
	{
		go_adjust(450,AD_UpBridge);
	}
	
	/*  ���� */
	TIM1_ON();
	_second = 0;
	while(1)
	{
		go_adjust(650,AD_OnBridge);
		if(_second >= 0.8 )
		{
			TIM1_OFF();
			break;
		}
	}
	
	/*  ���� */
	TIM1_ON();
	while(1)
	{
		go_adjust(500,AD_DownBridge);
		if(G_L == 0)//���˵���
		{
			TIM1_OFF();
			break;
		}
	}
	go_closed(Road_Speed_L,Straight_Quick,0.5);
	platform_new();
}

/*************************************
*�������ƣ�right_turn1
*�������ܣ���ƽ̨2,�ߵ��ֲ�㴦����ת
*��һ״̬��_mountains_new	
**************************************/
void right_turn1(void)
{
	Read_Digital_Data();
	down_platform();//�����ܵ�������
	
	forward_mid(700,Straight_Quick,1);
	stop(0.1);
	right2line(Rotate_Speed,0.2);
	
}

/*************************************
*�������ƣ�mountains
*�������ܣ���������ɽ(�ɸ���)
*��һ״̬��
**************************************/
void mountains(void)//����ɽ
{
	go_closed(Road_Speed_H,Straight_Quick,0.3);
	
	while(1)	//�·���
	{
		go_forward(600,Straight_Quick);//����
		if(G_L==0)//�������´� G_L
		{
			stop(0.1);
			break;
		}
	}
	
	/* ���� */
	TIM1_ON();
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//����
		if(_second >= 1.7)//�������1.6
		{
			TIM1_OFF();
			break;
		}
	}

}

/*************************************
*�������ƣ�mountains_new
*�������ܣ���������ɽ(�ɸ���)
*��һ״̬��
**************************************/
void mountains_new(void)//����ɽ
{
	float roll_origin;
	_MPU_READ;
	go_closed(Road_Speed_H,Straight_Quick,0.1);
	go_closed(600,Straight_Quick,0.15);

	_MPU_READ;
	_MPU_READ;
	roll_origin = abs(roll);
	while(1)
	{
		go_forward(550,Straight_Quick);//����
		_MPU_READ;
		if( abs(abs(roll) - roll_origin) >=10 || G_L ==0 )//��������ɽ
			break;
	}
	
	/* ���� */
	TIM1_ON();
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//����
		//if(_second >= 1.1 && G_L==0)//�������1.6  1.8
		if(_second >= 1.6)
		{
			TIM1_OFF();
			break;
		}
	}

	go_closed(Mountain_Speed,Straight_Quick,0.5);
}

/*************************************
*�������ƣ�mountains1
*�������ܣ���������ɽ(���ڰ��߱Ƚ϶̵�ʱ��)
*��һ״̬��
**************************************/
void mountains1(void)//����ɽ
{
	float roll_origin;
	_MPU_READ;
	go_closed(Road_Speed_H,Straight_Quick,0.2);
	
	_MPU_READ;
	_MPU_READ;
	roll_origin = abs(roll);
	while(1)
	{
		go_forward(550,Straight_Quick);//����
		_MPU_READ;
		if( abs(abs(roll) - roll_origin) >=10 || G_L ==0 )//��������ɽ
			break;
	}
	
	/* ���� */
	TIM1_ON();
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//����
		if(_second >= 1.7)//�������1.1
		{
			TIM1_OFF();
			break;
		}
	}
	
//	forward_mid(550,Straight_Quick,1);

}
/*************************************
*�������ƣ�bumps_2
*�������ܣ����ܱ��ж��Ƿ񾭹����ٴ�,������˼��ٴ���ʼ����,ͨ��ʱ�˳��ú���
*��һ״̬��	
**************************************/
void bumps_2(void)
{
	/* �ӿ�ʼ�����ٴ�ǰ */
	while(1)
	{
		go_forward(600,Straight_Quick);//����
		if(G_L==0)//�������´�
			break;
	}
//	stop(1);
	
	TIM8_OFF();//�Ȱ�ʱ�����
	TIM1_ON();
	/* �����ٴ� */   //(��ʱ,�������һ��ʱ��G_L����1,���������)
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//����
		if(_second > 1.4)//���û����ס
			TIM8_ON();
		
		if(G_L == 0)//����ֱ���ס,������0
			_second8 = 0;
		
		if(_second8 >= 0.2)//�������//0.4
		{
			TIM8_OFF();
			TIM1_OFF();
			break;
		}
	}

//	stop(0.15);
}

/*************************************
*�������ƣ�bumps_3
*�������ܣ����ܱ��ж��Ƿ񾭹����ٴ�,������˼��ٴ���ʼ����,ͨ��ʱ�˳��ú���
*��һ״̬��	
**************************************/
void bumps_3(void)
{
	/* �ӿ�ʼ�����ٴ�ǰ */
	while(1)
	{
		go_forward(600,Straight_Quick);//����
		if(G_L==0)//�������´�
			break;
	}
//	stop(1);
	
	TIM8_OFF();//�Ȱ�ʱ�����
	TIM1_ON();
	/* �����ٴ� */   //(��ʱ,�������һ��ʱ��G_L����1,���������)
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//����
		if(_second > 1.4)//���û����ס
		{
//			stop(2);
			TIM8_ON();
		}
		
		if(G_L == 0)//����ֱ���ס,������0
			_second8 = 0;
		
		if(_second8 >= 0.4 || _second >1.9)//�������//0.4
		{
			TIM8_OFF();
			TIM1_OFF();
			break;
		}
	}

//	stop(0.15);
}

/*************************************
*�������ƣ�node3_p4
*�������ܣ�����ƽ̨4,����1���ֲ��ߵ�node3,Ȼ����ת����4�ķ���
*��һ״̬��_node4_d4	
**************************************/
void node3_p4(void)
{
	down_platform();
	forward_mid_light_L(850,Straight_Quick,1,3);//���ߵ�node4
	stop(0.1);
	
	left2line(Rotate_Speed,0.2);
	
	if(Door.D4 == _open)
		left2line(Rotate_Speed,0.2);//ת��door4
	
}

/*************************************
*�������ƣ�node4_d4
*�������ܣ��趨һ��ʱ������4��ȥ,�ڴ�ʱ���ڼ�����Ƿ�����
					 ��4����������1���ֲ��ߵ�node4,����ת��ƽ̨5����,Ȼ����ƽ̨5����ת
					 ��4�رգ���ͷ,ת��node3����
*��һ״̬��_p7_p5 		    (��4��)
					 _rt_node4_d4 	(��4��)
**************************************/
void node4_d4(void)
{
	Door_Judege(4);
	/* �ſ� */
	if(Door.D4==_open)
	{
		forward_mid_light(Road_Speed_H,Straight_Quick,3,4);//�ߵ�node5
		stop(0.1);
		left2line(Rotate_Speed,0.2);//ת��ƽ̨7����
		bumps_3();//���ٴ�
		platform7();
	}
	
	/* �Ź�*/
	else if(Door.D4==_closed)
	{
		left2line(Rotate_Speed,0.4);//ת����3����
	}
}


/*************************************
*�������ƣ�p7_p5
*�������ܣ�����ƽ̨5,��������ɽ��node4���ٵ�node5����̨7��ת
*��һ״̬��_node5_p7
**************************************/
void p7_p5(void)
{
	down_platform();
	mountains_new();
	
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//�ߵ�node4
	stop(0.1);
	left2line(Rotate_Speed,0.4);//ת��node5����
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//�ߵ�node5
	stop(0.1);
	left2line(Rotate_Speed,0.2);//ת��platform7����
	
	bumps_3();//���ٴ�
//	stop(0.2);
	platform7();

}


/*------------------------------------------��������4�رյ�·��------------------------------------------*/
/*************************************
*�������ƣ�rt_node3_d4
*�������ܣ�����4����ֱ�߾���һ���ֲ��߷��ص�node3,��ת����3����
*��һ״̬��_node4_n3	
**************************************/
void rt_node3_d4(void)
{
	forward_mid_light(Road_Speed_H,Straight_Quick,1,1);//�ߵ�node3
//	dash();
	left2line(Rotate_Speed,0.2);
	left2line(Rotate_Speed,0.15);//ת��door3����	
}

/*************************************
*�������ƣ�node4_d3
*�������ܣ��趨һ��ʱ������3��ȥ,�ڴ�ʱ���ڼ�����Ƿ�����
					 ��3�������ȵ�node4Ȼ��ƽ̨5����ת
					 ��3�رգ���ͷ,��node3����d1��node2
*��һ״̬��	_p7_p5 		(��3��)
						_node2_node3		(��3��)
**************************************/
void node4_d3(void)
{
	Door_Judege(3);
	/* ��3�� */
	if(Door.D3==_open)
	{
		//forward_mid(Road_Speed_H,Straight_Quick,1);
		forward_mid_light(660,Straight_Quick,1,4);//�������м�
		stop(0.1);
		left2line(Rotate_Speed,0.4);//ת��node4����	
		dash();
		
		forward_mid(Road_Speed_H,Straight_Quick,1);
		dash();//��node4
		
		right2line(Rotate_Speed,0.2);//ת��node5����
		forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//�ߵ�node5
		stop(0.1);
		left2line(Rotate_Speed,0.2);//ת��ƽ̨7��
		
		bumps_3();//���ٴ�
		platform7();

	}
	
	/* ��3�� */
	else if(Door.D3==_closed)
	{
		left2line(Rotate_Speed,0.4);//ת��node3����
		forward_mid(Road_Speed_H,Straight_Quick,1);
		dash();//��node3
		
		left2line(Rotate_Speed,0.4);//ת��node1����

	}

}

/*------------------------------------------��������3�رյ�·��------------------------------------------*/
/*************************************
*�������ƣ�node2_node3
*�������ܣ���node3��node1�ٵ�node2
*��һ״̬��p7_node2
**************************************/
void node2_node3(void)
{
	bevel_4_1();
	forward_mid_light_L(Road_Speed_H,Straight_Quick,1,3);//��node1
	dash();
	left2line(Rotate_Speed,0.2);//ת��node2����
	go_door();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//��node2
	
//	stop(0.5);
}

/*************************************
*�������ƣ�p7_node2
*�������ܣ���node2��ƽ̨7����ת
*��һ״̬��_node5_p7	
**************************************/
void p7_node2(void)
{
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);
	stop(0.1);
	left2line(Rotate_Speed,0.4);
	
	forward_mid_light(Road_Speed_H,Straight_Quick,3,4);//node6�м�
	stop(0.1);
	right2line(Rotate_Speed,0.4);//ת��node5����
	
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//�ߵ�node5
	stop(0.1);
	left2line(Rotate_Speed,0.4);//ת��platform7����
	
	bumps_3();
	platform7();
}

/*************************************
*�������ƣ�_node5_p7
*�������ܣ���platform7��node5
*��һ״̬��	
**************************************/
void node5_p7(void)
{
	/* ���� */
	down_platform();
	bumps_3();
	
	go_closed(600,Straight_Quick,0.2);

	go_closed(Road_Speed_H,Straight_Quick,0.9);
}

/*************************************
*�������ƣ�_node4_p8
*�������ܣ���node5��platform8����ת
*��һ״̬��	�ؼ�
**************************************/
void node4_p8(void)
{
	mountains_new();

	platform8();//��̨8����ת
}

/*------------------------------------------�����Ǿ�����·��------------------------------------------*/

void seesaw(void)
{
	/* Ѱ�������ΰ� */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	go_open(500,500,0.95);
//	go_open(150,150,0.5);
	stop(1);//��������ȥ
	go_closed(500,Straight_Quick,0.4);
}


void bevel_1_3(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	TIM1_ON();
	/* ��б̨����һ�� */
	while(1)
	{
		go_adjust(550,AD_Seesaw);
		if(_second > 1)
		{
			TIM1_OFF();
			break;
		}
	}
	stop(0.1);
	go_open(-400,400,0.35);//ת��3����
	
	/* �����ߵ������� */
	while(1)
	{
		Read_Digital_Data();
		motor(500,500);
		if(sum1<8)
			break;
	}
	go_closed(500,Straight_Quick,0.4);
}

void bevel_1_4(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	TIM1_ON();
	_second = 0;
	/* ��б̨�ߵ����� */
	while(1)
	{
		if(_second < 1.3)
		{
			go_adjust(550,AD_Seesaw);
		}
		else if(_second >= 1.3)
		{
			motor(550,550);
		}
		
		if(sum1 < 8 && _second > 1.5)
		{
			TIM1_OFF();
			break;
		}
	}
	
	go_closed(500,Straight_Quick,0.4);
}

void bevel_2_3(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	/* ��б̨������ */
	while(1)
	{
		Read_Digital_Data();
		motor(450,450);
		if(S2 == 0)
		{
			stop(0.1);
			break;
		}
	}
	
	go_open(-400,400,0.15);//ת��
	
	go_open(400,400,0.25);//��ǰ��һ��
	
	go_open(-400,400,0.3);//ת��3����
	
	go_closed(500,Straight_Quick,0.4);
}
void bevel_2_4(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	/* �Ӹ���б̨��ת�� */
	TIM1_ON();
	while(1)
	{
		Read_Digital_Data();
		motor(450,450);
		if(S2 == 0 && _second > 0.5)
		{
			stop(0.1);
			break;
		}
	}
	go_open(-400,400,0.12);//ת��0.2
	
	/* ��б̨�ߵ����� */
	while(1)
	{
		
		Read_Digital_Data();
		motor(550,550);
		if(sum1 < 8)
			break;
	}
	go_closed(500,Straight_Quick,0.4);
}

void bevel_3_1(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	/* �Ӹ���б̨��ת�� */
	while(1)
	{
		Read_Digital_Data();
		motor(450,450);
		if(S1 == 0)
		{
			stop(0.1);
			break;
		}
	}
	go_open(400,-400,0.23);//ת��
	
	/* ��б̨�ߵ����� */
	while(1)
	{
		
		Read_Digital_Data();
		motor(550,550);
		if(sum1 < 8)
			break;
	}
	go_closed(500,Straight_Quick,0.4);
}

void bevel_3_2(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	/* ��б̨������ */
	while(1)
	{
		Read_Digital_Data();
		motor(450,450);
		if(S1 == 0)
		{
			stop(0.1);
			break;
		}
	}
	go_open(400,-400,0.15);//ת��
	
	go_open(400,400,0.25);//��ǰ��һ��
	stop(0.1);
	go_open(400,-400,0.3);//ת��3����
	
	go_closed(500,Straight_Quick,0.4);
}

void bevel_4_1(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	TIM1_ON();
	_second = 0;
	/* ��б̨�ߵ����� */
	while(1)
	{
		if(_second < 1.3)
		{
			go_adjust(550,AD_Seesaw);
		}
		else if(_second >= 1.3)
		{
			motor(550,550);
		}
		
		if(sum1 < 8 && _second > 1.5)
		{
			TIM1_OFF();
			break;
		}
	}
	
	go_closed(500,Straight_Quick,0.4);
}

void bevel_4_2(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	TIM1_ON();
	/* ��б̨����һ�� */
	while(1)
	{
		go_adjust(550,AD_Seesaw);
		if(_second > 1)
		{
			TIM1_OFF();
			break;
		}
	}
	stop(0.1);
	go_open(400,-400,0.3);//ת��3����
	
	/* �����ߵ������� */
	while(1)
	{
		Read_Digital_Data();
		motor(500,500);
		if(sum1<8)
			break;
	}
	go_closed(500,Straight_Quick,0.4);
}

void bevel_1_mid(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	TIM1_ON();
	/* ��б̨����һ�� */
	while(1)
	{
		motor(550,550);
		if(_second >= 0.8)
		{
			TIM1_OFF();
			break;
		}
	}
	stop(0.1);
	
	left2line(400,0.5);//ת�����߷���
	/* �����ߵ������� */
	while(1)
	{
		Read_Digital_Data();
		motor(500,500);
		if(sum1<8)
			break;
	}
	go_closed(500,Straight_Quick,0.4);
}

void bevel_4_mid(void)
	{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	TIM1_ON();
	/* ��б̨����һ�� */
	while(1)
	{
		motor(550,550);
		if(_second >= 0.8)
		{
			TIM1_OFF();
			break;
		}
	}
	stop(0.1);
	right2line(400,0.5);
	/* �����ߵ������� */
	while(1)
	{
		Read_Digital_Data();
		motor(500,500);
		if(sum1<8)
			break;
	}
	go_closed(500,Straight_Quick,0.4);
}
	
void bevel_mid_1(void)
{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	/* ��б̨����ֱ��ɫ��ɨ������ */
	while(1)
	{
		Read_Digital_Data();
		motor(500,500);
		if(S1==0 || S2==0)
		{
			go_open(400,400,0.1);
			stop(0.1);
			break;
		}
	}
	
	go_open(400,-400,0.4);//��ת��1
	
	/* ��б̨�ߵ����� */
	while(1)
	{
		go_adjust(550,AD_Seesaw);
		if(sum1 < 8)
			break;
	}
	go_closed(500,Straight_Quick,0.25);
}

void bevel_mid_4(void)
	{
	/* Ѱ����б̨ */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//��б̨
			break;
	}
	
	/* ��б̨����ֱ��ɫ��ɨ������ */
	while(1)
	{
		Read_Digital_Data();
		motor(500,500);
		if(S1==0 || S2==0)
		{
			go_open(400,400,0.1);
			stop(0.1);
			break;
		}
	}
	
	go_open(-400,400,0.5);//��ת��4
	
	/* ��б̨�ߵ����� */
	while(1)
	{
		go_adjust(550,AD_Seesaw);
		if(sum1 < 8)
			break;
	}
	go_closed(500,Straight_Quick,0.25);
}
#endif
