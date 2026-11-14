#include <stdio.h>
#define MAXF 8
static int find(const int f[], int n, int p) { for (int i = 0; i < n; i++) if (f[i] == p) return i; return -1; }
static int fifo(const int r[], int len, int fr)
{
    int f[MAXF], used = 0, nx = 0, faults = 0;
    for (int i = 0; i < len; i++) {
        if (find(f, used, r[i]) >= 0) continue;
        faults++;
        if (used < fr) f[used++] = r[i]; else { f[nx] = r[i]; nx = (nx + 1) % fr; }
    }
    return faults;
}
static int lru(const int r[], int len, int fr)
{
    int f[MAXF], last[MAXF], used = 0, faults = 0;
    for (int i = 0; i < len; i++) {
        int k = find(f, used, r[i]);
        if (k >= 0) { last[k] = i; continue; }
        faults++;
        if (used < fr) { f[used] = r[i]; last[used++] = i; continue; }
        int v = 0; for (int j = 1; j < fr; j++) if (last[j] < last[v]) v = j;
        f[v] = r[i]; last[v] = i;
    }
    return faults;
}
int main(void)
{
    int b[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    printf("Belady string 1 2 3 4 1 2 5 1 2 3 4 5\nframes  FIFO  LRU\n");
    for (int fr = 1; fr <= 6; fr++) printf("%6d %5d %4d\n", fr, fifo(b, 12, fr), lru(b, 12, fr));
    return 0;
}
