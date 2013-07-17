#include "speed_packet.h"
#ifdef _LINUX_
#include "stdio.h"
#endif

void SpeedPacket_print(const PacketHeader* state_){
  const SpeedPacket* msg = (const SpeedPacket*) msg;
  printf("Speed:\n [ %f, %f ]\n",
	 msg->translationalSpeed, 
	 msg->rotationalSpeed);
 
}

void SpeedPacket_execute(PacketHeader* header, HexMessage* response){
  const SpeedPacket* speed = (const SpeedPacket*) header ;
  printf("IMPLEMENT ME: Setting Speed on base: %f, %f\n", speed->translationalSpeed, speed->rotationalSpeed);
}

#define formatField(field) \
  if(HexMessage_writeHex(msg, &state->field, sizeof(state->field)) != Ok) return WriteOverflow

enum HexMessageStatus SpeedPacket_write(HexMessage* msg, const PacketHeader* state_){
  const SpeedPacket* state= (const SpeedPacket*) state_;
  formatField(translationalSpeed);
  formatField(rotationalSpeed);
  return Ok;
}
#undef formatField

#define formatField(field) \
  if(HexMessage_readHex(msg, &state->field, sizeof(state->field)) != Ok) return ReadUnderflow

enum HexMessageStatus SpeedPacket_read(HexMessage* msg, PacketHeader* state_){
  SpeedPacket* state= (SpeedPacket*) state_;
  formatField(translationalSpeed);
  formatField(rotationalSpeed);
  return Ok;
}
#undef formatField

int16_t SpeedPacket_type=-1;

static const char* description= "SpeedPacket { float translationalVelocity; float rotationalVelocity }";

int  SpeedPacket_initHandler(int16_t type){
  if (PacketHandler_registerPacket(description, type,SpeedPacket_write,SpeedPacket_read, SpeedPacket_print, SpeedPacket_execute)==0)
    SpeedPacket_type=type;
  return 0;
}

void SpeedPacket_initHeader(SpeedPacket* packet){
  packet->header.type=SpeedPacket_type;
}
