/*
 * File:   commands.h
 * Author: mauriliodc
 *
 * Created on 16 maggio 2013, 12.04
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#define COMMANDS_SIZE 2
#define HEADER '#'
#define FOOTER '%'

struct _commandBase
{
    int _commandID;
    void (*_parseFN)();
    //void (*_initFN)(struct _commandBase* c);
};

#include "velocityCommand.h"
#include "encoderCommand.h"

struct _commandBase* allTheCommands[COMMANDS_SIZE];


int getCommandCode()
{
    char codeC[2];
    memcpy(codeC,DoubleBuffer.parsingBuffer->start+1,2);
    return atoi(codeC);
}

void parseAndExecuteCommand() {

    int code=getCommandCode();
    if(code<=COMMANDS_SIZE)
        allTheCommands[code]->_parseFN((DoubleBuffer.parsingBuffer->start+3)); //+3 to ignore the header and the command code
    
}





#endif	/* COMMANDS_H */
