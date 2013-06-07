/* 
 * File:   main.c
 * Author: malcom
 *
 * Created on May 8, 2013, 12:43 PM
 */

int acc;
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

#include "signatures.h"

#include "settings.h"
#include "utils.h"
#include "interrupts.h"
#include "commands.h"
#include "pid.h"
#include "motorController.h"
#include "pwmController.h"
#include "fancyTimer.h"

#include "callbacks.h"



int main() {

    acc=0;
    int step=1;
    clock_settings();
    led_settings();
    timer1_confguration();
    pin_remapping();
    init_uart1();
    LED1 = 0;
    DelayN1ms(2000);
    putsUART1((unsigned int *) mio);
    
    generateCommands();

    anEvent.millisecs=100;
    anEvent.repetitions=0;
    anEvent.callback=&anEventCallback;
    anEvent.runInHandler=0;
    anEvent.executeNow=0;


    ledEvent.millisecs=200;
    ledEvent.repetitions=-1;
    ledEvent.callback=&ledEventCallback;
    ledEvent.runInHandler=0;
    ledEvent.executeNow=0;

    
    
    //ENCODER INIT
    //---------------------------------------------------------------------------
    initEncoder(&encoder1,(unsigned int*)0x01E4,&enc1Event,step,&encoder1Callback);
    initEncoder(&encoder2,(unsigned int*)0x01F4,&enc2Event,step,&encoder2Callback);
    initEncoderController(&encoderController,&encoder1,&encoder2);
    //---------------------------------------------------------------------------
    
    //PWM INIT
    //---------------------------------------------------------------------------
    PWMinit(&pwm1,(unsigned int*)0x02CC,1 << 14); //16384 = 14th bit high
    PWMinit(&pwm2,(unsigned int*)0x02CC,1 << 12);//4096 = 12th bit high
    PWMinitController(&pwmController,&pwm1,&pwm2);
    //---------------------------------------------------------------------------

    //PID INIT
    //---------------------------------------------------------------------------
    PIDinitPID(&pidmotor1,
    80,        //I
    80,          //P
    0.2,       //D
    (float)step/1000);
    PIDinitPID(&pidmotor2,
    80,        //I
    80,        //P
    0.2,       //D
    (float)step/1000);
    InitPIDController(&pid,&pidmotor1,&pidmotor2,&pidUpdateEvent,step);
    //---------------------------------------------------------------------------

    //MOTOR CONTROLLER INIT
    //-------------------------------------------------------------------------------------------------------
    initMotorController(&motorController, &leftMotor, &rightMotor, &pwmController, &encoderController, &pid);
    //-------------------------------------------------------------------------------------------------------

    //TIMER EVENTS
    bigTimer.events=0;
    struct timerEvent* tArr[FANCYTIMEREVENTS];
    tArr[0] = &anEvent;
    tArr[1] = &ledEvent;
    tArr[2] = &enc1Event;
    tArr[3] = &enc2Event;
    tArr[4] = &pidUpdateEvent;
    bigTimer.timerEventsArray=tArr;
    bigTimer.events=FANCYTIMEREVENTS;

    
    while (1) {
        handleTimerEvents(&bigTimer);
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

            ReceivedCommand = (struct _ReceivedCommand*) CommandBuf;

            //memcpy(argument, ReceivedCommand->argument, 4 * sizeof (unsigned char));
            //memcpy(command, ReceivedCommand->code, 2 * sizeof (unsigned char));
    
            putsUART1((unsigned int *) "Comando ricevuto");
            putsUART1((unsigned int *) CommandBuf);
            putsUART1((unsigned int *) "\n");
            parseAndExecuteCommand();
            //memset(Buf, 0, sizeof (Buf));
            RX_hasToParse = 0;
        }

        

//        if(secAcc==5000)
//        {
//        //sprintf(posPacket, "%04d:%04d", POS1CNT,POS2CNT);
//        sprintf(posPacket,"%f",metersW1);
//        putsUART1((unsigned int*) "SPEED1: ");
//        putsUART1((unsigned int*) posPacket);
//
//        sprintf(posPacket,"%f",metersW2);
//        putsUART1((unsigned int*) " SPEED2: ");
//        putsUART1((unsigned int*) posPacket);
//        //putsUART1((unsigned int*) "\n");
//
//
//        sprintf(posPacket,"%d",QEI1CONbits.UPDN);
//        putsUART1((unsigned int*) " DIR: ");
//        putsUART1((unsigned int*) posPacket);
//
//
//        putsUART1((unsigned int*) " POS1CNT: ");
//        sprintf(posPacket,"%d",(int)POS1CNT);
//        putsUART1((unsigned int*) posPacket);
//        putsUART1((unsigned int*) "\n");
//
//        }


    }
    return (1);
}
