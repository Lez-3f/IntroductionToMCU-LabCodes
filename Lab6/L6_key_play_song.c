/*
 * L6_key_play_song.c
 *
 *  Created on: 2021年8月26日
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
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    P2SEL |=BIT1; //置 P2.1为定时器 TA1 的 PWM 输出引脚
    P2SEL2 &=~(BIT1); //P2.1 为比较器 1 的 PWM 输出引脚
    P2DIR |= BIT1;
    TA1CTL |=TASSEL0; //选择 TA1 计数时钟为 ACLK，使用上电复位设置，即 32768Hz
    TA1CCTL1|=OUTMOD1;
    TA1CTL |=TACLR+MC0; //设置增计数方式，使计数器从 0 开始计数，计数到 TA1CCR0 后又从 0 计数。

    //p1全为输入 p2.0输入
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

    //中断引脚设置
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



