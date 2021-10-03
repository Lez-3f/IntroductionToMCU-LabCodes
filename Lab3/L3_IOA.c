/*
 * L3_IOA.c
 *
 *  Created on: 2021��8��24��
 *      Author: ZEL
 */

#include <msp430.h>
void delay(unsigned int numloop);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P2SEL = 0;
    P2SEL2 = 0;
    P2DIR &= ~BIT0; //2.0 �����OUT������
    P2REN |= BIT0;
    P2OUT &= ~BIT0;
    P2DIR |= (BIT1 + BIT2); //2.1,2.2Ϊ������ֱ����С�ƺͷ�����
    P2OUT |= BIT1;
    P2OUT |= BIT2;
    while(1)
    {
        if((P2IN & BIT0) == 0) //�����ϰ���2.0����͵�ƽ
        {
            P2OUT &= ~BIT1;  //L2����
            P2OUT &= ~BIT2; //��������
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



