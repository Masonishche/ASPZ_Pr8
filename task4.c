#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    printf("PID: %d\n", pid);
    
    // Add sleep to make output order clearer in demonstration
    sleep(1);
    return 0;
}
