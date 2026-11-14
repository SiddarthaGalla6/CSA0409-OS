Code:
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
int sharedData = 0, readCount = 0;
sem_t mutex, writeLock;
void *reader(void *arg)
{
    sem_wait(&mutex);
    readCount++;
    if (readCount == 1) sem_wait(&writeLock);
    sem_post(&mutex);
    printf("Reader reads: %d\n", sharedData);
    sem_wait(&mutex);
    readCount--;
    if (readCount == 0) sem_post(&writeLock);
    sem_post(&mutex);
    return NULL;
}
void *writer(void *arg)
{
    sem_wait(&writeLock);
    sharedData++;
    printf("Writer writes: %d\n", sharedData);
    sem_post(&writeLock);
    return NULL;
}
int main()
{
    pthread_t r1, r2, w1;
    sem_init(&mutex, 0, 1);
    sem_init(&writeLock, 0, 1);
    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&r2, NULL, reader, NULL);
    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);
    sem_destroy(&mutex);
    sem_destroy(&writeLock);
    return 0;
}

Output:
Reader reads: 0\nWriter writes: 1\nReader reads: 1\n(Thread output order may vary.)
