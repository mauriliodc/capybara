/* 
 * File:   interrupts_handlers.h
 * Author: malcom
 *
 * Created on June 12, 2013, 1:43 PM
 */

#ifndef INTERRUPTS_HANDLERS_H
#define	INTERRUPTS_HANDLERS_H
#include "timer_handler.h"



void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void) {

    
    IFS0bits.T1IF = 0;
    
}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI1Interrupt(void) {
    _QEI1IF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI2Interrupt(void) {
    _QEI2IF = 0;
}


#endif	/* INTERRUPTS_HANDLERS_H */

