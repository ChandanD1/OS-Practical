#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define MAX_MSG_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[MAX_MSG_SIZE];
    int n;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is running on port %d...\n", PORT);

    while (1) {
        // Receive message from client
        if ((n = recvfrom(sockfd, buffer, MAX_MSG_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        // Display client connection information
        printf("Message received from client %s:%d - %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // Echo back the message to the client
        if (sendto(sockfd, buffer, n, 0, (struct sockaddr *)&client_addr, addr_len) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }
    }

    close(sockfd);
    return 0;
}

