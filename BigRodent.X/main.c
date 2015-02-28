/* 
 * File:   main.c
 * Author: malcom
 *
 * Created on June 12, 2013, 12:31 PM
 */

#include <p33FJ128MC802.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "Eeprom.h"
#include "configurationData.h"
#include "mal_comm.h"
#include "mal_buffer.h"

/*
 * 
 */

#define RUN_CACAPYBARA_RUN 1

struct PIDControlAlgorithm leftPID;
struct PIDControlAlgorithm rightPID;
struct EncoderController ec;
struct PWMController pwmc;
struct TimerEventHandler tHandler;
struct MotorController LeftMotorController;
struct MotorController RightMotorController;
struct DifferentialDriveOdometer odo;
struct trasmissionBuffer TransmissionBuffer;
struct Double_Buffer outputBuffer;


extern int complete;
struct Packet_Decoder pDecoder;
int ascii;
char* pEnd;
char* charToSend;
struct Packet clientPacket;

//*************************************************************************
//Test handlers for the test event
//*************************************************************************
//void upper(struct TimerEvent* t) {
//    if (LED1 == 1) {
//        LED1 = 0;
//    } else {
//        LED1 = 1;
//    }
//}
//
//void lower(struct TimerEvent* t) {
//    if (LED1 == 1) {
//        LED2 = 0;
//    } else {
//        LED2 = 1;
//    }
//    putsUART1((unsigned int *) "ping\n");
//}
//*************************************************************************

int main() {
    charToSend = 0;
    pEnd = 0;
    Double_Buffer_init(&outputBuffer);
    Micro_init();
    ascii = 1;
    putsUART1((unsigned int *) "{{Micro is up and running}}\r\n=================================\n");
    initConsts();


    Packet_Decoder_init(&pDecoder, ascii);

    //ENCODER
    //=================================================
    struct Encoder e1;
    struct Encoder e2;
    EncoderController_init(&ec);
    ec.encoders[0] = &e1;
    ec.encoders[1] = &e2;
    Encoder_init(&e1, (uint16_t*) 0x01E4);
    Encoder_init(&e2, (uint16_t*) 0x01F4);
    //=================================================


    //PWM
    //=================================================
    struct PWM p1;
    struct PWM p2;
    p1.dutyCycle = 0;
    p1.period = 0;
    p2.dutyCycle = 0;
    p2.period = 0;
    pwmc.pwms[0] = &p1;
    pwmc.pwms[1] = &p2;
    //PWM
    //39khz, page 14 at http://ww1.microchip.com/downloads/en/DeviceDoc/70187E.pdf
    PWMController_init(&pwmc, 1024);
    PIDControlAlgorithm_init(&leftPID, 40, 20, 1, 18000, 2, 1);
    PIDControlAlgorithm_init(&rightPID, 40, 20, 1, 18000, 2, 1);

    MotorController_init(&RightMotorController,
            &ec, 0,
            &pwmc, 0,
            1 << 14, (unsigned int*) 0x02CC,
            (struct ControlAlgorithm*) &leftPID, leftPID._period);
    MotorController_setMaxPositiveSpeedIncrement(&RightMotorController, 155);
    MotorController_setMaxNegativeSpeedIncrement(&RightMotorController, 155);

    MotorController_init(&LeftMotorController,
            &ec, 1,
            &pwmc, 1,
            1 << 12, (unsigned int*) 0x02CC,
            (struct ControlAlgorithm*) &rightPID, rightPID._period);
    MotorController_setMaxPositiveSpeedIncrement(&LeftMotorController, 155);
    MotorController_setMaxNegativeSpeedIncrement(&LeftMotorController, 155);

    DifferentialDriveOdometryHandler_init(&odo,
            0.4, //baseling
            &LeftMotorController, &RightMotorController,
            0.1, 0.1, //radius
            0.000349066, 0.000349066, //radians per ticks
            2, //period
            &TransmissionBuffer); //trasmissionbuffer

    TimerEventHandler_init(&tHandler);

    //*************************************************************************
    //Test event
    //*************************************************************************
    //use this to debug and testing purposes (especially on the timing part)
    //*************************************************************************
    //TimerEvent testTimerEvent;
    //testTimerEvent._period = 1000;
    //testTimerEvent._upperHalf = upper;
    //testTimerEvent._lowerHalf = lower;
    //TimerEventHandler_setEvent(&tHandler, 0, &testTimerEvent);
    //*************************************************************************
    TimerEventHandler_setEvent(&tHandler, 0, &RightMotorController.event);
    TimerEventHandler_setEvent(&tHandler, 1, &LeftMotorController.event);
    TimerEventHandler_setEvent(&tHandler, 2, &odo._base.event);

    TimerEventHandler_setRunning(&tHandler, 1);

    while (RUN_CACAPYBARA_RUN) {
        TimerEventHandler_handleScheduledEvents(&tHandler);
        if (IEC0bits.U1TXIE == 0) {
            Double_Buffer_swapBuffers(&outputBuffer);
            charToSend = outputBuffer._ready;
            pEnd = outputBuffer._readyEndPtr;
            if (charToSend != pEnd)
                IEC0bits.U1TXIE = 1;
            else
                IEC0bits.U1TXIE = 0;
        }
        //        if (charToSend == pEnd) {
        //            IEC0bits.U1TXIE = 0;
        //        }

        if (U1STAbits.OERR) U1STAbits.OERR = 0;
        if (complete) {
            Packet_parse(pDecoder.buffer_start, &clientPacket, ascii);
            Packet_execute(&clientPacket);
            complete = 0;
        }

    }
    return (EXIT_SUCCESS);
}


