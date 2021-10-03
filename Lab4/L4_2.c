/*
 * L4_2.c
 *
 *  Created on: 2021年8月24日
 *      Author: ZEL
 */
#include "msp430.h"
void delay(unsigned int i) //延时函数
{
    unsigned int j; //定义局部变量
    for (j=0; j<i; j++);
}
void _K2_react_()
{
    unsigned int i;
    for(i=0; i<6; i++)
    {
        P1OUT ^= BIT4;
        delay(0xf000);
    }
}
void _K4_react_( ) //蜂鸣响
{
    unsigned int i;
    for (i=0; i<2; i++)
    {
        P1OUT ^=BIT0; //对引脚输出求反
        delay(0xf000);
    };
}
void _main_loop_()
{
    P1OUT &=~BIT5;
    delay(0xf000);
    P1OUT |= BIT5;
    delay(0xf000);
}

int main()
{
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    // p1.0,p1.4,p1.5输出，p1.0--buzz, p1.4--L3, p1.5--L8
    P1SEL &= ~(BIT0 + BIT4 + BIT5);
    P1SEL2 &= ~(BIT0 + BIT4 + BIT5);
    P1DIR |= (BIT0 + BIT4 + BIT5);
    P1OUT |= (BIT0 + BIT4 + BIT5);

    //设置中断 p1.2--K2, p1.6--K4
    P1SEL &=~(BIT2 + BIT6);
    P1SEL2 &=~(BIT2 + BIT6);
    P1OUT |=(BIT2 + BIT6);
    P1REN |=(BIT2 + BIT6);
    P1DIR &=~(BIT2 + BIT6);
    P1IES |= (BIT2 + BIT6);
    P1IFG &=~(BIT2 + BIT6);
    P1IE |= (BIT2 + BIT6);

    _EINT();
    while(1)
    {
        _main_loop_();
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void port_ISR( )
{
    if ( (P1IFG&BIT2)!=0 ) //判断是P1.2上的中断
    {
        _K2_react_();
        P1IFG &=~BIT2;
    }
    if ( (P1IFG&BIT6)!=0 ) //判断是P1.6上的中断
    {
        _K4_react_();
        P1IFG &=~BIT6;
    }
}



