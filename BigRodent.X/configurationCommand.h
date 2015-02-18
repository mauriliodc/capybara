/* 
 * File:   configurationCommand.h
 * Author: malcom
 *
 * Created on 6 febbraio 2015, 0.07
 */

#ifndef CONFIGURATIONCOMMAND_H
#define	CONFIGURATIONCOMMAND_H

#include "OutputBuffer.h"

struct _configurationCommand
{
    struct _commandBase base;
    int address;
    int isInt;
    int intvalue;
    float floatValue;
    

}configurationCommand;

void configurationCommandParser(char* buffer){
    //sscanf(buffer,"%2d%1d",(&configurationCommand.address));
   
}



void configurationCommandInit(int id,struct _commandBase** c){
    configurationCommand.base._commandID=id;
    configurationCommand.base._parseFN=&configurationCommandParser;
    c[id]=(struct _commandBase*)&configurationCommand;
    printf("CONFIGURATION COMMAND PACKET INIT");
}


#endif	/* CONFIGURATIONCOMMAND_H */

