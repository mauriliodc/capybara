/* 
 * File:   globals.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:07 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

int secAcc = 0;
int bufferSize=100;
char U1Buffer[100]="";
int U1BufferPtr=0;
//  UART 1 STATES
//- 0 waiting for header
//- 1 receiving message

int U1States=0;
char header='@';




#endif	/* GLOBALS_H */

