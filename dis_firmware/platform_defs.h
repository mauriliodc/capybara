#ifndef _PLATFORM_DEFS_H_
#define _PLATFORM_DEFS_H_
/*
  this file contains the defines to compile the stuff for different targets:
  - linux
  - dsPIC
  - arduino
  We must specify which native compiler type uses integers at 8, 16 and 32 bit.
  In our code we will use only the typedefed types to improve portability.

  here are the types that you need to typedef
  int8_t   : 8 bit signed integer
  int16_t  : 16 bit signed integer
  int32_t  : 32 bit signed integer
  uint8_t  : 8 bit unsigned integer
  uint16_t : 16 bit unsigned integer
  uint32_t : 32 bit unsigned integer
  boolean  : to represent boolean values, defaults to the platform int
  time_t   : to represent the time, should be castable to int.
  In addition to that we need to specify a function that measures the clock cycles (or something else),
  as in the api of the specific system.

  In addition to that you should define the following functions:
  
  
  time_t getTime(); returns the system time (ticks, clocks, whatever);
  
*/

#ifdef _LINUX_
#include <stdint.h> // in linux-gcc the  types come for free
#endif

typedef void(*irq_handler_t)();

time_t getTime();

struct StringBuffer{
  _char _buf[MAX_BUF_SIZE];
  char* _bStart;
  char* _bEnd;
};

const char tmap[] = {
  "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"
};

char* writeFloat(StringBuffer* buf, float4 f){
  const char* temp = &f; 
  for (int i=0; i<sizeof(float4); i++){
    char c = *temp;
    *buf->_bEnd++ = tmap[(c&0xF0)>>4];
    *buf->_bEnd++ = tmap[(c&0x0F)>>4];
  }
}

#endif