/* 
 * File:   interrupts.h
 * Author: malcom
 *
 * Created on May 9, 2013, 1:07 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include "pid.h"

char posPacket[9];

char mio[] = "Board ready\n\0";
char message[] = "Message received\n\0";
char PID[10];

float velocityMotor1=0;
float velocityMotor2=0;

float requestVelocityMotor1=0;
float requestVelocityMotor2=0;

int tick1=0;
int tick2=0;
int inc=0;
int inc2=0;

extern struct PID pidmotor1;
extern struct PID pidmotor2;
int wrapAround1=0;
int wrapAround2=0;
float metersW1=0;
float metersW2=0;
float tmp=0;
void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void) {
    secAcc++;
    millisec20++;
    if (secAcc == 1000) {
        toggleLed1();

        secAcc = 0;
        LED2 = 0;

        sprintf(PID,"%f",pidmotor1.PID);
        putsUART1((unsigned int *)"PID1: ");
        putsUART1((unsigned int *)PID);

        sprintf(PID,"%f",pidmotor2.PID);
        putsUART1((unsigned int *)" PID2: ");
        putsUART1((unsigned int *)PID);

        sprintf(PID,"%d",POS1CNT);
        putsUART1((unsigned int *)" ENC1: ");
        putsUART1((unsigned int *)PID);

        sprintf(PID,"%d",POS2CNT);
        putsUART1((unsigned int *)" ENC2: ");
        putsUART1((unsigned int *)PID);
        
        putsUART1((unsigned int *)"\n");

        sprintf(PID,"%u",tick1);
        putsUART1((unsigned int *)"TICK1 : ");
        putsUART1((unsigned int *)PID);

        sprintf(PID,"%u",tick2);
        putsUART1((unsigned int *)" TICK2 : ");
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)"\n");

        putsUART1((unsigned int *)"V1 RICHIESTA: ");
        sprintf(PID,"%f",requestVelocityMotor1);
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)" V1 EFFETTIVA: ");
        sprintf(PID,"%f",(float)(POS1CNT*METERPERTICK1));
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)" V1 INC: ");
        sprintf(PID,"%d",inc);
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)"\n");

        putsUART1((unsigned int *)"V2 RICHIESTA: ");
        sprintf(PID,"%f",requestVelocityMotor2);
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)" V2 EFFETTIVA: ");
        sprintf(PID,"%f",(float)(POS2CNT*METERPERTICK2));
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)" V2 INC: ");
        sprintf(PID,"%d",inc2);
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)"\n");

        putsUART1((unsigned int *)"V->1: ");
        sprintf(PID,"%f",velocityMotor1);
        putsUART1((unsigned int *)PID);

        putsUART1((unsigned int *)" V->2: ");
        sprintf(PID,"%f",velocityMotor2);
        putsUART1((unsigned int *)PID);

        putsUART1((unsigned int *)" KONSTANT ");
        sprintf(PID,"%f",TICKPERMETER1);
        putsUART1((unsigned int *)PID);
        putsUART1((unsigned int *)"\n");
        putsUART1((unsigned int *)"\n");
        
    }

    if(millisec20>=20 )
    {
        millisec20=0;
//
//        putsUART1((unsigned int *)"--------------------------------\n");
//        sprintf(PID,"%f",pidmotor1.I);
//        putsUART1((unsigned int *)"I: ");
//        putsUART1((unsigned int *)PID);
//
//        sprintf(PID,"%f",pidmotor1.D);
//        putsUART1((unsigned int *)" D: ");
//        putsUART1((unsigned int *)PID);
//
//        sprintf(PID,"%f",pidmotor1.P);
//        putsUART1((unsigned int *)" P: ");
//        putsUART1((unsigned int *)PID);
//
//        sprintf(PID,"%f",pidmotor1.error);
//        putsUART1((unsigned int *)" ERR: ");
//        putsUART1((unsigned int *)PID);
//
//        sprintf(PID,"%f",pidmotor1.reference);
//        putsUART1((unsigned int *)" REF: ");
//        putsUART1((unsigned int *)PID);
//
//        sprintf(PID,"%f",pidmotor1.PID);
//        putsUART1((unsigned int *)" PID: ");
//        putsUART1((unsigned int *)PID);
//        putsUART1((unsigned int *)"\n");
//
//        putsUART1((unsigned int *)"VEL RICHIESTA: ");
//        sprintf(PID,"%f",requestVelocityMotor1);
//        putsUART1((unsigned int *)PID);
//        putsUART1((unsigned int *)" VEL ATTUALE: ");
//        sprintf(PID,"%f",(float)(POS1CNT*METERPERTICK1));
//        putsUART1((unsigned int *)PID);
//        putsUART1((unsigned int *)"\n");
//
//        putsUART1((unsigned int *)"TICK RICHIESTI: ");
//        sprintf(PID,"%d",tick1);
//        putsUART1((unsigned int *)PID);
//        putsUART1((unsigned int *)" TICK ATTUALI: ");
//        sprintf(PID,"%d",POS1CNT);
//        putsUART1((unsigned int *)PID);
//        putsUART1((unsigned int *)"\n");


        //VALORE ATTUALE DEL MOTORE IN METRI AL SECONDO
        PIDsetReference(&pidmotor1,(float)(POS1CNT*METERPERTICK1));
        //VALORE RICHIESTO IN METRI AL SECONDO
        PIDUpdate(&pidmotor1,requestVelocityMotor1/1000);

        PIDsetReference(&pidmotor2,(float)(POS2CNT*METERPERTICK2));
        PIDUpdate(&pidmotor2,requestVelocityMotor2/1000);
        //POS1CNT=mypid.PID
        
        //MODIFICATORE DI VELOCITA' IN METRI AL SECONDO
        velocityMotor1=velocityMotor1+pidmotor1.PID;
        velocityMotor2=velocityMotor2+pidmotor2.PID;

        //METRI AL SECONDO IN TICK AL SECONDO
        tick1=(unsigned int)((velocityMotor1*TICKPERMETER1)+1);
        tick2=(unsigned int)((velocityMotor2*TICKPERMETER2)+1);

       
        motor1VEL=(int)(tick1*0.1);
        motor2VEL=(int)(tick2*0.1);
        //metersW1 = (int)POS1CNT*(float)METERPERTICK1;
        

       
        modifyMotor1();
        modifyMotor2();
        POS1CNT=0;
        POS2CNT=0;
    }
    WriteTimer1(0);


    IFS0bits.T1IF = 0;
    /* Clear Timer interrupt flag */
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void) {
    LED2 = 1;
    charRX = ReadUART1();
    if (charRX != RX_header && i == 0) {
        i = 0;
    } else {
        Buf[i] = charRX;

        if (i == (MAX_BUFF - 1)) {
            i = 0;
        }//lunghezza del buffer
        else if (i < MAX_BUFF) {
            i++;
        }
        if (charRX == RX_footer) {
            RX_hasToSend = 1;
            RX_hasToParse = 1;
            i = 0;
        }
    }
    IFS0bits.U1RXIF = 0;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI1Interrupt(void) {

    _QEI1IF = 0;


}

void __attribute__((__interrupt__, __no_auto_psv__)) _QEI2Interrupt(void) {

    _QEI2IF = 0;


}

#endif	/* INTERRUPTS_H */

