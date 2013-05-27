/* 
 * File:   globals.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:07 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

//MOTORI

int motor1VEL=5000;
int motor2VEL=5000;

int secAcc = 0;
int millisec20=0;

int bufferSize=100;
char U1Buffer[100]="";
int U1BufferPtr=0;
//  UART 1 STATES
//- 0 waiting for header
//- 1 receiving message

int U1States=0;
int RX_hasToSend=0;
int RX_hasToParse=0;
unsigned char Buf[MAX_BUFF];
unsigned char commandCode[2];

struct _ReceivedCommand
{
    unsigned char header;
    unsigned char code[2];
    unsigned char argument[4];
    unsigned char footer;
};
struct _ReceivedCommand* ReceivedCommand;

unsigned char charRX;
int i=0;
char RX_header='$';
char RX_footer='%';



//ENCODER

int enc1=0;
int enc2=0;

#endif	/* GLOBALS_H */

