#include "serialFriend.h"
#include <cstring>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

SerialFriend::SerialFriend(std::string portName, int baudRate, char h, char f){

  this->_portName=portName;
  this->_baudRate=baudRate;
  tcgetattr(STDOUT_FILENO,&this->_old_stdio);
  memset(&this->_stdio,0,sizeof(this->_stdio));
  this->_stdio.c_iflag=0;
  this->_stdio.c_oflag=0;
  this->_stdio.c_cflag=0;
  this->_stdio.c_lflag=0;
  this->_stdio.c_cc[VMIN]=1;
  this->_stdio.c_cc[VTIME]=0;
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  memset(&this->_tio,0,sizeof(this->_tio));
  this->_tio.c_iflag=0;
  this->_tio.c_oflag=0;
  this->_tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
  this->_tio.c_lflag=0;
  this->_tio.c_cc[VMIN]=1;
  this->_tio.c_cc[VTIME]=5;
  this->_tty_fd=open(portName.c_str(), O_RDWR | O_NONBLOCK);
  cfsetospeed(&this->_tio,B115200);            // 115200 baud
  cfsetispeed(&this->_tio,B115200);            // 115200 baud
  tcsetattr(this->_tty_fd,TCSANOW,&this->_tio);
  tcsetattr(this->_tty_fd, TCSAFLUSH, &this->_tio);
  this->_header=h;
  this->_footer=f;
}

SerialFriend::~SerialFriend(){
  if (_tty_fd>0)
    ::close(_tty_fd);
}

int SerialFriend::read(char* buf){
  char* b=buf;

    return  ::read(this->_tty_fd,b,1);

}

void SerialFriend::write(char* buf, int debug){
  ::write(this->_tty_fd,&this->_header,1);
    if(debug) printf("Sending via UART: [%c",this->_header);
    for(int i=0;i<strlen(buf);i++){
	char tmp;
	tmp=buf[i];
	::write(this->_tty_fd,&tmp,1);
    if(debug)printf("%c",tmp);
	}
    ::write(this->_tty_fd,&this->_footer,1);
    if(debug) printf("%c]\n",this->_footer);
}

char SerialFriend::getHeader()
{
    return this->_header;
}

char SerialFriend::getFooter()
{
    return this->_footer;
}
