#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    
    file = fopen("5writeHW.txt", "w+");
    if (file == NULL) {
        printf("Error: Could not create file\n");
        return 1;
    }
    
    fprintf(file, "Hello, World!\n");
    
    fclose(file);
    
    printf("Data written to file successfully.\n");
    
    return 0;
}

