/* 
 * File:   pwm_controller.h
 * Author: malcom
 *
 * Created on June 12, 2013, 3:00 PM
 */


#include <p33Fxxxx.h>
#include <pwm12.h>
#include "platform_defs.h"

#ifndef PWM_CONTROLLER_H
#define	PWM_CONTROLLER_H

#define NUM_PWMS 2

struct PWM
{
    uint16_t dutyCycle;
    uint16_t period;
};

struct PWMController
{
    struct PWM* pwms[2];
};

void PWMController_init(struct PWMController* controller, uint16_t period);

uint8_t PWMController_num(const struct PWMController* controller);

int16_t PWMController_period(const struct  PWMController* controller,uint8_t numPwm);

void PWMController_setPeriod(struct PWMController* controller, uint16_t period,uint8_t numPwm);

uint16_t PWMController_dutycycle(const struct PWMController* controller, uint8_t pwmNum);

void PWMController_setDutycycle(struct PWMController* controller, uint8_t pwmNum, int16_t dutycycle);


#endif	/* PWM_CONTROLLER_H */

