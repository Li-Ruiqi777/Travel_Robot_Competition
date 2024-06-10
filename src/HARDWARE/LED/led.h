#ifndef __LED_H 
#define __LED_H  
#include "sys.h" 
//LED ¶Ë¿Ú¶¨Òå
#define LED_G PAout(0)//ºìµÆ  1:ÁÁ£¬0Ãð
#define LED_R PAout(1)//ºìµÆ  1:ÁÁ£¬0Ãð
#define LED_Y PAout(2)//ºìµÆ  1:ÁÁ£¬0Ãð

#define LED_G_ON	LED_G=1
#define LED_G_OFF	LED_G=0

#define LED_R_ON	LED_R=1
#define LED_R_OFF	LED_R=0

#define LED_Y_ON	LED_Y=1
#define LED_Y_OFF	LED_Y=0

void LED_Init(void);//³õÊ¼»¯ 
void blink(void);
void LED_ALL_ON(void);
void LED_ALL_OFF(void);

#endif