#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

#define DEVICE_PATH "/dev/int_stack"

// Print usage
void print_usage() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  kernel_stack set-size <size>\n");
    fprintf(stderr, "  kernel_stack push <value>\n");
    fprintf(stderr, "  kernel_stack pop\n");
    fprintf(stderr, "  kernel_stack unwind\n");
}

int main(int argc, char *argv[]) {
    if (access(DEVICE_PATH, F_OK) == -1) {
        fprintf(stderr, "ERROR: USB key not inserted\n");
        return EXIT_FAILURE;
    }
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "set-size") == 0) {
        if (argc != 3) {
            fprintf(stderr, "ERROR: missing size argument\n");
            return EXIT_FAILURE;
        }

        // Set stack size function
        int size = atoi(argv[2]);
        if (size <= 0) {
            fprintf(stderr, "ERROR: size should be > 0\n");
            return EXIT_FAILURE;
        }
        int fd = open(DEVICE_PATH, O_RDWR);
        if (fd < 0) {
            perror("ERROR: failed to open device");
            return EXIT_FAILURE;
        }
        if (ioctl(fd, 0, size) < 0) {
            if (errno == ENOSPC) {
                fprintf(stderr, "ERROR: new size too small for current elements\n");
            } else {
                perror("ERROR: ioctl failed");
            }
            close(fd);
            return EXIT_FAILURE;
        }
        close(fd);
        return EXIT_SUCCESS;
    }
    else if (strcmp(argv[1], "push") == 0) {
        if (argc != 3) {
            fprintf(stderr, "ERROR: missing value argument\n");
            return EXIT_FAILURE;
        }

        // Push function
        int value = atoi(argv[2]);
        int fd = open(DEVICE_PATH, O_RDWR);
        if (fd < 0) {
            perror("ERROR: failed to open device");
            return EXIT_FAILURE;
        }
        ssize_t ret = write(fd, &value, sizeof(int));
        close(fd);
        if (ret < 0) {
            if (errno == ERANGE) {
                fprintf(stderr, "ERROR: stack is full\n");
                return ERANGE;
            }
            perror("ERROR: write failed");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    else if (strcmp(argv[1], "pop") == 0) {
        if (argc != 2) {
            fprintf(stderr, "ERROR: pop takes no arguments\n");
            return EXIT_FAILURE;
        }

        // Pop function
        int fd = open(DEVICE_PATH, O_RDWR);
        if (fd < 0) {
            perror("ERROR: failed to open device");
            return EXIT_FAILURE;
        }
        int value;
        ssize_t ret = read(fd, &value, sizeof(int));
        close(fd);
        if (ret == 0) {
            printf("NULL\n");
            return EXIT_SUCCESS;
        }
        else if (ret < 0) {
            perror("ERROR: read failed");
            return EXIT_FAILURE;
        }
        else {
            printf("%d\n", value);
            return EXIT_SUCCESS;
        }
    }
    else if (strcmp(argv[1], "unwind") == 0) {
        if (argc != 2) {
            fprintf(stderr, "ERROR: unwind takes no arguments\n");
            return EXIT_FAILURE;
        }

        // Unwind function
        int fd = open(DEVICE_PATH, O_RDWR);
        if (fd < 0) {
            perror("ERROR: failed to open device");
            return EXIT_FAILURE;
        }
        int value;
        while (1) {
            ssize_t ret = read(fd, &value, sizeof(int));
            if (ret == 0) {
                break;
            }
            else if (ret < 0) {
                perror("ERROR: read failed");
                break;
            }
            else {
                printf("%d\n", value);
            }
        }
        close(fd);
        return EXIT_SUCCESS;
    }
    else {
        print_usage();
        return EXIT_FAILURE;
    }
}
