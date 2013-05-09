/* 
 * File:   utils.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:08 PM
 */

#ifndef UTILS_H
#define	UTILS_H

void toggleLed1() {
    if (LED1)LED1 = 0;
    else if (LED1 == 0)LED1 = 1;
}

void toggleLed2() {
    if (LED2 == 1)LED2 = 0;
    else if (LED2 == 0)LED2 = 1;
}

#endif	/* UTILS_H */

