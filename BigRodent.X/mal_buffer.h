/* 
 * File:   mal_buffer.h
 * Author: malcom
 *
 * Created on 26 febbraio 2015, 19.00
 */

#ifndef MAL_BUFFER_H
#define	MAL_BUFFER_H

#include <stdint.h>
#include <string.h>

#define COMMUNICATION_BUFFER_SIZE 1024

struct Double_Buffer {
    char _buffer_0[COMMUNICATION_BUFFER_SIZE];
    char _buffer_1[COMMUNICATION_BUFFER_SIZE];
    char* _activeCurrPtr;
    char* _activeEndPtr;
    char* _active;
    char* _ready;
};

void Double_Buffer_init(struct Double_Buffer* db);
void Double_Buffer_write(struct Double_Buffer* db, const char* buffer, uint16_t len);
char* Double_Buffer_getReady(struct Double_Buffer* db);
void Double_Buffer_swapBuffers(struct Double_Buffer* db);


#endif	/* MAL_BUFFER_H */

