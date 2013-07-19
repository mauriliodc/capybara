/* 
 * File:   main.c
 * Author: malcom
 *
 * Created on June 12, 2013, 12:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "packets.h"



/*
 * 
 */
struct PIDControlAlgorithm leftPID;
struct PIDControlAlgorithm rightPID;
struct EncoderController ec;
struct PWMController pwmc;
struct TimerEventHandler tHandler;
struct MotorController LeftMotorController;
struct MotorController RightMotorController;
struct DifferentialDriveOdometer odo;
struct trasmissionBuffer TransmissionBuffer;

//TODO TEMPORANEO
char CommandBuf[100];
char Buf[100];
int i = 0;
int RX_hasToSend = 0;
int RX_hasToParse = 0;



#define MAX_BUFFER_SIZE 200
StatePacket outState;

char outputBuffer[MAX_BUFFER_SIZE];
char inputBuffer[MAX_BUFFER_SIZE];

HexMessage outputStream;
HexMessage inputStream;

void stringFN(const unsigned char* c) {
    putsUART1((unsigned int*) "string callback\n");
}


//void PacketHandler_stringExecuteFn(const unsigned char*);

extern StringExecuteFn PacketHandler_stringExecuteFn;
char packetBuffer [MAX_BUFFER_SIZE]; // where we write our deserialized packet
PacketHeader * parsedPacket = (PacketHeader *) packetBuffer;

void PacketHandlerLoop(HexMessage* inputStream, HexMessage* outputStream){
  int error=0;
  //HexMessage_reset(outputStream);
  //putsUART1((unsigned int*)inputStream->start);

  while(! error &&
	inputStream->current<inputStream->end){
    enum HexMessageStatus status=Packet_read(inputStream,parsedPacket);
    if (status==Ok ) {
      if (parsedPacket->type>=0){
      	//Packet_print(parsedPacket);
	Packet_execute(parsedPacket, outputStream);
      }


    } else  {
      printf("Parsing error ");
      printf("%d \n",status);
      putsUART1((unsigned int*)inputStream->start);

      error = 1;
    }
    
  }

}




int main() {



    Micro_init();
    generateCommands();
    putsUART1((unsigned int *) ">>>>>>>>>>>>>>>>>>>>>>>>>>>Micro is up and running<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");


    memset(buffa, '\0', 100);
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

    struct PWM p1;
    p1.dutyCycle = 0;
    p1.period = 0;
    struct PWM p2;
    p2.dutyCycle = 0;
    p2.period = 0;

    pwmc.pwms[0] = &p1;
    pwmc.pwms[1] = &p2;

    PWMController_init(&pwmc, 1024); //39khz

    //=================================================


    //PID INIT
    //=================================================
    PIDControlAlgorithm_init(&leftPID, 10, 5, 1, 800, 2, 2);
    PIDControlAlgorithm_init(&rightPID, 10, 5, 1, 800, 2, 2);
    //=================================================
    putsUART1((unsigned int *) "MOTOR INIT\n");
    MotorController_init(&RightMotorController,
            &ec, 0,
            &pwmc, 0,
            1 << 14, (unsigned int*) 0x02CC,
            (struct ControlAlgorithm*) &leftPID, leftPID._period);
    putsUART1((unsigned int *) "MOTOR INIT\n");
    MotorController_init(&LeftMotorController,
            &ec, 1,
            &pwmc, 1,
            1 << 12, (unsigned int*) 0x02CC,
            (struct ControlAlgorithm*) &rightPID, rightPID._period);
    putsUART1((unsigned int *) "DIFFERENTIAL INIT\n");
    DifferentialDriveOdometryHandler_init(&odo,
            0.4, //baseling
            &LeftMotorController, &RightMotorController,
            0.1, 0.1, //radius
            0.000349066, 0.000349066, //radians per ticks
            200, //period
            &TransmissionBuffer); //trasmissionbuffer


    //TRANSMISSION BUFFER
    putsUART1((unsigned int *) "TRANSMISSION INIT\n");
    transmissionBuffer_init(&TransmissionBuffer, 200);


    //TIMER TEST
    //=================================================
    putsUART1((unsigned int *) "TIMER INIT\n");
    TimerEventHandler_init(&tHandler);
    putsUART1((unsigned int *) "RIGHT MOTOR EVENT\n");
    TimerEventHandler_setEvent(&tHandler, 0, &RightMotorController.event);
    putsUART1((unsigned int *) "LEFT MOTOR EVENT\n");
    TimerEventHandler_setEvent(&tHandler, 1, &LeftMotorController.event);
    putsUART1((unsigned int *) "ODO EVENT\n");
    TimerEventHandler_setEvent(&tHandler, 2, &odo._base.event);
    putsUART1((unsigned int *) "TRANSMISSION EVENT\n");
    TimerEventHandler_setEvent(&tHandler, 3, &TransmissionBuffer.event);

    //=================================================


    //MotorController_setDesiredSpeed(&RightMotorController,50);
    //MotorController_setDesiredSpeed(&LeftMotorController,50);
    putsUART1((unsigned int *) "STARTING SCHEDULER\n");
    TimerEventHandler_setRunning(&tHandler, 1);


    //PACKET HANDLER
    putsUART1((unsigned int *) "STARTING MESSAGE HANDLER\n");
    StatePacket_initVoid(&outState);
    Packets_init();
    PacketHandler_setStringExecuteFn(stringFN);
    StatePacket_initHeader(&outState);
    // construct  a buffer
    HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
    memset(outputBuffer, 0, MAX_BUFFER_SIZE);
    HexMessage_setBuffer(&inputStream, inputBuffer, MAX_BUFFER_SIZE);
    memset(inputBuffer, 0, MAX_BUFFER_SIZE);

    putsUART1((unsigned int *) "STARTING MAIN LOOP\n");




    //--------------------------------------------------------------------------
    while (1) {
        TimerEventHandler_handleScheduledEvents(&tHandler);
        //putsUART1((unsigned int*) "$00FF\n%");
        if (U1STAbits.OERR) U1STAbits.OERR = 0;
            U1STAbits.OERR = 0;
            if(inputStream.current > inputStream.start)
            {
                HexMessage_rewind(&inputStream);                
                PacketHandlerLoop(&inputStream, &outputStream);
                HexMessage_reset(&inputStream);
            }
            if (outputStream.current > outputStream.start) {
                *outputStream.current++ = '\n';
                *outputStream.current++ = 0;
                putsUART1((unsigned int*) "$");
                putsUART1((unsigned int*) outputStream.start);
                putsUART1((unsigned int*) "%");
                HexMessage_reset(&outputStream);
            }


        }
        return (EXIT_SUCCESS);
    }

