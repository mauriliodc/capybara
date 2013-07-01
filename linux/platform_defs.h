/* 
 * File:   platform_defs.h
 * Author: malcom
 *
 * Created on June 12, 2013, 12:34 PM
 */

#ifndef PLATFORM_DEFS_H
#define	PLATFORM_DEFS_H

#ifdef _LINUX_
#include <sys/time.h>
#include <stdint.h> // in linux-gcc the  types come for free
#include <string.h>
typedef int mtime_t;
typedef uint8_t uchar8_t;
#endif

//TYPES
//----------------------------------------------------------
#ifdef _MICROCHIP_
typedef unsigned int uint8_t;
typedef int int16_t;
typedef char int8_t ;
typedef unsigned int uint16_t;
typedef unsigned char uchar8_t;
typedef int16_t mtime_t;
//----------------------------------------------------------
#endif

typedef void(*irq_handler_t)();

mtime_t getTime();

#endif	/* PLATFORM_DEFS_H */

