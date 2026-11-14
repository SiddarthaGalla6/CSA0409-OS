/* Start-up benchmark: fork+exec a program N times, report mean wall time. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 3) return 1;
    int runs = atoi(argv[1]);
    struct timespec a, b;
    clock_gettime(CLOCK_MONOTONIC, &a);
    for (int i = 0; i < runs; i++) {
        pid_t p = fork();
        if (p == 0) {
            int fd = open("/dev/null", O_WRONLY); dup2(fd, 1);
            execv(argv[2], argv + 2); _exit(127);
        }
        waitpid(p, NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC, &b);
    double us = ((b.tv_sec - a.tv_sec) * 1e9 + (b.tv_nsec - a.tv_nsec)) / 1e3 / runs;
    printf("%-14s mean start-up+run time over %d runs: %.1f us\n", argv[2], runs, us);
    return 0;
}
