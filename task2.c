#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int fd;
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    // Create and write data to file
    fd = open("data.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, data, sizeof(data)) != sizeof(data)) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Set offset to 3rd byte
    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Read 4 bytes
    ssize_t bytes_read = read(fd, buffer, 4);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Print buffer contents
    printf("Buffer contains %zd bytes: ", bytes_read);
    for (ssize_t i = 0; i < bytes_read; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    // Clean up
    close(fd);
    unlink("data.bin");
    return 0;
}
