#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main() {
    int fd = open("/dev/int_stack", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        if (write(fd, &values[i], sizeof(int)) != sizeof(int)) {
            perror("write");
            close(fd);
            return 1;
        }
        printf("Pushed: %d\n", values[i]);
    }
    printf("Popping values:\n");
    int val;
    while (read(fd, &val, sizeof(int)) == sizeof(int)) {
        printf("Popped: %d\n", val);
    }
    close(fd);
    return 0;
}
