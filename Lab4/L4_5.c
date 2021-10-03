/*
 * L4_5.c
 *
 *  Created on: 2021��8��24��
 *      Author: ZEL
 */
#include "msp430.h"

void delay(unsigned int numLoop)
{
    unsigned int j;
    for(j = 0;j < numLoop; j++);
}

int main()
{
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    __disable_interrupt(); //_DINT(); ��ֹ���ж�
    P1SEL=0; //�� P2 Ϊ���� I/O ����
    P1SEL2=0; //
    P1DIR &= ~BIT0; //�� P1.0 Ϊ���뷽��
    P1DIR |= BIT1; //1.1 output
    P1OUT |=BIT0;
    P1OUT |= BIT1;
    P1REN |= BIT0;
    P1IES |= BIT0;
    P1IE |= BIT0;
    P1IFG &=~BIT0;

    __enable_interrupt(); //_EINT(); ���ж�����
     while(1){ };
}
void Ring()
{
    P1OUT &= ~BIT1;
    delay(0x500);
    P1OUT |= BIT1;
}

#pragma vector=PORT1_VECTOR
__interrupt void port_int(void)
{
    if ( (P1IFG&BIT0) !=0 )
    {
        delay(0x500);
        Ring();
        delay(0x5000);
    }
    P1IFG &=~BIT0;
}



