#include "task.h"
/* 修改路线通过改各个函数内的Road_flag即可 */
#ifdef __Routine3
/*该路线走平台3、4、5*/
int k=0;

void origin(void)
{
	Read_Digital_Data();
	/* 等待移开挡板 */
	motor(0,0);
	while(!G_R)
	{
		Read_Digital_Data();
		motor(0,0);
	}
	
	down_platform();//开环跑到白线上
	TIM1_ON();

	while(1)	//开始寻迹
	{
		go_forward(Road_Speed_H,Straight_Quick);
		if( (sum1==8) && (_second>=0.8) && (G_L==0))//到了上坡处
		{
			TIM1_OFF();
			break;
		}
	}

}

/*************************************
*函数名称：go_bridge_new
*函数功能：上桥+过桥+下桥(纯靠光电)
*下一状态：
**************************************/
void go_bridge_new(void)
{
	Read_Digital_Data();
	TIM1_ON();
	/*  在上桥 */
	while(_second <1.2)
	{
		go_adjust(450,AD_UpBridge);
	}
	
	/*  桥上 */
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
	
	/*  下桥 */
	TIM1_ON();
	while(1)
	{
		go_adjust(500,AD_DownBridge);
		if(G_L == 0)//到了地上
		{
			TIM1_OFF();
			break;
		}
	}
	go_closed(Road_Speed_L,Straight_Quick,0.5);
	platform_new();
}

/*************************************
*函数名称：right_turn1
*函数功能：下平台2,走到分叉点处并右转
*下一状态：_mountains_new	
**************************************/
void right_turn1(void)
{
	Read_Digital_Data();
	down_platform();//开环跑到白线上
	
	forward_mid(700,Straight_Quick,1);
	stop(0.1);
	right2line(Rotate_Speed,0.2);
	
}

/*************************************
*函数名称：mountains
*函数功能：经过梯形山(可复用)
*下一状态：
**************************************/
void mountains(void)//梯形山
{
	go_closed(Road_Speed_H,Straight_Quick,0.3);
	
	while(1)	//新方法
	{
		go_forward(600,Straight_Quick);//快速
		if(G_L==0)//到了上坡处 G_L
		{
			stop(0.1);
			break;
		}
	}
	
	/* 上坡 */
	TIM1_ON();
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//慢速
		if(_second >= 1.7)//上坡完成1.6
		{
			TIM1_OFF();
			break;
		}
	}

}

/*************************************
*函数名称：mountains_new
*函数功能：经过梯形山(可复用)
*下一状态：
**************************************/
void mountains_new(void)//梯形山
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
		go_forward(550,Straight_Quick);//快速
		_MPU_READ;
		if( abs(abs(roll) - roll_origin) >=10 || G_L ==0 )//到了梯形山
			break;
	}
	
	/* 上坡 */
	TIM1_ON();
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//慢速
		//if(_second >= 1.1 && G_L==0)//上坡完成1.6  1.8
		if(_second >= 1.6)
		{
			TIM1_OFF();
			break;
		}
	}

	go_closed(Mountain_Speed,Straight_Quick,0.5);
}

/*************************************
*函数名称：mountains1
*函数功能：经过梯形山(用于白线比较短的时候)
*下一状态：
**************************************/
void mountains1(void)//梯形山
{
	float roll_origin;
	_MPU_READ;
	go_closed(Road_Speed_H,Straight_Quick,0.2);
	
	_MPU_READ;
	_MPU_READ;
	roll_origin = abs(roll);
	while(1)
	{
		go_forward(550,Straight_Quick);//快速
		_MPU_READ;
		if( abs(abs(roll) - roll_origin) >=10 || G_L ==0 )//到了梯形山
			break;
	}
	
	/* 上坡 */
	TIM1_ON();
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//慢速
		if(_second >= 1.7)//上坡完成1.1
		{
			TIM1_OFF();
			break;
		}
	}
	
//	forward_mid(550,Straight_Quick,1);

}
/*************************************
*函数名称：bumps_2
*函数功能：边跑边判断是否经过减速带,如果到了减速带开始减速,通过时退出该函数
*下一状态：	
**************************************/
void bumps_2(void)
{
	/* 从开始到减速带前 */
	while(1)
	{
		go_forward(600,Straight_Quick);//快速
		if(G_L==0)//到了上坡处
			break;
	}
//	stop(1);
	
	TIM8_OFF();//先把时间清空
	TIM1_ON();
	/* 过减速带 */   //(定时,如果超过一定时间G_L都是1,则下坡完成)
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//慢速
		if(_second > 1.4)//光电没被挡住
			TIM8_ON();
		
		if(G_L == 0)//如果又被挡住,计数清0
			_second8 = 0;
		
		if(_second8 >= 0.2)//下坡完成//0.4
		{
			TIM8_OFF();
			TIM1_OFF();
			break;
		}
	}

