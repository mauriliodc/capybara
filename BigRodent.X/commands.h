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
//INTERNALS
//====================================================================
struct _ReceivedCommand
{
    unsigned char header;
    unsigned char code[2];
    unsigned char argument[4];
    unsigned char footer;
};
struct _ReceivedCommand* ReceivedCommand;

extern struct MotorController LeftMotorController;
extern struct MotorController RightMotorController;

struct CommandsAndFunctions {
    unsigned char commandName[100];
    void (*callback)(void);
};

struct CommandsAndFunctions commandsArray[7];

extern struct DifferentialDriveOdometer odo;

int compareCommands(unsigned char* ReceivedCommandCode, unsigned char* CommandCode) {

    if (strncmp((const char*) ReceivedCommandCode, (const char*) CommandCode, 2) == 0) return 1;
    else return 0;


}

void assignCommand(const char* c, unsigned char* p) {
    strcpy((char*) p, c);
}
//COMMANDS
//====================================================================
//SETTO VELOCITA' E DIREZIONE AD ENTRAMBI I MOTORI

void comando0(void) {
    //int c = atoi((const char*) ReceivedCommand->argument);
    
}

//SETTO VELOCITA' E DIREZIONE AD ENTRAMBI I MOTORI

void comando1(void) {
    //int c = atoi((const char*) ReceivedCommand->argument);
   
}

void comando2(void) {
    int c = atoi((const char*) ReceivedCommand->argument);
    MotorController_setDesiredSpeed(&RightMotorController,c);
    
}

void comando3(void) {
    int c = atoi((const char*) ReceivedCommand->argument);
    MotorController_setDesiredSpeed(&RightMotorController,-c);
    
}

void comando4(void) {
    odo._base._globalPose._x=0;
    odo._base._globalPose._y=0;
    odo._base._globalPose._theta=0;
    odo._base._pose._x=0;
    odo._base._pose._y=0;
    odo._base._pose._theta=0;

}

void comando5(void) {
    int c = atoi((const char*) ReceivedCommand->argument);
    MotorController_setDesiredSpeed(&LeftMotorController,c);
}

void comando6(void) {
    int c = atoi((const char*) ReceivedCommand->argument);
    MotorController_setDesiredSpeed(&LeftMotorController,-c);
}
//====================================================================

void generateCommands() {
    assignCommand("00", commandsArray[0].commandName);
    commandsArray[0].callback = &comando0;

    assignCommand("01", commandsArray[1].commandName);
    commandsArray[1].callback = &comando1;

    assignCommand("02", commandsArray[2].commandName);
    commandsArray[2].callback = &comando2;

    assignCommand("03", commandsArray[3].commandName);
    commandsArray[3].callback = &comando3;

    assignCommand("04", commandsArray[4].commandName);
    commandsArray[4].callback = &comando4;

    assignCommand("05", commandsArray[5].commandName);
    commandsArray[5].callback = &comando5;

    assignCommand("06", commandsArray[6].commandName);
    commandsArray[6].callback = &comando6;
}

void parseAndExecuteCommand() {
    int i = 0;
    for (i = 0; i < 7; i++) {
        if (compareCommands(ReceivedCommand->code, commandsArray[i].commandName)) {
            commandsArray[i].callback();
            return;
        };
    }
}



#endif	/* COMMANDS_H */
