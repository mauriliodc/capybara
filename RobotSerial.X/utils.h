/* 
 * File:   utils.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:08 PM
 */

#ifndef UTILS_H
#define	UTILS_H

void toggleLed1() {
    if (LED1)LED1 = 0;
    else if (LED1 == 0)LED1 = 1;
}

void toggleLed2() {
    if (LED2 == 1)LED2 = 0;
    else if (LED2 == 0)LED2 = 1;
}

void DelayN10us(int n) // [22]
{
    int DelayCount;
    for (DelayCount = 0; DelayCount < (57 * n); DelayCount++);
}

void DelayN1ms(int n) {
    int ms;
    for (ms = 0; ms < n; ms++) {
        DelayN10us(100);
    }
}

void enableMotor1() {
    SetDCMCPWM1(1, 2048, 0); //0->4095 //pwmInitSpeed defined in dsPid33.c
}

void enableMotor2() {
    SetDCMCPWM1(2, 2048, 0); //0->4095 //pwmInitSpeed defined in dsPid33.c //SECONDO MOTORE, 0);
}

#define MOTOR_FREQ(freqHz)      (P1TPER = FCY  / 64 / freqHz -1)
#define MOTOR1_DUTY(percent)    (P1DC1 = (2UL*P1TPER+2)*percent/100)

void enableMotors() {
    //TRISTATE SETTATI COME OUTPUT
    	_TRISB0  = 0;
	_TRISB1	 = 0;
	_TRISB4	 = 0;
	_TRISB9	 = 0;
    TRISBbits.TRISB12 = 0b0; //pwm
    TRISBbits.TRISB13 = 0b0; //pwm
    TRISBbits.TRISB14 = 0b0; //pwm
    TRISBbits.TRISB15 = 0b0; //pwm
    //DIREZIONE DEI MOTORI
    LATBbits.LATB14 = 1; //dir
    LATBbits.LATB12 = 0; //dir

    unsigned int period = 1999;
    unsigned int sptime = 0x0;
    unsigned int config1 = PWM1_EN & PWM1_IDLE_CON & PWM1_OP_SCALE1 & PWM1_IPCLK_SCALE4 & PWM1_MOD_FREE;
    unsigned int config2 = PWM1_MOD1_COMP & PWM1_PEN1L & PWM1_PDIS1H & PWM1_MOD2_COMP & PWM1_PEN2L & PWM1_PDIS2H & PWM1_PDIS3H & PWM1_PDIS3L;
    unsigned int config3 = PWM1_SEVOPS1 & PWM1_OSYNC_PWM & PWM1_UEN;
    OpenMCPWM1(period, sptime, config1, config2, config3);
    SetDCMCPWM1(1, 3000, 0); //MOTORE R
    SetDCMCPWM1(2, 3000, 0); //MOTORE L
    
}




#endif	/* UTILS_H */

