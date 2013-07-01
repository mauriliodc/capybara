#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"
#include <string.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char** argv) {
  // initializes the packet handler and registers the packets (see the function)
  Packets_init();



  // fill some packets randomly;
  StatePacket outState = {
    {0}, // this is the type, should be set by initSpeedPacket;
    10,
    1,2,
    {0.1, 0.1, 0.2},
    {1.1, 1.1, 1.2},
    1.0, 0.0,
    1.0, 0.0,
    125,
    10, 11
  };
  // !!!!! remmeber to initialize the header after creating a packet
  StatePacket_initHeader(&outState);

  QueryCommandsPacket outQuery = {{0}, -1};
  QueryCommandsPacket_initHeader(&outQuery);

  SpeedPacket outSpeed = {{0}, 0.1, 0.2};
  // !!!!! remmeber to initialize the header after creating a packet
  SpeedPacket_initHeader(&outSpeed);

  PIDPacket outPID = {{0}, 0, {1,2,3}, {1,2,3}};
  // !!!!! remmeber to initialize the header after creating a packet
  PIDPacket_initHeader(&outPID);

  OdometryCalibPacket outOdom = {{0}, 0, 1e-3, 1e-3, 0.25};
  // !!!!! remmeber to initialize the header after creating a packet
  OdometryCalibPacket_initHeader(&outOdom);


  // construct  a buffer
  char buffer[MAX_BUFFER_SIZE];
  HexMessage msg;
  HexMessage_setBuffer(&msg, buffer,MAX_BUFFER_SIZE);
  memset(buffer, 0, MAX_BUFFER_SIZE);


  // write the query for the num of messages"
  if(Packet_write(&msg,(const struct PacketHeader*)&outQuery)!=Ok)
    printf("write error\n");
  *msg.current=0;
  printf("%s\n",msg.start);
  HexMessage_reset(&msg);
  
  // query the description of each message
  int j;
  for (j=0; j< PacketHandler_maxPacketTypes(); j++){
    outQuery.type = j;
    if(Packet_write(&msg,(const struct PacketHeader*)&outQuery)!=Ok)
      printf("write error\n");
    *msg.current=0;
    printf("%s\n",msg.start);
    HexMessage_reset(&msg);
  }

  
  // simulate a random run
  int i;
  for  (i=0; i<5; i++){
    // we serialize the messages



    if(Packet_write(&msg,(const struct PacketHeader*)&outState)!=Ok)
      printf("write error\n");
    *msg.current=0;
    printf("%s\n",msg.start);
    HexMessage_reset(&msg);

    if(Packet_write(&msg,(const struct PacketHeader*)&outSpeed)!=Ok)
      printf("write error\n");
    *msg.current=0;
    printf("%s\n",msg.start);
    HexMessage_reset(&msg);

    if(Packet_write(&msg,(const struct PacketHeader*)&outPID)!=Ok)
      printf("write error\n");
    *msg.current=0;
    printf("%s\n",msg.start);
    HexMessage_reset(&msg);

    if(Packet_write(&msg,(const struct PacketHeader*)&outOdom)!=Ok)
      printf("write error\n");
    *msg.current=0;
    printf("%s\n",msg.start);
    HexMessage_reset(&msg);
  }
  
  return 0;
}
