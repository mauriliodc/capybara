#ifndef _STATE_PACKET_H_
#define _STATE_PACKET_H_

#include "packet_handler.h"

typedef struct StatePacket{
  PacketHeader header;
  int32_t seq;
  int16_t leftEncoder, rightEncoder;

  float incrementalOdometry[3];
  float globalOdometry[3];
  float translationalVelocity, rotationalVelocity;
  float translationalAcceleration, rotationalAcceleration;
  int16_t batteryVoltage;                  // in steps of 0.1 v;
  int16_t leftPWMCurrent, rightPWMCurrent; // in steps of 0.1 A
} StatePacket;

/*
void StatePacket_print(const PacketHeader* state); // print on stdout;
enum HexMessageStatus StatePacket_write(HexMessage* msg, const PacketHeader* state); // write the payload in a message
enum HexMessageStatus StatePacket_read(HexMessage* msg, PacketHeader* state); // read the payload in a message
*/

int  StatePacket_initHandler(int16_t type);

void StatePacket_initHeader(StatePacket* packet);

#endif
