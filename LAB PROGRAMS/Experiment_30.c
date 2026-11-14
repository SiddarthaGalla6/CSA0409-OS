Code:
#include <stdio.h>
#include <pthread.h>
#include <string.h>
void *run(void *arg)
{
    printf("Thread is running\n");
    return arg;
}
int main()
{
    pthread_t thread, self;
    void *result;
    pthread_create(&thread, NULL, run, NULL);
    pthread_join(thread, &result);
    self = pthread_self();
    printf("Thread joined successfully\n");
    printf("Thread equal to itself: %s\n", pthread_equal(self, self) ? "Yes" : "No");
    pthread_exit(NULL);
}

Output:
Thread is running\nThread joined successfully\nThread equal to itself: Yes
