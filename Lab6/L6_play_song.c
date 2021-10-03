/*
 * L6_play_song.c
 *
 *  Created on: 2021年8月26日
 *      Author: ZEL
 */
#include "msp430.h"
#include "L6_tone.h"
#include "Two_tiger.h"
#include "Qinghuaci.h"
#include "Juhuacan.h"
void delay(unsigned int beat);
void buzz(unsigned int TA1CCR0_set, unsigned int beat)
{
    TA1CCR0=TA1CCR0_set;//262Hz
    TA1CCR1=TA1CCR0_set / 20;
    delay(beat);
    TA1CCR0 = 32768;
}
void delay(unsigned int beat)
{
    unsigned int i;
    for(i = 0;i < beat; i++)
    {
        unsigned int j;
        for(j = 0; j < 0x3000; j++);
    }

}
void pause()
{
    unsigned int j;
    for(j = 0; j < 0x500;j++);
}
void Song_play(const unsigned int *Song, const unsigned int *Beats, const unsigned int note_num)
{
    unsigned int i;
    unsigned int beats_played = 0;
    for(i = 0;i < note_num; i++)
    {
        buzz(Song[i], Beats[i]);
        beats_played += Beats[i];
        if(beats_played == beat_4)
        {
            beats_played = 0;
            pause();
        }
    }
    delay(24);
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
    TA1CCR0 = 32768;

    //test();
    while(1)
    {
        //Song_play(Two_tiger, Beats_Two_tiger, note_num_TT);
        //Song_play(QHC, Beats_QHC, note_num_QHC);
        Song_play(JHT, Beats_JHT, note_num_JHT);
        //test();
    }
}




