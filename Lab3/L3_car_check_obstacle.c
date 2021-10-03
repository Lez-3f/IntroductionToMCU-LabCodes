/*
 * L3_car_check_obstacle.c
 *
 *  Created on: 2021年8月24日
 *      Author: ZEL
 */
#include <msp430.h>
void delay(unsigned int numloop);
void run_straight(int speed_level); //1 - 5
/*
 *  2.0--PWMA
 *  2.1--PWMB
 *  2.2--AIN1
 *  2.3--AIN2
 *  2.4--STBY
 *  2.5--buzz
 *  go straight ***10111
 *  go back     ***11011
 *  go right    ***10101
 *  go left     ***10110
 *  stop        ***10100
 *
 *  1.x -- key(x+1)
 *  k1 -- 前进
 *  k2 -- 后退
 *
 *  1.3 -- 避障模块
 *
 *  k8 -- 停止
 *
 *  k4 -- 加速
 *  k5 -- 减速
 *
 *  k6 -- 右转
 *  k7 -- 左转
 */
void Buzz()
{
    P2OUT &= ~BIT5;
    delay(0x5000);
    P2OUT |= BIT5;
}
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P2SEL = 0;
    P2SEL2 = 0;
    P2DIR = 0x3f; // 前6个端口设为输出端
    P2OUT = 0x34; // 初始车是停止的

    P1SEL = 0;
    P1SEL2 = 0;
    P1DIR = 0x00;
    P1REN = 0xff;
    P1OUT = 0xff;

    while(1)
    {
        start:
        if((P1IN & BIT0) == 0)
        {
            while(1)
            {
                s1:
                P2OUT |= (BIT0 + BIT1);
                delay(0x30);
                P2OUT &= ~(BIT0 + BIT1);
                delay(0x20);
                if((P1IN & BIT7) == 0) //停车
                {
                    P2OUT = 0x34;
                    goto start;
                }
                if((P1IN & BIT2) == 0) //有障碍
                {
                    Buzz();
                    while((P1IN & BIT2) == 0)
                    {
                        P2OUT |= (BIT1 + BIT3); P2OUT &= ~BIT2;
                        delay(0x40);
                        P2OUT = 0x34;
                        delay(0x10);
                    }
                    unsigned int j;
                    for(j= 0;j<100;j++)
                    {
                        P2OUT |= (BIT1 + BIT3); P2OUT &= ~BIT2;
                        delay(0x40);
                        P2OUT = 0x34;
                        delay(0x10);
                    }
                    delay(0x500);
                    goto s1;
                }
                if((P1IN & BIT3) == 0) //加速
                {
                    while(1)
                    {
                        P2OUT |= (BIT0 + BIT1);
                        delay(0x40);
                        P2OUT &= ~(BIT0 + BIT1);
                        delay(0x10);
                        if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //停车
                        {
                            P2OUT = 0x34;
                            goto start;
                        }
                        else if((P1IN & BIT4) == 0) //减速
                        {
                            goto s1;
                        }
                    }
                }
            }
        }
        else if((P1IN & BIT1) == 0) //后退
        {
            while(1)
            {
                P2OUT |= (BIT0 + BIT1 + BIT3); P2OUT &= ~BIT2;
                delay(0x20);
                P2OUT &= ~(BIT0 + BIT1);
                delay(0x30);
                if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //停车
                {
                    P2OUT = 0x34;
                    goto start;
                }
            }
        }

        else if((P1IN & BIT5) == 0) //右转
        {
            while(1)
            {
                P2OUT |= (BIT0);
                delay(0x30);
                P2OUT &= ~(BIT0);
                delay(0x20);
                if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //停车
                {
                    P2OUT = 0x34;
                    goto start;
                }
            }
        }

        else if((P1IN & BIT6) == 0) //左转
        {
            while(1)
            {
                P2OUT |= (BIT1);
                delay(0x30);
                P2OUT &= ~(BIT1);
                delay(0x20);
                if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //停车
                {
                    P2OUT = 0x34;
                    goto start;
                }
            }
        }
    }

}

void delay(unsigned int numloop)
{
    unsigned int j, i;
    for(i = 0; i < 5;i++)
    {

        for(j = 0;j < numloop; j++);
    }
}



