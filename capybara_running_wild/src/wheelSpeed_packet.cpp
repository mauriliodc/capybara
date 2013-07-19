#include "wheelSpeed_packet.h"
#ifdef _LINUX_
#include "stdio.h"
#endif

void WheelSpeedPacket_print(const PacketHeader* state_){
  const WheelSpeedPacket* msg = (const WheelSpeedPacket*) state_;
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><Speed:\n [ %d, %d ]\n",
	 msg->leftSpeed,
	 msg->rightSpeed);

}

void WheelSpeedPacket_execute(PacketHeader* header, HexMessage* response){
  const WheelSpeedPacket* speed = (const WheelSpeedPacket*) header ;

}

#define formatField(field) \
  if(HexMessage_writeHex(msg, &state->field, sizeof(state->field)) != Ok) return WriteOverflow

enum HexMessageStatus WheelSpeedPacket_write(HexMessage* msg, const PacketHeader* state_){
  const WheelSpeedPacket* state= (const WheelSpeedPacket*) state_;
  formatField(leftSpeed);
  formatField(rightSpeed);
  return Ok;
}
#undef formatField

#define formatField(field) \
  if(HexMessage_readHex(msg, &state->field, sizeof(state->field)) != Ok) return ReadUnderflow

enum HexMessageStatus WheelSpeedPacket_read(HexMessage* msg, PacketHeader* state_){
  WheelSpeedPacket* state= ( WheelSpeedPacket*) state_;
  formatField(leftSpeed);
  formatField(rightSpeed);
  return Ok;
}
#undef formatField

int16_t WheelSpeedPacket_type=-1;

static const char* description= "WheelSpeedPacket { int leftSpeed; int rightSpeed }";

int  WheelSpeedPacket_initHandler(int16_t type){
  if (PacketHandler_registerPacket(description, type,WheelSpeedPacket_write,WheelSpeedPacket_read, WheelSpeedPacket_print, WheelSpeedPacket_execute)==0)
    WheelSpeedPacket_type=type;
  return 0;
}

void WheelSpeedPacket_initHeader(WheelSpeedPacket* packet){
  packet->header.type=WheelSpeedPacket_type;
  //printf("Wheel speed packet init!\n");

}

