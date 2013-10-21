/*
 * File:   OutputBuffer.h
 * Author: malcom
 *
 * Created on October 16, 2013, 4:34 PM
 */

#ifndef OUTPUTBUFFER_H
#define	OUTPUTBUFFER_H

#include <stdio.h>

#define OUTPUTBUFFER 200

struct _OutputBuffer {
    char payload[OUTPUTBUFFER];
    char* start;
    char* end;
    char* curr;
};
extern struct _OutputBuffer outputBuffer;


void outputBuffer_Init();
void outputBuffer_resetBuffer();
void outputBuffer_write(char *incomingMessage);
void outputBuffer_flush();

#endif	/* OUTPUTBUFFER_H */

