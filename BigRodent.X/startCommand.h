/* 
 * File:   startCommand.h
 * Author: malcom
 *
 * Created on 6 febbraio 2015, 0.07
 */

#ifndef STARTCOMMAND_H
#define	STARTCOMMAND_H
#include "OutputBuffer.h"

extern int canIRun;

struct _startCommand
{
    struct _commandBase base;
    int start;

}startCommand;

void startCommandParser(char* buffer){
    sscanf(buffer,"%1d",&startCommand.start);
    if(startCommand.start==1){
        canIRun=1;
    }
}



void startCommandInit(int id,struct _commandBase** c){
    startCommand.base._commandID=id;
    startCommand.base._parseFN=&startCommandParser;
    c[id]=(struct _commandBase*)&startCommand;
    printf("START COMMAND PACKET INIT");
}

#endif	/* STARTCOMMAND_H */

