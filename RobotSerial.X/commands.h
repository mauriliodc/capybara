/* 
 * File:   commands.h
 * Author: mauriliodc
 *
 * Created on 16 maggio 2013, 12.04
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#include "globals.h"



//INTERNALS
//====================================================================

struct CommandsAndFunctions {
    unsigned char commandName[MAX_BUFF];
    void (*callback)(void);
};

struct CommandsAndFunctions commandsArray[COMMAND_SIZE];

int compareCommands(unsigned char* ReceivedCommandCode, unsigned char* CommandCode) {

    if( strncmp((const char*)ReceivedCommandCode,(const char*)CommandCode,2)==0 ) return 1;
    else return 0;


}

void assignCommand(const char* c, unsigned char* p) {
    strcpy((char*) p, c);
}
//COMMANDS
//====================================================================

void comando(void) {
    putsUART1((unsigned int *) "MOTORE 1: ");
    putsUART1((unsigned int *) ReceivedCommand->argument);
    modifyMotor1(atoi((const char*)ReceivedCommand->argument));
}

void comando2(void) {
    putsUART1((unsigned int *) "MOTORE 2: ");
    putsUART1((unsigned int *) ReceivedCommand->argument);
    modifyMotor2(atoi((const char*)ReceivedCommand->argument));
}
//====================================================================

void generateCommands() {
    assignCommand("00", commandsArray[0].commandName);
    commandsArray[0].callback = &comando;

    assignCommand("01", commandsArray[1].commandName);
    commandsArray[1].callback = &comando2;
}

void parseAndExecuteCommand() {
    int i = 0;
    for (i = 0; i < COMMAND_SIZE; i++) {
        if (compareCommands(ReceivedCommand->code, commandsArray[i].commandName)) {
            commandsArray[i].callback();
            return;
        };
    }
}



#endif	/* COMMANDS_H */

