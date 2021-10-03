/*
 * L4_1.c
 *
 *  Created on: 2021��8��24��
 *      Author: ZEL
 */
#include "msp430.h"
void delay(unsigned int i) //��ʱ����
{
    unsigned int j; //����ֲ�����
    for (j=0; j<i; j++);
}
void Blink( ) //LED��
{
    P2OUT &=~BIT3;
    delay(0xf000);
    P2OUT |= BIT3;
    delay(0xf000);
}
void Buzz( ) //������
{
        unsigned int i;
        for (i=0; i<8; i++)
        {
            P2OUT ^=BIT4; //�����������
            delay(0xf000);
        };
}
void main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    //��������P2.4��P2.3�����P2.3����LED��P2.4���ӷ�����
    P2SEL &=~(BIT3+BIT4);
    P2SEL2 &=~(BIT3+BIT4);
    P2OUT|=(BIT3+BIT4);
    P2DIR|=(BIT3+BIT4);
    //�ж��������
    P2SEL &=~BIT1;
    P2SEL2 &=~BIT1;
    P2OUT |=BIT1;
    P2REN |=BIT1;
    P2DIR &=~BIT1;
    P2IES |= BIT1;
    P2IFG &=~BIT1;
    P2IE |= BIT1;
    _EINT(); //���ж�����
    for (;;) //��ѭ��
    {
        Blink();
    };
}
#pragma vector=PORT2_VECTOR
__interrupt void port_ISR( )
{
    if ( (P2IFG&BIT1)!=0 ) //�ж���P2.1�ϵ��ж�
        Buzz();
        P2IFG &=~BIT1;
}


