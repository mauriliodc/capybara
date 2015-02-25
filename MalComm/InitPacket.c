#include "MalComm.h"
//InitPacket
//==============================================================================
//Write
//==============================================================================
char* writeInitPacket(const struct Packet* p, char* buffer, int ascii) {
  //BinaryMode
  if (!ascii) {
    uint8_t lenght = 7;
    //PACKET LENGTH
    buffer = writeUint8(lenght, buffer);
    //PACKET ID
    buffer = writeUint8(InitPacketID, buffer);
    buffer = writeUint32(p->seq, buffer);

    buffer = writeUint16(p->init.init, buffer);
  }//Ascii mode
    else {
        buffer = writeHeaderAscii(buffer);
        buffer = writeUint8Ascii(InitPacketID, buffer);
        buffer = writeUint32Ascii(p->seq, buffer);
        buffer = writeUint16Ascii(p->init.init, buffer);
        buffer = writeFooterAscii(buffer);
    }
    return buffer;
}

//Read
//==============================================================================

char* readInitPacket(struct Packet* p, char* buffer, int ascii) {
    if (!ascii) {
        buffer = readUint32(&(p->seq), buffer);
        buffer = readUint8(&(p->init.init), buffer);
    } else {
        long int a, b = 0;
        sscanf(buffer, "%ld %ld", &a, &b);
        p->seq = (uint32_t) a;
        p->init.init = (uint8_t) b;
        return buffer;



    }
}
    //==============================================================================
    //==============================================================================
