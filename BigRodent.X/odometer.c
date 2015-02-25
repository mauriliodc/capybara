
#include "odometer.h"
#include "motor_controller.h"
#include "message_buffer.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265
#define RATIO_RAD_GRAD PI/180

void DifferentialDrive_UpperHandler(struct TimerEvent* t) {
    struct Odometer* oh = (struct Odometer*) t;
    uint8_t i;
    for (i = 0; i < MOTORS_NUM; i++) {
        oh->_distance[i] = (long_t) MotorController_setMeasuredDistance(oh->mc[i], 0);
    }

    //     putsUART1((unsigned int *) "uppper\n");
    //     char a[100];
    //    sprintf(a,"m1: %d m2:%d \n",oh->_distance[0],oh->_distance[1]);
    //    putsUART1((unsigned int *) a);
}

void DifferentialDrive_LowerHandler(struct TimerEvent* t) {

    //struct DifferentialDriveOdometer* dd = (struct DifferentialDriveOdometer*) t;
    struct Odometer* oh = (struct Odometer*) t;
    //struct PIDControlAlgorithm* p1 = oh->mc[0]->_ca;
    //struct PIDControlAlgorithm* p2 = oh->mc[1]->_ca;

    //printf("PID1 %d %d %d >%d PID2 %d %d %d >%d \n", p1->_Pi,p1->_I,p1->_D,p1->_error,p2->_Pi,p2->_I,p2->_D,p2->_error);
    //    printf("PID1 %d PID2 %d ERR1 %d ERR2 %d \n", p1->_I,p2->_I,p1->_error, p2->_error);
    //    printf("PWM %d %d \n",PWMController_dutycycle(oh->mc[0]->_pwms,0),PWMController_dutycycle(oh->mc[1]->_pwms,1));
    //printf("ENC %d %d \n",oh->mc[0]->_measuredSpeed,oh->mc[1]->_measuredSpeed);
    //    long_t dl=dd->_base._distance[0]*dd->_leftEncoderDegreesPerTicks*dd->_leftWheelRadius;
    //    long_t dr=dd->_base._distance[1]*dd->_rightEncoderDegreesPerTicks*dd->_rightWheelRadius;
    //    long_t r = (dl+dr)/2;
    //
    //    dd->_base._pose._theta= (dr-dl)/(2*dd->_baseline);
    //    dd->_base._pose._x=r*(cos(dd->_base._globalPose._theta));
    //    dd->_base._pose._y=r*(sin(dd->_base._globalPose._theta));
    //
    //    dd->_base._globalPose._x+=dd->_base._pose._x;
    //    dd->_base._globalPose._y+=dd->_base._pose._y;
    //    dd->_base._globalPose._theta+=dd->_base._pose._theta;





    char a[100];
    //sprintf(a,"# %d %d %d %d %d %d %d @ \n", oh->_distance[0],oh->_distance[1],dd->_base._pose._x,dd->_base._pose._y,dd->_base._pose._theta,t->_lastTickUpperHalfExecuted,t->_lastLowerHalfExecutionTime);
    //sprintf(a,"# %f %f %f %f %f %f %f %f @ \n", oh->_distance[0],oh->_distance[1],dd->_base._pose._x,dd->_base._pose._y,dd->_base._pose._theta,dd->_base._globalPose._x,dd->_base._globalPose._y,dd->_base._globalPose._theta);
    //putsUART1((unsigned int*)a);


    //sprintf(a, "#%d %d @\n", oh->mc[0]->_measuredSpeed, oh->mc[1]->_measuredSpeed);
    //outputBuffer_write(a);
    //putsUART1((unsigned int*)a);


    //transmissionBuffer_write(dd->_base._tbuf,a);

    //    sprintf(a,"x: %d y:%d theta:%d \n",dd->_base._pose._x,dd->_base._pose._y,dd->_base._pose._theta);
    //    putsUART1((unsigned int *) a);
    //    sprintf(a,"m1: %d m2:%d \n",oh->_distance[0],oh->_distance[1]);
    //    putsUART1((unsigned int *) a);


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