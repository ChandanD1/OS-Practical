#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *file;
	char buffer[11];
	size_t bytesRead;

	file = fopen("file.txt","rb");
	if (file == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}

	bytesRead = fread(buffer, sizeof(char), 10, file);
	if (bytesRead != 10) {
		if (feof(file)) {
			printf("End of file reached after reading %zu bytes. \n",bytesRead);} else if (ferror(file)) {
		perror("Error reading file.");}
	}

	buffer[bytesRead] = '\0';

	printf("First 10 bytes: %s\n", buffer);
	
	fclose(file);
	
	return EXIT_SUCCESS;
}



