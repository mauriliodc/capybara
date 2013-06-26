/* 
 * File:   message_buffer.h
 * Author: malcom
 *
 * Created on June 25, 2013, 11:34 AM
 */

#ifndef MESSAGE_BUFFER_H
#define	MESSAGE_BUFFER_H

#include "timer_handler.h"

#define TRANSMISSION_BUFFER_LEN 2000

struct trasmissionBuffer
{
    TimerEvent event;
    char _buffer[TRANSMISSION_BUFFER_LEN];
    char* _bufferPTR;
    int16_t period;
};


void transmissionBuffer_init(struct trasmissionBuffer*, int16_t);
void transmissionBuffer_write(struct trasmissionBuffer*, char*);
void transmissionBuffer_clear(struct trasmissionBuffer*);
void transmissionBuffer_Flush(struct trasmissionBuffer*);






#endif	/* MESSAGE_BUFFER_H */

