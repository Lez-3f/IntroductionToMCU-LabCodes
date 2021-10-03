#include "msp430.h"
void delay();
void Loop1();
void Loop2();
void Ring();

int main()
{
    WDTCTL = WDTPW + WDTHOLD;  //�رտ��Ź�
    P2DIR = 0xff;               //���ö˿ڶ�Ϊ�������
    P2SEL = 0;      //���ö˿�P2��8������Ϊ���������������
    P2SEL2 = 0;
    P2OUT = 0xff;   //���ö˿�P2�����Ϊȫ��

    P1DIR = ~(BIT1 + BIT3);   //���ö˿�1.1�� 1.3Ϊ���뷽��
    P1SEL = 0;
    P1SEL2 = 0;
    P1REN = (BIT1 + BIT3);
    P1OUT = (BIT0 + BIT1 + BIT3);
    while(1)
    {
        if((P1IN & BIT1) == 0)
        {
            Ring();
            Loop1();
        }
        if((P1IN & BIT3) == 0)
        {
            Ring();
            Loop2();
        }
    }
}

void Ring()
{
    P1OUT &= ~BIT0;
    delay();
    P1OUT |= BIT0;
}

void Loop1()
{
    unsigned int loop1[8] = {~BIT5, ~BIT6, ~BIT1, ~BIT2, ~BIT3, ~BIT0, ~BIT7, ~BIT4};
    unsigned int j;
    for(j = 0; j < 8; j++)
    {
        P2OUT = loop1[j];
        delay();
    }
    P2OUT = 0xff;
}

void Loop2()
{
    unsigned int loop2[4] = {~(BIT5 + BIT3), ~(BIT4 + BIT2), ~(BIT6 + BIT0), ~(BIT7 + BIT1)};
    unsigned int j;
    for(j = 0; j < 4; j++)
    {
        P2OUT = loop2[j];
        delay();
    }
    P2OUT = 0xff;
}

void delay()
{
    unsigned int j;
    for(j = 0;j < 0xffff; j++);
}
