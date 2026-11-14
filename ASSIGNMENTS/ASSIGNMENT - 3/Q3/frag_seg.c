#include <stdio.h>
#define MEM 1200            /* KB of memory */
#define N 20
static unsigned long long seed = 7;
static int rnd(int lo, int hi) { seed = seed * 6364136223846793005ULL + 1442695040888963407ULL; return lo + (int)((seed >> 33) % (unsigned)(hi - lo + 1)); }
int owner[MEM];             /* 0 = free, k = segment k (1 KB units) */
static int place(int id, int size)          /* first-fit */
{
    int run = 0;
    for (int i = 0; i < MEM; i++) {
        run = owner[i] ? 0 : run + 1;
        if (run == size) { for (int j = i - size + 1; j <= i; j++) owner[j] = id; return i - size + 1; }
    }
    return -1;
}
static void dump(const char *file)
{
    FILE *f = fopen(file, "w"); int i = 0;
    while (i < MEM) { int j = i; while (j < MEM && owner[j] == owner[i]) j++; fprintf(f, "%d,%d,%d\n", owner[i], i, j - i); i = j; }
    fclose(f);
}
static void report(const char *when)
{
    int free_total = 0, holes = 0, largest = 0, run = 0;
    for (int i = 0; i <= MEM; i++) {
        if (i < MEM && !owner[i]) { run++; free_total++; }
        else if (run) { holes++; if (run > largest) largest = run; run = 0; }
    }
    printf("%-22s free %4d KB, holes %2d, largest hole %4d KB, external fragmentation = %.1f %%\n",
           when, free_total, holes, largest, free_total ? 100.0 * (free_total - largest) / free_total : 0.0);
}
int main(void)
{
    int size[N + 1];
    for (int k = 1; k <= N; k++) { size[k] = rnd(20, 90); if (place(k, size[k]) < 0) printf("segment %d (%d KB) does not fit\n", k, size[k]); }
    report("after loading 20:"); dump("layout_before.csv");
    for (int k = 2; k <= N; k += 3) { for (int i = 0; i < MEM; i++) if (owner[i] == k) owner[i] = 0; printf("removed segment %2d (%d KB)\n", k, size[k]); }
    report("after removing 7:"); dump("layout_after.csv");
    int big = 0, free_total = 0, largest = 0, run = 0;
    for (int i = 0; i <= MEM; i++) { if (i < MEM && !owner[i]) { run++; free_total++; } else { if (run > largest) largest = run; run = 0; } }
    big = largest + 1;
    printf("New segment of %d KB (<= %d KB total free): %s\n", big, free_total, place(99, big) < 0 ? "CANNOT be loaded (external fragmentation)" : "loaded");
    return 0;
}
