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
#include "MalComm.h"


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
int read=0;
int write=1;
int parse=0;
char sendingBuffer[255];

extern int complete;
struct PacketDecoder pDecoder;
struct Packet receivedPacket;

char* pEnd;
char* charToSend;
struct Packet clientPacket;
int _s1;
int _s2;

void Packet_execute(struct Packet* p){
    uint8_t id= p->id;
    if(id==SpeedPacketID){
        _s1=p->speed.leftTick;
        _s2=p->speed.rightTick;
        
    }
}

int main() {
    charToSend=0;
    pEnd=0;
    
    Micro_init();

    putsUART1((unsigned int *) "{{Micro is up and running}}\r\n=================================\n");
    initConsts();
    
    int ascii = 1;
    DecoderInit(&pDecoder,ascii);
//    while (1) {
//
//            if(U1STAbits.OERR == 1){
//                U1STAbits.OERR = 0;
//                continue;
//            }
//            if(complete){
//                parsePacket(pDecoder.buffer_start,&clientPacket,ascii);
//                pEnd=writePacket(&clientPacket,sendingBuffer,ascii);
//                charToSend = sendingBuffer;
//                IEC0bits.U1TXIE = 1;
//                complete=0;
//            }
//
//
//   }
        
    


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

    
    //=================================================

//    //PID
//    //=================================================
    PIDControlAlgorithm_init(&leftPID, 30, 10, 1, 28000, 1, 1);
    PIDControlAlgorithm_init(&rightPID, 30, 10, 1, 28000, 1, 1);
//    //=================================================
//
//    putsUART1((unsigned int *) "MOTOR 1 INIT\r\n");
//    MotorController_init(&RightMotorController,
//            &ec, 0,
//            &pwmc, 0,
//            1 << 14, (unsigned int*) 0x02CC,
//            (struct ControlAlgorithm*) &leftPID, leftPID._period);
//
//    MotorController_setMaxPositiveSpeedIncrement(&RightMotorController, 155);
//    MotorController_setMaxNegativeSpeedIncrement(&RightMotorController, 155);
//
//    putsUART1((unsigned int *) "MOTOR 2 INIT\r\n");
//    MotorController_init(&LeftMotorController,
//            &ec, 1,
//            &pwmc, 1,
//            1 << 12, (unsigned int*) 0x02CC,
//            (struct ControlAlgorithm*) &rightPID, rightPID._period);
//
//    MotorController_setMaxPositiveSpeedIncrement(&LeftMotorController, 155);
//    MotorController_setMaxNegativeSpeedIncrement(&LeftMotorController, 155);
//
//    putsUART1((unsigned int *) "DIFFERENTIAL ODOMETRY INIT\r\n");
//    DifferentialDriveOdometryHandler_init(&odo,
//            0.4, //baseling
//            &LeftMotorController, &RightMotorController,
//            0.1, 0.1, //radius
//            0.000349066, 0.000349066, //radians per ticks
//            10, //period
//            &TransmissionBuffer); //trasmissionbuffer
//
//
//    //TRANSMISSION BUFFER
////    putsUART1((unsigned int *) "TRANSMISSION BUFFER INIT\r\n");
////    transmissionBuffer_init(&TransmissionBuffer, 200);
//
//
//    //TIMER TEST
//    //=================================================
//    putsUART1((unsigned int *) "TIMER INIT\r\n");
//    TimerEventHandler_init(&tHandler);
//    putsUART1((unsigned int *) "RIGHT MOTOR EVENT\r\n");
//    TimerEventHandler_setEvent(&tHandler, 0, &RightMotorController.event);
//    putsUART1((unsigned int *) "LEFT MOTOR EVENT\r\n");
//    TimerEventHandler_setEvent(&tHandler, 1, &LeftMotorController.event);
//    putsUART1((unsigned int *) "ODO EVENT\r\n");
//    TimerEventHandler_setEvent(&tHandler, 2, &odo._base.event);
////    putsUART1((unsigned int *) "TRANSMISSION EVENT\n");
////    TimerEventHandler_setEvent(&tHandler, 3, &TransmissionBuffer.event);
//
//    //=================================================
//
//    putsUART1((unsigned int *) "STARTING SCHEDULER\r\n");
//    TimerEventHandler_setRunning(&tHandler, 1);
//    putsUART1((unsigned int *) "INITIALIZING DOUBLE BUFFER SCHEDULER\r\n");
//    putsUART1((unsigned int *) "STARTING MAIN LOOP\r\n");


    
//    MotorController_setDesiredSpeed(&LeftMotorController,5);
//    MotorController_setDesiredSpeed(&RightMotorController,5);
      
        while (RUN_CACAPYBARA_RUN) {
            //====================================================

            if(tiMerda==10){
            int c1=ControlAlgorithm_update(&leftPID,POS1CNT,_s1);
            int c2=ControlAlgorithm_update(&rightPID,POS2CNT,_s2);
            int LdirectionPin=(1 << 14);
            unsigned int* LdirectionPTR = (unsigned int*) 0x02CC;
            int RdirectionPin=(1 << 12);
            unsigned int* RdirectionPTR= (unsigned int*) 0x02CC;
            if(c1>0){
                (*LdirectionPTR) = (*(LdirectionPTR)) | LdirectionPin;
            }else{
                (*LdirectionPTR) = (*(LdirectionPTR)) & (LdirectionPin^0b1111111111111111);
            }
            if(c2>0){
                (*RdirectionPTR) = (*(RdirectionPTR)) | RdirectionPin;
            }else{
                (*RdirectionPTR) = (*(RdirectionPTR)) & (RdirectionPin^0b1111111111111111);
            }
            SetDCMCPWM1(1, c1,0);
            SetDCMCPWM1(2, c2,0);
            }

            //====================================================
            //TimerEventHandler_handleScheduledEvents(&tHandler);
            if(IEC0bits.U1TXIE==0){
            struct SpeedPacket sp;
            sp.leftTick=(POS1CNT);
            sp.rightTick=(POS2CNT);
            struct Packet pa;
            pa.id=SpeedPacketID;
            pa.speed=sp;
            pEnd=writePacket(&pa,sendingBuffer,1);
            charToSend = sendingBuffer;
            IEC0bits.U1TXIE = 1;
            }
            if (U1STAbits.OERR) U1STAbits.OERR = 0;
             if(complete){

                 parsePacket(pDecoder.buffer_start,&clientPacket,ascii);
//                 pEnd=writePacket(&clientPacket,sendingBuffer,1);
//                 charToSend=sendingBuffer;
//                 IEC0bits.U1TXIE = 1;
              
                 Packet_execute(&clientPacket);
//                pEnd=writePacket(&clientPacket,sendingBuffer,ascii);
//                charToSend = sendingBuffer;
//                IEC0bits.U1TXIE = 1;
                complete=0;
            }
    
        }
        return (EXIT_SUCCESS);
}




