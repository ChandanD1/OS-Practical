#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 1024

// Define a structure for message queue
struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Prepare message
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello, message queue!");

    // Send message
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd failed");
        return 1;
    }

    printf("Message sent: %s\n", message.msg_text);

    // Receive message
    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv failed");
        return 1;
    }

    printf("Message received: %s\n", message.msg_text);

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl(IPC_RMID) failed");
        return 1;
    }

    return 0;
}
