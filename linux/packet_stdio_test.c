#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"

#define MAX_BUFFER_SIZE 1024

char outputBuffer[MAX_BUFFER_SIZE]; // where we write our responses
char inputBuffer[MAX_BUFFER_SIZE];  // where we read our input

HexMessage outputStream; // wrappers to the char arrays with counters
HexMessage inputStream;

char packetBuffer [MAX_BUFFER_SIZE]; // where we write our deserialized packet
PacketHeader * parsedPacket = (PacketHeader *) packetBuffer;

void PacketInit(){
  //initialize the packet handler
  Packets_init();
  //hook the buffers on the streams
  HexMessage_setBuffer(&inputStream, inputBuffer, MAX_BUFFER_SIZE);
  HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
}

void PacketHandlerLoop(){
  int error=0;
  HexMessage_reset(&outputStream);
  while(! error && inputStream.current!=inputStream.end){
    if (Packet_read(&inputStream,parsedPacket)!=Ok){
      printf("error in deserialization, aborting\n");
      error = 1;
    } 
    Packet_execute(parsedPacket, &outputStream);
  }

  // now send the output stream to the serial line
}
