/* 
 * File:   interrupts.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:07 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

char mio[] = "Board ready\n\0";
char message[] = "Message received\n\0";

void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void) {
    secAcc++;
    if (secAcc == 1000) {
        toggleLed1();
        
        //if(LATBbits.LATB14==0)LATBbits.LATB14 = 1;
        //else if(LATBbits.LATB14==1)LATBbits.LATB14 = 0;
        
        secAcc = 0;
        LED2=0;
    }

    WriteTimer1(0);
    IFS0bits.T1IF = 0;
    /* Clear Timer interrupt flag */
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
}

void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void) {
    LED2=1;
    hasToSend=1;
    
    IFS0bits.U1RXIF = 0;
}


#endif	/* INTERRUPTS_H */

