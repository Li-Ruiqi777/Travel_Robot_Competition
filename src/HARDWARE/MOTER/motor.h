#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#include "stdio.h"
#include "stdlib.h"

void TIM3_PWM_Init(u16 arr,u16 psc);
void MOTOR_GPIO_Init(void);
void motor(int32_t comparex,int32_t comparey);
void Limit_PWM(int32_t comparex,int32_t comparey,int32_t limit);

#endif
