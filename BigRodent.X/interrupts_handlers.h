/* 
 * File:   interrupts_handlers.h
 * Author: malcom
 *
 * Created on June 12, 2013, 1:43 PM
 */

#ifndef INTERRUPTS_HANDLERS_H
#define	INTERRUPTS_HANDLERS_H

#include "headers.h"
#include "timer_handler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MalComm.h"

//#include "DoubleBuffer.h"

extern struct TimerEventHandler tHandler;

extern struct PacketDecoder pDecoder;
extern int complete;

void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void) {

    TimerEventHandler_handleIRQEvents(&tHandler);
    IFS0bits.T1IF = 0;

}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI1Interrupt(void) {
    _QEI1IF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI2Interrupt(void) {
    _QEI2IF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void) {
    if(!complete){
    complete=DecoderPutChar(&pDecoder,(unsigned char)U1RXREG);
    }
    IFS0bits.U1RXIF = 0;

}

#endif	/* INTERRUPTS_HANDLERS_H */

