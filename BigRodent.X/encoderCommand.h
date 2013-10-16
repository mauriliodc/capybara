/* 
 * File:   encoderCommand.h
 * Author: malcom
 *
 * Created on October 16, 2013, 2:17 PM
 */

#ifndef ENCODERCOMMAND_H
#define	ENCODERCOMMAND_H


struct _stateCommand
{
    struct _commandBase base;
    int _state;
} stateCommand;


void encoderCommandParser(char* buffer)
{
    sscanf(buffer,"%1d",&stateCommand._state);
    printf("Called state packet");
    //printf("\nBUFFER IS: %s\n",buffer);
   // printf("done\n");
}


void encoderCommandInit(int id,struct _commandBase** c )
{
    stateCommand.base._commandID=id;
    stateCommand.base._parseFN=&encoderCommandParser;
    c[id]=&stateCommand;
    printf("STATE PACKET INIT");
}


void encoderMessageCompose(int left_tick, int right_tick)
{

}


#endif	/* ENCODERCOMMAND_H */

