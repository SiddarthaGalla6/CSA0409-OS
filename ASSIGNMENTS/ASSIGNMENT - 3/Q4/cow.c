/* Copy-on-write with fork(): measure private memory of the child before and after writing. */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

static long kb(const char *key)                 /* read one field from /proc/self/smaps_rollup */
{
    FILE *f = fopen("/proc/self/smaps_rollup", "r"); char line[256]; long v = -1;
    while (f && fgets(line, sizeof line, f))
        if (!strncmp(line, key, strlen(key))) { sscanf(line + strlen(key), " %ld", &v); break; }
    if (f) fclose(f);
    return v;
}
static double now(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec * 1e3 + t.tv_nsec / 1e6; }

int main(int argc, char *argv[])
{
    size_t mb = argc > 1 ? (size_t)atol(argv[1]) : 64, n = mb << 20;
    char *buf = malloc(n);
    memset(buf, 1, n);                           /* parent touches (owns) all pages */
    printf("Parent: buffer %zu MB, Private_Dirty = %ld kB, Rss = %ld kB\n", mb, kb("Private_Dirty:"), kb("Rss:"));
    fflush(stdout);
    double t0 = now();
    pid_t p = fork();
    if (p == 0) {
        double t1 = now();
        printf("Child : fork() returned after %.3f ms\n", t1 - t0);
        printf("Child : BEFORE writing: Rss = %ld kB, Private_Dirty = %ld kB, Pss = %ld kB\n", kb("Rss:"), kb("Private_Dirty:"), kb("Pss:"));
        double w0 = now();
        for (size_t i = 0; i < n; i += 4096) buf[i] = 2;             /* write one byte in every page */
        double w1 = now();
        printf("Child : AFTER  writing: Rss = %ld kB, Private_Dirty = %ld kB, Pss = %ld kB (copy took %.1f ms)\n",
               kb("Rss:"), kb("Private_Dirty:"), kb("Pss:"), w1 - w0);
        fflush(stdout);
        _exit(0);
    }
    waitpid(p, NULL, 0);
    double w0 = now(); memcpy(buf, buf + 0, 0);
    char *copy = malloc(n); memcpy(copy, buf, n);                    /* what a full copy at fork time would cost */
    printf("For comparison: copying %zu MB eagerly (as a fork without COW would) takes %.1f ms\n", mb, now() - w0);
    return copy[0] == 0;
}
