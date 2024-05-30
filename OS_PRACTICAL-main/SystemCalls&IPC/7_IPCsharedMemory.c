#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *shm_ptr;

    // Generate a unique key for shared memory
    key = ftok("/tmp", 'B');
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Attach shared memory segment
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (void *) -1) {
        perror("shmat failed");
        return 1;
    }

    // Write to shared memory
    strcpy(shm_ptr, "Hello, shared memory!");

    printf("Message written to shared memory: %s\n", shm_ptr);

    // Detach shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
        return 1;
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl(IPC_RMID) failed");
        return 1;
    }

    return 0;
}

