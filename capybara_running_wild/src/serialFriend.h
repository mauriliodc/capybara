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
        SerialFriend(std::string portName, int baudRate, char h='$', char f='%');
 		~SerialFriend();
		int read(char* buf);
        void write(char* buf, int debug=0);
        char getHeader();
        char getFooter();
	private:
		std::string _portName;
		int _baudRate;
		char _data_in[1000];
		int _tty_fd;
        char _header;
        char _footer;
		struct termios _tio;
		struct termios _stdio;
		struct termios _old_stdio;
};

#endif
