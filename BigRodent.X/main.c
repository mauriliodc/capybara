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


char* packetBuffer[2];
char buffer_1[255];
char buffer_2[255];
int read = 0;
int write = 1;
int parse = 0;
char sendingBuffer[255];

extern int complete;
struct Packet_Decoder pDecoder;
struct Packet receivedPacket;

char* pEnd;
char* charToSend;
struct Packet clientPacket;
int _s1;
int _s2;

int main() {
    charToSend = 0;
    pEnd = 0;

    Micro_init();

    putsUART1((unsigned int *) "{{Micro is up and running}}\r\n=================================\n");
    initConsts();

    int ascii = 1;
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
    PIDControlAlgorithm_init(&leftPID, 30, 10, 1, 28000, 1, 1);
    PIDControlAlgorithm_init(&rightPID, 30, 10, 1, 28000, 1, 1);
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
            10, //period
            &TransmissionBuffer); //trasmissionbuffer

    TimerEventHandler_init(&tHandler);
    TimerEventHandler_setEvent(&tHandler, 0, &RightMotorController.event);
    TimerEventHandler_setEvent(&tHandler, 1, &LeftMotorController.event);
    TimerEventHandler_setEvent(&tHandler, 2, &odo._base.event);

    TimerEventHandler_setRunning(&tHandler,1);
    while (RUN_CACAPYBARA_RUN) {

        TimerEventHandler_handleScheduledEvents(&tHandler);
//        if (IEC0bits.U1TXIE == 0) {
//            struct SpeedPacket sp;
//            sp.leftTick = (POS1CNT);
//            sp.rightTick = (POS2CNT);
//            struct Packet pa;
//            pa.id = SpeedPacketID;
//            pa.speed = sp;
//            pEnd = writePacket(&pa, sendingBuffer, 1);
//            charToSend = sendingBuffer;
//            IEC0bits.U1TXIE = 1;
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


//int Packet_execute(struct Packet* p){
//    MotorController_setDesiredSpeed(&LeftMotorController,p->speed.leftTick);
//    MotorController_setDesiredSpeed(&RightMotorController,p->speed.rightTick);
//    return 0;
//}

