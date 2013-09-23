/*
 * File:   commands.h
 * Author: mauriliodc
 *
 * Created on 16 maggio 2013, 12.04
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

extern  struct MotorController LeftMotorController;
extern struct MotorController RightMotorController;

struct _commandBase
{
    int _commandID;
    void (*_parseFN)();
};

struct _commandBase* allTheCommands[10];

struct _velocityCommand
{
    struct _commandBase base;
    int leftSpeed;
    int rightSpeed;
    int leftDir;
    int rightDir;
} velocityCommand;


void velocitcyCommandParser(char* buffer)
{
    char FIELD[4];
//    memcpy(FIELD,buffer,4);
//    velocityCommand.leftDir=atoi(FIELD);
//    memcpy(FIELD,buffer+4,4);
//    velocityCommand.rightDir=atoi(FIELD);
//    memcpy(FIELD,buffer+8,4);
//    velocityCommand.leftSpeed=atoi(FIELD);
//    memcpy(FIELD,buffer+12,4);
//    velocityCommand.rightSpeed=atoi(FIELD);

    sscanf(buffer,"%4d%4d%4d%4d",&velocityCommand.leftDir,
    &velocityCommand.rightDir,
    &velocityCommand.leftSpeed,
    &velocityCommand.rightSpeed);
    printf("\nBUFFER IS: %s\n",buffer);
    printf("RIGHT DIR: %d LEFT DIR:%d RIGHT SPEED:%d LEFT SPEED %d\n",velocityCommand.rightDir,velocityCommand.leftDir,velocityCommand.rightSpeed,velocityCommand.leftSpeed);
    if(velocityCommand.leftDir)
        MotorController_setDesiredSpeed(&LeftMotorController,velocityCommand.leftSpeed);
    else
         MotorController_setDesiredSpeed(&LeftMotorController,-velocityCommand.leftSpeed);
    if(velocityCommand.rightDir)
        MotorController_setDesiredSpeed(&RightMotorController,velocityCommand.rightSpeed);
    else
        MotorController_setDesiredSpeed(&RightMotorController,-velocityCommand.rightSpeed);
    printf("done\n");
}

void velocityCommandInit()
{
    velocityCommand.base._commandID=1;
    velocityCommand.base._parseFN=&velocitcyCommandParser;
    allTheCommands[velocityCommand.base._commandID]=&velocityCommand;
}


int getCommandCode()
{
    char codeC[2];
    memcpy(codeC,DoubleBuffer.parsingBuffer->start+1,2);
    return atoi(codeC);
}

void parseAndExecuteCommand() {

    int code=getCommandCode();
    allTheCommands[1]->_parseFN((DoubleBuffer.parsingBuffer->start+3));
    
}



#endif	/* COMMANDS_H */
