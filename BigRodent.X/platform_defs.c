#include "platform_defs.h"

#ifdef _LINUX_
#include <time.h>

int getTime(){
  return clock();
}

#endif

time_t getTime() { return 0; }