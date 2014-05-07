/*
  Copyright 2013-2014 bcstack.org

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#if USE_BTUART

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "bluetooth.h"

static int fd;

void bt_uart_open(void)
{
    int status = 0;
	struct termios ti;
	uint8_t delay, activity = 0x00;
	int timeout = 0;
    char* device = "/dev/ttyUSB0";
    speed_t baudrate = B921600;

	if (!device)
		device = "/dev/ttyS0";

	fd = open(device, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		printf("Can't open serial port: %s (%d)\n",
						strerror(errno), errno);
		status = -1;
        goto out;
	}

	tcflush(fd, TCIOFLUSH);

	if (tcgetattr(fd, &ti) < 0) {
		fprintf(stderr, "Can't get port settings: %s (%d)\n",
						strerror(errno), errno);
		close(fd);
		status = -1;
        goto out;
	}

	cfmakeraw(&ti);

	ti.c_cflag |=  CLOCAL;
	ti.c_cflag &= ~CRTSCTS;
	ti.c_cflag |=  PARENB;
	ti.c_cflag &= ~PARODD;
	ti.c_cflag &= ~CSIZE;
	ti.c_cflag |=  CS8;
	ti.c_cflag &= ~CSTOPB;

	ti.c_cc[VMIN] = 1;
	ti.c_cc[VTIME] = 0;

	cfsetospeed(&ti, baudrate);

	if (tcsetattr(fd, TCSANOW, &ti) < 0) {
		fprintf(stderr, "Can't change port settings: %s (%d)\n",
						strerror(errno), errno);
		close(fd);
		status = -1;
        goto out;
	}

	tcflush(fd, TCIOFLUSH);

	if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0) {
		fprintf(stderr, "Can't set non blocking mode: %s (%d)\n",
						strerror(errno), errno);
		close(fd);
		status = -1;
        goto out;
	}

out:
    if (status != 0) {
        printf("failed to open bt uart\n");
        exit(-1);
    }
}

void bt_uart_close(void)
{
    close(fd);
}

void bt_uart_write (u8 c)
{
	if (write(fd, &c, 1) < 0)
		fprintf(stderr, "UART write error\n");
}

u8 bt_uart_read(u8* c)
{
	int res = read(fd, c, 1);

    //printf("<%02x", *c);

	return res > 0 ? res : 0;
}

#endif
