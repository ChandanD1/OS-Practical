#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    char filename[] = "modes.txt";

    // O_RDONLY - Open the file in read-only mode
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file in read-only mode");
    } else {
        printf("Opened file in read-only mode with file descriptor: %d\n", fd);
        close(fd);
    }

 

   // O_WRONLY - Open the file in write-only mode
    fd = open(filename, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open file in write-only mode");
    } else {
        printf("Opened file in write-only mode with file descriptor: %d\n", fd);
        close(fd);
    }




    // O_RDWR - Open the file in read and write mode
    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Failed to open file in read/write mode");
    } else {
        printf("Opened file in read/write mode with file descriptor: %d\n", fd);
        close(fd);
    }




    // O_CREAT - Create the file if it doesn't exist
    fd = open(filename, O_CREAT | O_WRONLY, 0666);  // 0666 gives read/write permissions to owner, group, and others
    if (fd == -1) {
        perror("Failed to create file if it doesn't exist");
    } else {
        printf("Created file if it doesn't exist with file descriptor: %d\n", fd);
        close(fd);
    }





    // O_EXCL - Prevent creation if it already exists
    fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
    if (fd == -1) {
        perror("Failed to create file if it doesn't exist without O_EXCL");
    } else {
        printf("Created file if it doesn't exist without O_EXCL with file descriptor: %d\n", fd);
        close(fd);
    }





    // O_APPEND - Open the file and place the cursor at the end of the contents
    fd = open(filename, O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Failed to open file in append mode");
    } else {
        printf("Opened file in append mode with file descriptor: %d\n", fd);
        close(fd);
    }




    // O_ASYNC - Enable input and output control by signal
    // Note: O_ASYNC is not supported on all systems, and its behavior may vary.
    // It's typically used with `fcntl()` after opening the file.
    fd = open(filename, O_WRONLY | O_ASYNC);
    if (fd == -1) {
        perror("Failed to open file with O_ASYNC");
    } else {
        printf("Opened file with O_ASYNC with file descriptor: %d\n", fd);
        close(fd);
    }

    return 0;
}
