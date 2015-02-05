#include "configurationData.h"

int initEeprom(){
  int programmed = DataEERead(ADDR_programmed);
  printf("STATUS: %d\n",dataEEFlags.addrNotFound);
  printf("STATUS: %d\n\n--------\n",dataEEFlags.val);
  if(dataEEFlags.addrNotFound==0){
    programmed++;
    DataEEWrite(programmed,ADDR_programmed);
    printf("Eeprom has data\n");
    return 1;
  }
  else if(dataEEFlags.addrNotFound==1){
    programmed=DataEEWrite(1,ADDR_programmed);
    printf("Eeprom NEW\n");
    return 0;
  }
}
void writeConfigurationToEeprom(const struct _configuration* conf) {
DataEEWrite(conf->leftMotor.decrement,ADDR_lmd);
DataEEWrite(conf->leftMotor.increment,ADDR_lmi);
DataEEWrite(conf->leftMotor.motorMode,ADDR_lmm);

DataEEWrite(conf->rightMotor.decrement,ADDR_rmd);
DataEEWrite(conf->rightMotor.increment,ADDR_rmi);
DataEEWrite(conf->rightMotor.motorMode,ADDR_rmm);

DataEEWrite(conf->leftPid.kd,ADDR_lpkd);
DataEEWrite(conf->leftPid.ki,ADDR_lpki);
DataEEWrite(conf->leftPid.kp,ADDR_lpkp);
DataEEWrite(conf->leftPid.kwindup,ADDR_lpkw);
DataEEWrite(conf->leftPid.period,ADDR_lpp);

DataEEWrite(conf->rightPid.kd,ADDR_rpkd);
DataEEWrite(conf->rightPid.ki,ADDR_rpki);
DataEEWrite(conf->rightPid.kp,ADDR_rpkp);
DataEEWrite(conf->rightPid.kwindup,ADDR_rpkw);
DataEEWrite(conf->rightPid.period,ADDR_rpp);

DataEEWrite(conf->pwm.period,ADDR_pwmo);

DataEEWrite(conf->odometry.period,ADDR_odop);
DataEEWrite(conf->odometry.baseline,ADDR_odob);
DataEEWrite(conf->odometry.radiansPerTickLeft,ADDR_odortl);
DataEEWrite(conf->odometry.radiansPerTickRight,ADDR_odortr);
DataEEWrite(conf->odometry.radiusLeft,ADDR_odorl);
DataEEWrite(conf->odometry.radiusRight,ADDR_odorr);

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
    
    conf->pwm.period = DataEERead(ADDR_pwmo);
    
    conf->odometry.period = DataEERead(ADDR_odop);
    conf->odometry.baseline = (float)DataEERead(ADDR_odob);
    conf->odometry.radiansPerTickLeft = (float)DataEERead(ADDR_odortl);
    conf->odometry.radiansPerTickRight = (float)DataEERead(ADDR_odortr);
    conf->odometry.radiusLeft = (float)DataEERead(ADDR_odorl);
    conf->odometry.radiusRight = (float)DataEERead(ADDR_odorr);

}

void debugConfigurationDataToSerial(const struct _configuration* conf) {

    printf("\nDumping configuration data\r\n");
    printf("-------------------------------\r\n");
    printf("PWM\r\n");
    printf("%d\n", conf->pwm.period);
    printf("\nLEFT PID\r\n");
    printf("%d\n", conf->leftPid.kp);
    printf("%d\n", conf->leftPid.ki);
    printf("%d\n", conf->leftPid.kd);
    printf("%d\n", conf->leftPid.kwindup);
    printf("%d\n", conf->leftPid.period);
    printf("\nRIGHT PID\r\n");
    printf("%d\n", conf->rightPid.kp);
    printf("%d\n", conf->rightPid.ki);
    printf("%d\n", conf->rightPid.kd);
    printf("%d\n", conf->rightPid.kwindup);
    printf("%d\n", conf->rightPid.period);
    printf("\nLEFT MOTOR\r\n");
    printf("%d\n", conf->leftMotor.increment);
    printf("%d\n", conf->leftMotor.decrement);
    printf("%d\n", conf->leftMotor.motorMode);
    printf("\nRIGHT MOTOR\r\n");
    printf("%d\n", conf->rightMotor.increment);
    printf("%d\n", conf->rightMotor.decrement);
    printf("%d\n", conf->rightMotor.motorMode);
    printf("\nODOMETRY\r\n");
    printf("%f\n", conf->odometry.baseline);
    printf("%f\n", conf->odometry.radiusLeft);
    printf("%f\n", conf->odometry.radiusRight);
    printf("%f\n", conf->odometry.radiansPerTickLeft);
    printf("%f\n", conf->odometry.radiansPerTickRight);
    printf("%d\n", conf->odometry.period);
    printf("-------------------------------\r\n\n");
}
