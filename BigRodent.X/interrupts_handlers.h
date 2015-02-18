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
//#include "DoubleBuffer.h"

extern struct TimerEventHandler tHandler;

extern char CommandBuf[100];
extern char Buf[100];
int MAX_BUFF = 100;
extern int i;
unsigned char charRX;
char RX_header = '$';
char RX_footer = '%';
extern int RX_hasToSend;
extern int RX_hasToParse;
extern struct PacketDecoder decoder;
int cnt=0;

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
int wait_flag = 0;
//
void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void) {
//
//    charRX = (unsigned char) ReadUART1();
//    if (RX_hasToParse == 0) {
//        printf("%x",charRX);
//        complete = PacketDecoder_putChar(&decoder, (unsigned char)charRX);
//        if (complete) { //packet is complete?
//            RX_hasToParse = 1;
//        }
//    }
//
//    /*
//    if (!RX_hasToParse) {
//        charRX = ReadUART1();
//        if (charRX != RX_header && DoubleBuffer.readingBuffer->curr == DoubleBuffer.readingBuffer->start) {
//            DoubleBuffer.readingBuffer->curr = DoubleBuffer.readingBuffer->start;
//        } else {
//            //Buf[i] = charRX;
//     *(DoubleBuffer.readingBuffer->curr) = charRX;
//            if (DoubleBuffer.readingBuffer->curr < DoubleBuffer.readingBuffer->end) {
//                DoubleBuffer.readingBuffer->curr++;
//            } else {
//                DoubleBuffer.readingBuffer->curr = DoubleBuffer.readingBuffer->start;
//            }
//        }
//
//        if (charRX == RX_footer) {
//
//     *(DoubleBuffer.readingBuffer->curr) = '\0';
//
//            DoubleBuffer_swapBuffers();
//            RX_hasToParse = 1;
//            DoubleBuffer_resetReadingBuffer();
//
//
//        }
//    }
//     */
    IFS0bits.U1RXIF = 0;

}

#endif	/* INTERRUPTS_HANDLERS_H */

