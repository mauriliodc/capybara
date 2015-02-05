/* 
 * File:   configurationData.h
 * Author: malcom
 *
 * Created on 5 febbraio 2015, 17.35
 */

#ifndef CONFIGURATIONDATA_H
#define	CONFIGURATIONDATA_H

#include <uart.h>
#include "Eeprom.h"

#define ADDR_programmed 2
#define ADDR_lmd 4
#define ADDR_lmi 6
#define ADDR_lmm 8

#define ADDR_rmd 10
#define ADDR_rmi 12
#define ADDR_rmm 14

#define ADDR_lpkd 16
#define ADDR_lpki 18
#define ADDR_lpkp 20
#define ADDR_lpkw 22
#define ADDR_lpp 24

#define ADDR_rpkd 26
#define ADDR_rpki 28
#define ADDR_rpkp 30
#define ADDR_rpkw 32
#define ADDR_rpp 34

#define ADDR_pwmo 36

#define ADDR_odop 38
#define ADDR_odob 40
#define ADDR_odortl 44
#define ADDR_odortr 48
#define ADDR_odorl 52
#define ADDR_odorr 56



struct _pwmConfiguration{
    int period;
};

struct _pidConfiguration{
    int kp;
    int ki;
    int kd;
    int kwindup;
    int period;
};

enum _motorMode{
    Independant,
    Complementary
};

struct _motorControllerConfiguration{
    int increment;
    int decrement;
    enum _motorMode motorMode;

};

struct _odometryConfiguration{
    float baseline;
    float radiusLeft;
    float radiusRight;
    float radiansPerTickLeft;
    float radiansPerTickRight;
    int period;
};



struct _configuration{
    int programmed;
    struct _pwmConfiguration pwm;
    struct _pidConfiguration leftPid;
    struct _pidConfiguration rightPid;
    struct _motorControllerConfiguration leftMotor;
    struct _motorControllerConfiguration rightMotor;
    struct _odometryConfiguration odometry;
};


int initEeprom();
void writeConfigurationToEeprom(const struct _configuration* conf);
void readConfigurationFromEeprom(struct _configuration* conf);
void debugConfigurationDataToSerial(const struct _configuration* conf);


#endif	/* CONFIGURATIONDATA_H */