//	stop(0.15);
}

/*************************************
*函数名称：bumps_3
*函数功能：边跑边判断是否经过减速带,如果到了减速带开始减速,通过时退出该函数
*下一状态：	
**************************************/
void bumps_3(void)
{
	/* 从开始到减速带前 */
	while(1)
	{
		go_forward(600,Straight_Quick);//快速
		if(G_L==0)//到了上坡处
			break;
	}
//	stop(1);
	
	TIM8_OFF();//先把时间清空
	TIM1_ON();
	/* 过减速带 */   //(定时,如果超过一定时间G_L都是1,则下坡完成)
	while(1)
	{
		go_forward(Mountain_Speed,Straight_Quick);//慢速
		if(_second > 1.4)//光电没被挡住
		{
//			stop(2);
			TIM8_ON();
		}
		
		if(G_L == 0)//如果又被挡住,计数清0
			_second8 = 0;
		
		if(_second8 >= 0.4 || _second >1.9)//下坡完成//0.4
		{
			TIM8_OFF();
			TIM1_OFF();
			break;
		}
	}

//	stop(0.15);
}

/*************************************
*函数名称：node3_p4
*函数功能：先下平台4,经过1条分叉线到node3,然后左转到门4的方向
*下一状态：_node4_d4	
**************************************/
void node3_p4(void)
{
	down_platform();
	forward_mid_light_L(850,Straight_Quick,1,3);//先走到node4
	stop(0.1);
	
	left2line(Rotate_Speed,0.2);
	
	if(Door.D4 == _open)
		left2line(Rotate_Speed,0.2);//转到door4
	
}

/*************************************
*函数名称：node4_d4
*函数功能：设定一个时间向门4跑去,在此时间内检测门是否开启。
					 门4开启：经过1个分叉走到node4,并左转到平台5方向,然后上平台5并自转
					 门4关闭：调头,转到node3方向
*下一状态：_p7_p5 		    (门4开)
					 _rt_node4_d4 	(门4关)
**************************************/
void node4_d4(void)
{
	Door_Judege(4);
	/* 门开 */
	if(Door.D4==_open)
	{
		forward_mid_light(Road_Speed_H,Straight_Quick,3,4);//走到node5
		stop(0.1);
		left2line(Rotate_Speed,0.2);//转到平台7方向
		bumps_3();//减速带
		platform7();
	}
	
	/* 门关*/
	else if(Door.D4==_closed)
	{
		left2line(Rotate_Speed,0.4);//转到门3方向
	}
}


/*************************************
*函数名称：p7_p5
*函数功能：先下平台5,经过梯形山到node4并再到node5再上台7自转
*下一状态：_node5_p7
**************************************/
void p7_p5(void)
{
	down_platform();
	mountains_new();
	
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//走到node4
	stop(0.1);
	left2line(Rotate_Speed,0.4);//转到node5方向
	
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);//走到node5
	stop(0.1);
	left2line(Rotate_Speed,0.2);//转到platform7方向
	
	bumps_3();//减速带
//	stop(0.2);
	platform7();

}


/*------------------------------------------以下是门4关闭的路线------------------------------------------*/
/*************************************
*函数名称：rt_node3_d4
*函数功能：从门4方向直走经过一条分叉线返回到node3,并转到门3方向
*下一状态：_node4_n3	
**************************************/
void rt_node3_d4(void)
{
	forward_mid_light(Road_Speed_H,Straight_Quick,1,1);//走到node3
//	dash();
	left2line(Rotate_Speed,0.2);
	left2line(Rotate_Speed,0.15);//转到door3方向	
}

