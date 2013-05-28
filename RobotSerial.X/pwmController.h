/* 
 * File:   pwmController.h
 * Author: malcom
 *
 * Created on May 28, 2013, 4:48 PM
 */

#ifndef PWMCONTROLLER_H
#define	PWMCONTROLLER_H

struct PWM
{
    LATBBITS* directionPTR;
    int speedTick;
};

struct PWMController
{
    struct PWM* pwm1;
    struct PWM* pwm2;
    int enabled;
    

};


void PWMinitController(struct PWMController*)
{
    //TRISTATE SETTATI COME OUTPUT
    _TRISB0 = 0;
    _TRISB1 = 0;
    _TRISB4 = 0;
    _TRISB9 = 0;
    //PWM
    TRISBbits.TRISB12 = 0b0;
    TRISBbits.TRISB13 = 0b0; 
    TRISBbits.TRISB14 = 0b0;
    TRISBbits.TRISB15 = 0b0;

    unsigned int period = 1999;
    unsigned int sptime = 0x0;
    unsigned int config1 = PWM1_EN & PWM1_IDLE_CON & PWM1_OP_SCALE1 & PWM1_IPCLK_SCALE4 & PWM1_MOD_FREE;
    unsigned int config2 = PWM1_MOD1_COMP & PWM1_PEN1L & PWM1_PDIS1H & PWM1_MOD2_COMP & PWM1_PEN2L & PWM1_PDIS2H & PWM1_PDIS3H & PWM1_PDIS3L;
    unsigned int config3 = PWM1_SEVOPS1 & PWM1_OSYNC_PWM & PWM1_UEN;
    OpenMCPWM1(period, sptime, config1, config2, config3);

    PWMController->enabled=1;
}

void PWMEnableController(struct PWMController*)
{
    PWMController->enabled=1;
}

void PWMDisableController(struct PWMController*)
{
    PWMController->enabled=0;
}

void PWMSetSpeed(struct PWMController*, int motor, int speed)
{
    
}

int PWMGetSpeed(struct PWMController*, int motor)
{

}



#endif	/* PWMCONTROLLER_H */

