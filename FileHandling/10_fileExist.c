#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool fileExists(const char *filename) {
    FILE *file;
    
    file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    
    return false;
}

int main() {
    char filename[] = "file.txt";
    
    if (fileExists(filename)) {
        printf("File %s exists. Proceeding to open...\n", filename);
        
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error: Could not open file %s\n", filename);
            return 1;
        }
        
        fclose(file);
    } else {
        printf("File %s does not exist.\n", filename);
    }
    
    return 0;
}

