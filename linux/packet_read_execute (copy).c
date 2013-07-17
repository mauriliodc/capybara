#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"
#include <string.h>

#define MAX_BUFFER_SIZE 1024

char outputBuffer[MAX_BUFFER_SIZE]; // where we write our responses
HexMessage outputStream; // wrappers to the char arrays with counters
char packetBuffer [MAX_BUFFER_SIZE]; // where we write our deserialized packet
PacketHeader * parsedPacket = (PacketHeader *) packetBuffer;


void PacketHandlerLoop(HexMessage* inputStream, HexMessage* outputStream){
  int error=0;
  HexMessage_reset(outputStream);
  while(! error && 
	inputStream->current!=inputStream->end){
    enum HexMessageStatus status=Packet_read(inputStream,parsedPacket);
    if (status==Ok ) {
      if (parsedPacket->type>=0){
      	Packet_print(parsedPacket);
	Packet_execute(parsedPacket, outputStream);
      }
      

    } else  {
      printf("Parsing error\n");
      error = 1;
    }
  }
  // now send the output stream to the serial line
}

void onStringReceived(const unsigned char * s) {
  printf("I am a nice handler, and i received a string \"%s\"\n",s);
}

int main(int argc, char** argv){
  Packets_init();
  // what we do when we receive soemthign in quotes

  PacketHandler_setStringExecuteFn(onStringReceived);
  HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
  HexMessage inputStream;
  char line[MAX_BUFFER_SIZE];
  char* endLine;
  while((endLine = fgets(line, 1024, stdin))){
    //reset the output buffer
    // simulate we ge the string from the serial something 
    HexMessage_setBuffer(&inputStream, line, strlen(line)-1); // skip the newline
    printf("incoming packet: [%s]\n",inputStream.start);
    PacketHandlerLoop(&inputStream, &outputStream);
    //*outputStream.current=0;
    // write on stdout the answers
    printf("answer packet:   [%s]\n",outputStream.start);
  }
  return 0;
}
