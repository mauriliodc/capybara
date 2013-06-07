/* 
 * File:   pid.h
 * Author: malcom
 *
 * Created on May 27, 2013, 5:54 PM
 */

#ifndef PID_H
#define	PID_H

#include "fancyTimer.h"
typedef int PIDtype;

struct PID {

    PIDtype DT;
    PIDtype kP;
    PIDtype kI;
    PIDtype kI_times_DT;
    PIDtype kD;
    PIDtype kD_div_DT;
    PIDtype iWindupThreshold;


    PIDtype P, I, D, PID;


    PIDtype error;
    PIDtype previous_error;
    PIDtype reference;
    PIDtype request;

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

void PIDinitPID(struct PID* s, PIDtype I, PIDtype P, PIDtype D, PIDtype secs) {
    s->kI = I;
    s->kP = P;
    s->kD = D;
    s->DT = secs;
    
    s->kD_div_DT = s->kD/s->DT;
    s->kI_times_DT = s->kI*s->DT;

    s->reference = 0;
    s->iWindupThreshold = 5000;
    
    s->error = 0;
    s->previous_error = 0;
    s->I = 0;
    s->P = 0;
    s->D = 0;
    s->PID = 0;

}

inline void PIDsetReference(struct PID* s, PIDtype r) {
    //reference rappresenta la variabile da controllare, input rappresenta il controllo
    s->reference = r;
}

inline void PIDsetRequest(struct PID* s, PIDtype r) {
    
    s->request = r;
}

inline void PIDUpdate(struct PID* s) {
    //compute error
    s->error = s->request - s->reference;
    //compute P
    s->P = s->kP * s->error;
    //compute I
    s->I += s->kI_times_DT *  s->error;

    s->I = (s->I > s->iWindupThreshold) ? s->iWindupThreshold : s->I;
    s->I = (s->I < -s->iWindupThreshold) ? -s->iWindupThreshold : s->I;

    s->D = (s->error - s->previous_error) * s->kD_div_DT;
    s->previous_error = s->error;
    //compute the PID
    s->PID = s->P + s->I + s->D;
    
}


void InitPIDController(struct PIDController* p, struct PID* p1, struct PID* p2,struct timerEvent* event, PIDtype millisecs)
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


inline void updatePIDs(struct PIDController* p)
{
    PIDUpdate(p->p1);
    PIDUpdate(p->p2);
}


//******************************************************************************
//******************************************************************************
struct PID pidmotor1;
struct PID pidmotor2;
struct PIDController pid;

#endif	/* PID_H */