/*************************************
*函数名称：node4_d3
*函数功能：设定一个时间向门3跑去,在此时间内检测门是否开启。
					 门3开启：先到node4然后到平台5并自转
					 门3关闭：调头,回node3并从d1到node2
*下一状态：	_p7_p5 		(门3开)
						_node2_node3		(门3关)
**************************************/
void node4_d3(void)
{
	Door_Judege(3);
	/* 门3开 */
	if(Door.D3==_open)
	{
		//forward_mid(Road_Speed_H,Straight_Quick,1);
		forward_mid_light(660,Straight_Quick,1,4);//到矩形中间
		stop(0.1);
		left2line(Rotate_Speed,0.4);//转到node4方向	
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
	
	/* 门3关 */
	else if(Door.D3==_closed)
	{
		left2line(Rotate_Speed,0.4);//转到node3方向
		forward_mid(Road_Speed_H,Straight_Quick,1);
		dash();//回node3
		
		left2line(Rotate_Speed,0.4);//转到node1方向

	}

}

/*------------------------------------------以下是门3关闭的路线------------------------------------------*/
/*************************************
*函数名称：node2_node3
*函数功能：从node3到node1再到node2
*下一状态：p7_node2
**************************************/
void node2_node3(void)
{
	bevel_4_1();
	forward_mid_light_L(Road_Speed_H,Straight_Quick,1,3);//到node1
	dash();
	left2line(Rotate_Speed,0.2);//转到node2方向
	go_door();
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//到node2
	
//	stop(0.5);
}

/*************************************
*函数名称：p7_node2
*函数功能：从node2到平台7并自转
*下一状态：_node5_p7	
**************************************/
void p7_node2(void)
{
	forward_mid_light(Road_Speed_H,Straight_Quick,2,4);
	stop(0.1);
	left2line(Rotate_Speed,0.4);
	
	forward_mid_light(Road_Speed_H,Straight_Quick,3,4);//node6中间
	stop(0.1);
	right2line(Rotate_Speed,0.4);//转到node5方向
	
	forward_mid_light(Road_Speed_H,Straight_Quick,1,3);//走到node5
	stop(0.1);
	left2line(Rotate_Speed,0.4);//转到platform7方向
	
	bumps_3();
	platform7();
}

/*************************************
*函数名称：_node5_p7
*函数功能：从platform7到node5
*下一状态：	
**************************************/
void node5_p7(void)
{
	/* 下坡 */
	down_platform();
	bumps_3();
	
	go_closed(600,Straight_Quick,0.2);

	go_closed(Road_Speed_H,Straight_Quick,0.9);
}

/*************************************
*函数名称：_node4_p8
*函数功能：从node5到platform8并自转
*下一状态：	回家
**************************************/
void node4_p8(void)
{
	mountains_new();

	platform8();//上台8并自转
}

/*------------------------------------------以下是决赛的路线------------------------------------------*/

void seesaw(void)
{
	/* 寻迹到跷跷板 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	go_open(500,500,0.95);
//	go_open(150,150,0.5);
	stop(1);//靠重力下去
	go_closed(500,Straight_Quick,0.4);
}


void bevel_1_3(void)
{
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	TIM1_ON();
	/* 在斜台上走一段 */
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
	go_open(-400,400,0.35);//转到3方向
	
	/* 开环走到白线上 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	TIM1_ON();
	_second = 0;
	/* 从斜台走到白线 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	/* 从斜台到白线 */
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
	
	go_open(-400,400,0.15);//转正
	
	go_open(400,400,0.25);//往前走一点
	
	go_open(-400,400,0.3);//转到3方向
	
	go_closed(500,Straight_Quick,0.4);
}
void bevel_2_4(void)
{
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	/* 从刚上斜台到转正 */
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
	go_open(-400,400,0.12);//转正0.2
	
	/* 从斜台走到白线 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	/* 从刚上斜台到转正 */
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
	go_open(400,-400,0.23);//转正
	
	/* 从斜台走到白线 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	/* 从斜台到白线 */
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
	go_open(400,-400,0.15);//转正
	
	go_open(400,400,0.25);//往前走一点
	stop(0.1);
	go_open(400,-400,0.3);//转到3方向
	
	go_closed(500,Straight_Quick,0.4);
}

void bevel_4_1(void)
{
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	TIM1_ON();
	_second = 0;
	/* 从斜台走到白线 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	TIM1_ON();
	/* 在斜台上走一段 */
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
	go_open(400,-400,0.3);//转到3方向
	
	/* 开环走到白线上 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	TIM1_ON();
	/* 在斜台上走一段 */
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
	
	left2line(400,0.5);//转到中线方向
	/* 开环走到白线上 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	TIM1_ON();
	/* 在斜台上走一段 */
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
	/* 开环走到白线上 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	/* 从斜台往上直到色标扫到红线 */
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
	
	go_open(400,-400,0.4);//右转到1
	
	/* 从斜台走到白线 */
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
	/* 寻迹到斜台 */
	while(1)
	{
		go_forward(700,Straight_Quick);
		if(sum1 == 8)//到斜台
			break;
	}
	
	/* 从斜台往上直到色标扫到红线 */
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
	
	go_open(-400,400,0.5);//左转到4
	
	/* 从斜台走到白线 */
	while(1)
	{
		go_adjust(550,AD_Seesaw);
		if(sum1 < 8)
			break;
	}
	go_closed(500,Straight_Quick,0.25);
}
#endif
