#ifndef _ENCODER_CONTROLLER_H
#define _ENCODER_CONTROLLER_H
/**
   This class handles the encoders Upon initialization, it initializes
   the QEI decoders on the platform and installs the necessary
   handlers
 */

struct EncoderController;
void EncoderController_init(struct EncoderController* controller);

uint8_t  EncoderController_num(const struct EncoderController* controller);

int16_t EncoderController_ticks(const struct EncoderController* controller, 
				uint8_t numEncoder);

int16_t EncoderController_setTicks(struct EncoderController* controller, 
				   uint8_t numEncoder, 
				   int16_t ticks);

#endif
