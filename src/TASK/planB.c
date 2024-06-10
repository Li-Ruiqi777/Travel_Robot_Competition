#include "task.h"
/* 修改路线通过改各个函数内的Road_flag即可 */
#ifdef __Routine2
/*该路线走平台3、4、5*/
int k=0;

void origin(void)
{
	Read_Digital_Data();
	//motor(0,0);
	//while(!G1);//等待移开挡板 
	
	go_open(500,500,0.5);//开环跑到白线上
	TIM1_ON();

	while(1)	//开始寻迹
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
//	while(abs(roll)>15)//在上坡
//	{
//		_MPU_READ;
//		go_adjust(550,AD_UpBridge);//冲刺上坡，靠色标调整----------------------------
//	}
////	stop(1);
//	flag.Road_flag=_on_bridge;
}

void on_bridge(void)
{
	Read_Digital_Data();
	_MPU_READ;

	while(1)//在平桥上
	{
		Read_Digital_Data();
		_MPU_READ;
		go_adjust(650,AD_OnBridge);
		if(sum1<=6)//检测到白线
			break;
	}

	flag.Road_flag=_platform2;
}

void down_bridge(void)
{
//	Read_Digital_Data();
//	mpu_dmp_get_data(&pitch,&roll,&yaw);
//	while(abs(roll)>15)//在下坡
//	{
//		_MPU_READ;
//		motor(200,200);//慢速下坡，靠色标调整
//	}
//	
//	//stop(0.2);
//	flag.Road_flag=_platform2;
}

/*************************************
*函数名称：platform2
*函数功能：上平台2并自转一圈
*下一状态：_right_turn1
**************************************/
void platform2(void)
{
	int upflag=0;
	TIM1_ON();
	while(1)
	{
		go_forward(700,Straight_Quick);//在平地寻迹直到走到平台2上
		_MPU_READ;
		if(abs(roll)>15 && _second>0.5)//到上坡了
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//已经走到了平台2上
		{
			go_open(500,500,0.2);
			stop(0.2); 
			TIM1_OFF();
			break;
		}
	}
	blink();
	_MPU_READ;
	turn_right(450,175);//在平台上自转一圈170
	
	flag.Road_flag=_right_turn1;
}

/*************************************
*函数名称：right_turn1
*函数功能：下平台2,走到分叉点处并右转
*下一状态：_mountains	
**************************************/
void right_turn1(void)
{
	Read_Digital_Data();
	go_open(500,500,0.5);//开环跑到白线上
	
	forward_mid(700,Straight_Quick,1);
	turn_until_line(500,-500,0.2);
	
	flag.Road_flag=_mountains;
}

/*************************************
*函数名称：mountains
*函数功能：经过梯形山并停在分叉点处
*下一状态：_platform4	
**************************************/
void mountains(void)//梯形山
{
	forward_mid(500,Straight_Quick,1);
	flag.Road_flag=_platform4;
}

/*************************************
*函数名称：platform4
*函数功能：直走上平台4并自转
*下一状态：_platform3	
**************************************/
void platform4(void)
{
	int upflag=0;
	Read_Digital_Data();

	forward_mid(800,Straight_Quick,1);//先走到node3
	while(1)
	{
		go_forward(750,Straight_Quick);//在平地寻迹直到走到平台上
		_MPU_READ;
		if(abs(roll)>15)//到上坡了
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//已经走到了平台上
		{
			go_open(300,300,0.4);
			stop(0.2); 
			break;
		}
	}
	
	_MPU_READ;
	turn_right(400,175);//在平台上自转一圈170
	
	flag.Road_flag=_platform3;
}

