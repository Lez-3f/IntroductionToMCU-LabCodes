/*
 * L5_3_test.c
 *
 *  Created on: 2021年8月25日
 *      Author: ZEL
 */
#include "msp430.h"
void main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    //初始化 LED 引脚，基本输出，初值 LED 灭    2.0--led  2.1--buzz
    P2SEL &= ~(BIT0 + BIT1);
    P2SEL &= ~(BIT0 + BIT1);
    P2DIR |= (BIT0 + BIT1);
    P2OUT |= (BIT0 + BIT1);
    //设置基本时钟 ACLK =32768Hz/8=4096Hz(上电复位 ACLK 来自外部晶振时钟)
    //BCSCTL1 = DIVA_3;
    //设置 P1.4 输出时钟 ACLK
    P1SEL |=BIT4; //设置 P1.0 输出 ACLK 时钟
    P1SEL2 &= ~BIT4;
    P1DIR |=BIT4;
    //中断引脚的相关设置
    P1SEL &= ~BIT5;
    P1SEL &= ~BIT5;
    P1DIR &= ~BIT5; //输入
    P1REN |= BIT5;
    P1OUT |= BIT5;
    P1IE |= BIT5;
    P1IES |= BIT5;
    P1IFG &= ~BIT5;

    _EINT(); //总中断允许
    while (1) { }; //主循环
}

unsigned int num_clk=0; //计数时钟个数变量
unsigned int num_clk_buzz= 0;
#pragma vector=PORT1_VECTOR
__interrupt void count_clk( )
{
    num_clk++; //中断次数加 1，即时钟个数加 1
    if (num_clk==2048) //半秒计数时钟个数到
    {
        P2OUT ^= BIT0; //对 LED 状态取反，即半秒变化一次:亮半秒,灭半秒
        num_clk=0; //计数时钟个数清零
        num_clk_buzz++;
        if(num_clk_buzz>=12 && num_clk_buzz<20)
        {
            P2OUT^=BIT1;
        }
        if(num_clk_buzz == 20)
        {
            num_clk_buzz=0;
        }
    }
    if(num_clk_buzz)
    P1IFG &= ~BIT5; //清除中断标志
}



