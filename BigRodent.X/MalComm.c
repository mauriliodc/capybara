#include "MalComm.h"

//INITIALIZATION STUFF
//==============================================================================
uint8_t DummyPacketID;
uint8_t DumbPacketID;
uint8_t SlimStatePacketID;
uint8_t InitPacketID;
uint8_t SpeedPacketID;
char header_1;
char header_2;
char AsciiHeader;
char AsciiFooter;
int complete = 0;
//Consts init
//==============================================================================

void initConsts() {
    DummyPacketID = 1;
    DumbPacketID = 2;
    SlimStatePacketID = 3;
    InitPacketID = 4;
    SpeedPacketID = 5;
    header_1 = 0xaa;
    header_2 = 0x55;
    AsciiHeader = '(';
    AsciiFooter = ')';
}
//==============================================================================
//==============================================================================


//Decoder init and useful stuff
//==============================================================================

void DecoderInit(struct PacketDecoder* d, int ascii) {
    ResetDecoderBuffer(d);
    d->buffer_start = &(d->buffer[0]);
    d->bufferPtr = &(d->buffer[0]);
    d->status = Unsync;
    d->lenght = 0;
    d->ascii = ascii;

}

void ResetDecoderBuffer(struct PacketDecoder* d) {
    memset(d->buffer, '\0', BUFFER_SIZE);
    d->bufferPtr = d->buffer_start;
}
//==============================================================================
//==============================================================================

//Decoder main loop
//==============================================================================

int DecoderPutChar(struct PacketDecoder* d, char c) {
    //binary mode
    //-----------------------------------------------------
    if (d->ascii == 0) {
        if (d->status == Unsync) {
            //clear the buffer
            ResetDecoderBuffer(d);
            //clear the checksum, just in case
            d->checksum = 0;
            if (c == header_1) {
                d->status = Sync;
            }
        } else if (d->status == Sync) {
            if (c == header_2) {
                d->status = Length;
            } else {
                d->status = Unsync;
            }
        } else if (d->status == Length) {
            d->lenght = (uint8_t) c;
            d->status = Payload;
        } else if (d->status == Payload) {
            if (d->lenght > 0) {
                d->checksum ^= c;
                *(d->bufferPtr) = c;
                d->bufferPtr++;
                d->lenght--;
            } else {
                d->checksum ^= c;
                d->status = Unsync;
                if (d->checksum == 0) return 1; //checksum good
                else return 0; //checksum error;
            }

        } else {
            d->status = Unsync;
        }
    }        //-----------------------------------------------------
        //ascii mode
        //-----------------------------------------------------
    else if (d->ascii == 1) {
        if (d->status == Unsync) {
            //clear the buffer
            ResetDecoderBuffer(d);
            if (c == AsciiHeader) {
                d->status = Payload;
            }
        } else if (d->status == Payload) {
            //Sync Error, clean buffer and start oveer
            if (c == AsciiHeader) {
                d->status = Unsync;
            }//Packet end, process it
            else if (c == AsciiFooter) {
                d->status = Unsync;
                return 1;
            }//in any other case, the char received is probably good!
            else {
                *(d->bufferPtr) = c;
                d->bufferPtr++;
            }
        }
    }
    return 0;
}
//==============================================================================
//==============================================================================


//PACKET STUFF
//==============================================================================
//GenericPacket Utilities
//==============================================================================

char* writePacket(const struct Packet* p, char* buffer, int ascii) {
    //Binary mode
    char* buffPtr;
    if (!ascii) {
        buffer = writeUint8(header_1, buffer);
        buffer = writeUint8(header_2, buffer);
    }
    if (p->id == DummyPacketID) {
        buffPtr = buffer;
        buffer = writeDummyPacket(p, buffer, ascii);
    } else if (p->id == DumbPacketID) {
        buffPtr = buffer;
        buffer = writeDumbPacket(p, buffer, ascii);
    } else if (p->id == SlimStatePacketID) {
        buffPtr = buffer;
        buffer = writeSlimStatePacket(p, buffer, ascii);
    } else if (p->id == SpeedPacketID) {
        buffPtr = buffer;
        buffer = writeSpeedPacket(p, buffer, ascii);
    }
    else if (p->id == InitPacketID) {
        buffPtr = buffer;
        buffer = writeInitPacket(p, buffer, ascii);
    }
    //Binary mode, has to compute the checksum
    if (!ascii) {
        uint8_t checksum = computeChecksum(buffer, buffer - buffPtr);
        buffer = writeUint8(checksum, buffer);
    }
    return buffer;
}

//Note,buffer has to point to the ID, not to the length

char* parsePacket(char* buffer, struct Packet* p, int ascii) {
    uint8_t id;
    if (!ascii) {
        buffer = readUint8(&id, buffer);
    } else {
        buffer = readUint8Ascii((char*) &id, buffer);
    }
    //IF - ELSE-IF for each existing packet
    p->id = id;
    if (id == DummyPacketID) {
        readDummyPacket(p, buffer, ascii);
    } else if (id == DumbPacketID) {
        readDumbPacket(p, buffer, ascii);
    } else if (id == SlimStatePacketID) {
        readSlimStatePacket(p, buffer, ascii);
    } else if (id == SpeedPacketID) {
        readSpeedPacket(p, buffer, ascii);
    }
    else if (id == InitPacketID) {
        readInitPacket(p, buffer, ascii);
    }
    return buffer;
}

uint8_t computeChecksum(char* buffer, uint8_t length) {
    uint8_t checksum = 0;
    uint8_t len = length - 1;
    while (len) {
        checksum ^= *(buffer - len);
        len--;
    }
    return checksum;
}





//Uart facilities
//==============================================================================
#ifdef __33FJ128MC802_H
//use this only on the micro side

void sendToUart(char* buffer, int length, int intraCharDelayUs) {
    int i = 0;
    while (i < length) {
        U1TXREG = buffer[i];
        i++;
        DelayN10us(intraCharDelayUs);
    }
}
#else

void sendToUart(int device, char* buffer, int length, int intraCharDelayUs) {
    int i = 0;
    while (i < length) {
        write(device, &buffer[i], 1);
        i++;
        usleep(200);
        usleep(intraCharDelayUs);
    }
}
#endif
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================


