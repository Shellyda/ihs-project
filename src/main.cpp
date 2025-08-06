#include <stdio.h>	   /* printf */
#include <stdlib.h>	   /* malloc, atoi, rand... */
#include <string.h>	   /* memcpy, strlen... */
#include <stdint.h>	   /* uints types */
#include <sys/types.h> /* size_t ,ssize_t, off_t... */
#include <unistd.h>	   /* close() read() write() */
#include <fcntl.h>	   /* open() */
#include <sys/ioctl.h> /* ioctl() */
#include <errno.h>	   /* error codes */

// ioctl commands defined for the pci driver header
#include "ioctl_cmds.h"

const DEVICE_NODE_PATH = "/dev/mydev";

int main()
{
	printf("hello world\n");

	int fd, retval;

	fd = open(DEVICE_NODE_PATH, O_RDWR);

	unsigned int data = 0xFFFFFFFFF; // 0x0 to ON
	unsigned int swRead = 0, buttonRead = 0;

	ioctl(fd, WR_L_DISPLAY);
	retval = write(fd, &data, sizeof(data));
	cout << "DISPLAY Wrote" << retval << "bytes" << endl;

	ioctl(fd, RD_SWITCHES);

	retval = read(fd, &swRead, 1); // 1 Byte -> 8 bits -> 8 switches
	cout << "Read SWITCHES" << retval << "bytes" << endl;
	cout << "New data (How many switches are set) ->" << swRead << endl;

	ioctl(fd, RD_PBUTTONS);

	retval = read(fd, &buttonRead, 1); // 1 Byte -> 8 bits -> its more than necessary for the 4 buttons
	cout << "Read BUTTONS" << retval << "bytes" << endl;
	cout << "New data (How many switches are set) ->" << buttonRead << endl;

	close(fd);
	return 0;
}
