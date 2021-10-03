/*
 * L4_4.c
 *
 *  Created on: 2021年8月24日
 *      Author: ZEL
 */
#include "msp430.h"
unsigned int number=0; //记录响应按键次数
void delay(unsigned int i) //延时函数
{ unsigned int j; for (j=0; j<i; j++); }

int main( void )
{
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    __disable_interrupt(); //_DINT(); 禁止总中断
    P2SEL=0; //置 P2 为基本 I/O 功能
    P2SEL2=0; //
    P2OUT=0xFF; //置 P2 输出的初值
    P2DIR=0xFF; //置 P2 为输出方向
    P1SEL &= BIT2;
    P1SEL2 &= BIT2;
    P1OUT |=BIT2;;
    P1REN |=BIT2;
    P1DIR &=~BIT2;
    P1IES |= BIT2;
    P1IFG &=~BIT2;
    P1IE |= BIT2;
    __enable_interrupt(); //_EINT(); 总中断运行
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



