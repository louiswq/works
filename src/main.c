#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h> 
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <poll.h>

#include "serial.h"


struct MS1313B_MSG
{
	uint8_t header[3]; // 0xBD DB 0A
	float gyro[3];
	float accel[3];
	uint8_t crc;
};




int main(int argc, char *argv[])
{
	uint8_t buf[64];
	struct MS1313B_MSG sensor = {0};

	int fd = OpenDev("/dev/ttyUSB0");
	
	if (fd > 0)
		set_speed(fd, 115200);
	else {
		printf("Can't Open Serial Port!\n");
		exit(0);
	}
	
	if (set_Parity(fd, 8, 1, 'N') == false) {
		printf("Set Parity Error\n");
		exit(1);
	}
	
	printf("running...\r\n");

	int fd2 = open("a.txt", O_RDWR|O_CREAT|O_APPEND, S_IRWXU);
	if (fd2 < 0) {
		printf("open failed\r\n");
	}


	struct pollfd serial_fd[1];
	serial_fd[0].fd = fd;
	serial_fd[0].events = POLLRDNORM;

	while (1) {
	
		poll(serial_fd, 1, 2000);

		int nread = read(fd, buf, 64);
		if (nread > 0) {
			for (int i = 0; i < nread; i++)
				printf("%02x ", buf[i]);

			//memcpy();
			printf("\r\n");

			int ret = write(fd2, buf, strlen(buf));
			if (ret < 0) {
				printf("write failed\r\n");
			}
		}
	}
	
	//close(fd);
	//exit(0);
}
