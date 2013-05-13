/* 
 * File:   settings.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:05 PM
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

//NOTE
// velocit� massima supportata = 80mhz = 40mips
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

//UART BAUDRATE
#define BAUDRATE 115200
#define BRGVAL (FCY/(4*BAUDRATE))-1

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

void pin_remapping() {
    //PPSUnLock;
    //PPSOutput(OUT_FN_PPS_U1TX, OUT_PIN_PPS_RP3); //UART1TX su RP3
    //PPSInput (PPS_U1RX,PPS_RP2);
    //PPSLock;

    asm volatile ( "mov #OSCCONL, w1 \n"
	"mov #0x45, w2 \n"
	"mov #0x57, w3 \n"
	"mov.b w2, [w1] \n"
	"mov.b w3, [w1] \n"
	"bclr OSCCON, #6 ");

    //UART
    RPINR18bits.U1RXR = 2;  //INPUT
    RPOR1bits.RP3R = 3;     //OUTPUT

    asm volatile ( "mov #OSCCONL, w1 \n"
	"mov #0x45, w2 \n"
	"mov #0x57, w3 \n"
	"mov.b w2, [w1] \n"
	"mov.b w3, [w1] \n"
	"bset OSCCON, #6");

    AD1PCFGL = 0xFFFF; //FONDAMENTALE PER LA UART, DEVO CONFIGURARE QUEI PIN COME DIGITALI, DI BASE SONO ANALOGICI
}

void init_uart1() {
    CloseUART1();
    ConfigIntUART1(UART_RX_INT_EN // RX interrupt enable
            & UART_TX_INT_EN // TX interrupt disable
            & UART_RX_INT_PR2 // RX interrupt priority 2
            & UART_TX_INT_PR2); // TX interrupt priority 2
    /* Configuration du registre U1MODE */



    unsigned int U1MODEvalue = UART_EN //Bit 15 : Tx, Rx enable
            & UART_IDLE_CON //Bit 13: continue module operation in Idle mode
            & UART_IrDA_DISABLE //Bit 12 : IrDA encoder and decoder disabled
            & UART_MODE_FLOW //Bit 11 : Flow Control mode
            & UART_UEN_00 //Bit 8 & 9: TX,RX enabled, CTS,RTS not
            & UART_EN_WAKE //Bit 7 : UARTx continues to sample the UxRX pin; interrupt generated on falling edge; bit cleared in hardware on following rising edge.
            & UART_DIS_LOOPBACK //Bit 6 : Loopback disabled
            & UART_DIS_ABAUD //Bit 5 : Baud rate measurement disabled or completed
            & UART_UXRX_IDLE_ONE //Bit 4 : Idle state = 1
            & UART_BRGH_FOUR //Bit 3 : 16 clocks per bit period
            & UART_NO_PAR_8BIT //Bit 1 & 2 : 8-bit data, no parity
            & UART_1STOPBIT; //Bit 0 : One Stop Bit
    /* Configuration du registre U1STA */
    unsigned int U1STAvalue = UART_INT_TX //Bit 15 & 13 : Interrupt when character is transfered
            & UART_IrDA_POL_INV_ZERO //Bit 14 : IrDA config
            & UART_SYNC_BREAK_DISABLED //Bit 11 : Sync Break disabled
            & UART_TX_ENABLE //Bit 10 : Transmit enabled
            & UART_TX_BUF_NOT_FUL //Bit 9 : Transmit buffer is not full
            & UART_INT_RX_CHAR //Bit 6 & 7 : Interrupt when any character is received
            & UART_ADR_DETECT_DIS //Bit 5 : Adress Detect mode disabled
            & UART_RX_OVERRUN_CLEAR; //Bit 1 *Read Only Bit* et CLEAR
    OpenUART1(U1MODEvalue, U1STAvalue, BRGVAL);
}
#endif	/* SETTINGS_H */

