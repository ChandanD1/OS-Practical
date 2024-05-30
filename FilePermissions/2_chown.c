#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char filename[] = "file.txt";
    uid_t new_owner = 1000;  // Replace with the UID of the new owner
    
    // Use chown to change the owner of the file
    int result = chown(filename, new_owner, -1);  // -1 means do not change the group
    if (result == 0) {
        printf("Owner of file %s changed successfully.\n", filename);
    } else {
        perror("chown error");
        return 1;
    }
    
    return 0;
}

