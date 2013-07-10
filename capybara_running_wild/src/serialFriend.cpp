#include "serialFriend.h"
#include <cstring>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

SerialFriend::SerialFriend(std::string portName, int baudRate){

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
}

void SerialFriend::read(char* buf,int s){
  char* b=buf;
  while(1){
    int currentlyRead=b-buf;
    int currentlyToRead=s-currentlyRead-1;
    //printf ("cr: %d, ctr: %d\n",currentlyRead, currentlyToRead);
    char c[3];
    //int retval = ::read(this->_tty_fd,&c,currentlyToRead);
    int retval = ::read(this->_tty_fd,c,1);
    if (retval>0) {
      std::cerr << c[0];
      // for (int i=0; i<retval; i++) {
      // 	if(b[i]=='\n'){
      // 	  b[retval] = '\0';
      // 	  //printf("%s\n\n\n",buf);
      // 	  b = buf;
      // 	  break;
      // 	} 
      // }
      // std::cerr << buf;
      // b+=retval;  
    }
  }
}
