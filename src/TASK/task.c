#include "task.h"

#ifdef __Routine3
void jingdian1_2(void)
{
	origin();
	go_bridge_new();
	blink();
}

void jingdian2_4(void)
{
	right_turn1();
	mountains1();
	stop(0.2);
	bevel_2_4();
	
	platform_new();//ƽ̨4
}

void jingdian4_7(void)
{
	node3_p4();
	node4_d4();//��4�������ȵ�node4Ȼ��ƽ̨7����ת
	
	/* ��4�� */
	if(Door.D4==_closed)
	{
		rt_node3_d4();//��node3
		node4_d3();//��3�������ȵ�node4Ȼ��ƽ̨7����ת
		
		/* ��3�� */
		if(Door.D3==_closed)
		{
			node2_node3();
			p7_node2();//��node2��ƽ̨7
		}
		
	} 

}

void jingdian7_8(void)
{
	node5_p7();
	node4_p8();
}

/*************************************
*�������ƣ�return1_D4
*�������ܣ���һ�λؼ�--��D4
**************************************/
void return1_D4(void)
{
	down_platform8();
	mountains_new();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//������ɽ,��node5
	stop(0.2);
	left2line(Rotate_Speed,0.2);//ת��node4����
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,3);//��node4
//	stop(2);
	go_door();//�߹���4
	
	forward_mid_light(700,Straight_Quick,1,3);//��node3
//	dash();//��ʱ��ǰ�ߵ�
	left2line(Rotate_Speed,0.2);
//	dash_big();
	
	forward_mid(Road_Speed_H,Straight_Quick,1);//���ֲ��
	dash();//��ʱ��ǰ�ߵ�
	
	right2line(Rotate_Speed,0.15);
	right2line(Rotate_Speed,0.2);//ת���ؼҷ����б��
	
	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//���ſڵķֲ��
	dash();//��ʱ��ǰ�ߵ�
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*************************************
*�������ƣ�return2_D4
*�������ܣ���2�λؼ�--��D4
**************************************/
void return2_D4(void)
{
	down_platform8();
	mountains_new();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//������ɽ,��node5
	stop(0.2);
	left2line(Rotate_Speed,0.2);//ת��node4����
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//��node4
	go_door();//�߹���4
	
	forward_mid_light(700,Straight_Quick,1,3);//��node3
	dash();
	left2line(Rotate_Speed,0.2);
	bevel_4_1();
	
	platform3();//ƽ̨3
	down_platform();
	
	go_closed(Road_Speed_H,Straight_Quick,1.5);
	bevel_1_3();

	
	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//���ſڵķֲ��
	dash();//��ʱ��ǰ�ߵ�
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*************************************
*�������ƣ�return1_D3
*�������ܣ���һ�λؼ�--��D3
**************************************/
void return1_D3(void)
{
	down_platform8();
	mountains_new();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//������ɽ,��node5
	stop(0.1);
	left2line(Rotate_Speed,0.2);//ת��node4����
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//��node4
	stop(0.15);
	left2line(Rotate_Speed,0.2);

	forward_mid(Road_Speed_H,Straight_Quick,1);//���ֲ��
	stop(0.1);
	right2line(Rotate_Speed,0.2);//ת����3����
  go_door();
	
	forward_mid(700,Straight_Quick,1);//��node3
	dash();
	left2line(Rotate_Speed,0.2);
	bevel_4_1();
	
	platform3();//ƽ̨3
	down_platform();
	
	go_closed(Road_Speed_H,Straight_Quick,1.5);
	bevel_1_3();

	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//���ſڵķֲ��
	dash();//��ʱ��ǰ�ߵ�
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*************************************
*�������ƣ�return1_D1
*�������ܣ���һ�λؼ�--��D1
**************************************/
void return1_D1(void)
{
	down_platform8();
	mountains_new();

	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//������ɽ,��node5
	stop(0.2);
	left2line(Rotate_Speed,0.3);//ת��node6����
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//��node4
	stop(0.2);
	left2line(Rotate_Speed,0.18);

	forward_mid(Road_Speed_H,Straight_Quick,1);//�����м�
	go_door();
	
	forward_mid(700,Straight_Quick,1);//��node1
	dash();
	right2line(Rotate_Speed,0.2);
	
	bevel_1_3();

	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//���ſڵķֲ��
	dash();//��ʱ��ǰ�ߵ�
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*------------------------------------------�ڶ�Ȧ------------------------------------------*/
void jingdian2_3(void)
{
	right_turn1();
	mountains1();
	forward_mid(550,Straight_Quick,1);//�ߵ��ֲ��
	go_open(600,600,0.2);
	stop(0.15);
	
	right2line(Rotate_Speed,0.3);;

	platform3();//ƽ̨3
}

void jingdian3_5(void)
{
	down_platform();
	go_closed(Road_Speed_H,Straight_Quick,1.2);
	forward_mid_light_R(750,Straight_Quick,1,3);//�ߵ�node1
	right2line(Rotate_Speed,0.2);//ת����2
	go_door();
	forward_mid_light(700,Straight_Quick,1,3);//�������м�
	go_closed(Road_Speed_H,Straight_Quick,0.5);
	
	forward_mid(Road_Speed_H,Straight_Quick,1);//node4
	dash();
	stop(0.1);
	left2line(Rotate_Speed,0.2);	
	
	mountains_new();
	platform_new();
}

//�Ӿ���4��5,ֻ���ڵڶ�Ȧ���ֶ�����,
//�ʲ������ж���
void jingdian4_5(void)
{
	node3_p4();
	if(Door.D4 == _open)
	{
		forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//�ߵ�node4
		left2line(Rotate_Speed,0.4);//ת��ƽ̨5����
	}
	else
	{
		go_door();
		forward_mid_light(660,Straight_Quick,1,4);//�������м�
		left2line(Rotate_Speed,0.4);//ת��node4����	
		forward_mid(Road_Speed_H,Straight_Quick,1);
		dash();//��node4
		left2line(Rotate_Speed,0.15);//ת��platform5����
	}
	
	mountains_new();
	platform_new();
}

void jingdian5_7(void)
{
	p7_p5();
}

void platform3(void)
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
	
	go_open(Origin_Speed,Origin_Speed,0.15);
	stop(Base_delay);

	_MPU_READ;
	_MPU_READ;
	turn_right(550,165);//��ƽ̨����תһȦ170
}

/*------------------------------------------����------------------------------------------*/
void jingdian4_7_D3(void)
{
	node3_p4();

	go_door();
	forward_mid_light(660,Straight_Quick,1,4);//�������м�
	stop(0.1);
	left2line(Rotate_Speed,0.2);//ת��node4����	
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
void jingdian4_3(void)
{
	down_platform();
	forward_mid_light_L(850,Straight_Quick,1,3);//���ߵ�node4
	bevel_4_1();
	platform3();
}

void jingdian3_7(void)
{
	down_platform();
	go_closed(Road_Speed_H,Straight_Quick,1.2);
	forward_mid_light_R(750,Straight_Quick,1,3);//�ߵ�node1
	right2line(Rotate_Speed,0.2);//ת����2
	go_door();
	forward_mid_light(700,Straight_Quick,1,3);//�������м�
	go_closed(Road_Speed_H,Straight_Quick,0.5);
	
	forward_mid(Road_Speed_H,Straight_Quick,1);//node4
	dash();
	stop(0.1);
	right2line(Rotate_Speed,0.2);//ת��node5����
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//�ߵ�node5
	stop(0.1);
	left2line(Rotate_Speed,0.2);//ת��ƽ̨7��
	
	bumps_3();//���ٴ�
	platform7();
}

#endif

