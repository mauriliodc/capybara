#include "encoder_controller.h"



void    Encoder_init(struct Encoder* encoder, uint8_t* positionCounterRegister)
{
    encoder->ticks=positionCounterRegister;
}

void EncoderController_init(struct EncoderController* controller)
{
    //ENCODER 1
    QEI1CONbits.QEIM 	= 0b101;	//	QEI_MODE_x2_MATCH
    QEI1CONbits.SWPAB 	= 1;	//	QEI_INPUTS_SWAP
    QEI1CONbits.QEISIDL	= 1;	//	QEI_IDLE_STOP
    QEI1CONbits.POSRES	= 0;	//	QEI_INDEX_RESET_DISABLE
    QEI1CONbits.PCDOUT	= 0;	//	QEI_NORMAL_IO
    QEI1CONbits.POSRES	= 0;	//	POS_CNT_ERR_INT_DISABLE

    DFLT1CONbits.QECK	= 6;	//	QEI_QE_CLK_DIVIDE_1_128
    DFLT1CONbits.QEOUT	= 1;	//	QEI_QE_OUT_ENABLE

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

    MAX2CNT = 0xffff;
    POS2CNT = 0;
    ConfigIntQEI2(QEI_INT_ENABLE & QEI_INT_PRI_1);
}



uint8_t EncoderController_num()
{
    return NUM_ENCODERS;
}

int16_t EncoderController_ticks(const struct EncoderController* controller, uint8_t numEncoder)
{
    return *controller->encoders[numEncoder]->ticks;
}

int16_t EncoderController_setTicks(struct EncoderController* controller, uint8_t numEncoder, int16_t ticks)
{
    *controller->encoders[numEncoder]->ticks=ticks;
    return *controller->encoders[numEncoder]->ticks;
}