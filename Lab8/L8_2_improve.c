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
{   WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
//做实验时，如果有示波器
//可在P1.0、P1.4引脚输出时钟ACLK、SMCLK，以便观察时钟频率,修改波特率寄存器设置
//    P1SEL |= BIT0+BIT4;
//    P1SEL2 |=~( BIT0+BIT4);
//    P1DIR |= BIT0+BIT4;

   UARTA0_init( );               //初始化串口
   //P1SEL &= ~(BIT1 + BIT2);
   //P1SEL2 &= ~(BIT1 + BIT2);
    P2SEL &= ~(BIT0 + BIT1);
    P2SEL2 &= ~(BIT0 + BIT1);
    P1SEL &= ~BIT0;
    P1SEL2 &= ~BIT0;
    P2DIR |= (BIT0 + BIT1); //2.0,2.1输出
    P2OUT |= (BIT0 + BIT1);
    P1DIR &= ~BIT0;
    P1REN |= BIT0;
    P1OUT |= BIT0;//1.0输入，上拉电阻
    P1IES |= BIT0;
    P1IFG &= ~BIT0;
    P1IE |= BIT0; //1.0中断设置

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
    if ( (P1IFG&BIT0)!=0 ) //判断是P1.0上的中断
    {
        unsigned int j;
        for(j = 0;j < 10;j++)
        {
            while((IFG2&UCA0TXIFG)==0);     //检测发送缓冲是否空
            UCA0TXBUF=hint[j];
        }//发出提示音

        while(1)
        {
            char _get;
            while((IFG2&UCA0RXIFG)==0);     //检测接收缓冲器是否满
            _get = UCA0RXBUF;       //接收一个数据并保存
            switch(_get)
            {
            case 'F'://全亮
                P2OUT &= ~(BIT0 + BIT1);
                break;
            case 'B'://全闪
                while((IFG2&UCA0RXIFG)==0)
                {
                    P2OUT &= ~(BIT0 + BIT1);
                    delay(0x5000);
                    P2OUT |= (BIT0 + BIT1);
                    delay(0x5000);
                }
                break;
            case 'L'://1闪
                P2OUT |= BIT1;
                while((IFG2&UCA0RXIFG)==0)
                {
                    P2OUT &= ~BIT0;
                    delay(0x5000);
                    P2OUT |= BIT0;
                    delay(0x5000);
                }
                break;
            case 'R'://2闪
                P2OUT |= BIT0;
                while((IFG2&UCA0RXIFG)==0)
                {
                    P2OUT &= ~BIT1;
                    delay(0x5000);
                    P2OUT |= BIT1;
                    delay(0x5000);
                }
                break;
            case 'S'://全灭
                P2OUT |= (BIT0 + BIT1);
                break;
            default:
                for(j = 0;j < 5;j++)
                {
                    while((IFG2&UCA0TXIFG)==0);     //检测发送缓冲是否空
                    UCA0TXBUF=hint_error[j];
                }//发出提示音
                break;
            }
        }
    }
    P1IFG &=~BIT0;
}

void  UARTA0_init( )
{   UCA0CTL1|= UCSWRST;      //置软件复位位swrst为1
    P1SEL |= BIT1+BIT2;         	//置P1.1、P1.2为串行接口收、发引脚功能
    P1SEL2 |= BIT1+BIT2;        	//
//数据格式选用上电复位设置：无校验，8位数据，1个停止位，异步串行通信
    UCA0CTL1|=UCSSEL0+UCRXEIE; //波特率时钟选择上电复位时的ACLK，32.768KHz，对错均收
    UCA0BR0 =3;              //波特率9600
    UCA0BR1 = 0;
    UCA0MCTL=UCBRF_0+UCBRS_3;
    UCA0CTL1 &=~UCSWRST;        //置软件复位位swrst为0，串口设置完毕
}
