#include "msp430.h"
void delay();

int main()
{
    WDTCTL = WDTPW + WDTHOLD;  //�رտ��Ź�
    P2DIR = 0xff;               //���ö˿ڶ�Ϊ�������2.4�ӷ���
    P2SEL = 0;      //���ö˿�P2��8������Ϊ���������������
    P2SEL2 = 0;
    P2OUT = 0xff;   //���ö˿�P2�����Ϊȫ��

    P1DIR = BIT5 + BIT6 + BIT7;   //���ö˿�1.0-1.4Ϊ���뷽��
    P1SEL = 0;
    P1SEL2 = 0;
    P1REN = ~(BIT5 + BIT6 + BIT7); //�е���
    P1OUT = ~(BIT5 + BIT6 + BIT7); //��������

    while(1)
    {
        start:
        if((P1IN & BIT0) == 0) //K1�պ�
        {
            while(1)
            {
                P2OUT = ~(BIT0 + BIT1);
                if((P1IN & BIT4) == 0) // K8�պ�
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
                    goto start;
                }
            }
        }

        else if((P1IN & BIT2) == 0) //K3�պ�
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
            unsigned int j;
            P2OUT &= ~BIT4; //����
            delay();
            P2OUT |= BIT4; //ֹͣ����

            while(1) // L5,L4��
            {
                P2OUT &= ~(BIT2 + BIT3);
                delay();
                P2OUT |= (BIT2 + BIT3);
                delay();
                if((P1IN & BIT4) == 0) // K8�պ�
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
                    goto start;
                }
            }

        }

        else if((P1IN & BIT1) == 0) // K2�պ�
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
            while(1) // L3,L4��
            {
                P2OUT &= ~(BIT1 + BIT3);
                delay();
                P2OUT |= (BIT1 + BIT3);
                delay();
                if((P1IN & BIT4) == 0) // K8�պ�
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
                    goto start;
                }
            }
        }

        else if((P1IN & BIT3) == 0) // K4�պ�
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
            while(1) // L6,L5��
            {
                P2OUT &= ~(BIT0 + BIT2);
                delay();
                P2OUT |= (BIT0 + BIT2);
                delay();
                if((P1IN & BIT4) == 0) // K8�պ�
                {
                    P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
                    goto start;
                }
            }
        }

        else if((P1IN & BIT4) == 0) // K8�պ�
        {
            P2OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // �ر����еƹ�
            goto start;
        }
    }
}

void delay()
{
    unsigned int j;
    for(j = 0;j < 0xffff; j++);
}
