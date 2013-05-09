/* 
 * File:   main.c
 * Author: malcom
 *
 * Created on May 8, 2013, 12:43 PM
 */

#include <p33Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <timer.h>
#include <pps.h>
#include <uart.h>

#include "globals.h"
#include "settings.h"
#include "utils.h"
#include "interrupts.h"


//#define BAUDRATE 57600
//#define BRGVAL (FCY/(BAUDRATE*4))-1

#define BAUDRATE 115200
#define BRGVAL ((FCY/BAUDRATE)/16)-1


int main() {
    clock_settings();
    led_settings();
    timer1_confguration();

    //PPSUnLock;
    //PPSOutput(OUT_FN_PPS_U1TX, OUT_PIN_PPS_RP3);
    //PPSInput (PPS_U1RX,PPS_RP2);
    //PPSLock;
    asm volatile ( "mov #OSCCONL, w1 \n"
	"mov #0x45, w2 \n"
	"mov #0x57, w3 \n"
	"mov.b w2, [w1] \n"
	"mov.b w3, [w1] \n"
	"bclr OSCCON, #6 ");
    // Assign U1Tx To Pin RP2
    RPOR1bits.RP3R = 3;
    
    asm volatile ( "mov #OSCCONL, w1 \n"
	"mov #0x45, w2 \n"
	"mov #0x57, w3 \n"
	"mov.b w2, [w1] \n"
	"mov.b w3, [w1] \n"
	"bset OSCCON, #6");
    /*
    CloseUART1();
    ConfigIntUART1(UART_RX_INT_DIS & UART_RX_INT_PR3  & UART_TX_INT_DIS & UART_TX_INT_PR3 );
    unsigned int U1MODE_VALUE = UART_EN &
                                UART_IDLE_STOP &
                                UART_DIS_WAKE  &
                                UART_DIS_LOOPBACK &
                                UART_DIS_ABAUD &
                                UART_NO_PAR_8BIT &
                                UART_BRGH_FOUR &
                                UART_1STOPBIT;
    unsigned int U1STA_VALUE =  UART_INT_TX  &
                                UART_TX_ENABLE &
                                UART_INT_RX_CHAR &
                                UART_ADR_DETECT_DIS &
                                UART_RX_OVERRUN_CLEAR;
    */
    U1MODEbits.STSEL = 0; // 1 Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8 data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 0; // Low Speed mode
    U1BRG = BRGVAL; // BAUD Rate Setting for 9600
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX Character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 1; // Enable UART TX Interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    LED1 = 0;
    //OpenUART1(U1MODE_VALUE, U1STA_VALUE, 5);
    LED1 = 1;

    while (1)
    {
        
        //WriteUART1(0xFF);
    }
    return (1);
}
