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
	
	platform_new();//平台4
}

void jingdian4_7(void)
{
	node3_p4();
	node4_d4();//门4开启：先到node4然后到平台7并自转
	
	/* 门4关 */
	if(Door.D4==_closed)
	{
		rt_node3_d4();//回node3
		node4_d3();//门3开启：先到node4然后到平台7并自转
		
		/* 门3关 */
		if(Door.D3==_closed)
		{
			node2_node3();
			p7_node2();//从node2到平台7
		}
		
	} 

}

void jingdian7_8(void)
{
	node5_p7();
	node4_p8();
}

/*************************************
*函数名称：return1_D4
*函数功能：第一次回家--走D4
**************************************/
void return1_D4(void)
{
	down_platform8();
	mountains_new();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//过梯形山,到node5
	stop(0.2);
	left2line(Rotate_Speed,0.2);//转到node4方向
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,3);//到node4
//	stop(2);
	go_door();//走过门4
	
	forward_mid_light(700,Straight_Quick,1,3);//到node3
//	dash();//延时往前走点
	left2line(Rotate_Speed,0.2);
//	dash_big();
	
	forward_mid(Road_Speed_H,Straight_Quick,1);//到分叉点
	dash();//延时往前走点
	
	right2line(Rotate_Speed,0.15);
	right2line(Rotate_Speed,0.2);//转到回家方向的斜线
	
	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//到门口的分叉点
	dash();//延时往前走点
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*************************************
*函数名称：return2_D4
*函数功能：第2次回家--走D4
**************************************/
void return2_D4(void)
{
	down_platform8();
	mountains_new();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//过梯形山,到node5
	stop(0.2);
	left2line(Rotate_Speed,0.2);//转到node4方向
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//到node4
	go_door();//走过门4
	
	forward_mid_light(700,Straight_Quick,1,3);//到node3
	dash();
	left2line(Rotate_Speed,0.2);
	bevel_4_1();
	
	platform3();//平台3
	down_platform();
	
	go_closed(Road_Speed_H,Straight_Quick,1.5);
	bevel_1_3();

	
	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//到门口的分叉点
	dash();//延时往前走点
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*************************************
*函数名称：return1_D3
*函数功能：第一次回家--走D3
**************************************/
void return1_D3(void)
{
	down_platform8();
	mountains_new();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//过梯形山,到node5
	stop(0.1);
	left2line(Rotate_Speed,0.2);//转到node4方向
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//到node4
	stop(0.15);
	left2line(Rotate_Speed,0.2);

	forward_mid(Road_Speed_H,Straight_Quick,1);//到分叉点
	stop(0.1);
	right2line(Rotate_Speed,0.2);//转到门3方向
  go_door();
	
	forward_mid(700,Straight_Quick,1);//到node3
	dash();
	left2line(Rotate_Speed,0.2);
	bevel_4_1();
	
	platform3();//平台3
	down_platform();
	
	go_closed(Road_Speed_H,Straight_Quick,1.5);
	bevel_1_3();

	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//到门口的分叉点
	dash();//延时往前走点
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*************************************
*函数名称：return1_D1
*函数功能：第一次回家--走D1
**************************************/
void return1_D1(void)
{
	down_platform8();
	mountains_new();

	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//过梯形山,到node5
	stop(0.2);
	left2line(Rotate_Speed,0.3);//转到node6方向
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//到node4
	stop(0.2);
	left2line(Rotate_Speed,0.18);

	forward_mid(Road_Speed_H,Straight_Quick,1);//矩形中间
	go_door();
	
	forward_mid(700,Straight_Quick,1);//到node1
	dash();
	right2line(Rotate_Speed,0.2);
	
	bevel_1_3();

	bumps_2();
	forward_mid(Road_Speed_H,Straight_Quick,1);//到门口的分叉点
	dash();//延时往前走点
	
	right2line(Rotate_Speed,0.1);
//	stop(5);
	platform_new();
	stop(2);
}

/*------------------------------------------第二圈------------------------------------------*/
void jingdian2_3(void)
{
	right_turn1();
	mountains1();
	forward_mid(550,Straight_Quick,1);//走到分叉点
	go_open(600,600,0.2);
	stop(0.15);
	
	right2line(Rotate_Speed,0.3);;

	platform3();//平台3
}

void jingdian3_5(void)
{
	down_platform();
	go_closed(Road_Speed_H,Straight_Quick,1.2);
	forward_mid_light_R(750,Straight_Quick,1,3);//走到node1
	right2line(Rotate_Speed,0.2);//转到门2
	go_door();
	forward_mid_light(700,Straight_Quick,1,3);//到矩形中间
	go_closed(Road_Speed_H,Straight_Quick,0.5);
	
	forward_mid(Road_Speed_H,Straight_Quick,1);//node4
	dash();
	stop(0.1);
	left2line(Rotate_Speed,0.2);	
	
	mountains_new();
	platform_new();
}

//从景点4到5,只用于第二圈或手动控制,
//故不包括判断门
void jingdian4_5(void)
{
	node3_p4();
	if(Door.D4 == _open)
	{
		forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//走到node4
		left2line(Rotate_Speed,0.4);//转到平台5方向
	}
	else
	{
		go_door();
		forward_mid_light(660,Straight_Quick,1,4);//到矩形中间
		left2line(Rotate_Speed,0.4);//转到node4方向	
		forward_mid(Road_Speed_H,Straight_Quick,1);
		dash();//到node4
		left2line(Rotate_Speed,0.15);//转到platform5方向
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
	
	go_open(Origin_Speed,Origin_Speed,0.15);
	stop(Base_delay);

	_MPU_READ;
	_MPU_READ;
	turn_right(550,165);//在平台上自转一圈170
}

/*------------------------------------------决赛------------------------------------------*/
void jingdian4_7_D3(void)
{
	node3_p4();

	go_door();
	forward_mid_light(660,Straight_Quick,1,4);//到矩形中间
	stop(0.1);
	left2line(Rotate_Speed,0.2);//转到node4方向	
	dash();
	
	forward_mid(Road_Speed_H,Straight_Quick,1);
	dash();//到node4
	
	right2line(Rotate_Speed,0.2);//转到node5方向
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//走到node5
	stop(0.1);
	left2line(Rotate_Speed,0.2);//转到平台7方
	
	bumps_3();//减速带
	platform7();
}
void jingdian4_3(void)
{
	down_platform();
	forward_mid_light_L(850,Straight_Quick,1,3);//先走到node4
	bevel_4_1();
	platform3();
}

void jingdian3_7(void)
{
	down_platform();
	go_closed(Road_Speed_H,Straight_Quick,1.2);
	forward_mid_light_R(750,Straight_Quick,1,3);//走到node1
	right2line(Rotate_Speed,0.2);//转到门2
	go_door();
	forward_mid_light(700,Straight_Quick,1,3);//到矩形中间
	go_closed(Road_Speed_H,Straight_Quick,0.5);
	
	forward_mid(Road_Speed_H,Straight_Quick,1);//node4
	dash();
	stop(0.1);
	right2line(Rotate_Speed,0.2);//转到node5方向
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//走到node5
	stop(0.1);
	left2line(Rotate_Speed,0.2);//转到平台7方
	
	bumps_3();//减速带
	platform7();
}

#endif

