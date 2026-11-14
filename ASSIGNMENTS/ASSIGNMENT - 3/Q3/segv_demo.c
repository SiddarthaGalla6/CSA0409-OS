#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
static void child(int mode)
{
    if (mode == 0) { int *p = NULL; *p = 1; }                    /* page not mapped */
    else { char *s = "read-only text"; s[0] = 'X'; }              /* write to read-only page */
}
int main(void)
{
    const char *why[] = {"write through a NULL pointer", "write into a string literal (read-only page)"};
    for (int m = 0; m < 2; m++) {
        pid_t p = fork();
        if (p == 0) { child(m); _exit(0); }
        int st; waitpid(p, &st, 0);
        if (WIFSIGNALED(st))
            printf("Test %d (%s): child killed by signal %d (%s), shell exit status would be %d\n",
                   m + 1, why[m], WTERMSIG(st), strsignal(WTERMSIG(st)), 128 + WTERMSIG(st));
        else printf("Test %d: child exited normally\n", m + 1);
    }
    return 0;
}
