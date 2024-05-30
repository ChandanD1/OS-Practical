#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

// Function to perform semaphore operations
void sem_op(int semid, int sem_num, int op) {
    struct sembuf sem_buf;

    sem_buf.sem_num = sem_num;
    sem_buf.sem_op = op;
    sem_buf.sem_flg = SEM_UNDO;

    if (semop(semid, &sem_buf, 1) == -1) {
        perror("semop failed");
        exit(1);
    }
}

int main() {
    key_t key;
    int semid;

    // Generate a unique key for the semaphore
    key = ftok("/tmp", 'C');
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Create a semaphore set with 1 semaphore
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget failed");
        return 1;
    }

    // Initialize the semaphore
    union semun sem_union;
    sem_union.val = 1;  // Initial value of the semaphore
    if (semctl(semid, 0, SETVAL, sem_union) == -1) {
        perror("semctl SETVAL failed");
        return 1;
    }

    // Perform semaphore operations (wait and signal)
    sem_op(semid, 0, -1); // Wait operation (P)
    printf("Critical section: Semaphore locked\n");
    sleep(2); // Simulate critical section work
    sem_op(semid, 0, 1); // Signal operation (V)
    printf("Critical section: Semaphore unlocked\n");

    // Remove the semaphore set
    if (semctl(semid, 0, IPC_RMID, sem_union) == -1) {
        perror("semctl IPC_RMID failed");
        return 1;
    }

    return 0;
}

