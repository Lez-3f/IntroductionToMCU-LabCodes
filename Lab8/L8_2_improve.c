#include "msp430.h"
void UARTA0_init( );
char buffer[20],string[30]="Please input 7 characters:\r\n\0";
unsigned char j;
void delay(unsigned int numloop)
{
    unsigned int i;
    for(i = 0;i < numloop; i++);
}
int  main ( void )
{   WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
//��ʵ��ʱ�������ʾ����
//����P1.0��P1.4�������ʱ��ACLK��SMCLK���Ա�۲�ʱ��Ƶ��,�޸Ĳ����ʼĴ�������
//    P1SEL |= BIT0+BIT4;
//    P1SEL2 |=~( BIT0+BIT4);
//    P1DIR |= BIT0+BIT4;

   UARTA0_init( );               //��ʼ������
   //P1SEL &= ~(BIT1 + BIT2);
   //P1SEL2 &= ~(BIT1 + BIT2);
    P2SEL &= ~(BIT0 + BIT1);
    P2SEL2 &= ~(BIT0 + BIT1);
    P1SEL &= ~BIT0;
    P1SEL2 &= ~BIT0;
    P2DIR |= (BIT0 + BIT1); //2.0,2.1���
    P2OUT |= (BIT0 + BIT1);
    P1DIR &= ~BIT0;
    P1REN |= BIT0;
    P1OUT |= BIT0;//1.0���룬��������
    P1IES |= BIT0;
    P1IFG &= ~BIT0;
    P1IE |= BIT0; //1.0�ж�����

    _EINT();
    while(1)
    {
    };
}

char hint[11] = "Get Ready!";
char hint_error[6] = "ERROR";
#pragma vector=PORT1_VECTOR
__interrupt void port_ISR( )
{
    if ( (P1IFG&BIT0)!=0 ) //�ж���P1.0�ϵ��ж�
    {
        unsigned int j;
        for(j = 0;j < 10;j++)
        {
            while((IFG2&UCA0TXIFG)==0);     //��ⷢ�ͻ����Ƿ��
            UCA0TXBUF=hint[j];
        }//������ʾ��

        while(1)
        {
            char _get;
            while((IFG2&UCA0RXIFG)==0);     //�����ջ������Ƿ���
            _get = UCA0RXBUF;       //����һ�����ݲ�����
            switch(_get)
            {
            case 'F'://ȫ��
                P2OUT &= ~(BIT0 + BIT1);
                break;
            case 'B'://ȫ��
                while((IFG2&UCA0RXIFG)==0)
                {
                    P2OUT &= ~(BIT0 + BIT1);
                    delay(0x5000);
                    P2OUT |= (BIT0 + BIT1);
                    delay(0x5000);
                }
                break;
            case 'L'://1��
                P2OUT |= BIT1;
                while((IFG2&UCA0RXIFG)==0)
                {
                    P2OUT &= ~BIT0;
                    delay(0x5000);
                    P2OUT |= BIT0;
                    delay(0x5000);
                }
                break;
            case 'R'://2��
                P2OUT |= BIT0;
                while((IFG2&UCA0RXIFG)==0)
                {
                    P2OUT &= ~BIT1;
                    delay(0x5000);
                    P2OUT |= BIT1;
                    delay(0x5000);
                }
                break;
            case 'S'://ȫ��
                P2OUT |= (BIT0 + BIT1);
                break;
            default:
                for(j = 0;j < 5;j++)
                {
                    while((IFG2&UCA0TXIFG)==0);     //��ⷢ�ͻ����Ƿ��
                    UCA0TXBUF=hint_error[j];
                }//������ʾ��
                break;
            }
        }
    }
    P1IFG &=~BIT0;
}

void  UARTA0_init( )
{   UCA0CTL1|= UCSWRST;      //�������λλswrstΪ1
    P1SEL |= BIT1+BIT2;         	//��P1.1��P1.2Ϊ���нӿ��ա������Ź���
    P1SEL2 |= BIT1+BIT2;        	//
//���ݸ�ʽѡ���ϵ縴λ���ã���У�飬8λ���ݣ�1��ֹͣλ���첽����ͨ��
    UCA0CTL1|=UCSSEL0+UCRXEIE; //������ʱ��ѡ���ϵ縴λʱ��ACLK��32.768KHz���Դ����
    UCA0BR0 =3;              //������9600
    UCA0BR1 = 0;
    UCA0MCTL=UCBRF_0+UCBRS_3;
    UCA0CTL1 &=~UCSWRST;        //�������λλswrstΪ0�������������
}
