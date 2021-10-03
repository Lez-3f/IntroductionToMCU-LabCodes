#include "msp430.h"
#define Led_a BIT0 //定义与 LED 连接的引脚
#define Led_b BIT5
unsigned int i; //定义延时用变量
int main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗

    //下面这段代码时钟信号输出代码，有示波器时用，无示波器时可不用
    P1SEL |=BIT0; //设置 P1.0 输出 ACLK 时钟
    P1SEL2 &= ~BIT0;
    P1DIR |=BIT0;
    P1SEL |=BIT4; //设置 P1.4 输出 SMCLK 时钟
    P1SEL2 &= ~BIT4;
    P1DIR |=BIT4;
    //
    P2SEL &=~(Led_a+Led_b); //设置引脚 P2.0 和 P2.5 为基本输入输出功能
    P2SEL2 &=~(Led_a+Led_b);
    P2OUT |=Led_a+Led_b; //设置引脚 P2.0 和 P2.5 输出的初值为 1
    P2DIR |=Led_a+Led_b; //设置端口 P2.0 和 P2.5 为输出方向
    while (1) //主循-环
    {
        P2OUT ^=(Led_a+Led_b); //将 P2.0 和 P2.5 的值取反后输出
        for (i=0xFFF; i>0; i--); //延时
    }
}
