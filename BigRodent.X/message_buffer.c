#include "message_buffer.h"
#include "timer_handler.h"
#include "string.h"
#include "uart.h"


void TransmissionBuffer_UpperHandler(struct TimerEvent* t)
{
    
}
void TransmissionBuffer_LowerHandler(struct TimerEvent* t)
{
    struct trasmissionBuffer* tb=(struct trasmissionBuffer*)t;
    transmissionBuffer_Flush(tb);
}


void transmissionBuffer_init(struct trasmissionBuffer* t, int16_t period)
{
    TimerEvent_init(&t->event, &TransmissionBuffer_UpperHandler, &TransmissionBuffer_LowerHandler, period);
    t->_bufferPTR=t->_buffer;
}
void transmissionBuffer_write(struct trasmissionBuffer* t, char* i)
{
    uint16_t l=strlen(i);
    memcpy(t->_bufferPTR,i,l);
    t->_bufferPTR+=l;
}
void transmissionBuffer_clear(struct trasmissionBuffer* t)
{
    t->_bufferPTR=t->_buffer;
    *t->_bufferPTR=0;
}
void transmissionBuffer_Flush(struct trasmissionBuffer* t)
{
        putsUART1((unsigned int*)t->_buffer);
        transmissionBuffer_clear(t);
}
