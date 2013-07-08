#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"
#include <string.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


#define MAX_BUFFER_SIZE 1024
 int fd;


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
  char data_in[1000];
  struct termios options;
  int fd;

  //===================================================================================
        struct termios tio;
        struct termios stdio;
        struct termios old_stdio;
        int tty_fd;
        unsigned char c='D';
        tcgetattr(STDOUT_FILENO,&old_stdio);
 
        printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;
        //tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        //tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
 
        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;
 
        tty_fd=open(argv[1], O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B115200);            // 115200 baud
        cfsetispeed(&tio,B115200);            // 115200 baud
 
        tcsetattr(tty_fd,TCSANOW,&tio);
        int i=0;
  //=========================================================================================
  PacketHandler_setStringExecuteFn(onStringReceived);
  HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
  HexMessage inputStream;
  
  while(1){
   i=0;
   c=' ';
   while (c!='\n'){
    if (read(tty_fd,&c,1)>0){
     data_in[i]=c;
     i++;
    }
   }
   char line[MAX_BUFFER_SIZE];
   char* endLine;
   HexMessage_setBuffer(&inputStream, data_in, strlen(data_in)-1); // skip the newline
   printf("incoming packet: [%s]\n",inputStream.start);
   PacketHandlerLoop(&inputStream, &outputStream);
   *outputStream.current=0;
   printf("answer packet:   [%s]\n",outputStream.start);
  }
  return 0;
}
