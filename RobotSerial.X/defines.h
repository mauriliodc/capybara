/* 
 * File:   defines.h
 * Author: malcom
 *
 * Created on May 13, 2013, 11:49 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

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


//UART
#define MAX_BUFF 40


//COMMANDS
#define COMMAND_SIZE 4
#define COMMAND_LENGHT 2


//ENCODES

#define TICKENC1 500
#define TICKENC2 500
#define RATIOGEAR1 17
#define RATIOGEAR2 17
#define BASELINE 0.40
#define RADIUSWHEEL1 0.06
#define RADIUSWHEEL2 0.06
#define DEGREEPERTICK 0.02
#define PI 3.14
#define METERPERTICK1 DEGREEPERTICK*2*RADIUSWHEEL1
#define METERPERTICK2 DEGREEPERTICK*2*RADIUSWHEEL1

#endif	/* DEFINES_H */
