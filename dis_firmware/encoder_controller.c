#include "encoder_controller.h"
#include "platform_defs.h"

#define NUM_ENCODERS 2

struct EncoderController{
};

void EncoderController_init(struct EncoderController* controller){
  // DOES THE THINGS REQUIRED TO INITIALIZE THE ENCODERS, INCLUDING INSTALLING THE INTERRUPTS AN SO ON
}

uint8_t  EncoderController_num(const struct EncoderController* controller){
  return NUM_ENCODERS;
}

int16_t EncoderController_ticks(const struct EncoderController* controller, 
				uint8_t numEncoder){
  // READS THE ITH ENCODER
}

int16_t EncoderController_setTicks(struct EncoderController* controller, 
				   uint8_t numEncoder, 
				   int16_t ticks){
  // READS THE ITH ENCODER AND SETS IT TO 0
}
