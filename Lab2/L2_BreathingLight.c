// Breathing Light
#include "msp430.h"
unsigned int L=0,M=0;
void delay();
int main ( void )
{
    unsigned int i;
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    P2SEL &=~(BIT2+BIT5);
    P2SEL2 &=~(BIT2+BIT5);
    P2OUT |=BIT2+BIT5;
    P2DIR |=BIT2+BIT5;
    for (;;) //主循环
    {
        while(L<0x500)
        {
            L = L + 5;
            M=0x500-L;
            P2OUT &=~(BIT2+BIT5);   //通过控制灯光闪亮的“占空比”来调节一盏灯的明暗度
            for (i=0; i<L; i++);
            P2OUT |=(BIT2+BIT5);
            for (i=0; i<M; i++);
        }
        while(L>0)
        {
            L = L - 5;
            M=0x500-L;
            P2OUT &=~(BIT2+BIT5);   //通过控制灯光闪亮的“占空比”来调节一盏灯的明暗度
            for (i=0; i<L; i++);
            P2OUT |=(BIT2+BIT5);
            for (i=0; i<M; i++);
        }
        delay();
    };
}
void delay( ) //延时函数
{
    unsigned int j;
    for (j=0;j<0xffff;j++);
}
