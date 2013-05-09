/* 
 * File:   main.c
 * Author: maurilio di cicco
 *
 * Created on May 8, 2013, 12:43 PM
 */

#include <p33Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>

//NOTE
// velocità massima supportata = 40mhz
//                             = 40mips
// FOSC = The output of the oscillator (or the output of the PLL  if a PLL mode has been selected)
// FCY = FOSC/2 = device instruction clock
// FP = peripheral clock time base


/***************************************************
 *  MICROCONTROLLER CONFIGURATION
 **************************************************/

// Select external XT oscillator with PLL support
_FOSCSEL(FNOSC_PRIPLL);
// Enable clock switching and configure POSC in XT mode
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
// Disabling watchdog
//_FWDT(FWDTEN_OFF)

int main() {
    _TRISA4=0;
    _TRISB4=0;
    PORTAbits.RA4=1;
    // Configure PLL prescaler, PLL postscaler, and PLL divisor
    PLLFBD = 14; // M = 16
    CLKDIVbits.PLLPRE = 0; // N1 = 2
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    // Initiate clock switch to primary oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);
    // Wait for clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1) {};
    
    
    PORTBbits.RB4=1;
    while(1)
    {
       
    }
    return(1);
}
