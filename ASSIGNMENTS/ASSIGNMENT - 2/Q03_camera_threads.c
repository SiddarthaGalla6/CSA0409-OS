/* CODE: */
#include <pthread.h>
#include <stdio.h>
#define CAMERAS 64
#define WORK 10000
long total=0;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
typedef struct {int id;} Job;
void *camera(void *arg){
 Job *j=(Job*)arg; long local=0;
 for(int i=0;i<WORK;i++) local+=(j->id+i)%7;
 pthread_mutex_lock(&lock); total+=local; pthread_mutex_unlock(&lock);
 return NULL;
}
int main(void){
 pthread_t th[CAMERAS]; Job jobs[CAMERAS];
 for(int i=0;i<CAMERAS;i++){jobs[i].id=i;pthread_create(&th[i],NULL,camera,&jobs[i]);}
 for(int i=0;i<CAMERAS;i++)pthread_join(th[i],NULL);
 printf("Processed %d cameras; checksum=%ld\n",CAMERAS,total);
 pthread_mutex_destroy(&lock); return 0;
}

/*
Input:
No keyboard input. The program simulates work for 64 cameras; WORK is set to 10,000 iterations per camera.
Output (reference/sample):
Processed 64 cameras; checksum=1919994
*/
