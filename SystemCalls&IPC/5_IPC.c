#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
    char write_msg[BUFFER_SIZE] = "Hello, pipe!";
    char read_msg[BUFFER_SIZE];

    int fd[2];
    pid_t pid;

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(fd[READ_END]); // Close the unused read end of the pipe

        // Write to the pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

        // Close the write end of the pipe
        close(fd[WRITE_END]);
    } else {
        // Child process
        close(fd[WRITE_END]); // Close the unused write end of the pipe

        // Read from the pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Child process read: %s\n", read_msg);

        // Close the read end of the pipe
        close(fd[READ_END]);
    }

    return 0;
}

