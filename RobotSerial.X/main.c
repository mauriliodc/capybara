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
#include <string.h>
#include <qei.h>

#include "defines.h"
#include "globals.h"
#include "settings.h"
#include "utils.h"
#include "interrupts.h"
#include "commands.h"
#include "pid.h"
#include "motorController.h"
#include "pwmController.h"
#include "fancyTimer.h"
//#include "fancyTimer.h"

struct PWM pwm1; //SINISTRO
struct PWM pwm2; //DESTRO
struct PWMController pwmController;

struct PID pidmotor1;
struct PID pidmotor2;

struct timerController bigTimer;
struct timerEvent anEvent;
struct timerEvent ledEvent;


void anEventCallback(void) {
putsUART1((unsigned int *) "it's me! mario!\n");
}

void ledEventCallback(void) {
toggleLed1();
}

int main() {

    clock_settings();
    led_settings();
    timer1_confguration();
    pin_remapping();
    init_uart1();
    LED1 = 0;
    DelayN1ms(2000);
    putsUART1((unsigned int *) mio);
    initEncoders();
    generateCommands();

    anEvent.millisecs=5000;
    anEvent.repetitions=-1;
    anEvent.callback=&anEventCallback;

    ledEvent.millisecs=200;
    ledEvent.repetitions=-1;
    ledEvent.callback=&ledEventCallback;

    bigTimer.events=2;

    struct timerEvent* tArr[2];
    tArr[0] = &anEvent;
    tArr[1] = &ledEvent;
    bigTimer.timerEventsArray=tArr;
    
    
  
    PWMinit(&pwm1,(unsigned int*)0x02CC,1 << 14); //16384 = 14th bit high
    PWMinit(&pwm2,(unsigned int*)0x02CC,1 << 12);//4096 = 12th bit high
    PWMinitController(&pwmController,&pwm1,&pwm2);
   
    
    PIDinitPID(&pidmotor1,
    0.0,        //I
    2,          //P
    0.00,       //D
    0.02);

    PIDinitPID(&pidmotor2,
    0.0,        //I
    2,          //P
    0.000,      //D
    0.02);


    
    
    while (1) {
        if (U1STAbits.OERR) { // non mi interessano i caratteri ev. in attesa...
            U1STAbits.OERR = 0;
        }
        if (U1STAbits.FERR == 1) {
            continue;
        }

        /*
        while (RX_hasToSend) {
            U1TXREG = Buf[sender];
            while (U1STAbits.UTXBF == 1);
            //Buf[sender] = '\0';
            if (sender == (MAX_BUFF - 1)) {
                RX_hasToSend = 0;

                sender = 0;
            } else {
                sender = sender + 1;
            }
        }
         */
        if (RX_hasToParse) {

            ReceivedCommand = (struct _ReceivedCommand*) Buf;

            //memcpy(argument, ReceivedCommand->argument, 4 * sizeof (unsigned char));
            //memcpy(command, ReceivedCommand->code, 2 * sizeof (unsigned char));
    
            putsUART1((unsigned int *) "Comando ricevuto");
            putsUART1((unsigned int *) Buf);
            parseAndExecuteCommand();
            memset(Buf, 0, sizeof (Buf));
            RX_hasToParse = 0;
        }

        

        if(secAcc==5000)
        {
        //sprintf(posPacket, "%04d:%04d", POS1CNT,POS2CNT);
        sprintf(posPacket,"%f",metersW1);
        putsUART1((unsigned int*) "SPEED1: ");
        putsUART1((unsigned int*) posPacket);

        sprintf(posPacket,"%f",metersW2);
        putsUART1((unsigned int*) " SPEED2: ");
        putsUART1((unsigned int*) posPacket);
        //putsUART1((unsigned int*) "\n");


        sprintf(posPacket,"%d",QEI1CONbits.UPDN);
        putsUART1((unsigned int*) " DIR: ");
        putsUART1((unsigned int*) posPacket);


        putsUART1((unsigned int*) " POS1CNT: ");
        sprintf(posPacket,"%d",(int)POS1CNT);
        putsUART1((unsigned int*) posPacket);
        putsUART1((unsigned int*) "\n");
        
        }


    }
    return (1);
}
