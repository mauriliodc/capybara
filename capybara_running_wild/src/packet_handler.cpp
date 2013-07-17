#include <stdio.h>
#include "packet_handler.h"

#define MAX_PACKET_TYPES 32
#define MAX_STRING_SIZE  1024

typedef struct PacketOps{
  uint16_t type;
  Packet_writeFn write;
  Packet_readFn read;
  Packet_printFn print;
  Packet_executeFn execute;
} PacketOps;



PacketOps packetOps[MAX_PACKET_TYPES];
const char* packetDescriptions[MAX_PACKET_TYPES] ;
unsigned char packetStringBuffer[MAX_STRING_SIZE];

StringExecuteFn PacketHandler_stringExecuteFn=0;

enum HexMessageStatus Packet_read(HexMessage *msg, PacketHeader* header){
  struct PacketOps* ops=0;
  enum HexMessageStatus status=Ok;
  // we read away all the strings, and call the string handler;
  if (HexMessage_nextIsString(msg) && status==Ok){
    status = HexMessage_readString(msg,packetStringBuffer);
    if (status==Ok && PacketHandler_stringExecuteFn)
      (*PacketHandler_stringExecuteFn)(packetStringBuffer);
    header->type=-1;
    return status;
  } else {
    status = HexMessage_readHex(msg, (void*)&header->type, sizeof(header->type));
    if (status!=Ok)
      return status;
    if (header->type<0 || header->type>=MAX_PACKET_TYPES)
      return UnknownMessage;
    ops = packetOps+header->type;
    if (ops->type<0)
      return UnknownMessage;
    if (ops->read){
      return (*ops->read)(msg,header);
    }
    return Ok;
  }
}

enum HexMessageStatus Packet_write(HexMessage *msg, const PacketHeader* header){
  struct PacketOps* ops=0;
  if (header->type<0 || header->type>=MAX_PACKET_TYPES)
    return UnknownMessage;
  ops = packetOps+header->type;
  if (ops->type<0)
    return UnknownMessage;
  enum HexMessageStatus status = HexMessage_writeHex(msg, (void*)&header->type, sizeof(header->type));
  if (status!=Ok)
    return status;
  if (ops->write){
    return (*ops->write)(msg,header);
  }
  return Ok;
}

// todo, use enum for errors
int Packet_print(const PacketHeader* header){
  struct PacketOps* ops=0;
  if (header->type<0 || header->type>=MAX_PACKET_TYPES)
    return -1;
  ops = packetOps+header->type;
  if (ops->type<0)
    return -2;
  printf("****** Message Type: %02d *******\n" , header->type);
  if (ops->print){
    (*ops->print)(header);
  }
  return 0;
}

// todo, use enum for errors
int Packet_execute(PacketHeader* header, HexMessage *msg){
  struct PacketOps* ops=0;
  if (header->type>=MAX_PACKET_TYPES)
    return -1;
  ops = packetOps+header->type;
  if (ops->type<0)
    return -2;
  if (ops->execute){
    (*ops->execute)(header,msg);
    return -3;
  }
  return 0;
}

void PacketHandler_init(){
  memset(packetOps, 0, sizeof(PacketOps)*MAX_PACKET_TYPES);
  memset(packetDescriptions, 0, sizeof(const char*)*MAX_PACKET_TYPES);
  int i;
  for(i=0; i<MAX_PACKET_TYPES; i++)
    packetOps[i].type=-1;
}

int PacketHandler_registerPacket(const char* description, int16_t type, Packet_writeFn write, Packet_readFn read, Packet_printFn print, Packet_executeFn execute){
  if (type<0)
    return -1;
  PacketOps *ops = &(packetOps[type]);
  ops->type=type;
  ops->write=write;
  ops->read=read;
  ops->print=print;
  ops->execute=execute;
  packetDescriptions[type] = description;
  return 0;
}

const char* Packet_description(int16_t type) {
  if (type<0 || type>=MAX_PACKET_TYPES)
    return 0;
  if (packetDescriptions[type])
    return packetDescriptions[type];
  return 0;
}

int16_t PacketHandler_maxPacketTypes() {return MAX_PACKET_TYPES;}

void PacketHandler_setStringExecuteFn(StringExecuteFn fn){
  PacketHandler_stringExecuteFn = fn;
}
