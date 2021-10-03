#include "msp430.h"
void delay();

int main()
{
    WDTCTL = WDTPW + WDTHOLD;  //关闭看门狗
    P2DIR = 0xff;               //设置端口二为输出方向，2.4接蜂鸣
    P2SEL = 0;      //设置端口P2的8个引脚为基本输入输出功能
    P2SEL2 = 0;
    P2OUT = 0xff;   //设置端口P2输出端为全灭

    P1DIR = BIT5 + BIT6 + BIT7;   //设置端口1.0-1.4为输入方向
    P1SEL = 0;
    P1SEL2 = 0;
    P1REN = ~(BIT5 + BIT6 + BIT7); //有电阻
    P1OUT = ~(BIT5 + BIT6 + BIT7); //设置上拉

    while(1)
    {
        start:
        if((P1IN & BIT0) == 0) //K1闭合
        {
            while(1)
            {
                P2OUT = ~(BIT0 + BIT1);
                if((P1IN & BIT4) == 0) // K8闭合
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
                    goto start;
                }
            }
        }

        else if((P1IN & BIT2) == 0) //K3闭合
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
            unsigned int j;
            P2OUT &= ~BIT4; //蜂鸣
            delay();
            P2OUT |= BIT4; //停止蜂鸣

            while(1) // L5,L4闪
            {
                P2OUT &= ~(BIT2 + BIT3);
                delay();
                P2OUT |= (BIT2 + BIT3);
                delay();
                if((P1IN & BIT4) == 0) // K8闭合
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
                    goto start;
                }
            }

        }

        else if((P1IN & BIT1) == 0) // K2闭合
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
            while(1) // L3,L4闪
            {
                P2OUT &= ~(BIT1 + BIT3);
                delay();
                P2OUT |= (BIT1 + BIT3);
                delay();
                if((P1IN & BIT4) == 0) // K8闭合
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
                    goto start;
                }
            }
        }

        else if((P1IN & BIT3) == 0) // K4闭合
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
            while(1) // L6,L5闪
            {
                P2OUT &= ~(BIT0 + BIT2);
                delay();
                P2OUT |= (BIT0 + BIT2);
                delay();
                if((P1IN & BIT4) == 0) // K8闭合
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
                    goto start;
                }
            }
        }

        else if((P1IN & BIT4) == 0) // K8闭合
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // 关闭所有灯光
            goto start;
        }
    }
}

void delay()
{
    unsigned int j;
    for(j = 0;j < 0xffff; j++);
}
