#include "querycommands_packet.h"
#ifdef _LINUX_
#include "stdio.h"
#endif

void QueryCommandsPacket_print(const PacketHeader* state_){
  const QueryCommandsPacket* msg = (const QueryCommandsPacket*)state_;
  printf("QueryCommand:\n  type:%d", msg->type);
 
}


void QueryCommandsPacket_execute(PacketHeader* header, HexMessage* response){
  const QueryCommandsPacket* query = (const QueryCommandsPacket*) header ;
  if (query->type<0 || query->type>=PacketHandler_maxPacketTypes()){
    QueryCommandsPacket outQueryCommands = {{0}, PacketHandler_maxPacketTypes()};
    QueryCommandsPacket_initHeader(&outQueryCommands);
    Packet_write(response, (const PacketHeader*)&outQueryCommands);
  } else {
    Packet_write(response, header);
    const char* desc = Packet_description(query->type);
    if (desc){
      HexMessage_writeString(response, desc);
    } else
      HexMessage_writeString(response, "");
  }
}

#define formatField(field) \
  if(HexMessage_writeHex(msg, &state->field, sizeof(state->field)) != Ok) return WriteOverflow

enum HexMessageStatus QueryCommandsPacket_write(HexMessage* msg, const PacketHeader* state_){
  const QueryCommandsPacket* state= (const QueryCommandsPacket*) state_;
  formatField(type);
  return Ok;
}
#undef formatField

#define formatField(field) \
  if(HexMessage_readHex(msg, &state->field, sizeof(state->field)) != Ok) return ReadUnderflow

enum HexMessageStatus QueryCommandsPacket_read(HexMessage* msg, PacketHeader* state_){
  QueryCommandsPacket* state= (QueryCommandsPacket*) state_;
  formatField(type);
  return Ok;
}
#undef formatField

int16_t QueryCommandsPacket_type=-1;

static const char* description= "QueryCommandsPacket { uint8_t setOrGet; int16_t leftQueryCommands[3]; int16_t leftQueryCommands[3]}";

int  QueryCommandsPacket_initHandler(int16_t type){
  if (PacketHandler_registerPacket(description, type,QueryCommandsPacket_write,QueryCommandsPacket_read, QueryCommandsPacket_print, QueryCommandsPacket_execute)==0){
    QueryCommandsPacket_type=type;
    return 0;
  }  
  return -1;
}

void QueryCommandsPacket_initHeader(QueryCommandsPacket* packet){
  packet->header.type=QueryCommandsPacket_type;
}
