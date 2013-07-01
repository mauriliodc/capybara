#ifndef _ODOMETRYCALIB_PACKET_H_
#define _ODOMETRYCALIB_PACKET_H_

#include "packet_handler.h"

typedef struct OdometryCalibPacket{
  PacketHeader header;
  uint8_t setOrGet;
  float kr, kl, baseline;
} OdometryCalibPacket;

/*
void OdometryCalibPacket_print(const PacketHeader* state); // print on stdout;
enum HexMessageStatus OdometryCalibPacket_write(HexMessage* msg, const PacketHeader* state); // write the payload in a message
enum HexMessageStatus OdometryCalibPacket_read(HexMessage* msg, PacketHeader* state); // read the payload in a message
*/

int  OdometryCalibPacket_initHandler(int16_t type);

void OdometryCalibPacket_initHeader(OdometryCalibPacket* packet);

#endif
