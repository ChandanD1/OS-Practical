#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 5000
#define SERVER_IP "127.0.0.1"
#define MAX_MSG_SIZE 1024

void receive_file_contents(int sockfd, char *filename) {
    char buffer[MAX_MSG_SIZE];
    int file_fd, n;

    // Create or open file for writing
    if ((file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
        perror("File open failed");
        return;
    }

    // Receive file contents from server
    while ((n = read(sockfd, buffer, MAX_MSG_SIZE)) > 0) {
        write(file_fd, buffer, n);
    }

    // Close file
    close(file_fd);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char filename[MAX_MSG_SIZE];
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

    // Input file name from user
    printf("Enter file name to receive: ");
    fgets(filename, MAX_MSG_SIZE, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline character

    // Send file name to server
    write(sockfd, filename, strlen(filename));

    // Receive file contents from server
    receive_file_contents(sockfd, filename);
    printf("File received successfully.\n");

    close(sockfd);
    return 0;
}

   

