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

void odoMetryCallback(void) {
    char a[30];
//    sprintf(a,"1: %d \n",encoder1.odoTicks);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"2: %d \n",encoder2.odoTicks);
    
    putsUART1((unsigned int *) a);
    float sS=((float)encoder1.odoTicks*METERPERTICK1+(float)encoder2.odoTicks*METERPERTICK2)/2;
    Teta+=((float)encoder2.odoTicks*METERPERTICK2-(float)encoder1.odoTicks*METERPERTICK1)/BASELINE;
    posX+=sS*cos(Teta);
    posY+=sS*sin(Teta);

    sprintf(a,"#x%f@\n",posX);
    putsUART1((unsigned int *) a);
    sprintf(a,"#y%f@\n",posY);
    putsUART1((unsigned int *) a);
    sprintf(a,"#t%f@\n",Teta);
    putsUART1((unsigned int *) a);

    encoder1.odoTicks=0;
    encoder2.odoTicks=0;
 //putsUART1((unsigned int *) "ping!\n");
//    char a[20];
//    sprintf(a,"I: %d ",pid.p1->I);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"D: %d ",pid.p1->D);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"P: %d ",pid.p1->P);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"DT: %d ",pid.p1->DT);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"REF: %d ",pid.p1->reference);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"REQ: %d ",pid.p1->request);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"ERR: %d ",pid.p1->error);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"PID: %d ",pid.p1->PID);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"m1: %d \n",(int)(pid.p1->request+(pid.p1->PID)/100));
//    putsUART1((unsigned int *) a);

//    sprintf(a,"I: %d ",pid.p2->I);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"D: %d ",pid.p2->D);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"P: %d ",pid.p2->P);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"DT: %d ",pid.p2->DT);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"REF: %d ",pid.p2->reference);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"REQ: %d ",pid.p2->request);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"ERR: %d ",pid.p2->error);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"PID: %d ",pid.p2->PID);
//    putsUART1((unsigned int *) a);
//    sprintf(a,"m1: %d \n",(int)(pid.p2->request+(pid.p2->PID)/100));
//    putsUART1((unsigned int *) a);
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
    pid.p1->reference = *(encoder1.ticks);
    encoder1.odoTicks+=*(encoder1.ticks);
    *(encoder1.ticks)=0;
}

void encoder2Callback(void)
{
    char pos[10];
//
//    putsUART1((unsigned int *) "e2: ");
//    putsUART1((unsigned int *) itoa(pos,*(encoder2.ticks),10));
//    putsUART1((unsigned int *) "\n");
    pid.p2->reference = *(encoder2.ticks);
    encoder2.odoTicks+=*(encoder2.ticks);
    *(encoder2.ticks)=0;
}


void pidCallback(void)
{

    updatePIDs(&pid);
    setMotorSpeed1(&motorController, (int)(pid.p1->request+(pid.p1->PID)));
    setMotorSpeed2(&motorController, (int)(pid.p2->request+(pid.p2->PID)));

}

#endif	/* CALLBACKS_H */

