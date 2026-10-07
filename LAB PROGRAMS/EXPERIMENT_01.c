#include <stdio.h>
#include <unistd.h>
int main(){
    int pid;
    printf("Current Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
    pid = fork();
    if (pid == 0){
        printf("Child Process ID: %d\n", getpid());
    }
    else{
        printf("Parent Process ID: %d\n", getpid());
    }
}


Output : 
Current Process ID: 2451
Parent Process ID: 1980
Parent Process ID: 2451
Child Process ID: 2452
