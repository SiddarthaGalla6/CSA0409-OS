/* Worst-case delay of a time-critical loop with and without locked memory.
   ./rt_loop unlocked   : buffer is allocated but pages are faulted in lazily (demand paging)
   ./rt_loop locked     : mlockall(MCL_CURRENT|MCL_FUTURE) and the buffer is pre-faulted before the loop */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/resource.h>
#define PAGES 8192            /* 32 MB buffer of 4 KB pages */
#define ITER  50000
static double now_us(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec * 1e6 + t.tv_nsec / 1e3; }
static int cmp(const void *a, const void *b) { double x = *(const double *)a, y = *(const double *)b; return (x > y) - (x < y); }
int main(int argc, char *argv[])
{
    int lock = argc > 1 && !strcmp(argv[1], "locked");
    volatile char *buf = mmap(NULL, (size_t)PAGES * 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    static double lat[ITER];
    if (lock) {
        if (mlockall(MCL_CURRENT | MCL_FUTURE)) { perror("mlockall"); return 1; }
        for (size_t i = 0; i < (size_t)PAGES * 4096; i += 4096) buf[i] = 0;      /* pre-fault while locked */
    }
    struct rusage a, b; getrusage(RUSAGE_SELF, &a);
    unsigned x = 1;
    for (int i = 0; i < ITER; i++) {
        double t0 = now_us();
        buf[(size_t)(i % PAGES) * 4096] = (char)i;                /* the control task touches its next data page */
        for (int k = 0; k < 200; k++) x = x * 1664525u + 1013904223u;   /* a little computation */
        lat[i] = now_us() - t0;
    }
    getrusage(RUSAGE_SELF, &b);
    double max = 0, sum = 0; int over = 0;
    for (int i = 0; i < ITER; i++) { sum += lat[i]; if (lat[i] > max) max = lat[i]; if (lat[i] > 20.0) over++; }
    qsort(lat, ITER, sizeof lat[0], cmp);
    printf("%-8s iterations=%d  mean=%.2f us  p99=%.2f us  p99.9=%.2f us  MAX=%.2f us  >20us: %d  page faults in loop: %ld%s\n",
           lock ? "locked" : "unlocked", ITER, sum / ITER, lat[(int)(ITER * 0.99)], lat[(int)(ITER * 0.999)], max, over,
           b.ru_minflt - a.ru_minflt, x == 0 ? "!" : "");
    return 0;
}
