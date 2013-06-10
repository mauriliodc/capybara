/* 
 * File:   interrupts.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:07 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H


extern struct timerController bigTimer;

#include "pid.h"

char posPacket[9];

char mio[] = "Board ready\n\0";
char message[] = "Message received\n\0";
char PID[10];

float velocityMotor1=0;
float velocityMotor2=0;

float requestVelocityMotor1=0;
float requestVelocityMotor2=0;

int tick1=0;
int tick2=0;
int inc=0;
int inc2=0;

extern struct PID pidmotor1;
extern struct PID pidmotor2;
int wrapAround1=0;
int wrapAround2=0;
float metersW1=0;
float metersW2=0;
float tmp=0;
void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void) {
    triggerEvent(&bigTimer);
    WriteTimer1(0);
    IFS0bits.T1IF = 0;
    /* Clear Timer interrupt flag */
}


//DISABILITATO
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
            memcpy(CommandBuf,Buf,MAX_BUFF);
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

