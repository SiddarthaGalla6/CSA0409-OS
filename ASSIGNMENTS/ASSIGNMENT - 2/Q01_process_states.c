/* CODE: */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    pid_t pid=fork();
    if(pid<0){perror("fork");return 1;}
    if(pid==0){
        printf("Child: PID=%d PPID=%d\n",getpid(),getppid());
        fflush(stdout);
        _exit(0);
    }
    printf("Parent: PID=%d child PID=%d\n",getpid(),pid);
    waitpid(pid,NULL,0);
    printf("Parent: child completed\n");
    return 0;
}

/*
Input:
No keyboard input. The program creates one child process using fork() and waits for it.
Output (reference/sample):
Parent: PID=<parent_pid> child PID=<child_pid>
Child: PID=<child_pid> PPID=<parent_pid>
Parent: child completed
*/
