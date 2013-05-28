/* 
 * File:   pid.h
 * Author: malcom
 *
 * Created on May 27, 2013, 5:54 PM
 */

#ifndef PID_H
#define	PID_H

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
    float iWindupThreshold;

    int isInitialized;
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
    s->iWindupThreshold = 10;
    s->isInitialized = 1;
}

void PIDsetReference(struct PID* s, float r) {
    //reference rappresenta la variabile da controllare, input rappresenta il controllo
    s->reference = r;
}

void PIDUpdate(struct PID* s, float input) {
    if (s->isInitialized == 1) {
        //compute error
        s->error = input - s->reference;
        //compute P
        s->P = s->kP * s->error;
        //compute I
        s->I = s->kI * (s->I + s->error * s->DT);
//        if (s->I > s->iWindupThreshold) {
//            s->I = s->iWindupThreshold;
//        }
        //compute D
        s->D = ((s->error - s->previous_error) / s->DT) * s->kD;
        s->previous_error = s->error;
        //compute the PID
        s->PID = s->P + s->I + s->D;
    }
}
#endif	/* PID_H */

