/*
 * L3_PassiveBuzzer.c
 *
 *  Created on: 2021Äê8ÔÂ24ÈÕ
 *      Author: ZEL
 */
#include <msp430.h>
void delay(unsigned int );
void ring(unsigned int);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P2SEL = 0;
    P2SEL2 = 0;
    P2DIR |= BIT0;

    P1SEL = 0;
    P1SEL2 = 0;
    P1DIR &= ~(BIT0 + BIT1 + BIT2);
    P1REN |= (BIT0 + BIT1 + BIT2);
    P1OUT |= (BIT0 + BIT1 + BIT2);

    while(1)
    {
        if((P1IN & BIT0) == 0)
        {
            ring(0x30);
        }
        else if((P1IN & BIT1) == 0)
        {
            ring(0x20);
        }
        else if((P1IN & BIT2) == 0)
        {
            ring(0x10);
        }
    }
}

void ring(unsigned int L)
{
    unsigned int j;
    for(j = 0; j < 5;j++)
    {
        P2OUT |= BIT0;
        delay(L*4);
        P2OUT &= ~BIT0;
        delay(L);
    }

}

void delay(unsigned int numloop)
{
    unsigned int j;
    for(j = 0;j < numloop; j++);
}


