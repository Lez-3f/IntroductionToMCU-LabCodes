/*
 * L6_buzz_ring.c
 *
 *  Created on: 2021��8��26��
 *      Author: ZEL
 */
#include "msp430.h"
void delay(unsigned int numloop)
{
    unsigned int j;
    for(j = 0;j < numloop;j++);
}
void buzz(unsigned int TA1CCR0_set, unsigned int numloop)
{
    TA1CCR0=TA1CCR0_set;//262Hz
    TA1CCR1=TA1CCR0_set / 15;
    delay(numloop);
}
void pause(unsigned int numloop)
{
    TA1CCR0 = 32678;
    delay(numloop);
}
void test()
{
    buzz(249, 0x5000);
    buzz(222, 0x5000);
    buzz(198, 0x5000);
    buzz(186, 0x5000);
    buzz(166, 0x5000);
    buzz(148, 0x5000);
    buzz(132, 0x5000);

    buzz(124, 0x5000);
    buzz(110, 0x5000);
    buzz(98, 0x5000);
    buzz(93, 0x5000);
    buzz(82, 0x5000);
    buzz(73, 0x5000);
    buzz(65, 0x5000);

    buzz(62, 0x5000);
    buzz(55, 0x5000);
    buzz(49, 0x5000);
    buzz(46, 0x5000);
    buzz(41, 0x5000);
    buzz(36, 0x5000);
    buzz(32, 0x5000);

}
void TWOTIGERS__Play()
{
    buzz(124, 0xf000);
    buzz(110, 0xf000);
    buzz(98, 0xf000);
    buzz(124, 0xf000);
    pause(0x500);
    buzz(124, 0xf000);
    buzz(110, 0xf000);
    buzz(98, 0xf000);
    buzz(124, 0xf000);
    pause(0x500);
    buzz(98, 0xf000);
    buzz(93, 0xf000);
    buzz(82, 0xf000);
    buzz(82, 0xf000);
    pause(0x500);
    buzz(98, 0xf000);
    buzz(93, 0xf000);
    buzz(82, 0xf000);
    buzz(82, 0xf000);
    pause(0x500);

    buzz(82, 0x8000);
    buzz(73, 0x8000);
    buzz(82, 0x8000);
    buzz(93, 0x8000);
    buzz(98, 0xf000);
    buzz(124, 0xf000);
    pause(0x500);
    buzz(82, 0x8000);
    buzz(73, 0x8000);
    buzz(82, 0x8000);
    buzz(93, 0x8000);
    buzz(98, 0xf000);
    buzz(124, 0xf000);

    pause(0x500);
    buzz(110, 0xf000);
    buzz(166, 0xf000);
    buzz(124, 0xffff);


    pause(0xf000);
    buzz(110, 0xf000);
    buzz(166, 0xf000);
    buzz(124, 0xffff);

    pause(0xffff);
}
int main()
{
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    P2SEL |=BIT1; //�� P2.1Ϊ��ʱ�� TA1 �� PWM �������
    P2SEL2 &=~(BIT1); //P2.1 Ϊ�Ƚ��� 1 �� PWM �������
    P2DIR |= BIT1;
    TA1CTL |=TASSEL0; //ѡ�� TA1 ����ʱ��Ϊ ACLK��ʹ���ϵ縴λ���ã��� 32768Hz
    TA1CCTL1|=OUTMOD1;
    TA1CTL |=TACLR+MC0; //������������ʽ��ʹ�������� 0 ��ʼ������������ TA1CCR0 ���ִ� 0 ������
    TA1CCR0 = 32678;

    //test();
    while(1)
    {
        TWOTIGERS__Play();
    }
}



