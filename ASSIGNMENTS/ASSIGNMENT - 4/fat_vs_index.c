#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Compares reaching block k of a file through (a) a FAT held in memory
   (linked chain, O(k) look-ups) and (b) a flat index table (O(1)).
   Block numbers are scattered pseudo-randomly so the chain is not sequential. */

static double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

int main(void)
{
    const long N = 1048576;                      /* 4 GB file / 4 KB blocks */
    unsigned *fat   = malloc(N * sizeof *fat);   /* fat[b] = next block of the file */
    unsigned *index = malloc(N * sizeof *index); /* index[k] = block number of block k */
    unsigned *perm  = malloc(N * sizeof *perm);
    if (!fat || !index || !perm) return 1;

    for (long i = 0; i < N; i++) perm[i] = (unsigned)i;
    unsigned long long s = 88172645463325252ULL; /* xorshift64, fixed seed */
    for (long i = N - 1; i > 0; i--) {           /* Fisher-Yates shuffle */
        s ^= s << 13; s ^= s >> 7; s ^= s << 17;
        long j = (long)(s % (unsigned long long)(i + 1));
        unsigned t = perm[i]; perm[i] = perm[j]; perm[j] = t;
    }
    for (long k = 0; k < N; k++) {
        index[k] = perm[k];
        fat[perm[k]] = (k + 1 < N) ? perm[k + 1] : 0xFFFFFFFFu;
    }

    printf("%10s %14s %14s %12s %12s\n", "k", "FAT lookups", "FAT time(us)", "index reads", "index t(us)");
    long ks[] = {1000, 10000, 100000, 524288, 1048575};
    volatile unsigned sink = 0;
    for (int q = 0; q < 5; q++) {
        long k = ks[q];
        int reps = (int)(2000000000L / (k + 1000)); if (reps > 200000) reps = 200000; if (reps < 50) reps = 50;
        double t0 = now_ms();
        for (int r = 0; r < reps; r++) {
            unsigned b = index[0];
            for (long i = 0; i < k; i++) b = fat[b];
            sink += b;
        }
        double fat_us = (now_ms() - t0) * 1000.0 / reps;
        t0 = now_ms();
        for (int r = 0; r < 1000000; r++) sink += index[(k + r) % N];
        double idx_us = (now_ms() - t0) * 1000.0 / 1000000.0;
        printf("%10ld %14ld %14.2f %12d %12.4f\n", k, k, fat_us, 1, idx_us);
    }
    printf("memory: FAT entry table for this file = %ld KiB\n", N * 4 / 1024);
    (void)sink;
    free(fat); free(index); free(perm);
    return 0;
}
