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
#include "mal_comm.h"

//#include "DoubleBuffer.h"

extern struct TimerEventHandler tHandler;

extern struct Packet_Decoder pDecoder;
extern int complete;

extern char* packetBuffer[2];
extern char buffer_1[255];
extern char buffer_2[255];
extern int read;
extern int write;
extern int parse;

extern char*  pEnd;
extern char* charToSend;
int tiMerda=0;
void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;
    TimerEventHandler_handleIRQEvents(&tHandler);
}



void __attribute__((__interrupt__, __no_auto_psv__)) _QEI1Interrupt(void) {
    _QEI1IF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI2Interrupt(void) {
    _QEI2IF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
    if (charToSend == pEnd){
            U1TXREG=0xA;
            IEC0bits.U1TXIE = 0;
    }else{
        U1TXREG=*charToSend;
        charToSend++;      
    }
   
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0;
    if(!complete)
    complete=Packet_Decoder_putChar(&pDecoder,(unsigned char)U1RXREG);
    

}

#endif	/* INTERRUPTS_HANDLERS_H */

