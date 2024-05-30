#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char filename[] = "file.txt";
    int result;
    
    // Use chmod to set file permissions to 644 (rw-r--r--)
    result = chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (result == 0) {
        printf("File permissions changed successfully.\n");
    } else {
        perror("chmod error");
        return 1;
    }
    
    return 0;
}

