#ifndef _PID_PACKET_H_
#define _PID_PACKET_H_

#include "packet_handler.h"

typedef struct PIDPacket{
  PacketHeader header;
  uint8_t setOrGet;
  uint16_t leftPID[3], rightPID[3];
} PIDPacket;

/*
void PIDPacket_print(const PacketHeader* state); // print on stdout;
enum HexMessageStatus PIDPacket_write(HexMessage* msg, const PacketHeader* state); // write the payload in a message
enum HexMessageStatus PIDPacket_read(HexMessage* msg, PacketHeader* state); // read the payload in a message
*/

int  PIDPacket_initHandler(int16_t type);

void PIDPacket_initHeader(PIDPacket* packet);

#endif
