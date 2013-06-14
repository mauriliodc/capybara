#include "timer_handler.h"

uchar8_t TimerEventHandler_num(const struct TimerEventHandler* handler) {
    return MAX_EVENTS;
}

void TimerEventHandler_setEvent(const struct TimerEventHandler* handler,uchar8_t numEvent, EventCallback upperHalf, EventCallback bottomHalf, int16_t period) {
    if (numEvent < TimerEventHandler_num(handler)) {
        handler->_events[numEvent]->_upperHalf = upperHalf;
        handler->_events[numEvent]->_lowerHalf = bottomHalf;
        handler->_events[numEvent]->_period = period;
        handler->_events[numEvent]->_lastTickUpperHalfExecuted = 0;
        handler->_events[numEvent]->_lastUpperHalfExecutionTime = 0;
        handler->_events[numEvent]->_lastLowerHalfExecutionTime = 0;
        handler->_events[numEvent]->_flags = ENABLED;
        handler->_events[numEvent]->_toBeExecuted = 1;

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

int TimerEventHandler_eventEnabled(const struct TimerEventHandler* handler,uchar8_t numEvent) {
    int r = 0;
    if (numEvent < TimerEventHandler_num(handler)) {
        r = handler->_events[numEvent]->_flags | ENABLED;
    }
    return r;
}

const TimerEvent* TimerEventHandler_event(const struct TimerEventHandler* handler, uchar8_t numEvent) {
    if (numEvent < TimerEventHandler_num(handler)) {
        return handler->_events[numEvent];
    }
    return 0;
}

void TimerEventHandler_setRunning(struct TimerEventHandler* handler,
        int running) {
    handler->_running = running;
}

int TimerEventHandler_running(const struct TimerEventHandler* handler) {
    return handler->_running;
}

void TimerEventHandler_handleIRQEvents(struct TimerEventHandler* handler) {
    handler->_tick++;
    uint8_t i;
    if (!handler->_running)
        return;
    for (i = 0; i < MAX_EVENTS; i++) {
        TimerEvent* e = handler->_events[i];
        if (e->_flags | ENABLED) {
            int16_t dt = handler->_tick - e->_lastTickUpperHalfExecuted;
            int t0 = getTime();
            if (dt >= e->_period && e->_upperHalf) {
                (e->_upperHalf)(e);
            }
            int t1 = getTime();
            e->_lastTickUpperHalfExecuted = handler->_tick;
            e->_lastUpperHalfExecutionTime = t1 - t0;
            e->_toBeExecuted = (e->_lowerHalf!=0); //TODO chiedere cosa fa
        }
    }
}

void TimerEventHandler_handleScheduledEvents(struct TimerEventHandler* handler) {
    handler->_tick++;
    uint8_t i;
    if (!handler->_running)
        return;
    for (i = 0; i < MAX_EVENTS; i++) {
        TimerEvent* e = handler->_events[i];
        if (e->_flags | ENABLED) {
            int16_t dt = handler->_tick - e->_lastUpperHalfExecutionTime;
            if (e->_toBeExecuted && e->_lowerHalf) {
                int t0 = getTime();
                if (dt >= e->_period) {
                    (*e->_lowerHalf)(e);
                }
                int t1 = getTime();
                e->_lastLowerHalfExecutionTime = t1 - t0;
                e->_toBeExecuted = 0;
            }
        }
    }
}

void TimerEventHandler_init(struct TimerEventHandler* handler) {
    uchar8_t i;
    for (i = 0; i < MAX_EVENTS; i++) {
        TimerEventHandler_setEvent(handler, i, 0, 0, 0);
        handler->_events[i]->_toBeExecuted = 0;
    }
    handler->_running = 0;
}