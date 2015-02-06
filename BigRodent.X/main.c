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
#include "DoubleBuffer.h"
#include "OutputBuffer.h"
#include "Eeprom.h"
#include "configurationData.h"
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

//TODO TEMPORANEO
char CommandBuf[100];
char Buf[100];
int i = 0;
int RX_hasToSend = 0;
int RX_hasToParse = 0;
int RX_hasParsed = 0;
int RX_isParsing = 0;
int canIRun = 0;
int main() {

    
    Micro_init();

    velocityCommandInit(1, allTheCommands);
    encoderCommandInit(0, allTheCommands);
    stopCommandInit(2,allTheCommands);
    startCommandInit(3,allTheCommands);
    
    outputBuffer_Init();

    putsUART1((unsigned int *) "{{Micro is up and running}}\r\n=================================\n");

    struct _configuration conf;
    int state = initEeprom();
    //EEPROM HAS DATA
    if (state == 1) {
        readConfigurationFromEeprom(&conf);
        debugConfigurationDataToSerial(&conf);
    }        //EEPOM NEW
    else {
        conf.leftMotor.decrement = 1;
        conf.leftMotor.increment = 2;
        conf.leftMotor.motorMode = Complementary;
        conf.leftPid.kd = 3;
        conf.leftPid.ki = 4;
        conf.leftPid.kp = 5;
        conf.leftPid.kwindup = 6;
        conf.leftPid.period = 7;
        conf.rightMotor.decrement = 1;
        conf.rightMotor.increment = 2;
        conf.rightMotor.motorMode = Independant;
        conf.rightPid.kd = 3;
        conf.rightPid.ki = 4;
        conf.rightPid.kp = 5;
        conf.rightPid.kwindup = 6;
        conf.rightPid.period = 7;
        conf.pwm.period = 8;
        conf.odometry.baseline = 1.0f;
        conf.odometry.period = 9;
        conf.odometry.radiansPerTickLeft = 2.0f;
        conf.odometry.radiansPerTickRight = 2.0f;
        conf.odometry.radiusLeft = 3.0f;
        conf.odometry.radiusRight = 4.0f;
        writeConfigurationToEeprom(&conf);
    }
  

    //ENCODER
    //=================================================
    struct Encoder e1;
    struct Encoder e2;
    EncoderController_init(&ec);
    ec.encoders[0] = &e1;
    ec.encoders[1] = &e2;
    Encoder_init(&e1, (uint8_t*) 0x01E4);
    Encoder_init(&e2, (uint8_t*) 0x01F4);
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

    //PID
    //=================================================
    PIDControlAlgorithm_init(&leftPID, 30, 10, 1, 28000, 10, 1);
    PIDControlAlgorithm_init(&rightPID, 30, 10, 1, 28000, 10, 1);
    //=================================================

    putsUART1((unsigned int *) "MOTOR 1 INIT\r\n");
    MotorController_init(&RightMotorController,
            &ec, 0,
            &pwmc, 0,
            1 << 14, (unsigned int*) 0x02CC,
            (struct ControlAlgorithm*) &leftPID, leftPID._period);

    MotorController_setMaxPositiveSpeedIncrement(&RightMotorController, 155);
    MotorController_setMaxNegativeSpeedIncrement(&RightMotorController, 155);

    putsUART1((unsigned int *) "MOTOR 2 INIT\r\n");
    MotorController_init(&LeftMotorController,
            &ec, 1,
            &pwmc, 1,
            1 << 12, (unsigned int*) 0x02CC,
            (struct ControlAlgorithm*) &rightPID, rightPID._period);

    MotorController_setMaxPositiveSpeedIncrement(&LeftMotorController, 155);
    MotorController_setMaxNegativeSpeedIncrement(&LeftMotorController, 155);

    putsUART1((unsigned int *) "DIFFERENTIAL ODOMETRY INIT\r\n");
    DifferentialDriveOdometryHandler_init(&odo,
            0.4, //baseling
            &LeftMotorController, &RightMotorController,
            0.1, 0.1, //radius
            0.000349066, 0.000349066, //radians per ticks
            10, //period
            &TransmissionBuffer); //trasmissionbuffer


    //TRANSMISSION BUFFER
    putsUART1((unsigned int *) "TRANSMISSION BUFFER INIT\r\n");
    transmissionBuffer_init(&TransmissionBuffer, 200);


    //TIMER TEST
    //=================================================
    putsUART1((unsigned int *) "TIMER INIT\r\n");
    TimerEventHandler_init(&tHandler);
    putsUART1((unsigned int *) "RIGHT MOTOR EVENT\r\n");
    TimerEventHandler_setEvent(&tHandler, 0, &RightMotorController.event);
    putsUART1((unsigned int *) "LEFT MOTOR EVENT\r\n");
    TimerEventHandler_setEvent(&tHandler, 1, &LeftMotorController.event);
    putsUART1((unsigned int *) "ODO EVENT\r\n");
    TimerEventHandler_setEvent(&tHandler, 2, &odo._base.event);
    putsUART1((unsigned int *) "TRANSMISSION EVENT\n");
    TimerEventHandler_setEvent(&tHandler, 3, &TransmissionBuffer.event);

    //=================================================

    putsUART1((unsigned int *) "STARTING SCHEDULER\r\n");
    TimerEventHandler_setRunning(&tHandler, 1);
    putsUART1((unsigned int *) "INITIALIZING DOUBLE BUFFER SCHEDULER\r\n");
    DoubleBuffer_Init();
    putsUART1((unsigned int *) "STARTING MAIN LOOP\r\n");

    canIRun=1;
    while(!canIRun){
        if (U1STAbits.OERR) U1STAbits.OERR = 0;
        if (RX_hasToParse) {
            parseAndExecuteCommand();
            DoubleBuffer_resetParsingBuffer();
            RX_hasToParse = 0;
        }
        outputBuffer_flush();
    }
    while (RUN_CACAPYBARA_RUN) {
        TimerEventHandler_handleScheduledEvents(&tHandler);
        if (U1STAbits.OERR) U1STAbits.OERR = 0;
        if (RX_hasToParse) {
            parseAndExecuteCommand();
            DoubleBuffer_resetParsingBuffer();
            RX_hasToParse = 0;
        }
        outputBuffer_flush();

    }
    return (EXIT_SUCCESS);
}

