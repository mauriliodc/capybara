/* 
 * File:   dspic_settings.h
 * Author: malcom
 *
 * Created on June 12, 2013, 12:38 PM
 */

#ifndef DSPIC_SETTINGS_H
#define	DSPIC_SETTINGS_H

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



//FUNCTIONS
void Clock_init();
void Pin_init();
void Uart1_init();
void Micro_init();
void Led_init();
void Timer1_init();
void Timer2_init();
#endif	/* DSPIC_SETTINGS_H */

