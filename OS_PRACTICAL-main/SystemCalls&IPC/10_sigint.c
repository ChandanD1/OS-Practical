#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("\nReceived SIGINT (Ctrl+C)\n");
    // Optionally, restore the default signal handler
    signal(SIGINT, SIG_DFL);
}

int main() {
    // Register signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    printf("Waiting for SIGINT (Ctrl+C)...\n");
    while(1) {
        sleep(1); // Do nothing in the main loop
    }

    return 0;
}

