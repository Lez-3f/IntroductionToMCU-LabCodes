/*
 * L4_4.c
 *
 *  Created on: 2021��8��24��
 *      Author: ZEL
 */
#include "msp430.h"
unsigned int number=0; //��¼��Ӧ��������
void delay(unsigned int i) //��ʱ����
{ unsigned int j; for (j=0; j<i; j++); }

int main( void )
{
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    __disable_interrupt(); //_DINT(); ��ֹ���ж�
    P2SEL=0; //�� P2 Ϊ���� I/O ����
    P2SEL2=0; //
    P2OUT=0xFF; //�� P2 ����ĳ�ֵ
    P2DIR=0xFF; //�� P2 Ϊ�������
    P1SEL &= BIT2;
    P1SEL2 &= BIT2;
    P1OUT |=BIT2;;
    P1REN |=BIT2;
    P1DIR &=~BIT2;
    P1IES |= BIT2;
    P1IFG &=~BIT2;
    P1IE |= BIT2;
    __enable_interrupt(); //_EINT(); ���ж�����
     while(1){ };
}
#pragma vector=PORT1_VECTOR
__interrupt void port_int(void)
{
    unsigned int i;
    if ( (P1IFG&BIT2)!=0 )
    {
        delay(0x500);
        number++;
        P2OUT=~number;
    }
     P1IFG &=~BIT2;
}



