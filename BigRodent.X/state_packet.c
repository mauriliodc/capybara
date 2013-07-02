#include "state_packet.h"
#ifdef _LINUX_
#include "stdio.h"
#endif

void StatePacket_print(const PacketHeader* state_){
  const StatePacket* msg= (const StatePacket*) state_;
//  printf("State:\nseq: %d\nenc: %d, %d\nincOdom: %f, %f, %f\nglobOdom: %f, %f, %f\nvel: %f, %f\nacc: %f, %f\nbattery:%f\ncurrent: %f, %f\n",
//	 msg->seq,
//	 msg->leftEncoder, msg->rightEncoder,
//	 msg->incrementalOdometry[0], msg->incrementalOdometry[1], msg->incrementalOdometry[2],
//	 msg->globalOdometry[0], msg->globalOdometry[1], msg->globalOdometry[2],
//	 msg->translationalVelocity, msg->rotationalVelocity,
//	 msg->translationalAcceleration, msg->rotationalAcceleration,
//	 0.1*msg->batteryVoltage,
//	 0.1*msg->leftPWMCurrent, 0.1*msg->rightPWMCurrent);

}

#define formatField(field) \
  if(HexMessage_writeHex(msg, &state->field, sizeof(state->field)) != Ok) return WriteOverflow

enum HexMessageStatus StatePacket_write(HexMessage* msg, const PacketHeader* state_){
  const StatePacket* state= (const StatePacket*) state_;
  formatField(seq);
  formatField(leftEncoder);
  formatField(rightEncoder);
  formatField(incrementalOdometry[0]);
  formatField(incrementalOdometry[1]);
  formatField(incrementalOdometry[2]);
  formatField(globalOdometry[0]);
  formatField(globalOdometry[1]);
  formatField(globalOdometry[2]);
  formatField(translationalVelocity);
  formatField(rotationalVelocity);
  formatField(translationalAcceleration);
  formatField(rotationalAcceleration);
  formatField(batteryVoltage);
  formatField(leftPWMCurrent);
  formatField(rightPWMCurrent);
  return Ok;
}
#undef formatField

#define formatField(field) \
  if(HexMessage_readHex(msg, &state->field, sizeof(state->field)) != Ok) return ReadUnderflow

enum HexMessageStatus StatePacket_read(HexMessage* msg, PacketHeader* state_){
  StatePacket* state= (StatePacket*) state_;
  formatField(seq);
  formatField(leftEncoder);
  formatField(rightEncoder);
  formatField(incrementalOdometry[0]);
  formatField(incrementalOdometry[1]);
  formatField(incrementalOdometry[2]);
  formatField(globalOdometry[0]);
  formatField(globalOdometry[1]);
  formatField(globalOdometry[2]);
  formatField(translationalVelocity);
  formatField(rotationalVelocity);
  formatField(translationalAcceleration);
  formatField(rotationalAcceleration);
  formatField(batteryVoltage);
  formatField(leftPWMCurrent);
  formatField(rightPWMCurrent);
  return Ok;
}
#undef formatField

static const char* description=
"StatePacket { int32_t seq; int16_t leftEncoder; int16_t rightEncoder; \
float incrementalOdometry[3];\
float globalOdometry[3];  float translationalVelocity; float rotationalVelocity; \
float translationalAcceleration; float rotationalAcceleration;\
int16_t batteryVoltage; int16_t leftPWMCurrent; int16_t rightPWMCurrent;}";

int16_t StatePacket_type=-1;
int  StatePacket_initHandler(int16_t type){
  if (PacketHandler_registerPacket(description, type,StatePacket_write,StatePacket_read, StatePacket_print, 0)==0)
    StatePacket_type=type;
  return 0;
}

void StatePacket_initHeader(StatePacket* packet){
  packet->header.type=StatePacket_type;
}



void StatePacket_initVoid(StatePacket* p)
{
    p->batteryVoltage=0;
    p->globalOdometry[0]=0;
    p->globalOdometry[1]=0;
    p->globalOdometry[2]=0;
    p->incrementalOdometry[0]=0;
    p->incrementalOdometry[1]=0;
    p->incrementalOdometry[2]=0;
    p->leftEncoder=0;
    p->leftPWMCurrent=0;
    p->rightEncoder=0;
    p->rightPWMCurrent=0;
    p->rotationalAcceleration=0;
    p->rotationalVelocity=0;
    p->translationalAcceleration=0;
    p->translationalVelocity=0;

}