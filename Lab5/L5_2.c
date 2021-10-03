/*
 * L5_2.c
 *
 *  Created on: 2021年8月25日
 *      Author: ZEL
 */
#include "msp430.h"
#define number 550000 //可根据实际需要，改变该常数大小
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



