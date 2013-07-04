#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"
#include <string.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

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


int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf ("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // ignore break signal
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag |= CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf ("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf ("error %d setting term attributes", errno);
}

int main(int argc, char** argv){
  Packets_init();
  char data_in[1000];
  struct termios options;
  int i=0;
  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY );
  set_interface_attribs (fd,115200, 0);
  set_blocking (fd, 1);
  char c;
  write(fd,"$030050%\n                 $030050%\n",sizeof(char)*8);
  while( c!='\n')
  {
	if(!read(fd, &c, sizeof(char))) continue;
  	data_in[i]=c;
	i++;
	printf("%c",c);
	//usleep(500);
  }
  data_in[i]='\0';
  
  PacketHandler_setStringExecuteFn(onStringReceived);
  HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
  HexMessage inputStream;
  char line[MAX_BUFFER_SIZE];
  char* endLine;
  //while((endLine = fgets(line, 1024, stdin))){
    //reset the output buffer
    // simulate we ge the string from the serial something 
    HexMessage_setBuffer(&inputStream, data_in, strlen(data_in)-1); // skip the newline
    printf("incoming packet: [%s]\n",inputStream.start);
    PacketHandlerLoop(&inputStream, &outputStream);
    *outputStream.current=0;
    // write on stdout the answers
    printf("answer packet:   [%s]\n",outputStream.start);
  //}
  
  return 0;
}
