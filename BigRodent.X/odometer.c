#include "odometer.h"
#include "motor_controller.h"
#include "message_buffer.h"
#include "state_packet.h"
#include <math.h>
#include "control_algorithm.h"

#define PI 3.14159265
#define RATIO_RAD_GRAD PI/180

extern StatePacket outState;
extern HexMessage outputStream;
void DifferentialDrive_UpperHandler(struct TimerEvent* t)
{
    struct Odometer* oh = (struct Odometer*)t;
    uint8_t i;
    for(i=0;i<MOTORS_NUM;i++)
    {
        oh->_distance[i]=(long_t)MotorController_setMeasuredDistance(oh->mc[i],0);
    }

}

void DifferentialDrive_LowerHandler(struct TimerEvent* t)
{
    
    struct DifferentialDriveOdometer* dd = (struct DifferentialDriveOdometer*) t;
    struct Odometer* oh = (struct Odometer*)t;

    long_t dl=dd->_base._distance[0]*dd->_leftEncoderDegreesPerTicks*dd->_leftWheelRadius;
    long_t dr=dd->_base._distance[1]*dd->_rightEncoderDegreesPerTicks*dd->_rightWheelRadius;
    long_t r = (dl+dr)/2;

    dd->_base._pose._theta= (dr-dl)/(2*dd->_baseline);
    dd->_base._pose._x=r*(cos(dd->_base._globalPose._theta));
    dd->_base._pose._y=r*(sin(dd->_base._globalPose._theta));

    dd->_base._globalPose._x+=dd->_base._pose._x;
    dd->_base._globalPose._y+=dd->_base._pose._y;
    dd->_base._globalPose._theta+=dd->_base._pose._theta;

    outState.seq++;
    outState.leftEncoder=oh->_distance[0];
    outState.rightEncoder=oh->_distance[1];
    outState.incrementalOdometry[0]=dd->_base._pose._x;
    outState.incrementalOdometry[1]=dd->_base._pose._y;
    outState.incrementalOdometry[2]=dd->_base._pose._theta;
    outState.globalOdometry[0]=dd->_base._globalPose._x;
    outState.globalOdometry[1]=dd->_base._globalPose._y;
    outState.globalOdometry[2]=dd->_base._globalPose._theta;
    outState.batteryVoltage=0;
    outState.leftPWMCurrent=0;
    outState.rightPWMCurrent=0;
    outState.rotationalAcceleration=0;
    outState.rotationalVelocity=0;
    outState.translationalAcceleration=0;
    outState.translationalVelocity=0;
    Packet_write(&outputStream,(const struct PacketHeader*)&outState);

    struct PIDControlAlgorithm* pid = (struct PIDControlAlgorithm*)oh->mc[0]->_ca;
    struct PIDControlAlgorithm* pid2 = (struct PIDControlAlgorithm*)oh->mc[1]->_ca;
    char tst[100];
    //sprintf(tst,"T: %03d  P1 %03d I1 %03d  D1 %03d P2 %03d I2 %03d  D2 %03d",t->_lastLowerHalfExecutionTime,pid->_Pi,pid->_I,pid->_D,pid2->_Pi,pid2->_I,pid2->_D);
    sprintf(tst,"T: %03d",t->_lastLowerHalfExecutionTime);
    HexMessage_writeString(&outputStream,tst);
    
    
}


void DifferentialDriveOdometryHandler_init( struct DifferentialDriveOdometer* dd,
                                            long_t baseline,
                                            struct MotorController *leftMc,struct MotorController *rightMc,
                                            long_t leftWheelRadius,long_t rightWheelRadius,
                                            long_t leftEncoderDegreesPerTicks, long_t rightEncoderDegreesPerTicks,
                                            long_t period,struct trasmissionBuffer* t)
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
    dd->_base._tbuf=t;
   
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

struct pose Odometer_setPoseElements(struct Odometer* oh, long_t x,long_t y, long_t theta)
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

struct pose Odometer_setGlobalPoseElements(struct Odometer* oh, long_t x,long_t y, long_t theta)
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