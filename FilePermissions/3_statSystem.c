#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct stat fileStat;
    char filename[] = "file.txt";
    
    // Use stat to get file status
    if (stat(filename, &fileStat) < 0) {
        perror("stat error");
        return 1;
    }

    // Display file status information
    printf("Information for %s\n", filename);
    printf("---------------------------\n");
    printf("File Size: \t\t%lld bytes\n", (long long) fileStat.st_size);
    printf("Number of Links: \t%hu\n", (unsigned short) fileStat.st_nlink);
    printf("File inode: \t\t%llu\n", (unsigned long long) fileStat.st_ino);

    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    printf("File Owner UID: \t%d\n", fileStat.st_uid);
    printf("File Group GID: \t%d\n", fileStat.st_gid);

    printf("Last access time: \t%s", ctime(&fileStat.st_atime));
    printf("Last modification time: \t%s", ctime(&fileStat.st_mtime));
    printf("Last status change time: \t%s", ctime(&fileStat.st_ctime));

    return 0;
}

