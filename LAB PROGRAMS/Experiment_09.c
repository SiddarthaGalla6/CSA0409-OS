Code:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
    int shmid;
    char *shared;
    key_t key = ftok(".", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }
    shared = (char *)shmat(shmid, NULL, 0);
    if (shared == (char *)-1)
    {
        perror("shmat");
        return 1;
    }
    strcpy(shared, "Hello, shared memory!");
    printf("Data written to shared memory: %s\n", shared);
    if (shmdt(shared) == -1)
    {
        perror("shmdt");
        return 1;
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        return 1;
    }
    return 0;
}

Output:
Data written to shared memory: Hello, shared memory!
