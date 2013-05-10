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
    enableMotors();
    while (1) 
    {
        
    }
    return (1);
}
