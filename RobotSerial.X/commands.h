/* 
 * File:   commands.h
 * Author: mauriliodc
 *
 * Created on 16 maggio 2013, 12.04
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#include "globals.h"
#include "pid.h"
#include "motorController.h"

//EXTERNS
extern struct PWM pwm1;
extern struct PWM pwm2;
extern struct PWMController pwmController;
extern struct MotorController motorController;

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
//SETTO VELOCITA' E DIREZIONE AD ENTRAMBI I MOTORI
void comando0(void) {
  
}

//SETTO VELOCITA' E DIREZIONE AD ENTRAMBI I MOTORI
void comando1(void) {

}
void comando2(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    pid.p1->request=(float)c;
    
}

void comando3(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    pid.p1->request=(float)-c;
}

void comando4(void) {
    
}


void comando5(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    
    pid.p2->request=(float)c;
}

void comando6(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    
    pid.p2->request=(float)-c;
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
    for (i = 0; i < COMMAND_SIZE; i++) {
        if (compareCommands(ReceivedCommand->code, commandsArray[i].commandName)) {
            commandsArray[i].callback();
            return;
        };
    }
}



#endif	/* COMMANDS_H */

