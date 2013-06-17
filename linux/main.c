
#include "platform_defs.h"
#include "timer_handler.h"
#include "stdio.h"

void inner(struct TimerEvent* t) {
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>inner\n");
}

void outer(struct TimerEvent* t) {
	printf("]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]out\n");
	printf("EXECUTION TIME: %d\n",t->_lastLowerHalfExecutionTime);
	
}

struct TimerEventHandler tHandler;

void main()
{
	struct TimerEvent t1;
	EventCallback innerEvent = &inner;
	EventCallback outerEvent = &outer;
	TimerEvent_init(&t1,innerEvent,outerEvent,10);
	TimerEventHandler_init(&tHandler);
	TimerEventHandler_setEvent(&tHandler,0,&t1);
	TimerEventHandler_setRunning(&tHandler,1);
	while(1){
		TimerEventHandler_handleIRQEvents(&tHandler);
		TimerEventHandler_handleScheduledEvents(&tHandler);
	}
}
