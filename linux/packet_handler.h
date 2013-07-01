#ifndef _PACKET_HANDLER_H_
#define _PACKET_HANDLER_H_

#include "hexmessage.h"

typedef struct PacketHeader{
  int8_t type;
} PacketHeader;

typedef enum HexMessageStatus (*Packet_writeFn)(HexMessage *msg, const PacketHeader* header);

typedef enum HexMessageStatus (*Packet_readFn)(HexMessage *msg, PacketHeader* header);

typedef void (*Packet_printFn)(const PacketHeader* header);

typedef void (*Packet_executeFn) (PacketHeader* header, HexMessage* response);

typedef void (*StringExecuteFn) (const unsigned char* c);

enum HexMessageStatus Packet_read(HexMessage *msg, PacketHeader* header);
enum HexMessageStatus Packet_write(HexMessage *msg, const PacketHeader* header);
int Packet_print(const PacketHeader* header); // 0 on success
int Packet_execute(PacketHeader* header, HexMessage* response); // 0 on success
const char* Packet_description(int16_t type);

void PacketHandler_init();

void PacketHandler_setStringExecuteFn(StringExecuteFn fn);

int PacketHandler_registerPacket(const char* description, int16_t type, Packet_writeFn write, Packet_readFn read, Packet_printFn print, Packet_executeFn execute);

int16_t PacketHandler_maxPacketTypes();
#endif
