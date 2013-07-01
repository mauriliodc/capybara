#include "platform_defs.h"
#include <timer.h>
#ifdef _LINUX_
#include <time.h>

int getTime(){
  return clock();
}

#endif



mtime_t getTime() { return (mtime_t)ReadTimer2(); }