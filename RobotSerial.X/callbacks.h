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
#include <math.h>

extern struct timerController bigTimer;

void anEventCallback(void) {
 //putsUART1((unsigned int *) "ping!\n");
    char a[20];
    sprintf(a,"I: %f ",pid.p1->I);
    putsUART1((unsigned int *) a);
    sprintf(a,"D: %f ",pid.p1->D);
    putsUART1((unsigned int *) a);
    sprintf(a,"P: %f ",pid.p1->P);
    putsUART1((unsigned int *) a);
    sprintf(a,"DT: %f ",pid.p1->DT);
    putsUART1((unsigned int *) a);
    sprintf(a,"REF: %f ",pid.p1->reference);
    putsUART1((unsigned int *) a);
    sprintf(a,"REQ: %f ",pid.p1->request);
    putsUART1((unsigned int *) a);
    sprintf(a,"ERR: %f ",pid.p1->error);
    putsUART1((unsigned int *) a);
    sprintf(a,"PID: %f ",pid.p1->PID);
    putsUART1((unsigned int *) a);
    putsUART1((unsigned int *) "\n");
    sprintf(a,"m1: %d \n",(int)((pid.p1->request+pid.p1->PID)/25));
    putsUART1((unsigned int *) a);
}

void ledEventCallback(void) {
toggleLed1();
}

void encoder1Callback(void)
{
//    char pos[20];
//    putsUART1((unsigned int *) "e1: ");
//    putsUART1((unsigned int *) itoa(pos,*(encoder1.ticks),10));
//    putsUART1((unsigned int *) "\n");
//    sprintf(pos,"%d \n",bigTimer.millisecsStash);
//    putsUART1((unsigned int *) pos);
    PIDsetReference(pid.p1,(int)(*(encoder1.ticks)));
    *(encoder1.ticks)=0;
}

void encoder2Callback(void)
{
//    char pos[10];
//
//    putsUART1((unsigned int *) "e2: ");
//    putsUART1((unsigned int *) itoa(pos,*(encoder2.ticks),10));
//    putsUART1((unsigned int *) "\n");
    PIDsetReference(pid.p2,(int)(*(encoder2.ticks)));
    *(encoder2.ticks)=0;
}


void pidCallback(void)
{
    updatePIDs(&pid);
    setMotorSpeed(&motorController, 1, (int)(pid.p1->request+(int)(pid.p1->PID/25)));
    setMotorSpeed(&motorController, 2, (int)(pid.p2->request+(int)(pid.p2->PID/25)));


}

#endif	/* CALLBACKS_H */

