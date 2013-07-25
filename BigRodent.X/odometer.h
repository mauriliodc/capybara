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
#include "message_buffer.h"

#define MOTORS_NUM 2

struct Odometer;

struct pose{
    long_t _x;
    long_t _y;
    long_t _theta;
};

struct Odometer
{
    TimerEvent event;
    struct MotorController* mc[MOTORS_NUM];
    long_t _period;
    int16_t _distance[MOTORS_NUM];
    struct pose _pose;
    struct pose _globalPose;
    struct trasmissionBuffer* _tbuf;

};

struct DifferentialDriveOdometer
{
    struct Odometer _base;
    long_t _baseline;
    long_t _leftWheelRadius;
    long_t _rightWheelRadius;
    long_t _leftEncoderDegreesPerTicks;
    long_t _rightEncoderDegreesPerTicks;

};


void DifferentialDrive_UpperHandler(struct TimerEvent* t);
void DifferentialDrive_LowerHandler(struct TimerEvent* t);

void DifferentialDriveOdometryHandler_init( struct DifferentialDriveOdometer* dd,
                                            long_t baseline,
                                            struct MotorController *leftMc, struct MotorController *rightMc,
                                            long_t leftWheelRadius,long_t rightWheelRadius,
                                            long_t leftEncoderDegreesPerTicks, long_t rightEncoderDegreesPerTicks,
                                            long_t period,
                                            struct trasmissionBuffer*);



struct pose Odometer_getPose(struct Odometer* oh);
struct pose Odometer_setPose(struct Odometer* oh,struct pose p);
struct pose Odometer_setPoseElements(struct Odometer* oh, long_t x,long_t y, long_t theta);
struct pose Odometer_getGlobalPose(struct Odometer* oh);
struct pose Odometer_setGlobalPose(struct Odometer* oh, struct pose p);
struct pose Odometer_setGlobalPoseElements(struct Odometer* oh, long_t x,long_t y, long_t theta);
#endif	/* ODOMETRY_HANDLER_H */

