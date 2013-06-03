/* 
 * File:   motorController.h
 * Author: malcom
 *
 * Created on May 28, 2013, 4:46 PM
 */

#ifndef MOTORCONTROLLER_H
#define	MOTORCONTROLLER_H

#include "pwmController.h"
#include "pid.h"
#include "encoderController.h"

struct MOTOR
{
    int speed; // -100 e 100
    
};


struct MotorController
{
    struct MOTOR* motor1;
    struct MOTOR* motor2;

    struct PWMController* pwmController;
    struct encoderController* encoderContoller;
    struct PIDController* pidController;
};

void initMotorController(struct MotorController* m, struct MOTOR* m1, struct MOTOR* m2, struct PWMController* pwm, struct encoderController* encoder, struct PIDController *pid)
{
    m->motor1=m1;
    m->motor2=m2;
    m->motor1->speed=0;
    m->motor2->speed=0;
    m->pwmController=pwm;
    m->encoderContoller=encoder;
    m->pidController=pid;
}



//*************************************************************
//*************************************************************

struct MOTOR leftMotor;
struct MOTOR rightMotor;
struct MotorController motorController;

#endif	/* MOTORCONTROLLER_H */

