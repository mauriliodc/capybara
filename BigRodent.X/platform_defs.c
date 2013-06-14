#include "platform_defs.h"
#include <timer.h>
#ifdef _LINUX_
#include <time.h>

int getTime(){
  return clock();
}

#endif

time_t getTime() { return (time_t)ReadTimer2(); }