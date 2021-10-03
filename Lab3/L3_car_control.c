/*
 * L3_car_control.c
 *
 *  Created on: 2021��8��24��
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
 *  go straight ***10111
 *  go back     ***11011
 *  go right    ***10101
 *  go left     ***10110
 *  stop        ***10100
 *
 *  1.x -- key(x+1)
 *  k1 -- ǰ��
 *  k2 -- ����
 *
 *  1.3 -- ����ģ��
 *
 *  k8 -- ֹͣ
 *
 *  k4 -- ����
 *  k5 -- ����
 *
 *  k6 -- ��ת
 *  k7 -- ��ת
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P2SEL = 0;
    P2SEL2 = 0;
    P2DIR = 0x1f; // ǰ5���˿���Ϊ�����
    P2OUT = 0x14; // ��ʼ����ֹͣ��

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
                if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //ͣ��
                {
                    P2OUT = 0x14;
                    goto start;
                }
                if((P1IN & BIT3) == 0) //����
                {
                    while(1)
                    {
                        P2OUT |= (BIT0 + BIT1);
                        delay(0x40);
                        P2OUT &= ~(BIT0 + BIT1);
                        delay(0x10);
                        if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //ͣ��
                        {
                            P2OUT = 0x14;
                            goto start;
                        }
                        else if((P1IN & BIT4) == 0) //����
                        {
                            goto s1;
                        }
                    }
                }
            }
        }
        else if((P1IN & BIT1) == 0) //����
        {
            while(1)
            {
                P2OUT |= (BIT0 + BIT1 + BIT3); P2OUT &= ~BIT2;
                delay(0x20);
                P2OUT &= ~(BIT0 + BIT1);
                delay(0x30);
                if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //ͣ��
                {
                    P2OUT = 0x14;
                    goto start;
                }
            }
        }

        else if((P1IN & BIT5) == 0) //��ת
        {
            while(1)
            {
                P2OUT |= (BIT0);
                delay(0x30);
                P2OUT &= ~(BIT0);
                delay(0x20);
                if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //ͣ��
                {
                    P2OUT = 0x14;
                    goto start;
                }
            }
        }

        else if((P1IN & BIT6) == 0) //��ת
        {
            while(1)
            {
                P2OUT |= (BIT1);
                delay(0x30);
                P2OUT &= ~(BIT1);
                delay(0x20);
                if((P1IN & BIT7) == 0 || (P1IN & BIT2) == 0) //ͣ��
                {
                    P2OUT = 0x14;
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


