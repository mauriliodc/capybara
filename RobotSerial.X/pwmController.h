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
    int directionPTR;
    unsigned int* directionRegister;
    int speed;
    int direction;
};

struct PWMController
{
    struct PWM* pwm1;
    struct PWM* pwm2;
};


void PWMinit(struct PWM* p,volatile unsigned int* d, int offset)
{
    p->directionRegister=d;
    p->speed=0;
    p->directionPTR=offset;
}

void PWMForward(struct PWM* p)
{

    (*p->directionRegister)=(*(p->directionRegister))|p->directionPTR;
    
}

void PWMBackward(struct PWM* p)
{

    (*p->directionRegister)=(*(p->directionRegister))&(p->directionPTR^0b1111111111111111);
    
}

void PWMSetDirection(struct PWM* p,int direction)
{
    if(direction==1)   PWMForward(p);
    if(direction==-1)  PWMBackward(p);
}

void PWMinitController(struct PWMController* p, struct PWM* p1, struct PWM* p2)
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
    unsigned int config1 = PWM1_EN & PWM1_IDLE_CON & PWM1_OP_SCALE1 & PWM1_IPCLK_SCALE1 & PWM1_MOD_UPDN;
    unsigned int config2 = PWM1_MOD1_IND & PWM1_PEN1L & PWM1_PDIS1H & PWM1_MOD2_IND & PWM1_PEN2L & PWM1_PDIS2H & PWM1_PDIS3H & PWM1_PDIS3L;
    unsigned int config3 = PWM1_SEVOPS1 & PWM1_OSYNC_PWM & PWM1_UEN;
    OpenMCPWM1(period, sptime, config1, config2, config3);

    p->pwm1=p1;
    p->pwm2=p2;

    p->pwm1->speed=0;
    p->pwm2->speed=0;
    p->pwm1->direction=0;
    p->pwm2->direction=0;
    PWMForward(p->pwm1);
    PWMForward(p->pwm2);
    
    SetDCMCPWM1(1, p->pwm1->speed, 0); //MOTORE R
    SetDCMCPWM1(2, p->pwm2->speed, 0); //MOTORE L
}

void PWMControllerDisable(struct PWMController* p)
{

}

void PWMControllerSetSpeed(struct PWMController* p, int speed,int direction,int motor)
{
    //if motor 1 or 2 set speed and direction to a single motor
    //if motor 0 set speed and direction to both motors
    
    if(motor==1)
    {
        p->pwm1->speed=speed;
        PWMSetDirection(p->pwm1,direction);
    }
    if(motor==2)
    {
        p->pwm2->speed=speed;
        PWMSetDirection(p->pwm2,direction);
    }
    if(motor==0)
    {
       p->pwm1->speed=speed;
       p->pwm2->speed=speed;
       PWMSetDirection(p->pwm1,direction);
       PWMSetDirection(p->pwm2,direction);
    }

    SetDCMCPWM1(1, p->pwm1->speed, 0); //MOTORE R
    SetDCMCPWM1(2, p->pwm2->speed, 0); //MOTORE L
}

#endif	/* PWMCONTROLLER_H */

