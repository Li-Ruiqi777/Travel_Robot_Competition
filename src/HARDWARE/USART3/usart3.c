#include "usart3.h"
//����3����stm32��OpenMvͨ��
//---------------------------------------------------------------------------
void USART3_Init(u32 My_BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	// ����ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
  GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);
	USART_DeInit(USART3);  //��λ����3 -> ����û��
	
	// ��ʼ�� ���ڶ�ӦIO��  TX-PC10  RX-PC11
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_11;
  GPIO_Init(GPIOC,&GPIO_InitStrue);
	
	// ��ʼ�� ����ģʽ״̬
	USART_InitStrue.USART_BaudRate=My_BaudRate; // ������
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; // Ӳ��������
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; // ���� ���� ģʽ��ʹ��
	USART_InitStrue.USART_Parity=USART_Parity_No; // û����żУ��
	USART_InitStrue.USART_StopBits=USART_StopBits_1; // һλֹͣλ
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; // ÿ�η������ݿ��Ϊ8λ
	USART_Init(USART3,&USART_InitStrue);
	
	USART_Cmd(USART3,ENABLE);//ʹ�ܴ���
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//���������ж�
	
	// ��ʼ�� �ж����ȼ�
	NVIC_InitStrue.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStrue);
}
 
void USART3_IRQHandler(void) // ����2�жϷ�����
{
	int32_t com_data;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)) // �жϱ�־
  {
		USART_ClearFlag(USART3,USART_FLAG_RXNE);//����жϱ�־
  }
}

