/* 
 * File:   stopCommand.h
 * Author: malcom
 *
 * Created on 6 febbraio 2015, 0.08
 */

#ifndef STOPCOMMAND_H
#define	STOPCOMMAND_H
#include "OutputBuffer.h"

struct _stopCommand
{
    struct _commandBase base;
    int stop;

}stopCommand;

void stopCommandParser(char* buffer){
    sscanf(buffer,"%1d",&stopCommand.stop);
    if(stopCommand.stop==1){
        exit(0);
    }
}



void stopCommandInit(int id,struct _commandBase** c){
    stopCommand.base._commandID=id;
    stopCommand.base._parseFN=&stopCommandParser;
    c[id]=(struct _commandBase*)&stopCommand;
    printf("STOP COMMAND PACKET INIT");
}

#endif	/* STOPCOMMAND_H */