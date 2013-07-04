#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

void main()
{
    printf("Hello world\n");

    int fd; /* File descriptor for the port */
    int n;
    int bytes;

    char c;

    char buffer[10];
    char *bufptr;

    struct termios options;

    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyUSB0 - ");
    }
    else {
        fcntl(fd, F_SETFL, FNDELAY);
    }

  tcgetattr( fd, &options );

  /* SEt Baud Rate */

  cfsetispeed( &options, B9600 );
  cfsetospeed( &options, B9600 );

  //I don't know what this is exactly

  options.c_cflag |= ( CLOCAL | CREAD );

  // Set the Charactor size

  options.c_cflag &= ~CSIZE; /* Mask the character size bits */
  options.c_cflag |= CS8;    /* Select 8 data bits */

  // Set parity - No Parity (8N1)

  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  // Disable Hardware flowcontrol

  //  options.c_cflag &= ~CNEW_RTSCTS;  -- not supported

  // Enable Raw Input

  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

  // Disable Software Flow control

  options.c_iflag &= ~(IXON | IXOFF | IXANY);

  // Chose raw (not processed) output

  options.c_oflag &= ~OPOST;

  if ( tcsetattr( fd, TCSANOW, &options ) == -1 )
    printf ("Error with tcsetattr = %s\n", strerror ( errno ) );
  else
    printf ( "%s\n", "tcsetattr succeed" );

    fcntl(fd, F_SETFL, 0);

    // Write to the port
    n = write(fd, "1", 1);

    if (n < 0) {
        fputs("write() of 1 bytes failed!\n", stderr);
    }

    // Read from the port

    //fcntl(fd, F_SETFL, FNDELAY);

    bytes = read(fd, &buffer, sizeof(buffer));
    printf("number of bytes read is %d\n", bytes);
    printf("%s\n", buffer);
    //perror ("read error:");

    close(fd);
}
