/*
 * L5_2.c
 *
 *  Created on: 2021��8��25��
 *      Author: ZEL
 */
#include "msp430.h"
#define number 550000 //�ɸ���ʵ����Ҫ���ı�ó�����С
void main( void )
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer to prevent time out reset
    P2DIR |=BIT0;
    while(1)
    {
        P2OUT|=BIT0;
        __delay_cycles(number);
        P2OUT&=~BIT0;
        __delay_cycles(number);
    }
 }



