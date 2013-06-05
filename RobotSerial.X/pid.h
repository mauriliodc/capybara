/* 
 * File:   pid.h
 * Author: malcom
 *
 * Created on May 27, 2013, 5:54 PM
 */

#ifndef PID_H
#define	PID_H

#include "fancyTimer.h"

struct PID {
    float kI;
    float I;

    float kP;
    float P;

    float kD;
    float D;

    float PID;

    float DT;

    float error;
    float previous_error;
    float reference;
    float request;
    float iWindupThreshold;

    int isInitialized;

    
};


struct PIDController
{
    struct PID* p1;
    struct PID* p2;
    struct timerEvent* event;
    float p1Ref;
    float p2Ref;
};

//HOW TO USE IS:

/*

 * - creating the structure
 * - initPID
 * - set the reference
 * - compute the error
 * - call the PID
 * - get the value from the PID


 */

void PIDinitPID(struct PID* s, float I, float P, float D, float secs) {
    s->kI = I;
    s->kP = P;
    s->kD = D;

    s->I = 0;
    s->P = 0;
    s->D = 0;

    s->PID = 0;

    s->DT = secs;
    s->error = 0;
    s->previous_error = 0;
    s->reference = 0;
    s->iWindupThreshold = 7500;
    s->isInitialized = 1;
}

void PIDsetReference(struct PID* s, float r) {
    //reference rappresenta la variabile da controllare, input rappresenta il controllo
    s->reference = r;
}

void PIDsetRequest(struct PID* s, float r) {
    
    s->request = r;
}

void PIDUpdate(struct PID* s) {
    if (s->isInitialized == 1) {
        //compute error
        s->error = s->request - s->reference;
        //compute P
        s->P = s->kP * s->error;
        //compute I
        s->I += s->kI * ( s->error * s->DT);
        
        if (s->I > s->iWindupThreshold) {
            s->I = s->iWindupThreshold;
        }
        if (s->I < -s->iWindupThreshold) {
            s->I = -s->iWindupThreshold;
        }
        //compute D
        s->D = ((s->error - s->previous_error) / s->DT) * s->kD;
        s->previous_error = s->error;
        //compute the PID
        s->PID = s->P + s->I + s->D;
    }
}


void InitPIDController(struct PIDController* p, struct PID* p1, struct PID* p2,struct timerEvent* event, int millisecs)
{
    p->p1=p1;
    p->p2=p2;
    p->event=event;

    p->event->millisecs=millisecs;
    p->event->repetitions=-1;
    p->event->callback=&pidCallback;
    p->event->runInHandler=1;
    p->event->executeNow=0;

}


void updatePIDs(struct PIDController* p)
{
    PIDUpdate(p->p1);
    PIDUpdate(p->p2);
}

void modifyPIDsRefs(struct PIDController* p, float r1, float r2)
{
    p->p1Ref=r1;
    p->p2Ref=r2;
}


//******************************************************************************
//******************************************************************************
struct PID pidmotor1;
struct PID pidmotor2;
struct PIDController pid;

#endif	/* PID_H */

