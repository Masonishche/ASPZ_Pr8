#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 100

int main() {
    // Allocate memory
    int *array = malloc(SIZE * sizeof(int));
    if (!array) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Initialize array
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    printf("Before fork - First few values: %d, %d, %d\n", array[0], array[1], array[2]);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        free(array);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: modify array
        for (int i = 0; i < SIZE; i++) {
            array[i] += 100;
        }
        printf("Child (PID %d) - Modified values: %d, %d, %d\n", getpid(), array[0], array[1], array[2]);
        free(array);
        exit(0);
    } else {
        // Parent process: modify array
        for (int i = 0; i < SIZE; i++) {
            array[i] -= 50;
        }
        printf("Parent (PID %d) - Modified values: %d, %d, %d\n", getpid(), array[0], array[1], array[2]);
        
        // Wait for child to finish
        wait(NULL);
        
        // Verify parent's memory is unchanged by child
        printf("Parent after child exit - Values: %d, %d, %d\n", array[0], array[1], array[2]);
        free(array);
    }

    return 0;
}
