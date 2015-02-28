
#include "odometer.h"
#include "motor_controller.h"
#include "message_buffer.h"
#include <math.h>
#include <stdio.h>
#include "mal_comm.h"
#include "mal_buffer.h"

#define PI 3.14159265
#define RATIO_RAD_GRAD PI/180

uint16_t stupid=0;

extern struct Double_Buffer outputBuffer;
extern int ascii;

void DifferentialDrive_UpperHandler(struct TimerEvent* t) {
    struct Odometer* oh = (struct Odometer*) t;
    uint8_t i;
    for (i = 0; i < MOTORS_NUM; i++) {
        oh->_distance[i] = (long_t) MotorController_setMeasuredDistance(oh->mc[i], 0);
    }
}

void DifferentialDrive_LowerHandler(struct TimerEvent* t) {
    struct Odometer* oh = (struct Odometer*) t;
    struct Packet p;
    struct State_Payload sp;
    p.id=State_Payload_ID;
    p.seq=stupid;
    stupid++;
    sp.leftEncoder=oh->_distance[0];
    oh->_distance[0]=0;
    sp.rightEncoder=oh->_distance[1];
    oh->_distance[1]=0;
    p.state=sp;
    char stateBuffer[255];
    char* pEnd=Packet_write(&p,stateBuffer,ascii);
    Double_Buffer_write(&outputBuffer,stateBuffer,pEnd-stateBuffer);
}

void DifferentialDriveOdometryHandler_init(struct DifferentialDriveOdometer* dd,
        long_t baseline,
        struct MotorController *leftMc, struct MotorController *rightMc,
        long_t leftWheelRadius, long_t rightWheelRadius,
        long_t leftEncoderDegreesPerTicks, long_t rightEncoderDegreesPerTicks,
        long_t period, struct trasmissionBuffer* t) {


    TimerEvent_init(&dd->_base.event, &DifferentialDrive_UpperHandler, &DifferentialDrive_LowerHandler, period);
    dd->_baseline = baseline;
    dd->_leftEncoderDegreesPerTicks = leftEncoderDegreesPerTicks;
    dd->_rightEncoderDegreesPerTicks = rightEncoderDegreesPerTicks;
    dd->_leftWheelRadius = leftWheelRadius;
    dd->_rightWheelRadius = rightWheelRadius;
    dd->_base._period = period;
    dd->_base.mc[0] = leftMc;
    dd->_base.mc[1] = rightMc;
    dd->_base._tbuf = t;

}







//GET POSE - SET POSE
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

struct pose Odometer_getPose(struct Odometer* oh) {
    return oh->_pose;
}

struct pose Odometer_setPose(struct Odometer* oh, struct pose p) {
    struct pose tmp;
    tmp._x = oh->_pose._x;
    tmp._y = oh->_pose._y;
    tmp._theta = oh->_pose._theta;

    oh->_pose._x = p._x;
    oh->_pose._y = p._y;
    oh->_pose._theta = p._theta;

    return tmp;
}

struct pose Odometer_setPoseElements(struct Odometer* oh, long_t x, long_t y, long_t theta) {
    struct pose tmp;
    tmp._x = oh->_pose._x;
    tmp._y = oh->_pose._y;
    tmp._theta = oh->_pose._theta;

    oh->_globalPose._x = x;
    oh->_globalPose._y = y;
    oh->_globalPose._theta = theta;

    return tmp;
}

struct pose Odometer_getGlobalPose(struct Odometer* oh) {
    return oh->_globalPose;
}

struct pose Odometer_setGlobalPose(struct Odometer* oh, struct pose p) {

    struct pose tmp;
    tmp._x = oh->_globalPose._x;
    tmp._y = oh->_globalPose._y;
    tmp._theta = oh->_globalPose._theta;

    oh->_globalPose._x = p._x;
    oh->_globalPose._y = p._y;
    oh->_globalPose._theta = p._theta;

    return tmp;
}

struct pose Odometer_setGlobalPoseElements(struct Odometer* oh, long_t x, long_t y, long_t theta) {

    struct pose tmp;
    tmp._x = oh->_globalPose._x;
    tmp._y = oh->_globalPose._y;
    tmp._theta = oh->_globalPose._theta;

    oh->_globalPose._x = x;
    oh->_globalPose._y = y;
    oh->_globalPose._theta = theta;

    return tmp;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------