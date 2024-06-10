#ifndef __SENSOR__H
#define __SENSOR__H	 
#include "sys.h"

/*-------------车头八路灰度----------------*/
/* 黑色返回1，白色返回0 */
#define E1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//左
#define E2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)
#define E3 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define E4 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define E5 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define E6 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)
#define E7 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
#define E8 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//右

/*-------------车身左右灰度----------------*/
#define EL GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)//左
#define ER GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)//右

/*-------------光电传感器--------------*/
//距离内-----光电上的灯亮------返回0
#define GR GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
#define GL GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)

/*-------------色标传感器--------------*/
/* 黑色返回1，红色返回0 */
#define S3 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)//左前
#define S4 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)//右前
#define S1 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//左后
#define S2 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//右后

/* 传感器初始化 */
void Eig_Hui_Init(void);
void GD_Sensor_Init(void);
void SB_Sensor_Init(void);
void Sensors_GPIO_Init(void);

#endif