/* 
 * File:   commands.h
 * Author: mauriliodc
 *
 * Created on 16 maggio 2013, 12.04
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#include "globals.h"

//EXTERNS
extern struct PWM pwm1;
extern struct PWM pwm2;
extern struct PWMController pwmController;


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
    
    motor1VEL=atoi((const char*)ReceivedCommand->argument);
    motor2VEL=atoi((const char*)ReceivedCommand->argument);
    LATBbits.LATB14=1;
    LATBbits.LATB12=1;
    modifyMotor1();
    modifyMotor2();
}

//SETTO VELOCITA' E DIREZIONE AD ENTRAMBI I MOTORI
void comando1(void) {
    
    motor1VEL=atoi((const char*)ReceivedCommand->argument);
    motor2VEL=atoi((const char*)ReceivedCommand->argument);
    LATBbits.LATB14=0;
    LATBbits.LATB12=0;
    modifyMotor1();
    modifyMotor2();
}
void comando2(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    PWMControllerSetSpeed(&pwmController,c,1,1);
}

void comando3(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    PWMControllerSetSpeed(&pwmController,c,1,2);
}

void comando4(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    requestVelocityMotor1=(float)c;
    requestVelocityMotor2=(float)c;
}


void comando5(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    
    PWMControllerSetSpeed(&pwmController,c,-1,1);
}

void comando6(void) {
    int c=atoi((const char*)ReceivedCommand->argument);
    
    PWMControllerSetSpeed(&pwmController,c,-1,2);
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

