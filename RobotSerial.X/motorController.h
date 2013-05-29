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
};

#endif	/* MOTORCONTROLLER_H */

