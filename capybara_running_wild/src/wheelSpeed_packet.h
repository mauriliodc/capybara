#ifndef _WHEEL_SPEED_PACKET_H_
#define _WHEEL_SPEED_PACKET_H_

#include "packet_handler.h"
#include "platform_defs.h"

typedef struct WheelSpeedPacket{
  PacketHeader header;
  int16_t leftSpeed, rightSpeed;
} WheelSpeedPacket;


int  WheelSpeedPacket_initHandler(int16_t type);

void WheelSpeedPacket_initHeader(WheelSpeedPacket* packet);

#endif
