/* 
 * File:   odometry_handler.h
 * Author: malcom
 *
 * Created on June 19, 2013, 4:45 PM
 */

#ifndef ODOMETRY_HANDLER_H
#define	ODOMETRY_HANDLER_H

#include "platform_defs.h"
#include "motor_controller.h"
#include "timer_handler.h"

#define MOTORS_NUM 2

struct Odometer;

struct pose{
    int16_t _x;
    int16_t _y;
    int16_t _theta;
};

struct Odometer
{
    TimerEvent event;
    struct MotorController* mc[MOTORS_NUM];
    uint16_t _period;
    uint16_t _distance[MOTORS_NUM];
    struct pose _pose;
    struct pose _globalPose;



};

struct DifferentialDriveOdometer
{
    struct Odometer _base;
    uint16_t _baseline;
    uint16_t _leftWheelRadius;
    uint16_t _rightWheelRadius;
    uint16_t _leftEncoderDegreesPerTicks;
    uint16_t _rightEncoderDegreesPerTicks;

};


void DifferentialDrive_UpperHandler(struct TimerEvent* t);
void DifferentialDrive_LowerHandler(struct TimerEvent* t);

void DifferentialDriveOdometryHandler_init( struct DifferentialDriveOdometer* dd,
                                            uint16_t baseline,
                                            struct MotorController *leftMc, struct MotorController *rightMc,
                                            uint16_t leftWheelRadius,uint16_t rightWheelRadius,
                                            uint16_t leftEncoderDegreesPerTicks, uint16_t rightEncoderDegreesPerTicks,
                                            uint16_t period);



struct pose Odometer_getPose(struct Odometer* oh);
struct pose Odometer_setPose(struct Odometer* oh,struct pose p);
struct pose Odometer_setPoseElements(struct Odometer* oh, int16_t x,int16_t y, int16_t theta);
struct pose Odometer_getGlobalPose(struct Odometer* oh);
struct pose Odometer_setGlobalPose(struct Odometer* oh, struct pose p);
struct pose Odometer_setGlobalPoseElements(struct Odometer* oh, int16_t x,int16_t y, int16_t theta);
#endif	/* ODOMETRY_HANDLER_H */

