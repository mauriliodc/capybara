#include "packets.h"


void Packets_init(){
  PacketHandler_init();
  QueryCommandsPacket_initHandler(0x0);
  StatePacket_initHandler(0x1);
  SpeedPacket_initHandler(0x2);
  PIDPacket_initHandler(0x3);
  WheelSpeedPacket_initHandler(0x4);
}
