/* CODE: */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    for (int i = 0; i < 1000; i++) {
        pid_t p = fork();
        if (p < 0) { perror("fork"); return 1; }
        if (p == 0) _exit(0);
        if (waitpid(p, NULL, 0) < 0) { perror("waitpid"); return 1; }
    }
    puts("Created and reaped 1000 child processes");
    return 0;
}

/*
Input:
No keyboard input. The program creates and waits for 1,000 child processes.
Output (reference/sample):
Created and reaped 1000 child processes
*/
