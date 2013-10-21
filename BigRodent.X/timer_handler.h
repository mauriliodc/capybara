/*
 * File:   timer_handler.h
 * Author: malcom
 *
 * Created on June 13, 2013, 2:12 PM
 */

#ifndef TIMER_HANDLER_H
#define	TIMER_HANDLER_H

#include "platform_defs.h"
#define MAX_EVENTS 4

struct TimerEvent;
struct TimerEventHandler;
enum TimerEventFlags;
typedef void (*EventCallback) (struct TimerEvent* t);


typedef enum TimerEventFlags {ENABLED = 1,DISABLED =0} TimerEventFlags;

typedef struct TimerEvent{
  EventCallback _upperHalf; // callback for the irq
  EventCallback _lowerHalf; // callback for the outer loop
  int16_t _period;
  int16_t _lastTickUpperHalfExecuted;
  mtime_t _lastUpperHalfExecutionTime;
  mtime_t _lastLowerHalfExecutionTime;
  TimerEventFlags _flags;
  int _toBeExecuted;
} TimerEvent;


typedef struct TimerEventHandler {
  TimerEvent *_events[MAX_EVENTS];
  int16_t _running;
  int16_t _tick;
} TimerEventHandler;



void TimerEvent_init(struct TimerEvent* event, EventCallback upperHalf, EventCallback lowerHalf, int16_t period);

void TimerEventHandler_init(TimerEventHandler* handler);

uchar8_t TimerEventHandler_num(const  TimerEventHandler* handler);

void TimerEventHandler_setEvent(struct TimerEventHandler* handler,uchar8_t numEvent, struct TimerEvent* event);

void TimerEventHandler_setEventEnabled(struct TimerEventHandler* handler, uchar8_t numEvent, int enable);

int TimerEventHandler_eventEnabled(const struct TimerEventHandler* handler, uchar8_t numEvent);

const struct TimerEvent* TimerEventHandler_event(const struct TimerEventHandler* handler,uchar8_t numEvent);

void TimerEventHandler_setRunning(struct TimerEventHandler* handler, int running);

int TimerEventHandler_running(const struct TimerEventHandler* handler);

void TimerEventHandler_handleIRQEvents(struct TimerEventHandler* handler);

void TimerEventHandler_handleScheduledEvents(struct TimerEventHandler* handler);

#endif	/* TIMER_HANDLER_H */
