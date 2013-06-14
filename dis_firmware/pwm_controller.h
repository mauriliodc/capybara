#ifndef _PWN_CONTROLLER_H_
#define _PWN_CONTROLLER_H_

struct PWMController;


// mettere un int in dutycycle

void PWMController_init(PWMController* controller, uint16_t period);

uint8_t PWMController_num(const PWMController* controller);

uint16_t PWMController_period(const PWMController* controller);

void PWMController_setPeriod(PWMController* controller, uint16_t period);

uint16_t PWMController_dutycycle(const PWMController* controller, uint8_t pwmNum);

void PWMController_setDutycycle(PWMController* controller, uint8_t pwmNum, uint16_t dutycycle);

#endif