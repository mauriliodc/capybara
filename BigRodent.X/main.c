/* 
 * File:   main.c
 * Author: malcom
 *
 * Created on June 12, 2013, 12:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "motor_controller.h"

/*
 * 
 */
struct PIDControlAlgorithm pid;
struct EncoderController ec;
struct PWMController pwmc;
struct TimerEventHandler tHandler;
struct MotorController LeftMotorController;

//void inner(struct TimerEvent* t) {
//    toggleLed1();
//    PWMController_setDutycycle(&pwmc, 0, ControlAlgorithm_update((struct ControlAlgorithm*)(&pid),EncoderController_setTicks(&ec,0,0),10));
//}
//
//void outer(struct TimerEvent* t) {
//    char a[200];
//    sprintf(a,"P: %d I: %d  D: %d  ERR: %d TICK: %d MEASUR: %d PID: %d EXEC: %d \n",   pid._Pi,
//                                                                    pid._I,
//                                                                    pid._D,
//                                                                    pid._error,
//                                                                    *ec.encoders[0]->ticks,
//                                                                    pid._base._measure,
//                                                                    pid._base._control,
//                                                                    t->_lastUpperHalfExecutionTime);
//    putsUART1((unsigned int *) a);
//}



int main() {
    Micro_init();
    //DelayN1s(1);
    putsUART1((unsigned int *) "Micro is up and running\n");


    //ENCODER TEST
    //=================================================
    struct Encoder e1;
    struct Encoder e2;
    

    EncoderController_init(&ec);
    ec.encoders[0] = &e1;
    ec.encoders[1] = &e2;

    Encoder_init(&e1, (uint8_t*) 0x01E4);
    Encoder_init(&e2, (uint8_t*) 0x01F4);
    //=================================================


    //PWM TEST
    //=================================================
    
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
//    PWMController_setDutycycle(&pwmc, 0, 10);
//    PWMController_setDutycycle(&pwmc, 1, 20);
    //=================================================


    //PID TEST
    //=================================================
    PIDControlAlgorithm_init(&pid,10,5,1,500,2);
    //=================================================

    MotorController_init(   &LeftMotorController,
                            &ec,   0,
                            &pwmc, 0,
                            1 << 14,(unsigned int*)0x02CC,
                            (struct ControlAlgorithm*)&pid,2);


    //TIMER TEST
    //=================================================
    TimerEventHandler_init(&tHandler);
    TimerEventHandler_setEvent(&tHandler,0,&LeftMotorController.event);
    TimerEventHandler_setRunning(&tHandler,1);
    //=================================================


    MotorController_setDesiredSpeed(&LeftMotorController,-50);

    while (1) {
        
        TimerEventHandler_handleScheduledEvents(&tHandler);


        //RUNNING TESTS
        //***********************************************************************************************
//                char tmp[50];
//                sprintf(tmp, "ENCODERS %d %d \n", EncoderController_ticks(&ec, 0), EncoderController_ticks(&ec, 1));
//                putsUART1((unsigned int *) tmp);
//                sprintf(tmp, "PERIOD %d %d \n", PWMController_period(&pwmc, 0), PWMController_period(&pwmc, 1));
//                putsUART1((unsigned int *) tmp);
//                sprintf(tmp, "DUTY %d %d \n", PWMController_dutycycle(&pwmc, 0), PWMController_dutycycle(&pwmc, 1));
//                putsUART1((unsigned int *) tmp);
        //***********************************************************************************************

    }
    return (EXIT_SUCCESS);
}

