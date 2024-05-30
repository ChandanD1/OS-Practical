#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 5000
#define MAX_MSG_SIZE 1024

void send_file_contents(int sockfd, char *filename) {
    char buffer[MAX_MSG_SIZE];
    int file_fd, n;

    // Open file
    if ((file_fd = open(filename, O_RDONLY)) < 0) {
        perror("File open failed");
        return;
    }

    // Read file and send contents to client
    while ((n = read(file_fd, buffer, MAX_MSG_SIZE)) > 0) {
        write(sockfd, buffer, n);
    }

    // Close file
    close(file_fd);
}

int main() {
    int sockfd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[MAX_MSG_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to the address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("TCP Server is running on port %d...\n", PORT);

    // Accept incoming connections and handle them
    while (1) {
        if ((client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("New client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Receive file name from client
        int n = read(client_fd, buffer, MAX_MSG_SIZE);
        if (n <= 0) {
            perror("Read error");
            close(client_fd);
            continue;
        }
        buffer[n] = '\0';

        // Send file contents to client
        send_file_contents(client_fd, buffer);

        // Close client socket
        close(client_fd);
    }

    close(sockfd);
    return 0;
}

