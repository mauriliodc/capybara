#ifndef _SPEED_PACKET_H_
#define _SPEED_PACKET_H_

#include "packet_handler.h"

typedef struct SpeedPacket{
  PacketHeader header;
  float translationalSpeed, rotationalSpeed;
} SpeedPacket;

/*
void SpeedPacket_print(const PacketHeader* state); // print on stdout;
enum HexMessageStatus SpeedPacket_write(HexMessage* msg, const PacketHeader* state); // write the payload in a message
enum HexMessageStatus SpeedPacket_read(HexMessage* msg, PacketHeader* state); // read the payload in a message
*/

int  SpeedPacket_initHandler(int16_t type);

void SpeedPacket_initHeader(SpeedPacket* packet);

#endif
