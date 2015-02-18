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

void DecoderInit(struct PacketDecoder* d) {
    ResetDecoderBuffer(d);
    d->status = Unsync;
    d->lenght = 0;
    d->ascii = 1;

}

void EncoderInit(struct PacketEncoder* e) {
    ResetEncoderBuffer(e);
    e->status = Unsync;
    e->lenght = 0;
    e->ascii = 1;
}

void ResetDecoderBuffer(struct PacketDecoder* d) {
    memset(d->buffer, '\0', BUFFER_SIZE);
    d->buffer_start = &(d->buffer[0]);
    d->buffer_end = &(d->buffer[BUFFER_SIZE - 1]);
}

void ResetEncoderBuffer(struct PacketEncoder* e) {
    memset(e->buffer, '\0', BUFFER_SIZE);
    e->buffer_start = &(e->buffer[0]);
    e->buffer_end = &(e->buffer[BUFFER_SIZE - 1]);
}
//==============================================================================

//ENCODER STUFF
//==============================================================================

//==============================================================================


//DECODER STUFF
//==============================================================================

//==============================================================================



//PACKET STUFF
//==============================================================================

void writePacket(const struct Packet* p, char* buffer, int ascii) {
    if (p->id == DummyPacketID) {
        writeDummyPacket(p, buffer, ascii);
    } else if (p->id == DumbPacketID) {
        writeDumbPacket(p, buffer, ascii);
    }
}

void parsePacket(char* buffer, struct Packet* p, int ascii) {
    uint8_t id = ReadUint8(buffer);
    buffer+=sizeof(uint8_t);
    if (id == DummyPacketID) {
        p->id = id;
        readDummyPacket(p, buffer, ascii);
    } else if (id == DumbPacketID) {
        p->id = id;
        readDumbPacket(p, buffer, ascii);
    }
}
//==============================================================================

//pay attention, this make side effect on buffer
void writeDummyPacket(const struct Packet* p, char* buffer, int ascii) {
    if (!ascii) {
        buffer=WriteUint8(DummyPacketID,buffer);
        buffer=WriteUint8(99,buffer);
        buffer=WriteUint8(p->dummy.field_1,buffer);
        buffer=WriteUint16(p->dummy.field_2,buffer);
        buffer=WriteUint8(p->dummy.field_3,buffer);
        buffer=WriteChar(p->dummy.field_4,buffer);
        buffer=WriteFloat(p->dummy.field_5,buffer);
        buffer=WriteChar(p->dummy.field_6,buffer);
        buffer=WriteUint32(p->dummy.field_7,buffer);
        buffer=WriteUint32(p->dummy.field_8,buffer);

    } else {

    }
}

void writeDumbPacket(const struct Packet* p, char* buffer, int ascii) {
    if (!ascii) {

    } else {

    }
}

void readDummyPacket(struct Packet* p,char* buffer, int ascii) {
    p->lenght = ReadUint8(buffer);
    buffer+=sizeof(uint8_t);
    p->dummy.field_1 = ReadUint8(buffer);
    buffer+=sizeof(uint8_t);
    p->dummy.field_2 = ReadUint16(buffer);
    buffer+=sizeof(uint16_t);
    p->dummy.field_3 = (int8_t) ReadUint8(buffer);
    buffer+=sizeof(uint8_t);
    p->dummy.field_4 = (char) ReadUint8(buffer);
    buffer+=sizeof(uint8_t);
    p->dummy.field_5 = ReadFloat(buffer);
    buffer+=sizeof(float);
    p->dummy.field_6 = (unsigned char) ReadUint8(buffer);
    buffer+=sizeof(unsigned char);
    p->dummy.field_7 = ReadUint32(buffer);
    buffer+=sizeof(uint32_t);
    p->dummy.field_8 = (int32_t) ReadUint32(buffer);
    buffer+=sizeof(int32_t);
}

void readDumbPacket(struct Packet* p,char* buffer, int ascii) {

}

//==============================================================================
//Conversion primitives:BINARY
char* WriteChar(char value, char* buffer){
   *(char*)buffer=value;
   buffer++;
   return buffer;
}
char* WriteUint8(uint8_t value, char* buffer) {
    *(uint8_t*)buffer=value;
   buffer++;
   return buffer;
}

char* WriteUint16(uint16_t value, char* buffer) {
    char* valuePTR=(char*)&value;
    *(char*)buffer=*valuePTR;
   buffer++;
   valuePTR++;
   *(char*)buffer=*valuePTR;
   buffer++;
   return buffer;
}

char* WriteUint32(uint32_t value, char* buffer) {
   char* valuePTR=(char*)&value;
   *(char*)buffer=*valuePTR;
   buffer++;
   valuePTR++;
   *(char*)buffer=*valuePTR;
   buffer++;
   valuePTR++;
   *(char*)buffer=*valuePTR;
   buffer++;
   valuePTR++;
   *(char*)buffer=*valuePTR;
   buffer++;
   return buffer;
}

char* WriteFloat(float value, char* buffer) {
   char* valuePTR=(char*)&value;
   *(char*)buffer=*valuePTR;
   buffer++;
   valuePTR++;
   *(char*)buffer=*valuePTR;
   buffer++;
   valuePTR++;
   *(char*)buffer=*valuePTR;
   buffer++;
   valuePTR++;
   *(char*)buffer=*valuePTR;
   buffer++;
   return buffer;
}





uint8_t ReadUint8(char* buffer) {
    uint8_t value=*(uint8_t*) buffer;
    *buffer++;
    return value;
}

uint16_t ReadUint16(char* buffer) {
    uint16_t value;
    char* valuePTR=(char*)&value;
    *(char*)valuePTR=*buffer;
    buffer++;
    valuePTR++;
    *(char*)valuePTR=*buffer;
    buffer++;
    return value;
}

uint32_t ReadUint32(char* buffer) {
    uint32_t value;
    char* valuePTR=(char*)&value;
    *(char*)valuePTR=*buffer;
    buffer++;
    valuePTR++;
    *(char*)valuePTR=*buffer;
    buffer++;
    valuePTR++;
    *(char*)valuePTR=*buffer;
    buffer++;
    valuePTR++;
    *(char*)valuePTR=*buffer;
    buffer++;
    return value;
}

float ReadFloat(char* buffer) {
    float value;
    char* valuePTR=(char*)&value;
    *(char*)valuePTR=*buffer;
    buffer++;
    valuePTR++;
    *(char*)valuePTR=*buffer;
    buffer++;
    valuePTR++;
    *(char*)valuePTR=*buffer;
    buffer++;
    valuePTR++;
    *(char*)valuePTR=*buffer;
    buffer++;
    return value;
}