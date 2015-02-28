#include "mal_buffer.h"

void Double_Buffer_init(struct Double_Buffer* db) {
    db->_active = db->_buffer_0;
    db->_ready = db->_buffer_1;
    db->_activeCurrPtr = db->_active;
    db->_activeEndPtr = db->_active + COMMUNICATION_BUFFER_SIZE;
}

void Double_Buffer_write(struct Double_Buffer* db, const char* buffer, uint16_t len) {
    if ((db->_activeEndPtr - db->_activeCurrPtr) > len) {
        memcpy(db->_activeCurrPtr, buffer, len);
        db->_activeCurrPtr += len;
    }
}

char* Double_Buffer_getReady(struct Double_Buffer* db){
    return db->_ready;
}

char* Double_Buffer_getReadyEndTPr(struct Double_Buffer* db){
    return db->_readyEndPtr;
}

void Double_Buffer_swapBuffers(struct Double_Buffer* db) {
    char* tmp;
    tmp = db->_active;
    db->_active = db->_ready;
    db->_ready = tmp;

    //NOW ready  = active
    //    active = ready

    db->_readyEndPtr =  db->_activeCurrPtr;
    db->_activeCurrPtr = db->_active;
    db->_activeEndPtr = db->_active + COMMUNICATION_BUFFER_SIZE;
}
