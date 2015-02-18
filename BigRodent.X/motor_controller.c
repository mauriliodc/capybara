#include "motor_controller.h"
#include "defines.h"


void MotorController_UpperHandler(struct TimerEvent* t);
void MotorController_LowerHandler(struct TimerEvent* t);

void MotorController_init(struct MotorController* mc,
        struct EncoderController* encoders, uint8_t encoderNum,
        struct PWMController* pwms, uint8_t pwnNum,
        int16_t directionPin, uint16_t* directionPTR,
        struct ControlAlgorithm* algorthm, int16_t period) {
    TimerEvent_init(&mc->event, &MotorController_UpperHandler, &MotorController_LowerHandler, period);
    mc->_ca = algorthm;
    mc->_ec = encoders;
    mc->_encoderNum = encoderNum;
    mc->_pwms = pwms;
    mc->_pwnNum = pwnNum;
    mc->_directionPin = directionPin;
    mc->_directionPTR = directionPTR;


}

void MotorController_UpperHandler(struct TimerEvent* t) {
    struct MotorController* mc = (struct MotorController*) t;
    mc->_measuredSpeed = EncoderController_setTicks(mc->_ec, mc->_encoderNum, 0);
    mc->_measuredDistance += mc->_measuredSpeed;

    int speed = mc->_desiredSpeed;

    //POSITIVE INCREMENT
    if (speed >= mc->_measuredSpeed) {
        if (speed > mc->_measuredSpeed + mc->_maxPositiveSpeedIncrement) {
            speed = mc->_measuredSpeed + mc->_maxPositiveSpeedIncrement;

        }
    }        //NEGATIVE DECREMENT
    else {
        if (speed < mc->_measuredSpeed - mc->_maxNegativeSpeedIncrement) {
            speed = mc->_measuredSpeed - mc->_maxNegativeSpeedIncrement;

        }
    }


    //int16_t control = ControlAlgorithm_update(mc->_ca, mc->_measuredSpeed, mc->_desiredSpeed);
    //control += mc->_desiredSpeed;
    int16_t control = ControlAlgorithm_update(mc->_ca, mc->_measuredSpeed, speed);


    control += speed;

    //COMPLEMENTARY
    //TODO:
    //one day this line could be written better, at the moment
    //34 is not a voodo number, just a regular one that do its job.
    //We need to conditionate the control value because in the complementary
    //mode we need to have something in 0-2048 with a different meaning
    //w.r.t the independant mode
    int d = control / 34 + 1024;
    
    //TANK 3A
    if (PWMMODE == 0) {
        d = control;
    }
    MotorController_setPWM(mc, d);
}

void MotorController_setPWM(struct MotorController* mc, int16_t speed) {


    //TANK 3A
    if (PWMMODE == 0) {
        int absSpeed = speed;
        if (speed >= 0)
            (*mc->_directionPTR) = (*(mc->_directionPTR)) | mc->_directionPin;
        else {
            (*mc->_directionPTR) = (*(mc->_directionPTR))&(mc->_directionPin^0b1111111111111111);
            absSpeed = -speed;
        }

        //TANK 3A
        speed = absSpeed;
    }

    PWMController_setDutycycle(mc->_pwms, mc->_pwnNum, speed);
}

void MotorController_LowerHandler(struct TimerEvent* t) {
    //struct MotorController* mc = (struct MotorController*) t;
    //struct PIDControlAlgorithm* ca = (struct PIDControlAlgorithm*)mc->_ca;
}

//Impose desired speed on desired motor controller
void MotorController_setDesiredSpeed(struct MotorController* controller, int16_t speed) {
    controller->_desiredSpeed = speed;
}

//Get desired speed on desired motor controller
int16_t MotorController_desiredSpeed(struct MotorController* controller) {
    return controller->_desiredSpeed;
}

//Get measured speed on desired motor controller
int16_t MotorController_measuredSpeed(struct MotorController* controller) {
    return controller->_measuredSpeed;
}
//Get measured distance on desired motor controller
int16_t MotorController_measuredDistance(struct MotorController* controller) {
    return controller->_measuredDistance;
}
//Set measured distance on desired motor controller
int16_t MotorController_setMeasuredDistance(struct MotorController* controller, uint16_t ticks) {
    int16_t distance = controller->_measuredDistance;
    controller->_measuredDistance = 0;
    return distance;
}

//Get max increment per interval (defines a velocity profile on motor)
int16_t MotorController_maxPositiveSpeedIncrement(struct MotorController* controller) {
    return controller->_maxPositiveSpeedIncrement;
}
//Get max decrement per interval (defines a velocity profile on motor)
int16_t MotorController_maxNegativeSpeedIncrement(struct MotorController* controller) {
    return controller->_maxNegativeSpeedIncrement;
}

//Set max increment per interval (defines a velocity profile on motor)
void MotorController_setMaxPositiveSpeedIncrement(struct MotorController* controller, int16_t inc) {
    controller->_maxPositiveSpeedIncrement = inc;
}
//Set max decrement per interval (defines a velocity profile on motor)
void MotorController_setMaxNegativeSpeedIncrement(struct MotorController* controller, int16_t inc) {
    controller->_maxNegativeSpeedIncrement = inc;
}

int16_t MotorController_maxPositiveeSpeed(struct MotorController* controller);
void MotorController_setPositiveMaxSpeed(struct MotorController* controller, int16_t inc);
int16_t MotorController_maxNegativeSpeed(struct MotorController* controller);
void MotorController_setNegativeMaxSpeed(struct MotorController* controller, int16_t inc);
