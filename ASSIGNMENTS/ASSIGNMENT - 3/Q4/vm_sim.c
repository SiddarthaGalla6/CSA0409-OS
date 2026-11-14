/* Demand-paging experiment with a LIMITED resident set.
   An anonymous mapping of N pages stands for the program's memory. At most F pages may be
   "resident": when the (F+1)th page is touched, the oldest resident page (FIFO) is dropped
   with madvise(MADV_DONTNEED), so touching it again causes a real page fault (a minor fault:
   no disk I/O, the kernel gives a fresh zero page). Faults are counted with getrusage().
   Usage: ./vm_sim N F pattern accesses      pattern = seq | rand | local               */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>

static unsigned long long seed = 12345;
static unsigned rnd(void) { seed = seed * 6364136223846793005ULL + 1442695040888963407ULL; return (unsigned)(seed >> 33); }
static double now(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec / 1e9; }

int main(int argc, char *argv[])
{
    if (argc < 5) { fprintf(stderr, "usage: %s N F seq|rand|local accesses\n", argv[0]); return 1; }
    long N = atol(argv[1]), F = atol(argv[2]), accesses = atol(argv[4]);
    const char *pat = argv[3];
    volatile char *m = mmap(NULL, N * 4096L, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (m == MAP_FAILED) { perror("mmap"); return 1; }
    char *res = calloc(N, 1);                    /* resident bitmap kept by the program */
    long *fifo = calloc(F, sizeof(long)), head = 0, count = 0, model_faults = 0;
    struct rusage a, b; getrusage(RUSAGE_SELF, &a); double t0 = now();
    long hot = N / 10 > 0 ? N / 10 : 1;
    for (long i = 0; i < accesses; i++) {
        long pg;
        if (!strcmp(pat, "seq")) pg = i % N;
        else if (!strcmp(pat, "rand")) pg = rnd() % N;
        else pg = (rnd() % 10 < 9) ? (long)(rnd() % hot) : hot + (long)(rnd() % (N - hot));  /* 90% of accesses to 10% of pages */
        if (!res[pg]) {                          /* page not resident: a fault is expected */
            model_faults++;
            if (count == F) {                    /* no free frame: evict the oldest page (FIFO) */
                long v = fifo[head];
                madvise((void *)(m + v * 4096L), 4096, MADV_DONTNEED);
                res[v] = 0; head = (head + 1) % F; count--;
            }
            fifo[(head + count) % F] = pg; count++;
            res[pg] = 1;
        }
        m[pg * 4096L] = (char)i;                 /* the actual memory access (a write) */
    }
    double t1 = now(); getrusage(RUSAGE_SELF, &b);
    printf("%-5s N=%6ld F=%6ld accesses=%8ld  model faults=%8ld  kernel minor faults=%8ld  time=%8.1f ms  fault rate=%.5f\n",
           pat, N, F, accesses, model_faults, b.ru_minflt - a.ru_minflt, (t1 - t0) * 1e3, (double)model_faults / accesses);
    return 0;
}
