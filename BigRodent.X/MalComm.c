#include "MalComm.h"
//INITIALIZATION STUFF
uint8_t DummyPacketID;
uint8_t DumbPacketID;
char header_1;
char header_2;

void initConsts() {
    DummyPacketID = 1;
    DumbPacketID = 2;
    header_1 = 0x43;
    header_2 = 0x3d;
}
//==============================================================================

void DecoderInit(struct PacketDecoder* d, int ascii) {
    ResetDecoderBuffer(d);
    d->status = Unsync;
    d->lenght = 0;
    d->ascii = ascii;

}

void ResetDecoderBuffer(struct PacketDecoder* d) {
    memset(d->buffer, '\0', BUFFER_SIZE);
    d->buffer_start = &(d->buffer[0]);
    d->buffer_end = &(d->buffer[BUFFER_SIZE - 1]);
}

//==============================================================================

//DECODER STUFF
//==============================================================================

int DecoderPutChar(struct PacketDecoder* d, char c) {
    //binary mode
    if (d->ascii == 0) {
        if (d->status == Unsync) {
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
    return 0;
}
//==============================================================================



//PACKET STUFF
//==============================================================================

void writePacket(const struct Packet* p, char* buffer, int ascii) {
    //Binary mode
    if (!ascii) {
        buffer = WriteUint8(header_1, buffer);
        buffer = WriteUint8(header_2, buffer);
    }//Ascii mode
    else {

    }
    if (p->id == DummyPacketID) {
        writeDummyPacket(p, buffer, ascii);
    } else if (p->id == DumbPacketID) {
        writeDumbPacket(p, buffer, ascii);
    }
}

//Note,buffer has to point to the ID, not to the length

void parsePacket(char* buffer, struct Packet* p, int ascii) {
    uint8_t id = ReadUint8(buffer);
    buffer += sizeof (uint8_t);
    //IF - ELSE-IF for each existing packet
    p->id = id;
    if (id == DummyPacketID) {
        readDummyPacket(p, buffer, ascii);
    } else if (id == DumbPacketID) {
        readDumbPacket(p, buffer, ascii);
    }
}
//==============================================================================

//pay attention, this make side effect on buffer
//The checksum is computed on the first byte of each field.
//We need to get the addresws of (buffer-1) because the Write primitive does side effect
//on the buffer, so the returned buffer points to a NUL byte

void writeDummyPacket(const struct Packet* p, char* buffer, int ascii) {
    //BinaryMode
    if (!ascii) {
        uint8_t lenght = sizeof (uint8_t)*6;
        lenght += sizeof (uint16_t);
        lenght += sizeof (uint32_t) *4;
        uint8_t checksum = 0;
        //PACKET LENGTH
        buffer = WriteUint8(lenght, buffer);
        //PACKET ID
        buffer = WriteUint8(DummyPacketID, buffer);
        buffer = WriteUint32(p->seq, buffer);
        buffer = WriteUint8(p->dummy.field_1, buffer);
        buffer = WriteUint16(p->dummy.field_2, buffer);
        buffer = WriteUint8(p->dummy.field_3, buffer);
        buffer = WriteChar(p->dummy.field_4, buffer);
        buffer = WriteFloat(p->dummy.field_5, buffer);
        buffer = WriteChar(p->dummy.field_6, buffer);
        buffer = WriteUint32(p->dummy.field_7, buffer);
        buffer = WriteUint32(p->dummy.field_8, buffer);
        //LET'S COMPUTE THE CHECKSUM
        //LEN is the lenght of the payload, minus one otherwise i would compute the checksum of the lenght
        uint8_t len = lenght - 1;
        while (len) {
            checksum ^= *(buffer - len);
            len--;
        }
        buffer = WriteUint8(checksum, buffer);
    }        //Ascii mode
    else {
        char* bufferPtr = buffer;
        buffer += WriteCharAscii('(', buffer);
        buffer += WriteUint8Ascii(DummyPacketID, buffer);
        buffer += WriteUint32Ascii(p->seq, buffer);
        buffer += WriteUint8Ascii(p->dummy.field_1, buffer);
        buffer += WriteUint16Ascii(p->dummy.field_2, buffer);
        buffer += WriteUint8Ascii(p->dummy.field_3, buffer);
        buffer += WriteCharAscii(p->dummy.field_4, buffer);
        buffer += WriteFloatAscii(p->dummy.field_5, buffer);
        buffer += WriteCharAscii((char)p->dummy.field_6, buffer);
        buffer += WriteUint32Ascii(p->dummy.field_7, buffer);
        buffer += WriteUint32Ascii(p->dummy.field_8, buffer);
        buffer += WriteCharAscii(')', buffer);
    }
}

void writeDumbPacket(const struct Packet* p, char* buffer, int ascii) {
    if (!ascii) {

    } else {

    }
}

void readDummyPacket(struct Packet* p, char* buffer, int ascii) {
    //Don't have to read the lenght
    p->seq = ReadUint32(buffer);
    buffer += sizeof (uint32_t);
    p->dummy.field_1 = ReadUint8(buffer);
    buffer += sizeof (uint8_t);
    p->dummy.field_2 = ReadUint16(buffer);
    buffer += sizeof (uint16_t);
    p->dummy.field_3 = (int8_t) ReadUint8(buffer);
    buffer += sizeof (uint8_t);
    p->dummy.field_4 = (char) ReadUint8(buffer);
    buffer += sizeof (uint8_t);
    p->dummy.field_5 = ReadFloat(buffer);
    buffer += sizeof (float);
    p->dummy.field_6 = (unsigned char) ReadUint8(buffer);
    buffer += sizeof (unsigned char);
    p->dummy.field_7 = ReadUint32(buffer);
    buffer += sizeof (uint32_t);
    p->dummy.field_8 = (int32_t) ReadUint32(buffer);
    buffer += sizeof (int32_t);
}

void readDumbPacket(struct Packet* p, char* buffer, int ascii) {

}

//==============================================================================
//Conversion primitives:BINARY

char* WriteChar(char value, char* buffer) {
    *(char*) buffer = value;
    buffer++;
    return buffer;
}

char* WriteUint8(uint8_t value, char* buffer) {
    *(uint8_t*) buffer = value;
    buffer++;
    return buffer;
}

char* WriteUint16(uint16_t value, char* buffer) {
    char* valuePTR = (char*) &value;
    *(char*) buffer = *valuePTR;
    buffer++;
    valuePTR++;
    *(char*) buffer = *valuePTR;
    buffer++;
    return buffer;
}

char* WriteUint32(uint32_t value, char* buffer) {
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

char* WriteFloat(float value, char* buffer) {
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

uint8_t ReadUint8(char* buffer) {
    uint8_t value = *(uint8_t*) buffer;
    return value;
}

uint16_t ReadUint16(char* buffer) {
    uint16_t value;
    char* valuePTR = (char*) &value;
    *(char*) valuePTR = *buffer;
    buffer++;
    valuePTR++;
    *(char*) valuePTR = *buffer;
    buffer++;
    return value;
}

uint32_t ReadUint32(char* buffer) {
    uint32_t value;
    char* valuePTR = (char*) &value;
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
    return value;
}

float ReadFloat(char* buffer) {
    float value;
    char* valuePTR = (char*) &value;
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
    return value;
}


//==============================================================================
//Conversion primitives:ASCII

int WriteCharAscii(char value, char* buffer) {
    return sprintf(buffer, "%c ", value);

}

int WriteUint8Ascii(uint8_t value, char* buffer) {
    return sprintf(buffer, "%u ", value);

}

int WriteUint16Ascii(uint16_t value, char* buffer) {
    return sprintf(buffer, "%u ", value);

}

int WriteUint32Ascii(uint32_t value, char* buffer) {
    return sprintf(buffer, "%lu ", value);

}

int WriteFloatAscii(float value, char* buffer) {
    return sprintf(buffer, "%f ", (double) value);

}

void ReadUint8Ascii(char* buffer, char* dest) {

}

void ReadUint16Ascii(char* buffer, char* dest) {

}

void ReadUint32Ascii(char* buffer, char* dest) {

}

void ReadFloatAscii(char* buffer, char* dest) {

}