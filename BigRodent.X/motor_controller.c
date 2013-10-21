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

    int d = control / 34 + 1024;
    //======================

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




    //    char a[200];
    //    sprintf(a,"P: %d I: %d  D: %d  ERR: %d TICK: %d MEASUR: %d DESIRED: %d PID: %d EXEC: %d  DUTY: %d\n", ca->_Pi,
    //                                                                    ca->_I,
    //                                                                    ca->_D,
    //                                                                    ca->_error,
    //                                                                    MotorController_measuredSpeed(mc),
    //                                                                    ca->_base._measure,
    //                                                                    MotorController_desiredSpeed(mc),
    //                                                                    ca->_base._control,
    //                                                                    t->_lastUpperHalfExecutionTime,
    //                                                                    PWMController_dutycycle(mc->_pwms,mc->_pwnNum)
    //                                                                    );
    //
    //        sprintf(a,"#%d, %d          @\n",mc->_encoderNum,MotorController_measuredSpeed(mc));
    //        putsUART1((unsigned int *) a);

}

void MotorController_setDesiredSpeed(struct MotorController* controller, int16_t speed) {

    controller->_desiredSpeed = speed;


}

int16_t MotorController_desiredSpeed(struct MotorController* controller) {
    return controller->_desiredSpeed;
}

int16_t MotorController_measuredSpeed(struct MotorController* controller) {
    return controller->_measuredSpeed;
}

int16_t MotorController_measuredDistance(struct MotorController* controller) {
    return controller->_measuredDistance;
}

int16_t MotorController_setMeasuredDistance(struct MotorController* controller, uint16_t ticks) {
    int16_t distance = controller->_measuredDistance;
    controller->_measuredDistance = 0;
    return distance;
}

int16_t MotorController_maxPositiveSpeedIncrement(struct MotorController* controller) {
    return controller->_maxPositiveSpeedIncrement;
}

int16_t MotorController_maxNegativeSpeedIncrement(struct MotorController* controller) {
    return controller->_maxNegativeSpeedIncrement;
}

void MotorController_setMaxPositiveSpeedIncrement(struct MotorController* controller, int16_t inc) {
    controller->_maxPositiveSpeedIncrement = inc;
}

void MotorController_setMaxNegativeSpeedIncrement(struct MotorController* controller, int16_t inc) {
    controller->_maxNegativeSpeedIncrement = inc;
}

int16_t MotorController_maxPositiveeSpeed(struct MotorController* controller);
void MotorController_setPositiveMaxSpeed(struct MotorController* controller, int16_t inc);
int16_t MotorController_maxNegativeSpeed(struct MotorController* controller);
void MotorController_setNegativeMaxSpeed(struct MotorController* controller, int16_t inc);
