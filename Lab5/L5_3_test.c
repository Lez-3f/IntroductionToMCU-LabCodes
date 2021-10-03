/*
 * L5_3_test.c
 *
 *  Created on: 2021��8��25��
 *      Author: ZEL
 */
#include "msp430.h"
void main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
    //��ʼ�� LED ���ţ������������ֵ LED ��    2.0--led  2.1--buzz
    P2SEL &= ~(BIT0 + BIT1);
    P2SEL &= ~(BIT0 + BIT1);
    P2DIR |= (BIT0 + BIT1);
    P2OUT |= (BIT0 + BIT1);
    //���û���ʱ�� ACLK =32768Hz/8=4096Hz(�ϵ縴λ ACLK �����ⲿ����ʱ��)
    //BCSCTL1 = DIVA_3;
    //���� P1.4 ���ʱ�� ACLK
    P1SEL |=BIT4; //���� P1.0 ��� ACLK ʱ��
    P1SEL2 &= ~BIT4;
    P1DIR |=BIT4;
    //�ж����ŵ��������
    P1SEL &= ~BIT5;
    P1SEL &= ~BIT5;
    P1DIR &= ~BIT5; //����
    P1REN |= BIT5;
    P1OUT |= BIT5;
    P1IE |= BIT5;
    P1IES |= BIT5;
    P1IFG &= ~BIT5;

    _EINT(); //���ж�����
    while (1) { }; //��ѭ��
}

unsigned int num_clk=0; //����ʱ�Ӹ�������
unsigned int num_clk_buzz= 0;
#pragma vector=PORT1_VECTOR
__interrupt void count_clk( )
{
    num_clk++; //�жϴ����� 1����ʱ�Ӹ����� 1
    if (num_clk==2048) //�������ʱ�Ӹ�����
    {
        P2OUT ^= BIT0; //�� LED ״̬ȡ����������仯һ��:������,�����
        num_clk=0; //����ʱ�Ӹ�������
        num_clk_buzz++;
        if(num_clk_buzz>=12 && num_clk_buzz<20)
        {
            P2OUT^=BIT1;
        }
        if(num_clk_buzz == 20)
        {
            num_clk_buzz=0;
        }
    }
    if(num_clk_buzz)
    P1IFG &= ~BIT5; //����жϱ�־
}



