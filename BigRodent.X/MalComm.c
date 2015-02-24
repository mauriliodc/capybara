#include "MalComm.h"

//INITIALIZATION STUFF
//==============================================================================
uint8_t DummyPacketID;
uint8_t DumbPacketID;
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
    header_1 = 0xaa;
    header_2 = 0x55;
    AsciiHeader='(';
    AsciiFooter=')';
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
    }
    //-----------------------------------------------------
    //ascii mode
    //-----------------------------------------------------
    else if (d->ascii == 1){
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
            }                //Packet end, process it
            else if (c == AsciiFooter) {
                return 1;
            }                //in any other case, the char received is probably good!
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
        buffPtr=buffer;
        buffer=writeDummyPacket(p, buffer, ascii);
    } else if (p->id == DumbPacketID) {
        buffer=writeDumbPacket(p, buffer, ascii);
    }
    //Binary mode, has to compute the checksum
    if(!ascii){
        uint8_t checksum = computeChecksum(buffer,buffer-buffPtr);
        buffer = writeUint8(checksum, buffer);
    }
    return buffer;
}

//Note,buffer has to point to the ID, not to the length
char* parsePacket(char* buffer, struct Packet* p, int ascii) {
    uint8_t id;
    if(!ascii){
        buffer = readUint8(&id, buffer);
    }
    else{
        buffer = readUint8Ascii((char*)&id, buffer);
    }
    //IF - ELSE-IF for each existing packet
    p->id = id;
    if (id == DummyPacketID) {
        readDummyPacket(p, buffer, ascii);
    } else if (id == DumbPacketID) {
        readDumbPacket(p, buffer, ascii);
    }
    return buffer;
}

uint8_t computeChecksum(char* buffer, uint8_t length){
    uint8_t checksum=0;
    uint8_t len = length - 1;
        while (len) {
            checksum ^= *(buffer - len);
            len--;
        }
    return checksum;
}
//==============================================================================
//DummyPacket
//==============================================================================
//pay attention, this make side effect on buffer
//The checksum is computed on the first byte of each field.
//We need to get the addresws of (buffer-1) because the Write primitive does side effect
//on the buffer, so the returned buffer points to a NUL byte
char* readDummyPacket(struct Packet* p, char* buffer, int ascii) {
    //Don't have to read the lenght
    if (!ascii) {
        buffer = readUint32(&(p->seq), buffer);
        buffer = readUint8(&(p->dummy.field_1), buffer);
        buffer = readUint16(&(p->dummy.field_2), buffer);
        buffer = readUint8((uint8_t*)&(p->dummy.field_3), buffer);
        buffer = readUint8((uint8_t*)&(p->dummy.field_4), buffer);
        buffer = readFloat(&(p->dummy.field_5), buffer);
        buffer = readUint8(&(p->dummy.field_6), buffer);
        buffer = readUint32(&(p->dummy.field_7), buffer);
        buffer = readUint32((uint32_t*)&(p->dummy.field_8), buffer);
    } else {

        //clean this mess, someday
        long int a, b, c, d, e, g, h, i = 0;
        float f = 0;
        sscanf(buffer, "%ld %ld %ld %ld %ld %f %d %ld %ld",
                &a,
                &b,
                &c,
                &d,
                &e,
                &f,
                &g,
                &h,
                &i);

        p->seq = (uint32_t) a;
        p->dummy.field_1 = (uint8_t) b;
        p->dummy.field_2 = (uint16_t) c;
        p->dummy.field_3 = (int8_t) d;
        p->dummy.field_4 = (char) e;
        p->dummy.field_5 = (float) f;
        p->dummy.field_6 = (unsigned char) g;
        p->dummy.field_7 = (uint32_t) h;
        p->dummy.field_8 = (int32_t) i;

    }
    return buffer;

}

char* writeDummyPacket(const struct Packet* p, char* buffer, int ascii) {
    //BinaryMode
    if (!ascii) {
        uint8_t lenght = 23;
        //PACKET LENGTH
        buffer = writeUint8(lenght, buffer);
        //PACKET ID
        buffer = writeUint8(DummyPacketID, buffer);
        buffer = writeUint32(p->seq, buffer);

        buffer = writeUint8(p->dummy.field_1, buffer);
        buffer = writeUint16(p->dummy.field_2, buffer);
        buffer = writeUint8(p->dummy.field_3, buffer);
        buffer = writeChar(p->dummy.field_4, buffer);
        buffer = writeFloat(p->dummy.field_5, buffer);
        buffer = writeChar(p->dummy.field_6, buffer);
        buffer = writeUint32(p->dummy.field_7, buffer);
        buffer = writeUint32(p->dummy.field_8, buffer);
    }//Ascii mode
    else {
        buffer = writeHeaderAscii(buffer);
        buffer = writeUint8Ascii(DummyPacketID, buffer);
        buffer = writeUint32Ascii(p->seq, buffer);
        buffer = writeUint8Ascii(p->dummy.field_1, buffer);
        buffer = writeUint16Ascii(p->dummy.field_2, buffer);
        buffer = writeUint8Ascii(p->dummy.field_3, buffer);
        buffer = writeCharAscii(p->dummy.field_4, buffer);
        buffer = writeFloatAscii(p->dummy.field_5, buffer);
        buffer = writeCharAscii((char) p->dummy.field_6, buffer);
        buffer = writeUint32Ascii(p->dummy.field_7, buffer);
        buffer = writeUint32Ascii(p->dummy.field_8, buffer);
        buffer = writeFooterAscii(buffer);
    }
    return buffer;
}
//==============================================================================
//==============================================================================


//DumbPacket
//==============================================================================
//Write
//==============================================================================
char* writeDumbPacket(const struct Packet* p, char* buffer, int ascii) {
    if (!ascii) {

    } else {

    }
    return buffer; //DUMMY
}

//Read
//==============================================================================
char* readDumbPacket(struct Packet* p, char* buffer, int ascii) {
    return buffer;
}

//==============================================================================
//==============================================================================


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
        write(device,&buffer[i],1);
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


