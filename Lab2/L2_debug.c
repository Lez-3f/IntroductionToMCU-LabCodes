#include "msp430.h"
void delay();

int main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    P2SEL=0; //���ö˿�P2��8������Ϊ���������������
    P2SEL2=0;
    P2OUT = 0;
    P2DIR=0xff; //���ö˿� 1 Ϊ�������
    while(1){
        P2OUT=~P2OUT; //���˿� 1 ��ֵȡ�������
        delay( ); //���ú�����ʱ
    }

}

void delay( ) //��ʱ����
{
    unsigned int j;
    for (j=0;j<0xffff;j++);
}
