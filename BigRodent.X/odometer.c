#include "odometer.h"
#include "motor_controller.h"
#include <math.h>


void DifferentialDrive_UpperHandler(struct TimerEvent* t)
{
    struct Odometer* oh = (struct Odometer*)t;
    uint8_t i;
    for(i=0;i<MOTORS_NUM;i++)
    {
        oh->_distance[i]=MotorController_setMeasuredDistance(oh->mc[i],0);
    }
}

void DifferentialDrive_LowerHandler(struct TimerEvent* t)
{
    struct DifferentialDriveOdometer* dd = (struct DifferentialDriveOdometer*) t;

    int16_t s=  dd->_base._distance[0]*dd->_leftEncoderDegreesPerTicks*dd->_leftWheelRadius+
                dd->_base._distance[1]*dd->_rightEncoderDegreesPerTicks*dd->_rightWheelRadius;

    dd->_base._pose._theta=(dd->_base._distance[1]*dd->_rightEncoderDegreesPerTicks*dd->_rightWheelRadius-
                            dd->_base._distance[0]*dd->_leftEncoderDegreesPerTicks*dd->_leftWheelRadius)/dd->_baseline;

    dd->_base._pose._x=s*cos(dd->_base._pose._theta);
    dd->_base._pose._y=s*sin(dd->_base._pose._theta);

    dd->_base._globalPose._x+=dd->_base._pose._x;
    dd->_base._globalPose._y+=dd->_base._pose._y;
    dd->_base._globalPose._theta+=dd->_base._pose._theta;
}


void DifferentialDriveOdometryHandler_init( struct DifferentialDriveOdometer* dd,
                                            uint16_t baseline,
                                            struct MotorController *leftMc,struct MotorController *rightMc,
                                            uint16_t leftWheelRadius,uint16_t rightWheelRadius,
                                            uint16_t leftEncoderDegreesPerTicks, uint16_t rightEncoderDegreesPerTicks,
                                            uint16_t period)
{


    TimerEvent_init(&dd->_base.event, &DifferentialDrive_UpperHandler, &DifferentialDrive_LowerHandler, period);
    dd->_baseline=baseline;
    dd->_leftEncoderDegreesPerTicks=leftEncoderDegreesPerTicks;
    dd->_rightEncoderDegreesPerTicks=rightEncoderDegreesPerTicks;
    dd->_leftWheelRadius=leftWheelRadius;
    dd->_rightWheelRadius=rightWheelRadius;
    dd->_base._period=period;
    dd->_base.mc[0]=leftMc;
    dd->_base.mc[1]=rightMc;
   
}







//GET POSE - SET POSE
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

struct pose Odometer_getPose(struct Odometer* oh)
{
    return oh->_pose;
}

struct pose Odometer_setPose(struct Odometer* oh,struct pose p)
{
    struct pose tmp;
    tmp._x=oh->_pose._x;
    tmp._y=oh->_pose._y;
    tmp._theta=oh->_pose._theta;

    oh->_pose._x=p._x;
    oh->_pose._y=p._y;
    oh->_pose._theta=p._theta;

    return tmp;
}

struct pose Odometer_setPoseElements(struct Odometer* oh, int16_t x,int16_t y, int16_t theta)
{
    struct pose tmp;
    tmp._x=oh->_pose._x;
    tmp._y=oh->_pose._y;
    tmp._theta=oh->_pose._theta;

    oh->_globalPose._x=x;
    oh->_globalPose._y=y;
    oh->_globalPose._theta=theta;

    return tmp;
}


struct pose Odometer_getGlobalPose(struct Odometer* oh)
{
    return oh->_globalPose;
}

struct pose Odometer_setGlobalPose(struct Odometer* oh, struct pose p)
{

    struct pose tmp;
    tmp._x=oh->_globalPose._x;
    tmp._y=oh->_globalPose._y;
    tmp._theta=oh->_globalPose._theta;

    oh->_globalPose._x=p._x;
    oh->_globalPose._y=p._y;
    oh->_globalPose._theta=p._theta;

    return tmp;
}

struct pose Odometer_setGlobalPoseElements(struct Odometer* oh, int16_t x,int16_t y, int16_t theta)
{

    struct pose tmp;
    tmp._x=oh->_globalPose._x;
    tmp._y=oh->_globalPose._y;
    tmp._theta=oh->_globalPose._theta;

    oh->_globalPose._x=x;
    oh->_globalPose._y=y;
    oh->_globalPose._theta=theta;

    return tmp;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------