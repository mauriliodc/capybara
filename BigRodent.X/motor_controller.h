

#ifndef _MOTOR_CONTROLLER_H
#define _MOTOR_CONTROLLER_H

#include "encoder_controller.h"
#include "pwm_controller.h"
#include "platform_defs.h"
#include "timer_handler.h"
#include "control_algorithm.h"

struct MotorController
{
    TimerEvent event;
    int16_t _measuredSpeed;
    int16_t _desiredSpeed;
    struct EncoderController* _ec;
    struct ControlAlgorithm* _ca;
    struct PWMController* _pwms;
    uint8_t _pwnNum;
    uint8_t  _encoderNum;
    int16_t _measuredDistance;
    int _directionPin;
    unsigned int* _directionPTR;
    uint16_t _period;

};

void MotorController_init(struct MotorController* mc,struct EncoderController* encoders, uint8_t  encoderNum,
		     struct PWMController* pwms, uint8_t pwnNum,
                     int16_t directionPin,uint16_t* directionPTR,
		     struct ControlAlgorithm* algorthm, int16_t period);

int16_t MotorController_period();
void MotorController_setPWM(struct MotorController* mc, int16_t speed);
void  MotorController_setDesiredSpeed(struct MotorController* controller,int16_t speed);
int16_t MotorController_desiredSpeed(struct MotorController* controller);
int16_t MotorController_measuredSpeed(struct MotorController* controller);

int16_t MotorController_measuredDistance(struct MotorController* controller);
int16_t MotorController_setMeasuredDistance(struct MotorController* controller, uint16_t ticks);

int16_t MotorController_maxPositiveSpeedIncrement(struct MotorController* controller);
int16_t  MotorController_maxNegativeSpeedIncrement(struct MotorController* controller);
void  MotorController_setMaxPositiveSpeedIncrement(struct MotorController* controller, int16_t inc);
void  MotorController_setMaxNegativeSpeedIncrement(struct MotorController* controller, int16_t inc);


int16_t MotorController_maxSpeed(struct MotorController* controller);
void MotorController_setMaxSpeed(struct MotorController* controller, int16_t inc);

#endif
