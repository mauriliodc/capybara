#include "pid_packet.h"
#ifdef _LINUX_
#include "stdio.h"
#endif

void PIDPacket_print(const PacketHeader* state_){
  const PIDPacket* msg = (const PIDPacket*)state_;
  printf("PID:\n set:%d, left[%d, %d, %d]\nright[%d, %d, %d]", 
	 msg->setOrGet,
	 msg->leftPID[0], msg->leftPID[1], msg->leftPID[2], 
	 msg->rightPID[0], msg->rightPID[1], msg->rightPID[2]);
 
}


void PIDPacket_execute(PacketHeader* header, HexMessage* response){
  const PIDPacket* pid = (const PIDPacket*) header ;
  if(pid->setOrGet){
    printf("IMPLEMENT ME, Setting  pid controller parameters\n");
  } else {
    printf("IMPLEMENT ME, Getting  pid controller parameters and sending back the output\n");
    // we simulate reading the PID from the platform and sending it to the output stream
    PIDPacket outPID = {{0}, 0, {1,2,3}, {1,2,3}};
    PIDPacket_initHeader(&outPID);
    Packet_write(response, (const PacketHeader*)&outPID);
  }
}


#define formatField(field) \
  if(HexMessage_writeHex(msg, &state->field, sizeof(state->field)) != Ok) return WriteOverflow

enum HexMessageStatus PIDPacket_write(HexMessage* msg, const PacketHeader* state_){
  const PIDPacket* state= (const PIDPacket*) state_;
  formatField(setOrGet);
  formatField(leftPID[0]);
  formatField(leftPID[1]);
  formatField(leftPID[2]);
  formatField(rightPID[0]);
  formatField(rightPID[1]);
  formatField(rightPID[2]);
  return Ok;
}
#undef formatField

#define formatField(field) \
  if(HexMessage_readHex(msg, &state->field, sizeof(state->field)) != Ok) return ReadUnderflow

enum HexMessageStatus PIDPacket_read(HexMessage* msg, PacketHeader* state_){
  PIDPacket* state= (PIDPacket*) state_;
  formatField(setOrGet);
  formatField(leftPID[0]);
  formatField(leftPID[1]);
  formatField(leftPID[2]);
  formatField(rightPID[0]);
  formatField(rightPID[1]);
  formatField(rightPID[2]);
  return Ok;
}
#undef formatField

int16_t PIDPacket_type=-1;

static const char* description= "PIDPacket { uint8_t setOrGet; int16_t leftPID[3]; int16_t leftPID[3]}";

int  PIDPacket_initHandler(int16_t type){
  if (PacketHandler_registerPacket(description, type,PIDPacket_write,PIDPacket_read, PIDPacket_print, PIDPacket_execute)==0){
    PIDPacket_type=type;
    return 0;
  }  
  return -1;
}

void PIDPacket_initHeader(PIDPacket* packet){
  packet->header.type=PIDPacket_type;
}
