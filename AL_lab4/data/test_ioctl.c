#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/int_stack", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    if (ioctl(fd, 0, 10) < 0) {
        perror("ioctl");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}
