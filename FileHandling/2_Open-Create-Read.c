#include<stdio.h>
#include<stdlib.h>

int main() {
    FILE *file;

    file = fopen("file2.txt", "w");
    if (file == NULL) {
        printf("Error: Could not create file\n");
        return 1;
    }

    fprintf(file, "Hello, World!\n");

    fclose(file);
	
    file = fopen("file2.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file for reading\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}

