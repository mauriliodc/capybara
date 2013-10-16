/* 
 * File:   BasePacket.h
 * Author: malcom
 *
 * Created on July 26, 2013, 11:42 AM
 */

#ifndef BASEPACKET_H
#define	BASEPACKET_H

#define MAX_COMMANDS 16

#include "WheelVelocityCommand.h"

struct _ReceivedCommand
{
    unsigned char header;
    unsigned char code[2];
    unsigned char argument[4];
    unsigned char footer;
};

struct CommandsAndFunctions {
    unsigned char commandName[100];
    void (*callback)(void);
};

void assignCommand(const char* c, unsigned char* p) {
    strcpy((char*) p, c);
}

struct CommandsAndFunctions commandsArray[MAX_COMMANDS];

void generateCommands() {
//    assignCommand("00", commandsArray[0].commandName);
//    commandsArray[0].callback = &comando0;
//
//    assignCommand("01", commandsArray[1].commandName);
//    commandsArray[1].callback = &comando1;

    assignCommand("02", commandsArray[2].commandName);
    commandsArray[2].callback = &comando2;

    assignCommand("03", commandsArray[3].commandName);
    commandsArray[3].callback = &comando3;

//    assignCommand("04", commandsArray[4].commandName);
//    commandsArray[4].callback = &comando4;

    assignCommand("05", commandsArray[5].commandName);
    commandsArray[5].callback = &comando5;

    assignCommand("06", commandsArray[6].commandName);
    commandsArray[6].callback = &comando6;
}

#endif	/* BASEPACKET_H */

