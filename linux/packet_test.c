#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"

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


  SpeedPacket outSpeed = {{0}, 0.1, 0.2};
  // !!!!! remmeber to initialize the header after creating a packet
  SpeedPacket_initHeader(&outSpeed);

  PIDPacket outPID = {{0}, 0, {1,2,3}, {1,2,3}};
  // !!!!! remmeber to initialize the header after creating a packet
  PIDPacket_initHeader(&outPID);


  // next we print what we are putting in the system;
  Packet_print((const struct PacketHeader*)&outState);
  Packet_print((const struct PacketHeader*)&outSpeed);
  Packet_print((const struct PacketHeader*)&outPID);

  
  // now we construct a buffer and attempt serializing the messages one after another

  // construct  a buffer
  char buffer[MAX_BUFFER_SIZE];
  HexMessage msg;
  HexMessage_setBuffer(&msg, buffer,MAX_BUFFER_SIZE);
  memset(buffer, 0, MAX_BUFFER_SIZE);

  int i;

  // we serialize the messages
  if(Packet_write(&msg,(const struct PacketHeader*)&outState)!=Ok)
    printf("write error\n");
  if(Packet_write(&msg,(const struct PacketHeader*)&outSpeed)!=Ok)
    printf("write error\n");
  if(Packet_write(&msg,(const struct PacketHeader*)&outPID)!=Ok)
    printf("write error\n");
  
  printf("Serialized message stream: \n\n%s\n\nlength %d\n\n ",msg.start, (int)(msg.current - msg.start));

  
  // now we rewind the buffer and we read what we wrote in new structures
  
  // rewind
  HexMessage_rewind(&msg);
  
  //
  char packetBuffer[MAX_BUFFER_SIZE];
  PacketHeader* unknownPacket=(PacketHeader*)packetBuffer;

  int k=0;
  while(msg.current!=msg.end){
    printf("deserializing message %d\n\n",k++);
    if (Packet_read(&msg,unknownPacket)!=Ok){
      printf("error in deserialization, aborting\n");
    }
    Packet_print(unknownPacket);
    printf("\n\n");
  }


  printf("*************** command filling ********************* \n");

  HexMessage_reset(&msg);
 
  // write a lot of messages in the buffer

  for  (i=0; i<5; i++){
    // we serialize the messages
    if(Packet_write(&msg,(const struct PacketHeader*)&outState)!=Ok)
      printf("write error\n");
    if(Packet_write(&msg,(const struct PacketHeader*)&outSpeed)!=Ok)
      printf("write error\n");
    if(Packet_write(&msg,(const struct PacketHeader*)&outPID)!=Ok)
      printf("write error\n");
  }

  HexMessage_rewind(&msg);

  char outputBuffer [MAX_BUFFER_SIZE];
  memset(outputBuffer, 0, MAX_BUFFER_SIZE);
  HexMessage outputMsg;
  HexMessage_setBuffer(&outputMsg, outputBuffer, MAX_BUFFER_SIZE);
  
  // execute them one after the other, if possible
  k = 0;
  while(msg.current!=msg.end){
    printf("executing message %d\n\n",k++);
    if (Packet_read(&msg,unknownPacket)!=Ok){
      printf("error in deserialization, aborting\n");
    } 

    // clear the output buffer
    outputMsg.start=outputBuffer;
    outputMsg.current=outputBuffer;
    
    // execute the command
    Packet_execute(unknownPacket, &outputMsg);
    *outputMsg.current=0;
    printf("response: [%s]",outputMsg.start);
    printf("\n\n");
  }
  
  
  return 0;
}
