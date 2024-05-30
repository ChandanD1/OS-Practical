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
    socklen_t addr_len = sizeof(server_addr);
    int n;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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

    while (1) {
        // Input message from user
        printf("Enter message to send (enter 'exit' to quit): ");
        fgets(buffer, MAX_MSG_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        // Send message to server
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

        // Exit loop if user enters "exit"
        if (strcmp(buffer, "exit") == 0)
            break;

        // Receive echoed message from server
        if ((n = recvfrom(sockfd, buffer, MAX_MSG_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len)) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        // Print echoed message from server
        buffer[n] = '\0';
        printf("Echoed message from server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

