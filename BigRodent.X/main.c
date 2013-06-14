/* 
 * File:   main.c
 * Author: malcom
 *
 * Created on June 12, 2013, 12:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

/*
 * 
 */

EventCallback inner() {
    char tmp[50] = "inner\n";
    putsUART1((unsigned int *) tmp);
    return 0;
}

EventCallback outer() {
    char tmp[50] = "outer\n";
    putsUART1((unsigned int *) tmp);
    return 0;
}

int main() {
    Micro_init();
    //DelayN1s(1);
    putsUART1((unsigned int *) "Micro is up and running\n");


    //ENCODER TEST
    //=================================================
    struct Encoder e1;
    struct Encoder e2;
    struct EncoderController ec;

    EncoderController_init(&ec);
    ec.encoders[0] = &e1;
    ec.encoders[1] = &e2;

    Encoder_init(&e1, (uint8_t*) 0x01E4);
    Encoder_init(&e2, (uint8_t*) 0x01F4);
    //=================================================


    //PWM TEST
    //=================================================
    struct PWMController pwmc;
    pwmc.minPeriod = 0;
    pwmc.maxPeriod = 5000;
    struct PWM p1;
    p1.dutyCycle = 0;
    p1.period = 0;
    struct PWM p2;
    p2.dutyCycle = 0;
    p2.period = 0;

    pwmc.pwms[0] = &p1;
    pwmc.pwms[1] = &p2;

    PWMController_init(&pwmc, 1999);
    //PWMController_setPeriod(&pwmc,1000,1);
    //PWMController_setPeriod(&pwmc,1000,2);
    PWMController_setDutycycle(&pwmc, 0, 10);
    PWMController_setDutycycle(&pwmc, 1, 30);
    
    //=================================================



    //TIMER TEST
    //=================================================
    struct TimerEvent t1;
    


    struct TimerEventHandler tHandler;

    tHandler._events[0]->_flags = ENABLED;
    tHandler._events[0]->_period = 2;
    tHandler._events[0]->_upperHalf=inner(&t1);
    tHandler._events[0]->_lowerHalf=outer(&t1);
    tHandler._events[0]->_lastLowerHalfExecutionTime=0;
    tHandler._events[0]->_lastTickUpperHalfExecuted=0;
    tHandler._events[0]->_lastUpperHalfExecutionTime=0;
    tHandler._events[0]->_toBeExecuted=1;

    TimerEventHandler_init(&tHandler);
    TimerEventHandler_setRunning(&tHandler,1);

    //=================================================

    while (1) {
        
        TimerEventHandler_handleScheduledEvents(&tHandler);
        //RUNNING TESTS
        //***********************************************************************************************
        //        char tmp[50];
        //        sprintf(tmp, "ENCODERS %d %d \n", EncoderController_ticks(&ec, 0), EncoderController_ticks(&ec, 1));
        //        putsUART1((unsigned int *) tmp);
        //        sprintf(tmp, "PERIOD %d %d \n", PWMController_period(&pwmc, 0), PWMController_period(&pwmc, 1));
        //        putsUART1((unsigned int *) tmp);
        //        sprintf(tmp, "DUTY %d %d \n", PWMController_dutycycle(&pwmc, 0), PWMController_dutycycle(&pwmc, 1));
        //        putsUART1((unsigned int *) tmp);
        //***********************************************************************************************

    }
    return (EXIT_SUCCESS);
}
