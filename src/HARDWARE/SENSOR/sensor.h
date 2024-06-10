#ifndef __SENSOR__H
#define __SENSOR__H	 
#include "sys.h"

/*-------------��ͷ��·�Ҷ�----------------*/
/* ��ɫ����1����ɫ����0 */
#define E1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//��
#define E2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)
#define E3 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define E4 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define E5 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define E6 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)
#define E7 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
#define E8 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//��

/*-------------�������һҶ�----------------*/
#define EL GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)//��
#define ER GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)//��

/*-------------��紫����--------------*/
//������-----����ϵĵ���------����0
#define GR GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
#define GL GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)

/*-------------ɫ�괫����--------------*/
/* ��ɫ����1����ɫ����0 */
#define S3 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)//��ǰ
#define S4 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)//��ǰ
#define S1 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//���
#define S2 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//�Һ�

/* ��������ʼ�� */
void Eig_Hui_Init(void);
void GD_Sensor_Init(void);
void SB_Sensor_Init(void);
void Sensors_GPIO_Init(void);

#endif