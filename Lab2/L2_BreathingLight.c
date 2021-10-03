// Breathing Light
#include "msp430.h"
unsigned int L=0,M=0;
void delay();
int main ( void )
{
    unsigned int i;
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    P2SEL &=~(BIT2+BIT5);
    P2SEL2 &=~(BIT2+BIT5);
    P2OUT |=BIT2+BIT5;
    P2DIR |=BIT2+BIT5;
    for (;;) //��ѭ��
    {
        while(L<0x500)
        {
            L = L + 5;
            M=0x500-L;
            P2OUT &=~(BIT2+BIT5);   //ͨ�����Ƶƹ������ġ�ռ�ձȡ�������һյ�Ƶ�������
            for (i=0; i<L; i++);
            P2OUT |=(BIT2+BIT5);
            for (i=0; i<M; i++);
        }
        while(L>0)
        {
            L = L - 5;
            M=0x500-L;
            P2OUT &=~(BIT2+BIT5);   //ͨ�����Ƶƹ������ġ�ռ�ձȡ�������һյ�Ƶ�������
            for (i=0; i<L; i++);
            P2OUT |=(BIT2+BIT5);
            for (i=0; i<M; i++);
        }
        delay();
    };
}
void delay( ) //��ʱ����
{
    unsigned int j;
    for (j=0;j<0xffff;j++);
}
