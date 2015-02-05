#include "pwm_controller.h"
#include "defines.h"

//PWM configuration
void PWMController_init(struct PWMController* controller, uint16_t period)
{
    //TRISTATE SETTATI COME OUTPUT
    _TRISB0 = 0;
    _TRISB1 = 0;
    _TRISB4 = 0;
    _TRISB9 = 0;
    _TRISB12 = 0;
    _TRISB14 = 0;

    //PWM
    TRISBbits.TRISB12 = 0b0;
    TRISBbits.TRISB13 = 0b0;
    TRISBbits.TRISB14 = 0b0;
    TRISBbits.TRISB15 = 0b0;

    unsigned int sptime = 0x0;
    unsigned int config1 = PWM1_EN & PWM1_IDLE_CON & PWM1_OP_SCALE1 & PWM1_IPCLK_SCALE1 & PWM1_MOD_UPDN;
    unsigned int config2;
    //TANK 3A
    if(PWMMODE==0)
    config2 = PWM1_MOD1_IND & PWM1_PEN1L & PWM1_PDIS1H & PWM1_MOD2_IND & PWM1_PEN2L & PWM1_PDIS2H & PWM1_PDIS3H & PWM1_PDIS3L;

    //COMPLEMENTARY
    if(PWMMODE==1)
    config2 = PWM1_MOD1_COMP & PWM1_PEN1L & PWM1_PEN1H & PWM1_MOD2_COMP & PWM1_PEN2L & PWM1_PEN2H & PWM1_PDIS3H & PWM1_PDIS3L;

    unsigned int config3 = PWM1_SEVOPS1 & PWM1_OSYNC_PWM & PWM1_UEN;
    OpenMCPWM1(period, sptime, config1, config2, config3);


}

//get number of pwm controllers
uint8_t PWMController_num(const struct PWMController* controller)
{
    return NUM_PWMS;
}

//get pwm period
int16_t PWMController_period(const struct  PWMController* controller,uint8_t numPwm)
{
    return controller->pwms[numPwm]->period;

}

//set pwm period
void PWMController_setPeriod(struct PWMController* controller, uint16_t period,uint8_t numPwm)
{
    controller->pwms[numPwm]->period=period;
}

//get pwm duty cycle
uint16_t PWMController_dutycycle(const struct PWMController* controller, uint8_t numPwm)
{
    return controller->pwms[numPwm]->dutyCycle;
}

//set pwm dutycyle
void PWMController_setDutycycle(struct PWMController* controller, uint8_t numPwm, int16_t dutycycle)
{
    controller->pwms[numPwm]->dutyCycle=dutycycle;   
    SetDCMCPWM1(numPwm+1, dutycycle,0);
}