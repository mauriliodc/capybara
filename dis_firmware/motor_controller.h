#ifndef _MOTOR_CONTROLLER_H
#define _MOTOR_CONTROLLER_H
#include "encoder_controller.h"
#include "pwm_controller.h"

struct MotorController;

MotorController_init(EncoderController* encoders, uint8_t  encoderNum, 
		     PWMController* pwms, uint8_t pwnNum, 
		     ControlAlgorithm* algorthm, int16_t period);

int16_t MotorController_period();
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

