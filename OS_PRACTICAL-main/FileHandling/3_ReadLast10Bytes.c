#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 11

int main() {
    FILE *file;
    char buffer[BUFFER_SIZE];
    
    file = fopen("file2.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }
    
    
    fseek(file, -10, SEEK_END);
    fread(buffer, sizeof(char), 10, file);
    buffer[10] = '\0';
    
    printf("Last 10 bytes of the file: %s\n", buffer);
    
    fclose(file);
    
    return 0;
}