/*************************************
*函数名称：platform3
*函数功能：先下平台4,经过3条分叉线到node1,然后上平台3,然后自转
*下一状态：_node1_p3	
**************************************/
void platform3(void)
{
	int upflag=0;
	Read_Digital_Data();
	forward_mid(800,Straight_Quick,3);//先走到node1
	while(1)
	{
		go_forward(800,Straight_Quick);//在平地寻迹直到走到平台上
		_MPU_READ;
		if(abs(roll)>15)//到上坡了
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//已经走到了平台上
		{
			go_open(300,300,0.2);
			stop(0.2); 
			break;
		}
	}
	
	_MPU_READ;
	turn_right(400,175);//在平台上自转一圈170
	
	flag.Road_flag=_node1_p3;
}

void node1_p0(void)
{
	
}

/*************************************
*函数名称：node1_p3
*函数功能：先下平台3,经过1条分叉线到node1,然后右转到门1的方向
*下一状态：_node2_d1	
**************************************/
void node1_p3(void)
{
	go_open(500,500,1);
	forward_mid_light(500,Straight_Quick,1,3);//先走到node1
	turn_until_line(400,-400,0.4);//转到门1方向
	flag.Road_flag=_node2_d1;
}

/*************************************
*函数名称：node2_d1
*函数功能：设定一个时间向门1跑去,在此时间内检测门是否开启。
					 门1开启：经过1个分叉走到node2,并右转到跷跷板方向
					 门1关闭：调头,转到node1方向
*下一状态：_seesaw1 		(门1开)
					 _rt_node1_d1 (门1关)
**************************************/
void node2_d1(void)
{
	go_closed(550,Straight_Quick,2,DT_1);
//	stop(1);
	//门开
	if(Door.D1==_open){
		forward_mid(800,Straight_Quick,1);//走到node2
		turn_until_line(500,-500,0.2);//转到跷跷板方向	
		flag.Road_flag=_seesaw1;
		}
	
	//门关
	else if(Door.D1==_closed){
		turn_until_line(-500,500,0.4);//转到node1方向		
		flag.Road_flag=_rt_node1_d1;
		}
}

/*************************************
*函数名称：rt_node1_d1
*函数功能：从门1方向直走经过一条分叉线返回到node1,并转到门2方向
*下一状态：_node2_d2	
**************************************/
void rt_node1_d1(void)
{
	forward_mid(450,Straight_Quick,1);//走到node1
	go_open(500,500,0.15);
	turn_until_line(500,-500,0.3);
	turn_until_line(500,-500,0.2);//转到门2方向,转2次增加准确率		
	flag.Road_flag=_node2_d2;
}

/*************************************
*函数名称：node2_d2
*函数功能：设定一个时间向门2跑去,在此时间内检测门是否开启。
					 门2开启：先经过一个分叉点到矩形中间,然后转到node2方向,再经过一个分叉点到node2,并转到跷跷板方向			
					 门2关闭：调头,转到node1方向
*下一状态：_seesaw1 		(门2开)
					 _rt_node1_d2 (门2关)
**************************************/
void node2_d2(void)
{
	go_closed(450,Straight_Quick,2,DT_2);
	//门开
	if(Door.D2==_open){
		forward_mid(450,Straight_Quick,1);//走到分叉点
		turn_until_line(500,-500,0.4);//转到跷跷板方向	
//		forward_mid(450,Straight_Quick,1);//走到node2
		forward_mid_light(450,Straight_Quick,1,4);
		go_open(500,500,0.1);
		turn_until_line(500,-500,0.2);//转到跷跷板方向	
		flag.Road_flag=_seesaw1;
		}
	
	//门关
	else if(Door.D2==_closed){
		turn_until_line(-500,500,0.4);//转到node1方向		
		flag.Road_flag=_rt_node1_d2;
		}
}

/*************************************
*函数名称：rt_node1_d2
*函数功能：从门2方向直走经过一条分叉线返回到node1,并转到node3方向
*下一状态：_node3_n1	
**************************************/
void rt_node1_d2(void)
{
	forward_mid(450,Straight_Quick,1);//走到node1
		go_open(500,500,0.15);
	turn_until_line(500,-500,0.4);//转到node3方向		
	flag.Road_flag=_node3_n1;
}

