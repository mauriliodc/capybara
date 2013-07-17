#ifndef _QUERYCOMMANDS_PACKET_H_
#define _QUERYCOMMANDS_PACKET_H_

#include "packet_handler.h"

typedef struct QueryCommandsPacket{
  PacketHeader header;
  int8_t type;
} QueryCommandsPacket;

/*
void QueryCommandsPacket_print(const PacketHeader* state); // print on stdout;
enum HexMessageStatus QueryCommandsPacket_write(HexMessage* msg, const PacketHeader* state); // write the payload in a message
enum HexMessageStatus QueryCommandsPacket_read(HexMessage* msg, PacketHeader* state); // read the payload in a message
*/

int  QueryCommandsPacket_initHandler(int16_t type);

void QueryCommandsPacket_initHeader(QueryCommandsPacket* packet);

#endif
