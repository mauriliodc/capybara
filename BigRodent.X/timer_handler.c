#include "timer_handler.h"


//return number of installed events
uchar8_t TimerEventHandler_num(const struct TimerEventHandler* handler) {
    return MAX_EVENTS;
}

//basic constructor for a timer event.
//you need to provide the period in milliseconds and the two callbacks o type <EventCallback>
void TimerEvent_init(struct TimerEvent* event, EventCallback upperHalf, EventCallback lowerHalf, int16_t period)
{
    event->_lowerHalf=lowerHalf;
    event->_upperHalf=upperHalf;
    event->_period=period;

}

//register a TimerEvent in the handler.
//all the statistics and the data is set to zero.
void TimerEventHandler_setEvent(struct TimerEventHandler* handler,uchar8_t numEvent, struct TimerEvent* event) {
    if (numEvent < TimerEventHandler_num(handler)) {
        handler->_events[numEvent]=event;
        handler->_events[numEvent]->_lastTickUpperHalfExecuted = 0;
        handler->_events[numEvent]->_lastUpperHalfExecutionTime = 0;
        handler->_events[numEvent]->_lastLowerHalfExecutionTime = 0;
        handler->_events[numEvent]->_flags = 0;
        handler->_events[numEvent]->_toBeExecuted = 0;

    }
}


void TimerEventHandler_setEventEnabled(struct TimerEventHandler* handler,uchar8_t numEvent,int enable) {
    TimerEventFlags en = 0;
    if (enable)
        en |= ENABLED;
    else
        en &= (~ENABLED);
    if (numEvent < TimerEventHandler_num(handler)) {
        handler->_events[numEvent]->_lastTickUpperHalfExecuted = 0;
        handler->_events[numEvent]->_lastUpperHalfExecutionTime = 0;
        handler->_events[numEvent]->_lastLowerHalfExecutionTime = 0;
        handler->_events[numEvent]->_flags = en;

    }
}

//get the enable status of an event
int TimerEventHandler_eventEnabled(const struct TimerEventHandler* handler,uchar8_t numEvent) {
    int r = 0;
    if (numEvent < TimerEventHandler_num(handler)) {
        r = handler->_events[numEvent]->_flags | ENABLED;
    }
    return r;
}

//return a pointer to the requested timer event
const TimerEvent* TimerEventHandler_event(const struct TimerEventHandler* handler, uchar8_t numEvent) {
    if (numEvent < TimerEventHandler_num(handler)) {
        return handler->_events[numEvent];
    }
    return 0;
}

//set the timer event handler running/stopped
void TimerEventHandler_setRunning(struct TimerEventHandler* handler,
        int running) {
    handler->_running = running;
}

//return the status of the handler
int TimerEventHandler_running(const struct TimerEventHandler* handler) {
    return handler->_running;
}

//this has to be called inside the timer interrupt at a granularity of 1ms (if
//you are reasing in ms)
void TimerEventHandler_handleIRQEvents(struct TimerEventHandler* handler) {
    handler->_tick++;
    uint8_t i;
    if (!handler->_running)
        return;
    for (i = 0; i < MAX_EVENTS; i++) {
        TimerEvent* e = handler->_events[i];
        if (e->_flags | ENABLED) {
            int16_t dt = handler->_tick - e->_lastTickUpperHalfExecuted;
            
            if (dt >= e->_period) {
            	mtime_t t0 = getTime();
            	if (e->_upperHalf)
            		(e->_upperHalf)(e);
                e->_lastTickUpperHalfExecuted = handler->_tick;
                mtime_t t1 = getTime();
                e->_lastUpperHalfExecutionTime = t1 - t0;               
                e->_toBeExecuted = (e->_lowerHalf!=0);


            }
        }
    }
}

//this has to be called in the main loop, basically calls the lower handlers
//of the upper handler events triggered in the interrupt
void TimerEventHandler_handleScheduledEvents(struct TimerEventHandler* handler) {
    uint8_t i;
    if (!handler->_running)
        return;
    for (i = 0; i < MAX_EVENTS; i++)
      {
        TimerEvent* e = handler->_events[i];
	if (e->_flags | ENABLED) {

            //int16_t dt = handler->_tick - e->_lastUpperHalfExecutionTime;
	    
            if (e->_toBeExecuted && e->_lowerHalf) {
               
               int t0 = getTime();
                (e->_lowerHalf)(e);
                mtime_t t1 = getTime();
                e->_lastLowerHalfExecutionTime = t1 - t0;
                e->_toBeExecuted = 0;
            }
        }
    }
}

//init
void TimerEventHandler_init(struct TimerEventHandler* handler) {
    uchar8_t i;
    for (i = 0; i < MAX_EVENTS; i++) {
        //TimerEventHandler_setEvent(handler,i,t);
        handler->_events[i]=0;
    }
    handler->_running = 0;
}