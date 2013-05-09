/* 
 * File:   settings.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:05 PM
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

//NOTE
// velocità massima supportata = 80mhz = 40mips
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

_FWDT(FWDTEN_OFF)


#define FIN 10000000
#define N1 2
#define N2 2
#define M 32
#define FOSC FIN*(M/(N1*N2)) //is in the range of 12.5 MHz to 80 MHz, which generates device operating speeds of 6.25-40 MIPS
#define FCY FOSC/2 // FCY defines the MIPS
#define TMR1_VALUE 40000 //1 millisecond

//Led configuration
#define LED1 PORTAbits.RA4
#define LED2 PORTBbits.RB4
#define LED1CONF _TRISA4
#define LED2CONF _TRISB4

void clock_settings() {
    // Configure PLL prescaler, PLL postscaler, and PLL divisor
    OSCTUN = 0;
    PLLFBD = 30; // M = 32
    CLKDIVbits.PLLPRE = 0; // N1 = 2
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    // Initiate clock switch to primary oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);
    // Wait for clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1) {
    };
}

void led_settings() {
    //tristate settings as output
    LED1CONF = 0;
    LED2CONF = 0;
    LED1 = 0;
    LED2 = 0;
}

void timer1_confguration() {
    ConfigIntTimer1(T1_INT_PRIOR_1 & T1_INT_ON);
    WriteTimer1(0);
    OpenTimer1(T1_ON &
            T1_GATE_OFF &
            T1_IDLE_STOP &
            T1_PS_1_1 &
            T1_SYNC_EXT_OFF &
            T1_SOURCE_INT,
            TMR1_VALUE);
}
#endif	/* SETTINGS_H */

