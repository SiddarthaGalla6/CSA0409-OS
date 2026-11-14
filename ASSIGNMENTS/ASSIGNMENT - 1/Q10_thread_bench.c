/* CODE: */
#include <stdio.h>
#include <pthread.h>
static void *worker(void *arg) { (void)arg; return NULL; }
int main(void) {
    pthread_t t[1000];
    for (int i = 0; i < 1000; i++) {
        int e = pthread_create(&t[i], NULL, worker, NULL);
        if (e) { fprintf(stderr, "pthread_create failed: %d\n", e); return 1; }
    }
    for (int i = 0; i < 1000; i++) {
        int e = pthread_join(t[i], NULL);
        if (e) { fprintf(stderr, "pthread_join failed: %d\n", e); return 1; }
    }
    puts("Created and joined 1000 threads");
    return 0;
}

/*
Input:
No keyboard input. The program creates and joins 1,000 POSIX threads.
Output (reference/sample):
Created and joined 1000 threads
*/
