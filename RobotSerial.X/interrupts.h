/* 
 * File:   interrupts.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:07 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void) {
    secAcc++;
    if (secAcc == 1000) {
        toggleLed2();
        U1TXREG = 'a';
        secAcc = 0;
    }
    WriteTimer1(0);
    IFS0bits.T1IF = 0;
    /* Clear Timer interrupt flag */
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0;
}


#endif	/* INTERRUPTS_H */

