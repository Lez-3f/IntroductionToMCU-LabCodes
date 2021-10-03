#include "msp430.h"
void delay();

int main ( void )
{
    WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
    P2SEL=0; //设置端口P2的8个引脚为基本输入输出功能
    P2SEL2=0;
    P2OUT = 0;
    P2DIR=0xff; //设置端口 1 为输出方向
    while(1){
        P2OUT=~P2OUT; //将端口 1 的值取反后输出
        delay( ); //调用函数延时
    }

}

void delay( ) //延时函数
{
    unsigned int j;
    for (j=0;j<0xffff;j++);
}
