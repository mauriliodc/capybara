#include "odometrycalib_packet.h"
#ifdef _LINUX_
#include "stdio.h"
#endif

void OdometryCalibPacket_print(const PacketHeader* state_){
  const OdometryCalibPacket* msg = (const OdometryCalibPacket*)state_;
  printf("OdometryCalib:\n set:%d, [%f, %f, %f]", 
	 msg->setOrGet,
	 msg->kl,msg->kr,msg->baseline);
 }


void OdometryCalibPacket_execute(PacketHeader* header, HexMessage* response){
  const OdometryCalibPacket* odo = (const OdometryCalibPacket*) header ;
  if(odo->setOrGet){
    printf("IMPLEMENT ME, Setting  odoemtry parameters\n");
  } else {
    printf("IMPLEMENT ME, getting  odoemtry parameters\n");
    // we simulate reading the OdometryCalib from the platform and sending it to the output stream
    OdometryCalibPacket outOdometryCalib = {{0}, 0, 1e-3, 1e-3, 0.25};
    OdometryCalibPacket_initHeader(&outOdometryCalib);
    Packet_write(response, (const PacketHeader*)&outOdometryCalib);
  }
}


#define formatField(field) \
  if(HexMessage_writeHex(msg, &state->field, sizeof(state->field)) != Ok) return WriteOverflow

enum HexMessageStatus OdometryCalibPacket_write(HexMessage* msg, const PacketHeader* state_){
  const OdometryCalibPacket* state= (const OdometryCalibPacket*) state_;
  formatField(setOrGet);
  formatField(kl);
  formatField(kr);
  formatField(baseline);
  return Ok;
}
#undef formatField

#define formatField(field) \
  if(HexMessage_readHex(msg, &state->field, sizeof(state->field)) != Ok) return ReadUnderflow

enum HexMessageStatus OdometryCalibPacket_read(HexMessage* msg, PacketHeader* state_){
  OdometryCalibPacket* state= (OdometryCalibPacket*) state_;
  formatField(setOrGet);
  formatField(kl);
  formatField(kr);
  formatField(baseline);
  return Ok;
}
#undef formatField

int16_t OdometryCalibPacket_type=-1;

static const char* description= "OdometryCalibPacket { uint8_t setOrGet; float kl; float kr; float baseline }";

int  OdometryCalibPacket_initHandler(int16_t type){
  if (PacketHandler_registerPacket(description, type,OdometryCalibPacket_write,OdometryCalibPacket_read, OdometryCalibPacket_print, OdometryCalibPacket_execute)==0){
    OdometryCalibPacket_type=type;
    return 0;
  }  
  return -1;
}

void OdometryCalibPacket_initHeader(OdometryCalibPacket* packet){
  packet->header.type=OdometryCalibPacket_type;
}
