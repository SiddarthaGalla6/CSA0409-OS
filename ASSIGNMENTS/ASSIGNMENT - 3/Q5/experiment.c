/* Page-replacement experiment: FIFO, LRU, Optimal and Clock on 100,000-reference strings.
   Usage: ./experiment            prints a CSV table of faults and a timing table.            */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 100000
#define PAGES 64
#define MAXF 16
static int loc[N], rnd_[N], nxt[N];
static unsigned long long seed = 99;
static unsigned rnd(void) { seed = seed * 6364136223846793005ULL + 1442695040888963407ULL; return (unsigned)(seed >> 33); }
static double now(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec / 1e9; }

static int fifo(const int *r, int fr)
{
    int f[MAXF], used = 0, nx = 0, faults = 0;
    for (int i = 0; i < N; i++) {
        int hit = 0; for (int j = 0; j < used; j++) if (f[j] == r[i]) { hit = 1; break; }
        if (hit) continue;
        faults++;
        if (used < fr) f[used++] = r[i]; else { f[nx] = r[i]; nx = (nx + 1) % fr; }
    }
    return faults;
}
static int lru(const int *r, int fr)
{
    int f[MAXF], last[MAXF], used = 0, faults = 0;
    for (int i = 0; i < N; i++) {
        int k = -1; for (int j = 0; j < used; j++) if (f[j] == r[i]) { k = j; break; }
        if (k >= 0) { last[k] = i; continue; }
        faults++;
        if (used < fr) { f[used] = r[i]; last[used++] = i; continue; }
        int v = 0; for (int j = 1; j < fr; j++) if (last[j] < last[v]) v = j;
        f[v] = r[i]; last[v] = i;
    }
    return faults;
}
static int optimal(const int *r, int fr)       /* uses nxt[i] = index of the next use of r[i] */
{
    int f[MAXF], when[MAXF], used = 0, faults = 0;
    for (int i = 0; i < N; i++) {
        int k = -1; for (int j = 0; j < used; j++) if (f[j] == r[i]) { k = j; break; }
        if (k >= 0) { when[k] = nxt[i]; continue; }
        faults++;
        if (used < fr) { f[used] = r[i]; when[used++] = nxt[i]; continue; }
        int v = 0; for (int j = 1; j < fr; j++) if (when[j] > when[v]) v = j;
        f[v] = r[i]; when[v] = nxt[i];
    }
    return faults;
}
static int clock_alg(const int *r, int fr)     /* second chance: one reference bit per frame */
{
    int f[MAXF], bit[MAXF], used = 0, hand = 0, faults = 0;
    for (int i = 0; i < N; i++) {
        int k = -1; for (int j = 0; j < used; j++) if (f[j] == r[i]) { k = j; break; }
        if (k >= 0) { bit[k] = 1; continue; }  /* hardware would set this bit */
        faults++;
        if (used < fr) { f[used] = r[i]; bit[used++] = 1; continue; }
        while (bit[hand]) { bit[hand] = 0; hand = (hand + 1) % fr; }   /* give a second chance */
        f[hand] = r[i]; bit[hand] = 1; hand = (hand + 1) % fr;
    }
    return faults;
}
static void make_next(const int *r)
{
    int pos[PAGES]; for (int p = 0; p < PAGES; p++) pos[p] = N;
    for (int i = N - 1; i >= 0; i--) { nxt[i] = pos[r[i]]; pos[r[i]] = i; }
}
int main(void)
{
    /* Strong locality: a hot set of 6 pages gets 95% of references; the hot set drifts every 2000 references. */
    int base = 0;
    for (int i = 0; i < N; i++) {
        if (i % 2000 == 0) base = rnd() % PAGES;
        loc[i] = (rnd() % 100 < 95) ? (base + (int)(rnd() % 6)) % PAGES : (int)(rnd() % PAGES);
    }
    for (int i = 0; i < N; i++) rnd_[i] = (int)(rnd() % PAGES);
    const char *nm[] = {"locality", "random"}; int *str[] = {loc, rnd_};
    printf("workload,frames,FIFO,LRU,CLOCK,OPT\n");
    for (int w = 0; w < 2; w++) {
        make_next(str[w]);
        for (int fr = 3; fr <= 10; fr++)
            printf("%s,%d,%d,%d,%d,%d\n", nm[w], fr, fifo(str[w], fr), lru(str[w], fr), clock_alg(str[w], fr), optimal(str[w], fr));
    }
    make_next(loc);
    printf("\nTiming for %d references, 8 frames, locality string (mean of 20 runs):\n", N);
    int (*fn[])(const int *, int) = {fifo, lru, clock_alg, optimal};
    const char *an[] = {"FIFO", "LRU", "CLOCK", "OPT"};
    volatile int sink = 0;
    for (int a = 0; a < 4; a++) {
        double t0 = now(); for (int k = 0; k < 20; k++) sink += fn[a](loc, 8);
        printf("  %-6s %8.3f ms per run\n", an[a], (now() - t0) / 20 * 1e3);
    }
    (void)sink;
    return 0;
}
