#include "pwn_controller.h"

struct PWMController;

void PWMController_init(PWMController* controller, uint16_t period);

uint8_t PWMController_num(const PWMController* controller);

uint16_t PWMController_period(const PWMController* controller);

void PWMController_setPeriod(PWMController* controller, uint16_t period);

uint16_t PWMController_dutycycle(const PWMController* controller, uint8_t pwmNum);

void PWMController_setDutycycle(PWMController* controller, uint8_t pwmNum, uint16_t dutycycle);

#endif
