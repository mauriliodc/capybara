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

    int TimeMillisec;

    float error;
    float reference;
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

void PIDinitPID(struct PID* s, float K, float P, float D, int millisecs) {
    s->kI = K;
    s->kP = P;
    s->kD = D;

    s->I = 0;
    s->P = 0;
    s->D = 0;

    s->TimeMillisec = millisecs;
    s->error = 0;
    s->reference = 0;
}

void PIDsetReference(struct PID* s, float r) {
    s->reference = r;
}

void PIDUpdate(struct PID* s, float input)
{
     s->error = s->reference - input;
     s->P=s->reference/s->kP;
     s->I = s->I + (s->P * s->TimeMillisec) / s->kI;
     s->D = s->error / s->TimeMillisec / s->kD;
     s->PID=s->P+s->I+s->D;
}
#endif	/* PID_H */

