#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define SERVER_IP "127.0.0.1"
#define MAX_MSG_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[MAX_MSG_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send message to server
    printf("Enter a string to reverse (exit to end): ");
    while (1) {
        fgets(buffer, MAX_MSG_SIZE, stdin);
        write(sockfd, buffer, strlen(buffer));

        // Receive reversed string from server
        int n = read(sockfd, buffer, MAX_MSG_SIZE);
        buffer[n] = '\0';
        printf("Reversed string from server: %s\n", buffer);

        // Exit if user types "exit"
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exiting...\n");
            break;
        }

        printf("Enter another string to reverse (exit to end): ");
    }

    close(sockfd);
    return 0;
}

