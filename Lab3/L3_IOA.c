/*
 * L3_IOA.c
 *
 *  Created on: 2021年8月24日
 *      Author: ZEL
 */

#include <msp430.h>
void delay(unsigned int numloop);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P2SEL = 0;
    P2SEL2 = 0;
    P2DIR &= ~BIT0; //2.0 与红外OUT相连接
    P2REN |= BIT0;
    P2OUT &= ~BIT0;
    P2DIR |= (BIT1 + BIT2); //2.1,2.2为输出，分别控制小灯和蜂鸣器
    P2OUT |= BIT1;
    P2OUT |= BIT2;
    while(1)
    {
        if((P2IN & BIT0) == 0) //碰到障碍，2.0输出低电平
        {
            P2OUT &= ~BIT1;  //L2亮起
            P2OUT &= ~BIT2; //蜂鸣响起
            delay(0x5000);
            P2OUT |= BIT2;
            P2OUT |= BIT1;

        }
    }
}

void delay(unsigned int numloop)
{
    unsigned int j;
    for(j = 0;j < numloop; j++);
}



