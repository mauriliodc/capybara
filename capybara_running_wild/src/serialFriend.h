#ifndef _SERIAL_FRIEND_H_
#define _SERIAL_FRIEND_H_

#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class SerialFriend{
	public:
		SerialFriend(std::string portName, int baudRate);
		~SerialFriend();
		void read(char* buf,int s);
		
	private:
		std::string _portName;
		int _baudRate;
		char _data_in[1000];
		int _tty_fd;
		struct termios _tio;
		struct termios _stdio;
		struct termios _old_stdio;
};

#endif
