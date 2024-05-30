#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
   	 if (fd == -1) {
        	perror("Failed to open output.txt");
       		 return 1;
   	 }

	int new_fd = dup(fd);

	dprintf(fd, "Hello, World! This is the original file descriptor.\n");

	dprintf(new_fd, "Hello, World! This is the duplicated file descriptor.\n");


	close(fd);
	close(new_fd);

	return 0;
}
