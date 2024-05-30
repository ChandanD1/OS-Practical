#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *source_file, *target_file;
    char source_filename[] = "file.txt";
    char target_filename[] = "target.txt";
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    source_file = fopen(source_filename, "r");
    if (source_file == NULL) {
        printf("Error: Could not open source file %s\n", source_filename);
        return 1;
    }


    target_file = fopen(target_filename, "w+");
    if (target_file == NULL) {
        printf("Error: Could not create or open target file %s\n", target_filename);
        fclose(source_file);
        return 1;
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, target_file);
    }

    fclose(source_file);
    fclose(target_file);

    printf("File copied successfully.\n");

    return 0;
}

