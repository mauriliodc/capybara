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
    putsUART1((unsigned int*)"comando 1");
    motor1VEL=atoi((const char*)ReceivedCommand->argument);
    motor2VEL=atoi((const char*)ReceivedCommand->argument);
    LATBbits.LATB14=1;
    LATBbits.LATB12=0;
    modifyMotor1();
    modifyMotor2();
}

void comando2(void) {
    putsUART1((unsigned int*)"comando 2");
    motor1VEL=atoi((const char*)ReceivedCommand->argument);
    motor2VEL=atoi((const char*)ReceivedCommand->argument);
    LATBbits.LATB14=0;
    LATBbits.LATB12=1;
    modifyMotor1();
    modifyMotor2();
}
void comando3(void) {
    int c=motor1VEL-atoi((const char*)ReceivedCommand->argument);
    putsUART1((unsigned int*)"comando 3");
    putsUART1((unsigned int*)motor1VEL);
    turnMotor1(c);
}

void comando4(void) {
    int c=motor2VEL-atoi((const char*)ReceivedCommand->argument);
    putsUART1((unsigned int*)"comando 4");
    putsUART1((unsigned int*)motor2VEL);
    turnMotor2(c);
}
//====================================================================

void generateCommands() {
    assignCommand("00", commandsArray[0].commandName);
    commandsArray[0].callback = &comando;

    assignCommand("01", commandsArray[1].commandName);
    commandsArray[1].callback = &comando2;

    assignCommand("02", commandsArray[2].commandName);
    commandsArray[2].callback = &comando3;

    assignCommand("03", commandsArray[3].commandName);
    commandsArray[3].callback = &comando4;
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

