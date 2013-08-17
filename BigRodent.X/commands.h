/*
 * File:   commands.h
 * Author: mauriliodc
 *
 * Created on 16 maggio 2013, 12.04
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#include "motor_controller.h"
#include "odometer.h"
#include "baseComm.h"

extern struct command* commandList[MAX_COMMANDS];

//INTERNALS
//====================================================================
struct _ReceivedCommand
{
    unsigned char header;
    unsigned char code[2];
    unsigned char argument[4];
    unsigned char footer;
};

//struct _ReceivedCommand* ReceivedCommand;
extern struct MotorController LeftMotorController;
extern struct MotorController RightMotorController;
extern struct DifferentialDriveOdometer odo;

int getCommandCode()
{
    char codeC[2];
    memcpy(codeC,CommandBuf+1,2);
    return atoi(codeC);
}

void parseAndExecuteCommand() {

    int code=getCommandCode();
    if(code<MAX_COMMANDS && commandList[code]!=0)
    {
        commandList[code]->parser(CommandBuf,WheelVelocityCommand);
    }
    
}



#endif	/* COMMANDS_H */
