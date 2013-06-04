/* 
 * File:   callbacks.h
 * Author: malcom
 *
 * Created on June 3, 2013, 3:18 PM
 */

#ifndef CALLBACKS_H
#define	CALLBACKS_H

#include "pid.h"
#include "encoderController.h"
#include "pwmController.h"
#include "motorController.h"



void anEventCallback(void) {
 //putsUART1((unsigned int *) "ping!\n");
}

void ledEventCallback(void) {
toggleLed1();
}

void encoder1Callback(void)
{
        char pos[10];

    putsUART1((unsigned int *) "e1: ");
    putsUART1((unsigned int *) itoa(pos,*(encoder1.ticks),10));
    putsUART1((unsigned int *) "\n");
    PIDsetReference(pid.p1,(int)(*(encoder1.ticks)));
    *(encoder1.ticks)=0;
}

void encoder2Callback(void)
{
    char pos[10];

    putsUART1((unsigned int *) "e2: ");
    putsUART1((unsigned int *) itoa(pos,*(encoder2.ticks),10));
    putsUART1((unsigned int *) "\n");
    PIDsetReference(pid.p2,(int)(*(encoder2.ticks)));
    *(encoder2.ticks)=0;
}


void pidCallback(void)
{

    char a[20];
//    sprintf(a,"M1: %d ",motorController.motor1->speed);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"M2: %d \n",motorController.motor2->speed);
//    putsUART1((unsigned int *) a);
    updatePIDs(&pid);
    
//     if (pid.p1->PID < (float)(*encoder1.ticks))
//    {
//        motorController.motor1->speed-=1;
//        setMotorSpeed(&motorController,1,motorController.motor1->speed);
//    }
//    if (pid.p1->PID > (float)(*encoder1.ticks))
//    {
//        motorController.motor1->speed+=1;
//        setMotorSpeed(&motorController,1,motorController.motor1->speed);
//    }
//
//     if (pid.p2->PID < (float)(*encoder2.ticks))
//    {
//        motorController.motor2->speed-=1;
//        setMotorSpeed(&motorController,2,motorController.motor2->speed);
//    }
//    if (pid.p2->PID > (float)(*encoder2.ticks))
//    {
//        motorController.motor2->speed+=1;
//        setMotorSpeed(&motorController,2,motorController.motor2->speed);
//    }
    
    
    sprintf(a,"I: %f ",pid.p1->I);
    putsUART1((unsigned int *) a);
    sprintf(a,"D: %f ",pid.p1->D);
    putsUART1((unsigned int *) a);
    sprintf(a,"DT: %f ",pid.p1->DT);
    putsUART1((unsigned int *) a);
    sprintf(a,"REF: %f ",pid.p1->reference);
    putsUART1((unsigned int *) a);
    sprintf(a,"ERR: %f ",pid.p1->error);
    putsUART1((unsigned int *) a);
    sprintf(a,"PID: %f ",pid.p1->PID);
    putsUART1((unsigned int *) a);
    putsUART1((unsigned int *) "\n");
    updatePIDs(&pid);

}

#endif	/* CALLBACKS_H */

