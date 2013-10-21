#include "OutputBuffer.h"

struct _OutputBuffer outputBuffer;


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
