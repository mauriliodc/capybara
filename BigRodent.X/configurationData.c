#include "configurationData.h"
#include <stdio.h>
int initEeprom() {
    DataEEInit();
    dataEEFlags.val = 0;

    int programmed = DataEERead(ADDR_programmed);
    printf("STATUS: %d\n", dataEEFlags.addrNotFound);
    printf("STATUS: %d\n\n--------\n", dataEEFlags.val);
    if (dataEEFlags.addrNotFound == 0) {
        programmed++;
        DataEEWrite(programmed, ADDR_programmed);
        printf("Eeprom has data\n");
        return 1;
    } else if (dataEEFlags.addrNotFound == 1) {
        programmed = DataEEWrite(1, ADDR_programmed);
        printf("Eeprom NEW\n");
        return 0;
    }
    return 0;
}

void writeConfigurationToEeprom(const struct _configuration* conf) {
    DataEEWrite(conf->leftMotor.decrement, ADDR_lmd);
    DataEEWrite(conf->leftMotor.increment, ADDR_lmi);
    DataEEWrite(conf->leftMotor.motorMode, ADDR_lmm);

    DataEEWrite(conf->rightMotor.decrement, ADDR_rmd);
    DataEEWrite(conf->rightMotor.increment, ADDR_rmi);
    DataEEWrite(conf->rightMotor.motorMode, ADDR_rmm);

    DataEEWrite(conf->leftPid.kd, ADDR_lpkd);
    DataEEWrite(conf->leftPid.ki, ADDR_lpki);
    DataEEWrite(conf->leftPid.kp, ADDR_lpkp);
    DataEEWrite(conf->leftPid.kwindup, ADDR_lpkw);
    DataEEWrite(conf->leftPid.period, ADDR_lpp);

    DataEEWrite(conf->rightPid.kd, ADDR_rpkd);
    DataEEWrite(conf->rightPid.ki, ADDR_rpki);
    DataEEWrite(conf->rightPid.kp, ADDR_rpkp);
    DataEEWrite(conf->rightPid.kwindup, ADDR_rpkw);
    DataEEWrite(conf->rightPid.period, ADDR_rpp);

    DataEEWrite(conf->pwm.period, ADDR_pwmp);

    DataEEWrite(conf->odometry.period, ADDR_odop);
    DataEEWrite(conf->odometry.baseline, ADDR_odob);
    DataEEWrite(conf->odometry.radiansPerTickLeft, ADDR_odortl);
    DataEEWrite(conf->odometry.radiansPerTickRight, ADDR_odortr);
    DataEEWrite(conf->odometry.radiusLeft, ADDR_odorl);
    DataEEWrite(conf->odometry.radiusRight, ADDR_odorr);

}

void readConfigurationFromEeprom(struct _configuration* conf) {
    conf->leftMotor.decrement = DataEERead(ADDR_lmd);
    conf->leftMotor.increment = DataEERead(ADDR_lmi);
    conf->leftMotor.motorMode = DataEERead(ADDR_lmm);

    conf->rightMotor.decrement = DataEERead(ADDR_rmd);
    conf->rightMotor.increment = DataEERead(ADDR_rmi);
    conf->rightMotor.motorMode = DataEERead(ADDR_rmm);

    conf->leftPid.kp = DataEERead(ADDR_lpkd);
    conf->leftPid.ki = DataEERead(ADDR_lpki);
    conf->leftPid.kd = DataEERead(ADDR_lpkp);
    conf->leftPid.kwindup = DataEERead(ADDR_lpkw);
    conf->leftPid.period = DataEERead(ADDR_lpp);

    conf->rightPid.kp = DataEERead(ADDR_rpkd);
    conf->rightPid.ki = DataEERead(ADDR_rpki);
    conf->rightPid.kd = DataEERead(ADDR_rpkp);
    conf->rightPid.kwindup = DataEERead(ADDR_rpkw);
    conf->rightPid.period = DataEERead(ADDR_rpp);

    conf->pwm.period = DataEERead(ADDR_pwmp);

    conf->odometry.period = DataEERead(ADDR_odop);
    conf->odometry.baseline = (float) DataEERead(ADDR_odob);
    conf->odometry.radiansPerTickLeft = (float) DataEERead(ADDR_odortl);
    conf->odometry.radiansPerTickRight = (float) DataEERead(ADDR_odortr);
    conf->odometry.radiusLeft = (float) DataEERead(ADDR_odorl);
    conf->odometry.radiusRight = (float) DataEERead(ADDR_odorr);

}

void debugConfigurationDataToSerial(const struct _configuration* conf) {

    printf("\nDumping configuration data\r\n");
    printf("-------------------------------\r\n");
    printf("PWM\r\n");
    printf("[%d] period %d\n", ADDR_pwmp, conf->pwm.period);
    printf("\nLEFT PID\r\n");
    printf("[%d] P %d\n", ADDR_lpkd, conf->leftPid.kp);
    printf("[%d] I %d\n", ADDR_lpki, conf->leftPid.ki);
    printf("[%d] D %d\n", ADDR_lpkp, conf->leftPid.kd);
    printf("[%d] Windup %d\n", ADDR_lpkw, conf->leftPid.kwindup);
    printf("[%d] period %d\n", ADDR_lpp, conf->leftPid.period);
    printf("\nRIGHT PID\r\n");
    printf("[%d] P %d\n", ADDR_rpkd, conf->rightPid.kp);
    printf("[%d] I %d\n", ADDR_rpki, conf->rightPid.ki);
    printf("[%d] D %d\n", ADDR_rpkp, conf->rightPid.kd);
    printf("[%d] Windup %d\n", ADDR_rpkw, conf->rightPid.kwindup);
    printf("[%d] period %d\n", ADDR_rpp, conf->rightPid.period);
    printf("\nLEFT MOTOR\r\n");
    printf("[%d] increment %d\n", ADDR_lmd, conf->leftMotor.increment);
    printf("[%d] decrement %d\n", ADDR_lmi, conf->leftMotor.decrement);
    printf("[%d] mode %d\n", ADDR_lmm, conf->leftMotor.motorMode);
    printf("\nRIGHT MOTOR\r\n");
    printf("[%d] increment %d\n", ADDR_rmd, conf->rightMotor.increment);
    printf("[%d] decrement %d\n", ADDR_rmi, conf->rightMotor.decrement);
    printf("[%d] mode %d\n", ADDR_rmm, conf->rightMotor.motorMode);
    printf("\nODOMETRY\r\n");
    //STUPID FLOAT->DOUBLE CONVERSION TO SILENCE THE WARNINGS
    printf("[%d] baseline %f\n", ADDR_odob, (double)conf->odometry.baseline);
    printf("[%d] leftwheel radius %f\n", ADDR_odorl, (double)conf->odometry.radiusLeft);
    printf("[%d] rightwheel radius %f\n", ADDR_odorr, (double)conf->odometry.radiusRight);
    printf("[%d] radians per tick left %f\n", ADDR_odortl, (double)conf->odometry.radiansPerTickLeft);
    printf("[%d] radians per tick right %f\n", ADDR_odortr, (double)conf->odometry.radiansPerTickRight);
    printf("[%d] period %d\n", ADDR_odop, conf->odometry.period);
    printf("-------------------------------\r\n\n");
}
