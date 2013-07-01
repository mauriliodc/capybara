#include "platform_defs.h"
#ifdef _LINUX_


mtime_t getTime(){
	struct timeval tv;
	gettimeofday(&tv,0);
	return tv.tv_usec;
}

#endif

#ifdef _MICROCHIP_
#include <timer.h>
time_t getTime() { return (time_t)ReadTimer2(); }
#endif
