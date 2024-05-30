#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>

#define PORT 5000
#define MAX_MSG_SIZE 1024
#define MAX_CLIENTS 10

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[MAX_MSG_SIZE];
    int n, max_fd;
    fd_set readfds;
    int client_fds[MAX_CLIENTS] = {0};

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
        FD_ZERO(&readfds);         // Clear file descriptor set
        FD_SET(sockfd, &readfds);  // Add UDP socket to set
        max_fd = sockfd;

        // Add client sockets to set
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (client_fds[i] > 0) {
                FD_SET(client_fds[i], &readfds);
                if (client_fds[i] > max_fd)
                    max_fd = client_fds[i];
            }
        }

        // Wait for activity on any of the sockets
        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("Select failed");
            exit(EXIT_FAILURE);
        }

        // Handle UDP socket
        if (FD_ISSET(sockfd, &readfds)) {
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

            // Add client to client_fds array
            for (int i = 0; i < MAX_CLIENTS; ++i) {
                if (client_fds[i] == 0) {
                    client_fds[i] = client_addr.sin_port; // Store client port number
                    break;
                }
            }
        }

        // Handle client sockets
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (client_fds[i] > 0 && FD_ISSET(client_fds[i], &readfds)) {
                // Receive message from client
                if ((n = recv(client_fds[i], buffer, MAX_MSG_SIZE, 0)) < 0) {
                    perror("recv failed");
                    exit(EXIT_FAILURE);
                }

                // Display client message
                buffer[n] = '\0';
                printf("Message from client %d: %s\n", client_fds[i], buffer);

                // Echo back the message to the client
                if (send(client_fds[i], buffer, n, 0) < 0) {
                    perror("send failed");
                    exit(EXIT_FAILURE);
                }

                // Remove client if "exit" received
                if (strcmp(buffer, "exit") == 0) {
                    printf("Client %d has disconnected.\n", client_fds[i]);
                    close(client_fds[i]);
                    client_fds[i] = 0; // Clear client socket from array
                }
            }
        }
    }

    close(sockfd);
    return 0;
}

