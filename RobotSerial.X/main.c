/* 
 * File:   main.c
 * Author: malcom
 *
 * Created on May 8, 2013, 12:43 PM
 */

#include <p33Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <timer.h>
#include <pps.h>
#include <uart.h>
#include <pwm12.h>
#include <string.h>
#include <qei.h>

#include "defines.h"
#include "globals.h"
#include "settings.h"
#include "utils.h"
#include "interrupts.h"
#include "commands.h"

char ttkk[10];

int main() {
    clock_settings();
    led_settings();
    timer1_confguration();
    pin_remapping();
    init_uart1();
    LED1 = 0;
    DelayN1ms(2000);
    putsUART1((unsigned int *) mio);
    initEncoders();
    enableMotors();
    generateCommands();



    //char pos1[4];
    //char pos2[4];
    
    
    while (1) {
        if (U1STAbits.OERR) { // non mi interessano i caratteri ev. in attesa...
            U1STAbits.OERR = 0;
        }
        if (U1STAbits.FERR == 1) {
            continue;
        }

        /*
        while (RX_hasToSend) {
            U1TXREG = Buf[sender];
            while (U1STAbits.UTXBF == 1);
            //Buf[sender] = '\0';
            if (sender == (MAX_BUFF - 1)) {
                RX_hasToSend = 0;

                sender = 0;
            } else {
                sender = sender + 1;
            }
        }
         */
        if (RX_hasToParse) {

            ReceivedCommand = (struct _ReceivedCommand*) Buf;

            //unsigned char argument[4];
            //unsigned char command[2];
            //memcpy(argument, ReceivedCommand->argument, 4 * sizeof (unsigned char));
            //memcpy(command, ReceivedCommand->code, 2 * sizeof (unsigned char));
            //putsUART1((unsigned int *) command);
            //putsUART1((unsigned int *) argument);
            putsUART1((unsigned int *) "Comando ricevuto");
            putsUART1((unsigned int *) Buf);
            parseAndExecuteCommand();
            memset(Buf, 0, sizeof (Buf));
            RX_hasToParse = 0;
        }

        //itoa( pos1,POS1CNT, 10);
        //itoa( pos2,POS2CNT, 10);

        //TEST DA COMMENTARE
        //sprintf(posPacket, "%04d:%04d", POS1CNT,POS2CNT);


        //sprintf(pos2, "%4d", POS2CNT);
        //memcpy(posPacket,pos1,4*sizeof(unsigned char));
        //posPacket[4]=':';
        //memcpy(&posPacket[5],pos2,4*sizeof(unsigned char));

        if(secAcc==5000)
        {
        //sprintf(posPacket, "%04d:%04d", POS1CNT,POS2CNT);
        sprintf(posPacket,"%f",metersW1);
        putsUART1((unsigned int*) "SPEED1: ");
        putsUART1((unsigned int*) posPacket);

        sprintf(posPacket,"%f",metersW2);
        putsUART1((unsigned int*) " SPEED2: ");
        putsUART1((unsigned int*) posPacket);
        //putsUART1((unsigned int*) "\n");


        sprintf(posPacket,"%d",QEI1CONbits.UPDN);
        putsUART1((unsigned int*) " DIR: ");
        putsUART1((unsigned int*) posPacket);


        putsUART1((unsigned int*) " POS1CNT: ");
        sprintf(posPacket,"%d",(int)POS1CNT);
        putsUART1((unsigned int*) posPacket);
        putsUART1((unsigned int*) "\n");
        
        }
    }
    return (1);
}
