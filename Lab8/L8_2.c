/*
 * L8_2.c
 *
 *  Created on: 2021Äê8ÔÂ26ÈÕ
 *      Author: ZEL
 */
#include "msp430.h"

int main()
{
    P1SEL &= ~(BIT1 + BIT2);
    P1SEL2 &= ~(BIT1 + BIT2);
    while(1){}
}