/*************************************
*函数名称：node3_n1
*函数功能：从node1方向直走经过2条分叉线返回到node3,并转到门3方向
*下一状态：_node2_d3	
**************************************/
void node3_n1(void)
{
//	forward_mid(550,Straight_Quick,1);//走到node3
//	go_closed(550,Straight_Quick,0.5,DT_Disable);
//	forward_mid(550,Straight_Quick,1);//走到node3

	forward_mid(750,Straight_Quick,2);//走到node3
	turn_until_line(500,-500,0.2);//转到node3方向	
	turn_until_line(500,-500,0.2);//转到node3方向		

	flag.Road_flag=_node2_d3;
}

/*************************************
*函数名称：node2_d3
*函数功能：从门3方向先经过1条分叉线到矩形中心,再经过一条分叉线到node2处并转到跷跷板方向
*下一状态：_seesaw1
**************************************/
void node2_d3(void)
{
	forward_mid(550,Straight_Quick,1);//走到node2
	forward_mid_light(450,Straight_Quick,1,4);
	go_open(500,500,0.1);
//	forward_mid(550,Straight_Quick,1);//走到node2
//	LED_R_ON;
//	go_open(500,500,0.15);
	turn_until_line(500,-500,0.2);//转到跷跷板方向	
	flag.Road_flag=_seesaw1;
}

/*************************************
*函数名称：seesaw1
*函数功能：先直走,在第一个分叉点处转到跷跷板1方向,寻迹并上板(上板前要左转一下)。
					 下板后前进一个分叉点,并转到平台6的方向。
*下一状态：_platform6
**************************************/
void seesaw1(void)//跷跷板1
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
	stop(1.5);//靠重力下去
	go_open(-100,500,0.4);//跑到白线上
	forward_mid(450,Straight_Quick,1);
	turn_until_line(-500,500,0.3);//转到平台6方向
	
	flag.Road_flag=_platform6;
}

/*************************************
*函数名称：platform6
*函数功能：直走上平台6,自转,下台,前进一个分叉点并转到板2的方向
*下一状态：_seesaw2
**************************************/
void platform6(void)//直走上平台6，自转，下去并到白线上左转
{
	int upflag=0;
	Read_Digital_Data();
	while(1)
	{
		go_forward(450,Straight_Quick);//在平地寻迹直到走到平台上
		_MPU_READ;
		if(abs(roll)>15)//到上坡了
		{
			upflag=1;
		}
		
		if( upflag==1 && ( (sum1<=3)||abs(roll)<=7) )	//已经走到了平台上
		{
			go_open(300,300,0.4);
			stop(0.2); 
			break;
		}
	}
	
	_MPU_READ;
	turn_right(500,175);//在平台上自转一圈170
	
	forward_mid(450,Straight_Quick,1);//走到圆上
	turn_until_line(-500,500,0.3);//转到跷跷板方向
	
	flag.Road_flag=_seesaw2;
}

/*************************************
*函数名称：seesaw2
*函数功能：寻迹并上板(上板前要左转一下)。
					 下板后前进一？？？个分叉点到node2
*下一状态：_platform6
**************************************/
void seesaw2(void)//跷跷板2
{
	while(1)
	{
		go_forward(450,S_Curve);
		if(sum1>=8)
			break;
	}
	go_open(-300,500,0.14);
	//灰度到跷跷板
	//go_open(100,500,0.3);//上跷跷板偏左上,以免直接掉下去了
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
	stop(1.5);//靠重力下去
	go_open(-100,500,0.4);//跑到白线上
	
	flag.Road_flag=_up_bevel_edge;
}

void up_bevel_edge(void)//上斜台
{
	forward_mid(450,Straight_Quick,2);
}

void down_bevel_edge(void)//下斜台
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

void crash(int initial_speed)//撞台并转180度
{
	/* 当成过程中的函数使用,而不是单独存在的 */
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
	turn_until_line(500,-500,0.4);//掉个头
//	flag.Road_flag=_crash2;
}



void return1(void)
{
	int upflag=0;

	stop(50);
	flag.Road_flag=20;
}
#endif
