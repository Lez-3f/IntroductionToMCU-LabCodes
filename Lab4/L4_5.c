/*
 * L4_5.c
 *
 *  Created on: 2021年8月24日
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
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    __disable_interrupt(); //_DINT(); 禁止总中断
    P1SEL=0; //置 P2 为基本 I/O 功能
    P1SEL2=0; //
    P1DIR &= ~BIT0; //置 P1.0 为输入方向
    P1DIR |= BIT1; //1.1 output
    P1OUT |=BIT0;
    P1OUT |= BIT1;
    P1REN |= BIT0;
    P1IES |= BIT0;
    P1IE |= BIT0;
    P1IFG &=~BIT0;

    __enable_interrupt(); //_EINT(); 总中断运行
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



