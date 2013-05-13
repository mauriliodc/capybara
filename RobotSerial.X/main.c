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
#include <pwm12.h>

#include "defines.h"
#include "globals.h"
#include "settings.h"
#include "utils.h"
#include "interrupts.h"

int main() {
    clock_settings();
    led_settings();
    timer1_confguration();
    pin_remapping();
    init_uart1();
    LED1 = 0;
    DelayN1ms(2000);
    putsUART1((unsigned int *) mio);
    //enableMotors();


    int sender = 0;
    while (1) {
        if (U1STAbits.OERR) { // non mi interessano i caratteri ev. in attesa...
            U1STAbits.OERR = 0;
        }
        if (U1STAbits.FERR == 1) {
            continue;
        }

        while (hasToSend) {
            U1TXREG = Buf[sender];
            while (U1STAbits.UTXBF == 1);
            Buf[sender]=' ';
            if (sender == (MAX_BUFF - 1)) {
                hasToSend = 0;
                sender = 0;
            } else {
                sender = sender + 1;
            }


        }
    }
    return (1);
}
