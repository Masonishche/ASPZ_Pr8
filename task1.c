#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    int pipefd[2];
    char buffer[100000]; // Large buffer to exceed typical pipe capacity
    ssize_t count;
    size_t nbytes = sizeof(buffer);

    // Initialize buffer with 'A'
    memset(buffer, 'A', nbytes);

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Set write end to non-blocking
    if (fcntl(pipefd[1], F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    // Attempt to write a large amount of data
    printf("Attempting to write %zu bytes to pipe...\n", nbytes);
    count = write(pipefd[1], buffer, nbytes);
    if (count == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("write() returned %zd bytes (requested %zu bytes)\n", count, nbytes);
    if (count < (ssize_t)nbytes) {
        printf("Partial write occurred, likely due to pipe buffer limit.\n");
    }

    // Clean up
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
