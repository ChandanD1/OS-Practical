#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {

        printf("Child process: PID = %d\n", getpid());
    } else {

        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}

