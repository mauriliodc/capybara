
#include "MalComm.h"
//SlimStatePacket
//==============================================================================
//Write
//==============================================================================
char* writeSlimStatePacket(const struct Packet* p, char* buffer, int ascii) {
  //BinaryMode
  if (!ascii) {
    uint8_t lenght = 9;
    //PACKET LENGTH
    buffer = writeUint8(lenght, buffer);
    //PACKET ID
    buffer = writeUint8(SlimStatePacketID, buffer);
    buffer = writeUint32(p->seq, buffer);
    buffer = writeUint16(p->slimState.leftEncoder, buffer);
    buffer = writeUint16(p->slimState.rightEncoder, buffer);
  }//Ascii mode
    else {
        buffer = writeHeaderAscii(buffer);
        buffer = writeUint8Ascii(SlimStatePacketID, buffer);
        buffer = writeUint32Ascii(p->seq, buffer);
        buffer = writeUint16Ascii(p->slimState.leftEncoder, buffer);
        buffer = writeUint16Ascii(p->slimState.rightEncoder, buffer);
        buffer = writeFooterAscii(buffer);
    }
    return buffer;
}

//Read
//==============================================================================

char* readSlimStatePacket(struct Packet* p, char* buffer, int ascii) {
    if (!ascii) {
        buffer = readUint32(&(p->seq), buffer);
        buffer = readUint16((uint16_t*)&(p->slimState.leftEncoder), buffer);
        buffer = readUint16((uint16_t*)&(p->slimState.rightEncoder), buffer);
    } else {
        long int a, b, c = 0;
        sscanf(buffer, "%ld %ld %ld", &a, &b, &c);
        p->seq = (uint32_t) a;
        p->slimState.leftEncoder = (uint16_t) b;
        p->slimState.rightEncoder = (uint16_t) c;
        return buffer;
    }


}

//==============================================================================
//==============================================================================
