#include <stdio.h>
#define MAXF 16
static int find(const int f[], int n, int p) { for (int i = 0; i < n; i++) if (f[i] == p) return i; return -1; }
static int fifo(const int r[], int len, int fr)
{
    int f[MAXF], used = 0, next = 0, faults = 0;
    for (int i = 0; i < len; i++) {
        if (find(f, used, r[i]) >= 0) continue;
        faults++;
        if (used < fr) f[used++] = r[i]; else { f[next] = r[i]; next = (next + 1) % fr; }
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
static int opt(const int r[], int len, int fr)
{
    int f[MAXF], used = 0, faults = 0;
    for (int i = 0; i < len; i++) {
        if (find(f, used, r[i]) >= 0) continue;
        faults++;
        if (used < fr) { f[used++] = r[i]; continue; }
        int v = 0, far = -1;
        for (int j = 0; j < fr; j++) {
            int nx = len; for (int t = i + 1; t < len; t++) if (r[t] == f[j]) { nx = t; break; }
            if (nx > far) { far = nx; v = j; }
        }
        f[v] = r[i];
    }
    return faults;
}
int main(void)
{
    int r[] = {1,2,3,4,1,2,5,1,2,3,4,5,6,1,2,7,3,4,1,2,3,6,7,1,2,5,3,4,1,2};
    int len = (int)(sizeof r / sizeof r[0]);
    printf("reference string length %d, 7 different pages\nframes  FIFO  LRU  OPT\n", len);
    for (int fr = 1; fr <= 8; fr++) printf("%6d %5d %4d %4d\n", fr, fifo(r, len, fr), lru(r, len, fr), opt(r, len, fr));
    return 0;
}
