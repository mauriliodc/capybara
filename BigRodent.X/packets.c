#include "packets.h"

void Packets_init(){
  PacketHandler_init();
  StatePacket_initHandler(0x1);
}