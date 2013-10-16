/* 
 * File:   velocityCommand.h
 * Author: malcom
 *
 * Created on October 16, 2013, 2:14 PM
 */

#ifndef VELOCITYCOMMAND_H
#define	VELOCITYCOMMAND_H

extern  struct MotorController LeftMotorController;
extern struct MotorController RightMotorController;


struct _velocityCommand
{
    struct _commandBase base;
    int leftSpeed;
    int rightSpeed;
    int leftDir;
    int rightDir;
} velocityCommand;


void velocityCommandParser(char* buffer)
{
    sscanf(buffer,"%1d%1d%2d%2d",&velocityCommand.leftDir,
    &velocityCommand.rightDir,
    &velocityCommand.leftSpeed,
    &velocityCommand.rightSpeed);
    if(velocityCommand.leftDir)
        MotorController_setDesiredSpeed(&LeftMotorController,velocityCommand.leftSpeed);
    else
         MotorController_setDesiredSpeed(&LeftMotorController,-velocityCommand.leftSpeed);
    if(velocityCommand.rightDir)
        MotorController_setDesiredSpeed(&RightMotorController,velocityCommand.rightSpeed);
    else
        MotorController_setDesiredSpeed(&RightMotorController,-velocityCommand.rightSpeed);
    
    outputBuffer_write("abcdefg");
    //printf("done\n");

}


void velocityCommandInit(int id,struct _commandBase** c )
{
    velocityCommand.base._commandID=id;
    velocityCommand.base._parseFN=&velocityCommandParser;
    c[id]=&velocityCommand;
    printf("VELOCITY PACKET INIT");
}




#endif	/* VELOCITYCOMMAND_H */

