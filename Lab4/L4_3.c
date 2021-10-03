/*
 * L4_3.c
 *
 *  Created on: 2021��8��24��
 *      Author: ZEL
 *
 *  Modified from L4_intB.c offered by School
 */
#include "msp430.h"
#define buzz_PSEL P2SEL //������������ӵ����źͶ˿�
#define buzz_PSEL2 P2SEL2
#define buzz_PDIR P2DIR
#define buzz_POUT P2OUT
#define buzz_Pin BIT4
#define num_Buzz 6 //������Ʒ�������İ�������
#define key_PSEL P1SEL //�����ж���ص����źͶ˿�
#define key_PSEL2 P1SEL2
#define key_POUT P1OUT
#define key_PREN P1REN
#define key_PDIR P1DIR
#define key_PIES P1IES
#define key_PIFG P1IFG
#define key_PIE P1IE
#define key_Pin BIT5
#define key_Vector PORT1_VECTOR
#define led_PSEL P2SEL //����led��ص����źͶ˿�
#define led_PSEL2 P2SEL2
#define led_POUT P2OUT
#define led_PREN P2REN
#define led_PDIR P2DIR
#define led_Pin BIT0

unsigned int num_Key=0; //������������
unsigned int flag_Buzz=0; //���������־
void delay(unsigned int i) //��ʱ����
{
    unsigned int j;
    for (j=0; j<i; j++);
}

void Buzz( ) //�����캯��
{
    unsigned int i;
    for ( i=0;i<8;i++ )
    {
        buzz_POUT ^=buzz_Pin;
        delay(0x6000);
    };
}
void main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    led_PSEL &=~BIT0; //��ʼ�� LED ���ţ������������ֵ LED ��
    led_PSEL2 &=~BIT0;
    led_POUT|=BIT0;
    led_PDIR|=BIT0;
    buzz_PSEL &=~buzz_Pin; //��ʼ�����������ţ������������ֵ����������
    buzz_PSEL2 &=~buzz_Pin;
    buzz_POUT|=buzz_Pin;
    buzz_PDIR|=buzz_Pin;
    key_PSEL &=~key_Pin; //�ж����ŵ��������
    key_PSEL2 &=~key_Pin;
    key_POUT |=key_Pin;
    key_PREN |=key_Pin;
    key_PDIR &=~key_Pin;
    key_PIES |= key_Pin;
    key_PIFG &=~key_Pin;
    key_PIE |= key_Pin;
    _EINT(); //���ж�����
    while (1) //��ѭ��
    {
        if ( flag_Buzz==1 ) //���������־����
        {
            Buzz(); //������
            flag_Buzz=0; //����������־
        };
    }
}
#pragma vector=key_Vector
__interrupt void port_ISR( )
{
    num_Key++; //���������� 1
    led_POUT^=led_Pin; //LED �仯һ��
    if (num_Key==num_Buzz) //�������������
    { //Buzz( ); //������;
        flag_Buzz=1; //���÷��������־
        num_Key=0; //�����������㣬���¼���
    };
    key_PIFG &=~key_Pin; //����жϱ�־
}


