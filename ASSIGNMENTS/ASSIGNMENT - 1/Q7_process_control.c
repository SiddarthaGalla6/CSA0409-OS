/* CODE: */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main(void)
{
    int status;
    printf("shell: running job 1\n");
    fflush(stdout);
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        execlp("expr", "expr", "6", "*", "7", (char *)NULL);
        perror("execlp");
        _exit(127);
    }
    if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("job 1 exit status %d\n", WEXITSTATUS(status));
    else
        printf("job 1 did not exit normally\n");
 
    printf("shell: running job 2\n");
    fflush(stdout);
    pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) _exit(3);
    if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("job 2 exit status %d\n", WEXITSTATUS(status));
    return 0;
}

/*
Input:
No keyboard input. The program runs expr 6 * 7 as a child process, then runs a second child that exits with status 3.
Output (reference/sample):
shell: running job 1
42
job 1 exit status 0
shell: running job 2
job 2 exit status 3
*/
