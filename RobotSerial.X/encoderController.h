/* 
 * File:   encoderController.h
 * Author: malcom
 *
 * Created on May 29, 2013, 6:07 PM
 */

#ifndef ENCODERCONTROLLER_H
#define	ENCODERCONTROLLER_H

#include "fancyTimer.h"

struct _encoder
{
    unsigned int tickPerQuantum;
    unsigned int* ticks;
    struct timerEvent* resetPositionCounter;
};

struct encoderController{
    
    struct _encoder* enc1;
    struct _encoder* enc2;
};


void initEncoder(struct _encoder* e,unsigned int* positionCounter,struct timerEvent* t, unsigned int dt, void *callback)
{
    e->resetPositionCounter=t;
    e->ticks=positionCounter;
    e->resetPositionCounter->millisecs=dt;
    e->resetPositionCounter->repetitions=-1;
    e->resetPositionCounter->callback=callback;
}

void initEncoderController(struct encoderController* ec,struct _encoder* e1, struct _encoder* e2)
{
    ec->enc1=e1;
    ec->enc2=e2;

    /*---------------------------------------------------------------------------*/
/* QEI1	[4]           			    									     */
/*---------------------------------------------------------------------------*/
/*
OpenQEI(QEI_MODE_x4_MATCH & QEI_INPUTS_NOSWAP & QEI_IDLE_STOP
		& QEI_NORMAL_IO & QEI_INDEX_RESET_DISABLE,
		QEI_QE_CLK_DIVIDE_1_128 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE);
*/
//MALCOM INIZIO
//ENCODER 1
QEI1CONbits.QEIM 	= 0b101;	//	QEI_MODE_x2_MATCH
QEI1CONbits.SWPAB 	= 1;	//	QEI_INPUTS_SWAP
QEI1CONbits.QEISIDL	= 1;	//	QEI_IDLE_STOP
QEI1CONbits.POSRES	= 0;	//	QEI_INDEX_RESET_DISABLE
QEI1CONbits.PCDOUT	= 0;	//	QEI_NORMAL_IO
QEI1CONbits.POSRES	= 1;	//	POS_CNT_ERR_INT_DISABLE

DFLT1CONbits.QECK	= 6;	//	QEI_QE_CLK_DIVIDE_1_128
DFLT1CONbits.QEOUT	= 1;	//	QEI_QE_OUT_ENABLE

//encoder settato a 2048 tick per giro completo
//posto alla shaft posteriore
//il QEI legge 2 tick (modalit? 2x)
MAX1CNT = 0xffff;
POS1CNT = 0;
ConfigIntQEI1(QEI_INT_ENABLE & QEI_INT_PRI_1);

//ENCODER 2
QEI2CONbits.QEIM 	= 0b101;	//	QEI_MODE_x2_MATCH
QEI2CONbits.SWPAB 	= 1;	//	QEI_INPUTS_SWAP
QEI2CONbits.QEISIDL	= 1;	//	QEI_IDLE_STOP
QEI2CONbits.POSRES	= 0;	//	QEI_INDEX_RESET_DISABLE
QEI2CONbits.PCDOUT	= 0;	//	QEI_NORMAL_IO
QEI2CONbits.POSRES	= 0;	//	POS_CNT_ERR_INT_DISABLE

DFLT2CONbits.QECK	= 6;	//	QEI_QE_CLK_DIVIDE_1_128
DFLT2CONbits.QEOUT	= 1;	//	QEI_QE_OUT_ENABLE


//encoder settato a 2048 tick per giro completo
//posto alla shaft posteriore
//il QEI legge 2 tick (modalit? 2x)
MAX2CNT = 0xffff;
POS2CNT = 0;
ConfigIntQEI2(QEI_INT_ENABLE & QEI_INT_PRI_1);
}

//******************************************************************************
//******************************************************************************
struct _encoder encoder1;
struct _encoder encoder2;
struct encoderController encoderController;


#endif	/* ENCODERCONTROLLER_H */

