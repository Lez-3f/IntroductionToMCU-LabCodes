/*
 * L6_key_play_song.c
 *
 *  Created on: 2021��8��26��
 *      Author: ZEL
 */
#include "L6_tone.h"
#include <msp430.h>
/*
 * 1.0 k1 mi
 * 1.1 k2 si
 * 1.2--key_blue --up
 * 1.3 k4 la
 * 1.4 k5 re
 * 1.5 k6 sol
 * 1.6 k7 do
 * 1.7 k8 fa
 * 2.0 key_red --low
 * 2.1 buzz
 */

void buzz(unsigned int TA1CCR0_set, unsigned int beat)
{
    TA1CCR0=TA1CCR0_set;//262Hz
    TA1CCR1=TA1CCR0_set / 20;
    delay(beat);
    TA1CCR1 = 32678;
}

void delay(unsigned int beat)
{
    unsigned int i;
    for(i = 0;i < beat; i++)
    {
        unsigned int j;
        for(j = 0; j < 0x4000; j++);
    }

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

    //p1ȫΪ���� p2.0����
    P1SEL = 0x00;
    P1SEL2 = 0x00;
    P1DIR = 0x00;
    P1REN = 0xff;
    P1OUT = 0xfb;

    P2SEL &= ~BIT0;
    P2SEL2 &= ~BIT0;
    P2DIR &= ~BIT0;
    P2REN |= BIT0;
    P2OUT &= ~BIT0;

    //�ж���������
    P1IES = 0xff;
    P1IFG = 0x00;
    P1IE = 0xff;
    //P2IES |= BIT0;
    //P2IFG &= ~BIT0;
    //P2IE |= BIT0;

    TA1CCR0 = 32678;

    _EINT();
    while(1){};
}

/*
 * 1.0 k1 mi
 * 1.1 k2 si
 * 1.2--key_blue --up
 * 1.3 k4 la
 * 1.4 k5 re
 * 1.5 k6 sol
 * 1.6 k7 do
 * 1.7 k8 fa
 * 2.0 key_red --low
 * 2.1 buzz
 */
#pragma vector=PORT1_VECTOR
__interrupt void port_ISR_1( )
{
    if((P1IN & BIT0) == 0) //1.0 --mi
    {
        while((P1IN & BIT0) == 0)
        {
            if((P1IN & BIT2) != 0) buzz(mi_h, beat_half);
            else if((P2IN & BIT0) != 0) buzz(mi_l, beat_half);
            else buzz(mi_m, beat_half);
        }
    }
    if((P1IN & BIT1) == 0)
    {
        while((P1IN & BIT1) == 0)
        {
            if((P1IN & BIT2) != 0) buzz(si_h, beat_half);
            else if((P2IN & BIT0) != 0) buzz(si_l, beat_half);
            else buzz(si_m, beat_half);
        }
    }
    if((P1IN & BIT3) == 0)
    {
        while((P1IN & BIT3) == 0)
        {
            if((P1IN & BIT2) != 0) buzz(la_h, beat_half);
            else if((P2IN & BIT0) != 0) buzz(la_l, beat_half);
            else buzz(la_m, beat_half);
        }
    }
    if((P1IN & BIT4) == 0)
    {
        while((P1IN & BIT4) == 0)
        {
            if((P1IN & BIT2) != 0) buzz(re_h, beat_half);
            else if((P2IN & BIT0) != 0) buzz(re_l, beat_half);
            else buzz(re_m, beat_half);
        }
    }
    if((P1IN & BIT5) == 0)
    {
        while((P1IN & BIT5) == 0)
        {
            if((P1IN & BIT2) != 0) buzz(sol_h, beat_half);
            else if((P2IN & BIT0) != 0) buzz(sol_l, beat_half);
            else buzz(sol_m, beat_half);
        }
    }
    if((P1IN & BIT6) == 0)
    {
        while((P1IN & BIT6) == 0)
        {
            if((P1IN & BIT2) != 0) buzz(do_h, beat_half);
            else if((P2IN & BIT0) != 0) buzz(do_l, beat_half);
            else buzz(do_m, beat_half);
        }
    }
    if((P1IN & BIT7) == 0)
    {
        while((P1IN & BIT7) == 0)
        {
            if((P1IN & BIT2) != 0) buzz(fa_h, beat_half);
            else if((P2IN & BIT0) != 0) buzz(fa_l, beat_half);
            else buzz(fa_m, beat_half);
        }
    }

    P1IFG = 0x00;
}



