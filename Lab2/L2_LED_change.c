#include "msp430.h"
void delay();
void Loop1();
void Loop2();

int main()
{
	WDTCTL = WDTPW + WDTHOLD;  //关闭看门狗
	P2DIR = 0xff;				//设置端口二为输出方向
	P2SEL = 0; 		//设置端口P2的8个引脚为基本输入输出功能
    P2SEL2 = 0;
    P2OUT = 0xff;
    while(1)
    {
    	Loop1();
    	Loop2();
    }    
}

void Loop1()
{
	unsigned int loop1[8] = {~BIT5, ~BIT6, ~BIT1, ~BIT2, ~BIT3, ~BIT0, ~BIT7, ~BIT4};
	unsigned int j;
	for(j = 0; j < 8; j++)
	{
		P2OUT = loop1[j];
		delay();
	}
}

void Loop2()
{
	unsigned int loop2[4] = {~(BIT5 + BIT3), ~(BIT4 + BIT2), ~(BIT6 + BIT0), ~(BIT7 + BIT1)};
	unsigned int j;
	for(j = 0; j < 4; j++)
	{
		P2OUT = loop2[j];
		delay();
	}
}

void delay()
{
	unsigned int j;
    for(j = 0;j < 0xffff; j++);
}