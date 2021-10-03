/*
 * L6_PWM.c
 *
 *  Created on: 2021年8月25日
 *      Author: ZEL
 */
#include "msp430.h"
int main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗

    P2SEL |=BIT1+BIT4; //置 P2.1 和 P2.4 为定时器 TA1 的 PWM 输出引脚
    P2SEL2 &=~(BIT1+BIT4); //P2.1 为比较器 1 的 PWM 输出引脚
    P2DIR |=BIT1+BIT4; //P2.4 为比较器 2 的 PWM 输出引脚
    TA1CTL |=TASSEL0; //选择 TA1 计数时钟为 ACLK，使用上电复位设置，即 32768Hz
    TA1CCR0=32767; //设置 PWM 周期，周期= (TA1CCR0+1)*T =(TA1CCR0+1)/计数时钟频率
    //即 PWM 频率=1/PWM 周期=计数时钟频率/(TA1CCR0+1)
    TA1CCTL1|=OUTMOD1; //设置 TA1 比较器 1 的 PWM 输出为模式 2： 计数到 CCR1 值翻转，到 CCR0 值置 0
    TA1CCR1=24575; //设置 TA1 比较器 1 设定值 CCR1，TA1CCR1=TA1CCR0*(1-PWM 波形占空比 25%)
    TA1CCTL2|=OUTMOD1; //设置比较器 2 的 PWM 输出为模式 2： 计数到 CCR2 值翻转，到 CCR0 值置 0
    TA1CCR2=16383; //设置 TA1 比较器 2 设定值 CCR2，TA1CCR2=TA1CCR0*(1-PWM 波形占空比 50%)
    TA1CTL |=TACLR+MC0; //设置增计数方式，使计数器从 0 开始计数，计数到 TA1CCR0 后又从 0 计数。
    while(1){ }; // 主循环，CPU 可做其他事情
}



