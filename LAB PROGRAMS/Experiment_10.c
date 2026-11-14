Code:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message
{
    long type;
    char text[100];
};
int main()
{
    int msgid;
    struct message msg;
    key_t key = ftok(".", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }
    msg.type = 1;
    strcpy(msg.text, "Hello, message queue!");
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1)
    {
        perror("msgsnd");
        return 1;
    }
    printf("Producer: Data sent: %s\n", msg.text);
    if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1)
    {
        perror("msgrcv");
        return 1;
    }
    printf("Consumer: Data received: %s\n", msg.text);
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        return 1;
    }
    return 0;
}

Output:
Producer: Data sent: Hello, message queue!\nConsumer: Data received: Hello, message queue!
