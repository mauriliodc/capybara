#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_
#include "platform_defs.h"

/**
   struct TimerEventHandler
*/

struct TimerEvent;
typedef void (*EventCallback) (struct TimerEvent* t);

enum TimerEventFlags={Enabled = 0x1};

typedef struct TimerEvent{
  EventCallback _upperHalf; // callback for the irq
  EventCallback _lowerHalf; // callback for the outer loop
  int16_t _period;
  int16_t _lastTickUpperHalfExecuted;
  int16_t _lastUpperHalfExecutionTime;
  int16_t _lastLowerHalfExecutionTime;
  TimerEventFlags _flags;
  int _toBeExecuted;
} TimerEvent;

struct TimerEventHandler;

void TimerEventHandler_init(const struct TimerEventHandler* handler); 

uchar8_t TimerEventHandler_num(const struct TimerEventHandler* handler);

void TimerEventHandler_setEvent(struct TimerEventHandler* handler, 
				       uchar8_t numEvent, 
				       EventCallback upperHalf, 
				       EventCallback bottomHAlf, 
				       int16_t period);

void TimerEventHandler_setEventEnabled(struct TimerEventHandler* handler, 
					      uchar8_t numEvent, 
					      int enable);

boolean TimerEventHandler_eventEnabled(const struct TimerEventHandler* handler, 
					  uchar8_t numEvent);

const TimerEvent* TimerEventHandler_event(const struct TimerEventHandler* handler, 
					  uchar8_t numEvent);

void TimerEventHandler_setRunning(struct TimerEventHandler* handler, 
				  boolean running);

boolean TimerEventHandler_running(const struct TimerEventHandler* handler);

void TimerEventHandler_handleIRQEvents(struct TimerEventHandler* handler);

void TimerEventHandler_handleScheduledEvents(struct TimerEventHandler* handler);

#endif
