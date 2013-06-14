#include "timer_handler.h"
#define MAX_EVENTS 10

typedef struct TimerEventHandler {
  TimerEvent (*_events)[MAX_EVENTS];
  int _running;
  int16_t _tick;
} TimerEventHandler;

uchar8_t TimerEventHandler_num(const struct TimerEventHandler* handler){
  return MAX_EVENTS;
}

void TimerEventHandler_setEvent(struct TimerEventHandler* handler, 
				uchar8_t numEvent, 
				EventCallback upperHalf, 
				EventCallback bottomHAlf, 
				int16_t period){
  if (numEvent < TimerEventHandler_num()) {
    handler->_events[numEvent] = {upperHalf, bottomHalf, period, 0, 0, 0, Enabled};
  }
}

void TimerEventHandler_setEventEnabled(struct TimerEventHandler* handler, 
				       uchar8_t numEvent, 
				       int enable){
  TimerEventFlags en;
  if (enable)
    en|=Enabled;
  else
    en&=(~Enabled);
  if (numEvent < TimerEventHandler_num()) {
    handler->_events[numEvent]->_ = {upperHalf, bottomHalf, period, 0, 0, 0, en};
  }
}

int TimerEventHandler_eventEnabled(const struct TimerEventHandler* handler, 
				   uchar8_t numEvent){
  int r = 0;
  if (numEvent < TimerEventHandler_num()) {
    r = handler->_events[numEvent]->_flags|Enabled;
  }
  return r;
}

const TimerEvent* TimerEventHandler_event(const struct TimerEventHandler* handler, 
					  uchar8_t numEvent){
  if (numEvent < TimerEventHandler_num()) {
    return handler->_events+numEvent;
  }
  return NULL:
}

void TimerEventHandler_setRunning(struct TimerEventHandler* handler, 
				  int running){
  _handler->running = runniing;
}

int TimerEventHandler_running(const struct TimerEventHandler* handler){
  return _handler->_running;
}

void TimerEventHandler_handleIRQEvents(struct TimerEventHandler* handler){
  handler->_tick ++;
  if (! handler->_running)
    return;
  for (uint8_t i = 0; i<MAX_EVENTS; i++){
    TimerEvent* e=handler->_events+i;
    if (e->_flags|Enabled) {
      int16_t dt = handler->_tick - e->_lastTickUpperHalfExecuted;
      int t0=getTime();
      if (dt >=e->_period && e->_upperHalf){
	(e->_upperHalf)(e);
      }
      int t1=getTime();
      e->_lastTickUpperHalfExecuted = handler->_tick();
      e->_lastUpperHalfExecutionTime = t1-t0;
      *e->_toBeExecuted = (e->_lowerHalf);
      if (e->_lowerHalf) {
	e->_toBeExecuted = 1;
      } else
	e->_toBeExecuted = 0;
    }
  }
}

void TimerEventHandler_handleScheduledEvents(struct TimerEventHandler* handler){
  handler->_tick ++;
  if (! handler->_running)
    return;
  for (uint8_t i = 0; i<MAX_EVENTS; i++){
    TimerEvent* e=handler->_events+i;
    if (e->_flags|Enabled) {
      int16_t dt = handler->_tick - e->_lastTimeUpperHalfExecuted;
      if (e->_toBeExecuted && e->_lowerHalf){
	int t0=getTime();
	if (dt >=e->_period){
	  (*e->_lowerHalf)(e);
	}
	int t1=getTime();
	e->_lastLowerHalfExecutionTime = t1-t0;
	e->_toBeExecuted = 0;
      }
    }
  }
}

void TimerEventHandler_init(const struct TimerEventHandler* handler){
  for (uchar8_t i=0; i<MAX_EVENTS; i++){
    TimerEventHandler_setEvent(handler, i, 0, 0, 0);
    handler->_events[i]._enabled=0;
  }
  handler->_running = 0;
}
