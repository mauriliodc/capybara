/* 
 * File:   platform_defs.h
 * Author: malcom
 *
 * Created on June 12, 2013, 12:34 PM
 */

#ifndef PLATFORM_DEFS_H
#define	PLATFORM_DEFS_H

#ifdef _LINUX_
#include <stdint.h> // in linux-gcc the  types come for free
#endif

//TYPES
//----------------------------------------------------------

typedef unsigned int uint8_t;
typedef int int16_t;
typedef int int8_t ;
typedef unsigned int uint16_t;
typedef unsigned char uchar8_t;
typedef int16_t time_t;
//----------------------------------------------------------

typedef void(*irq_handler_t)();

time_t getTime();

#endif	/* PLATFORM_DEFS_H */

