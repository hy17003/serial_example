#ifndef SERIAL_HELP_H
#define SERIAL_HELP_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/stat.h>
 
 
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>


void print(unsigned char * data, int len)
{

    for (int i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}



int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
		struct termios newtio,oldtio;
		if  ( tcgetattr( fd,&oldtio)  !=  0) { 
			perror("SetupSerial 1");
			return -1;
		}
		bzero( &newtio, sizeof( newtio ) );
		newtio.c_cflag  |=  CLOCAL | CREAD;
		newtio.c_cflag &= ~CSIZE;
 
		switch( nBits )
		{
			case 7:
				newtio.c_cflag |= CS7;
				break;
			case 8:
				newtio.c_cflag |= CS8;
				break;
		}
 
		switch( nEvent )
		{
		case 'O':
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case 'E': 
			newtio.c_iflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			break;
		case 'N':  
			newtio.c_cflag &= ~PARENB;
			break;
		}
 
		switch( nSpeed )
		{
			case 2400:
				cfsetispeed(&newtio, B2400);
				cfsetospeed(&newtio, B2400);
				break;
			case 4800:
				cfsetispeed(&newtio, B4800);
				cfsetospeed(&newtio, B4800);
				break;
			case 9600:
				cfsetispeed(&newtio, B9600);
				cfsetospeed(&newtio, B9600);
				break;
			case 115200:
				cfsetispeed(&newtio, B115200);
				cfsetospeed(&newtio, B115200);
				break;
			case 460800:
				cfsetispeed(&newtio, B460800);
				cfsetospeed(&newtio, B460800);
				break;
			default:
				cfsetispeed(&newtio, B9600);
				cfsetospeed(&newtio, B9600);
				break;
		}
		if( nStop == 1 )
			newtio.c_cflag &=  ~CSTOPB;
		else if ( nStop == 2 )
			newtio.c_cflag |=  CSTOPB;
			newtio.c_cc[VTIME]  = 0;
			newtio.c_cc[VMIN] = 0;
			tcflush(fd,TCIFLUSH);
		if((tcsetattr(fd,TCSANOW,&newtio))!=0)
		{
			perror("com set error");
			return -1;
		}
		
			printf("串口设置完成!\n\r");
		return 0;
}


#endif
