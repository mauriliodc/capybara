#include "baseComm.h"

struct command* commandList[MAX_COMMANDS];
void* commandParsers[MAX_COMMANDS];


//==============================================================================
void commandListCleaner()
{
    int i=0;
    for(i=0;i<MAX_COMMANDS;i++)
    {
        commandList[i]=0;
    }
}

int commandInit(struct command* c)
{
   if(commandList[c->header]!=0) return -1;
   else
   {
       commandList[c->header]=c;
       commandParsers[c->header]=c->parser;
       return 1;
   }
   
}
//==============================================================================

