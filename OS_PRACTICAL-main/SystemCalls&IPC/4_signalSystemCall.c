#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signum) {
    printf("Received signal %d\n", signum);
}

int main() {
    // Register signal handler for SIGINT
    signal(SIGINT, signal_handler);

    printf("Waiting for SIGINT (Ctrl+C)...\n");
    while(1) {
        sleep(1); // Do nothing in the main loop
    }

    return 0;
}

