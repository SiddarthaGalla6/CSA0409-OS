Code:
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5
sem_t chopstick[N];
sem_t room;
void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;
    sem_wait(&room);
    sem_wait(&chopstick[left]);
    sem_wait(&chopstick[right]);
    printf("Philosopher %d is eating\n", id + 1);
    sleep(1);
    sem_post(&chopstick[right]);
    sem_post(&chopstick[left]);
    sem_post(&room);
    return NULL;
}
int main()
{
    pthread_t t[N];
    int id[N], i;
    sem_init(&room, 0, N - 1);
    for (i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
        id[i] = i;
    }
    for (i = 0; i < N; i++)
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    for (i = 0; i < N; i++)
        pthread_join(t[i], NULL);
    for (i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);
    sem_destroy(&room);
    return 0;
}

Output:
Philosopher 1 is eating\nPhilosopher 2 is eating\n...\n(The order may vary.)
