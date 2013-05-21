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

        secAcc = 0;
        LED2 = 0;
    }

    WriteTimer1(0);
    IFS0bits.T1IF = 0;
    /* Clear Timer interrupt flag */
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void) {
    LED2 = 1;
    charRX = ReadUART1();
    if (charRX != RX_header && i == 0) {
        i = 0;
    } else {
        Buf[i] = charRX;

        if (i == (MAX_BUFF - 1)) {
            i = 0;
        }//lunghezza del buffer
        else if (i < MAX_BUFF) {
            i++;
        }
        if (charRX == RX_footer) {
            RX_hasToSend = 1;
            RX_hasToParse = 1;
            i = 0;
        }
    }
    IFS0bits.U1RXIF = 0;
}


void __attribute__((__interrupt__, __no_auto_psv__)) _QEI1Interrupt(void) {
    _QEI1IF = 0;
    

}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI2Interrupt(void) {
    _QEI2IF = 0;
    
    
}

#endif	/* INTERRUPTS_H */

