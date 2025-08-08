#include <stdio.h>     /* printf, fprintf */
#include <stdlib.h>    /* malloc, atoi, rand... */
#include <string.h>    /* memcpy, strlen... */
#include <stdint.h>    /* uint types */
#include <sys/types.h> /* size_t, ssize_t, off_t... */
#include <unistd.h>    /* close(), read(), write() */
#include <fcntl.h>     /* open() */
#include <sys/ioctl.h> /* ioctl() */
#include <errno.h>     /* error codes */

// ioctl commands defined for the pci driver header
#include "ioctl_cmds.h"

#define DEVICE_NODE_PATH "/dev/mydev"

int main() {
    printf("hello world\n");

    int fd, retval;

    fd = open(DEVICE_NODE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Erro ao abrir o dispositivo");
        return -1;
    }

    unsigned int data = 0x0; // 32 bits ON
    unsigned int swRead = 0, buttonRead = 0;

    ioctl(fd, WR_L_DISPLAY);
    retval = write(fd, &data, sizeof(data));
    printf("DISPLAY Wrote %d bytes\n", retval);

    ioctl(fd, RD_SWITCHES);
    retval = read(fd, &swRead, 1); // 1 Byte -> 8 bits
    printf("Read SWITCHES %d bytes\n", retval);
    printf("New data (How many switches are set) -> %u\n", swRead);

    ioctl(fd, RD_PBUTTONS);
    retval = read(fd, &buttonRead, 1); // 1 Byte -> 8 bits
    printf("Read BUTTONS %d bytes\n", retval);
    printf("New data (How many buttons are pressed) -> %u\n", buttonRead);

    close(fd);
    return 0;
}