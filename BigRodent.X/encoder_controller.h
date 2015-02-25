/* 
 * File:   encoder_controller.h
 * Author: malcom
 *
 * Created on June 12, 2013, 1:07 PM
 */

#ifndef ENCODER_CONTROLLER_H
#define	ENCODER_CONTROLLER_H

#include <p33FJ128MC802.h>
#include "platform_defs.h"
#include <qei.h>

#define NUM_ENCODERS 2

struct Encoder
{
    uint16_t* ticks; //position counter register address
};

struct EncoderController{
    struct Encoder* encoders[NUM_ENCODERS];
};

void    Encoder_init(struct Encoder* encoder, uint16_t* positionCounterRegister);
void    EncoderController_init(struct EncoderController* controller);
uint8_t EncoderController_num();
int16_t EncoderController_ticks(const struct EncoderController* controller, uint8_t numEncoder);
int16_t EncoderController_setTicks(struct EncoderController* controller, uint8_t numEncoder, int16_t ticks);

#endif	/* ENCODER_CONTROLLER_H */

