#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "file.txt";
    char ch;
    int line_count = 0;
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }
    
    fclose(file);
    
    printf("Number of lines in file %s: %d\n", filename, line_count);
    
    return 0;
}

