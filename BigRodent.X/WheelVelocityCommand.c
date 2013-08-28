#include "WheelVelocityCommand.h"
struct wheelVelocityCommand
{
    struct command* c;
    int leftDIR;
    int leftSpeed;
    int rightDIR;
    int rightSpeed;
    int fields[4];
};


struct wheelVelocityCommand WheelVelocityCommand;

void WheelVelocityCallback(int arg)
{
    
}

void WheelVelocityResponse()
{
    printf("RESPONSE\n");
}

void WheelVelocityCommandInit()
{
    WheelVelocityCommand.c->header=1;
    WheelVelocityCommand.c->callback=&WheelVelocityCallback;
    WheelVelocityCommand.c->response=&WheelVelocityResponse;

    WheelVelocityCommand.fields[0]=4;
    WheelVelocityCommand.fields[1]=4;
    WheelVelocityCommand.fields[2]=4;
    WheelVelocityCommand.fields[3]=4;
    
    commandInit(WheelVelocityCommand.c);
}

void WheelVelocityCommandParse(char* buff,struct wheelVelocityCommand* c)
{
//    buff++;
//    int i=0;
//    int f=0;
//    for(f=0;f<4;f++)
//    {
//        for(int i=0;i<sizeof(buff-1);i++)
//        {
//s
//        }
//    }

}