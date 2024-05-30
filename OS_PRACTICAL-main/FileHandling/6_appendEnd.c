#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    
    file = fopen("file.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }
    
    fprintf(file, "Appended by the Question no:. 6 as output\n");
    
    fclose(file);
    
    printf("Data appended to file successfully.\n");
    
    return 0;
}
