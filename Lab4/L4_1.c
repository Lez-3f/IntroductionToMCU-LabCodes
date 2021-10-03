/*
 * L4_1.c
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
void Blink( ) //LED闪
{
    P2OUT &=~BIT3;
    delay(0xf000);
    P2OUT |= BIT3;
    delay(0xf000);
}
void Buzz( ) //蜂鸣响
{
        unsigned int i;
        for (i=0; i<8; i++)
        {
            P2OUT ^=BIT4; //对引脚输出求反
            delay(0xf000);
        };
}
void main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    //设置引脚P2.4、P2.3输出，P2.3连接LED，P2.4连接蜂鸣器
    P2SEL &=~(BIT3+BIT4);
    P2SEL2 &=~(BIT3+BIT4);
    P2OUT|=(BIT3+BIT4);
    P2DIR|=(BIT3+BIT4);
    //中断相关设置
    P2SEL &=~BIT1;
    P2SEL2 &=~BIT1;
    P2OUT |=BIT1;
    P2REN |=BIT1;
    P2DIR &=~BIT1;
    P2IES |= BIT1;
    P2IFG &=~BIT1;
    P2IE |= BIT1;
    _EINT(); //总中断允许
    for (;;) //主循环
    {
        Blink();
    };
}
#pragma vector=PORT2_VECTOR
__interrupt void port_ISR( )
{
    if ( (P2IFG&BIT1)!=0 ) //判断是P2.1上的中断
        Buzz();
        P2IFG &=~BIT1;
}


