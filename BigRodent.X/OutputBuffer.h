/*
 * File:   OutputBuffer.h
 * Author: malcom
 *
 * Created on October 16, 2013, 4:34 PM
 */

#ifndef OUTPUTBUFFER_H
#define	OUTPUTBUFFER_H

#define OUTPUTBUFFER 200

struct _OutputBuffer {
    char payload[OUTPUTBUFFER];
    char* start;
    char* end;
    char* curr;
} outputBuffer;

void outputBuffer_Init() {
    outputBuffer.start = outputBuffer.payload;
    outputBuffer.curr = outputBuffer.start;
    outputBuffer.end = outputBuffer.start + sizeof (char) *OUTPUTBUFFER;
}

void outputBuffer_resetBuffer() {
    outputBuffer.start = outputBuffer.payload;
    outputBuffer.curr = outputBuffer.start;
    outputBuffer.end = outputBuffer.start + sizeof (char) *OUTPUTBUFFER;
}

void outputBuffer_write(char *incomingMessage) {
    while(*incomingMessage!='\0'){
        *outputBuffer.curr=*incomingMessage;
        outputBuffer.curr++;
        incomingMessage++;
    }
}

void outputBuffer_flush() {
    char* charPTR=outputBuffer.start;
    if (outputBuffer.curr != charPTR) {
        printf("%s",charPTR);
        charPTR++;
    }
    outputBuffer_resetBuffer();
}
#endif	/* OUTPUTBUFFER_H */

