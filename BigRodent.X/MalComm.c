#include "MalComm.h"
//INITIALIZATION STUFF
uint8_t DummyPacketID;
uint8_t DumbPacketID;
char header_1;
char header_2;
char AsciiHeader;
char AsciiFooter;
void initConsts() {
    DummyPacketID = 1;
    DumbPacketID = 2;
    header_1 = 0x43;
    header_2 = 0x3d;
    AsciiHeader='(';
    AsciiFooter=')';
}
//==============================================================================

void DecoderInit(struct PacketDecoder* d, int ascii) {
    ResetDecoderBuffer(d);
    d->buffer_start = &(d->buffer[0]);
    d->buffer_end = &(d->buffer[BUFFER_SIZE - 1]);
    d->status = Unsync;
    d->lenght = 0;
    d->ascii = ascii;

}

void ResetDecoderBuffer(struct PacketDecoder* d) {
    memset(d->buffer, '\0', BUFFER_SIZE);
}

//==============================================================================

//DECODER STUFF
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
            if (d->lenght > 1) {
                d->checksum ^= c;
                *(d->buffer_start) = c;
                d->buffer_start++;
                d->lenght--;
            } else {
                d->checksum ^= c;
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
                *(d->buffer_start) = c;
                d->buffer_start++;
            }
        }
        }
    return 0;
}
//==============================================================================



//PACKET STUFF
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

uint8_t computeChecksum(char* buffer, uint8_t length){
    uint8_t checksum=0;
    uint8_t len = length - 1;
        while (len) {
            checksum ^= *(buffer - len);
            len--;
        }
    return checksum;
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
//==============================================================================

//pay attention, this make side effect on buffer
//The checksum is computed on the first byte of each field.
//We need to get the addresws of (buffer-1) because the Write primitive does side effect
//on the buffer, so the returned buffer points to a NUL byte

char* writeDummyPacket(const struct Packet* p, char* buffer, int ascii) {
    //BinaryMode
    if (!ascii) {
        uint8_t lenght = sizeof (uint8_t)*6;
        lenght += sizeof (uint16_t);
        lenght += sizeof (uint32_t) *4;
//        uint8_t checksum = 0;
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
        //LET'S COMPUTE THE CHECKSUM
        //LEN is the lenght of the payload, minus one otherwise i would compute the checksum of the lenght
//        uint8_t len = lenght - 1;
//        while (len) {
//            checksum ^= *(buffer - len);
//            len--;
//        }
//        buffer = writeUint8(checksum, buffer);
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

char* writeDumbPacket(const struct Packet* p, char* buffer, int ascii) {
    if (!ascii) {

    } else {

    }
    return buffer; //DUMMY
}

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

char* readDumbPacket(struct Packet* p, char* buffer, int ascii) {
    return buffer;
}

//==============================================================================
//Conversion primitives:BINARY

char* writeChar(char value, char* buffer) {
    *(char*) buffer = value;
    buffer++;
    return buffer;
}

char* writeUint8(uint8_t value, char* buffer) {
    *(uint8_t*) buffer = value;
    buffer++;
    return buffer;
}

char* writeUint16(uint16_t value, char* buffer) {
    char* valuePTR = (char*) &value;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    return buffer;
}

char* writeUint32(uint32_t value, char* buffer) {
    char* valuePTR = (char*) &value;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    return buffer;
}

char* writeFloat(float value, char* buffer) {
    char* valuePTR = (char*) &value;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    return buffer;
}

char* readUint8(uint8_t* dest, char* buffer) {
    *dest = *(uint8_t*) buffer;
    return buffer + 1;
}

char* readUint16(uint16_t* dest, char* buffer) {
    char* valuePTR = (char*) dest;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    return buffer;
}

char* readUint32(uint32_t* dest, char* buffer) {
    char* valuePTR = (char*) dest;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    return buffer;
}

char* readFloat(float* dest, char* buffer) {
    char* valuePTR = (char*) dest;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    return buffer;
}


//==============================================================================
//Conversion primitives:ASCII
char* writeHeaderAscii(char* buffer){
    return buffer + sprintf(buffer, "%c ", AsciiHeader);
}
 char* writeFooterAscii(char* buffer){
     return buffer + sprintf(buffer, "%c ", AsciiFooter);
 }
char* writeCharAscii(char value, char* buffer) {
    return buffer + sprintf(buffer, "%u ", value);

}

char* writeUint8Ascii(uint8_t value, char* buffer) {
    return buffer + sprintf(buffer, "%u ", value);

}

char* writeUint16Ascii(uint16_t value, char* buffer) {
    return buffer + sprintf(buffer, "%u ", value);

}

char* writeUint32Ascii(uint32_t value, char* buffer) {
    return buffer + sprintf(buffer, "%lu ", value);

}

char* writeFloatAscii(float value, char* buffer) {
    return buffer + sprintf(buffer, "%f ", (double) value);

}

char* readUint8Ascii(char* dest, char* buffer) {
    *(uint8_t*) dest = (uint8_t) strtoul(buffer, &buffer, 10);
    return buffer;
}

char* readUint16Ascii(char* dest, char* buffer) {
    *(uint16_t*) dest = strtoul(buffer, &buffer, 10);
    return buffer;
}

char* readUint32Ascii(char* dest, char* buffer) {
    *(uint32_t*) dest = strtoul(buffer, &buffer, 10);
    return buffer;
}

char* readFloatAscii(char* dest, char* buffer) {
    *(float*) dest = strtoul(buffer, &buffer, 10);
    return buffer;
}


