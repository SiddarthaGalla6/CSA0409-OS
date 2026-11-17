#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Disk-scheduling simulator: FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK.
   Cylinders 0..199. Service time = SEEK_MS_PER_CYL * |distance| + FIXED_MS (4 ms)
   (rotational latency + transfer). Waiting time = start of service - arrival. */
#define MAXCYL 199
#define SEEK_MS_PER_CYL 0.04
static double FIXED_MS = 4.0;   /* average rotational latency + transfer, ms */

typedef struct { double arrive, start; int cyl; int done; } Req;
enum { FCFS, SSTF, SCAN, CSCAN, LOOK, CLOOK, NALG };
static const char *names[NALG] = {"FCFS", "SSTF", "SCAN", "C-SCAN", "LOOK", "C-LOOK"};

static unsigned long long rng = 0x9E3779B97F4A7C15ULL;
static double urand(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return (rng >> 11) * (1.0 / 9007199254740992.0); }

typedef struct { double total_move, max_wait, sum_wait, sum_wait2, makespan; long served; } Stats;

/* pick next request index among arrived (arrive <= t) and not done; -1 if none.
   dir: +1 up, -1 down (updated for SCAN/LOOK). Sets *extra_move for end-of-disk
   travel (SCAN/C-SCAN) or jump (C-LOOK/C-SCAN). */
static int pick(Req *r, int n, int first_pending, double t, int alg, int pos, int *dir, int *new_pos_via, int *extra)
{
    int best = -1, bd = 1 << 30; *extra = 0; *new_pos_via = pos;
    /* arrived requests are those with index < limit; r is sorted by arrival */
    int lim = first_pending;           /* first_pending reused as 'number arrived' */
    (void)n; (void)t;
    switch (alg) {
    case FCFS:
        for (int i = 0; i < lim; i++) if (!r[i].done) return i;
        return -1;
    case SSTF:
        for (int i = 0; i < lim; i++) if (!r[i].done) { int d = abs(r[i].cyl - pos); if (d < bd) { bd = d; best = i; } }
        return best;
    default: break;
    }
    int any = 0;
    for (int i = 0; i < lim; i++) if (!r[i].done) { any = 1; break; }
    if (!any) return -1;
    for (int attempt = 0; attempt < 2; attempt++) {
        best = -1; bd = 1 << 30;
        for (int i = 0; i < lim; i++) {
            if (r[i].done) continue;
            int d = (r[i].cyl - pos) * (*dir);          /* distance ahead in current direction */
            if (d >= 0 && d < bd) { bd = d; best = i; }
        }
        if (best >= 0) return best;
        /* nothing ahead */
        if (alg == SCAN) { int end = (*dir > 0) ? MAXCYL : 0; *extra = abs(end - pos); *new_pos_via = end; pos = end; *dir = -*dir; }
        else if (alg == LOOK) { *dir = -*dir; }
        else if (alg == CSCAN) { int end = (*dir > 0) ? MAXCYL : 0; *extra = abs(end - pos) + MAXCYL; *new_pos_via = 0; pos = 0; }
        else if (alg == CLOOK) {
            int lo = 1 << 30; for (int i = 0; i < lim; i++) if (!r[i].done && r[i].cyl < lo) lo = r[i].cyl;
            *extra = abs(pos - lo); *new_pos_via = lo; pos = lo;
        }
    }
    return -1;
}

static Stats run(Req *r, int n, int alg, int head, double horizon_stop_after_n)
{
    (void)horizon_stop_after_n;
    Stats st; memset(&st, 0, sizeof st);
    for (int i = 0; i < n; i++) { r[i].done = 0; r[i].start = -1; }
    double t = 0; int pos = head, dir = 1, arrived = 0, served = 0;
    while (served < n) {
        while (arrived < n && r[arrived].arrive <= t) arrived++;
        int extra, via;
        int dsave = dir;
        int k = pick(r, n, arrived, t, alg, pos, &dir, &via, &extra);
        if (k < 0) {                       /* idle until the next arrival */
            if (arrived >= n) break;
            t = r[arrived].arrive; dir = dsave; continue;
        }
        if (extra) { st.total_move += extra; t += extra * SEEK_MS_PER_CYL; pos = via;
                     while (arrived < n && r[arrived].arrive <= t) arrived++; }
        int d = abs(r[k].cyl - pos);
        r[k].start = t; r[k].done = 1;
        double w = t - r[k].arrive;
        if (w > st.max_wait) st.max_wait = w;
        st.sum_wait += w; st.sum_wait2 += w * w;
        st.total_move += d; t += d * SEEK_MS_PER_CYL + FIXED_MS; pos = r[k].cyl; served++;
    }
    st.served = served; st.makespan = t;
    return st;
}

static int cmpreq(const void *a, const void *b) { double x = ((const Req *)a)->arrive, y = ((const Req *)b)->arrive; return (x > y) - (x < y); }

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "starve") == 0) {
        /* Task 4.3 starvation test: given queue at t=0, then one request near
           cylinder 60 every millisecond for T ms. Report when cylinder 183 starts. */
        int given[8] = {98, 183, 37, 122, 14, 124, 65, 67};
        double Ts[3] = {1000, 5000, 20000};
        for (int q = 0; q < 3; q++) {
            double T = Ts[q];
            int n = 8 + (int)T;
            Req *r = malloc(sizeof(Req) * n);
            for (int i = 0; i < 8; i++) { r[i].arrive = 0; r[i].cyl = given[i]; }
            for (int i = 0; i < (int)T; i++) { r[8 + i].arrive = i + 1; r[8 + i].cyl = 58 + (i % 5); }
            printf("\nStream near cylinder 60, one request per ms for %.0f ms (head starts at 53, service = %.1f ms + seek)\n", T, FIXED_MS);
            printf("%-7s %22s\n", "Alg", "wait of cyl 183 (ms)");
            for (int a = 0; a < NALG; a++) {
                run(r, n, a, 53, 0);
                printf("%-7s %22.2f\n", names[a], r[1].start - r[1].arrive);
            }
            free(r);
        }
        return 0;
    }
    int N = 10000;
    struct { const char *label; double mean_gap; } loads[3] = {{"Light", 20.0}, {"Medium", 8.0}, {"Heavy", 6.5}};
    printf("10,000 random requests, cylinders 0-199, seek %.2f ms/cyl + %.1f ms fixed, exponential arrivals\n", SEEK_MS_PER_CYL, FIXED_MS);
    for (int L = 0; L < 3; L++) {
        rng = 0x9E3779B97F4A7C15ULL + 7919ULL * (L + 1);
        Req *r = malloc(sizeof(Req) * N);
        double t = 0;
        for (int i = 0; i < N; i++) { t += -loads[L].mean_gap * log(1.0 - urand()); r[i].arrive = t; r[i].cyl = (int)(urand() * 200); if (r[i].cyl > 199) r[i].cyl = 199; }
        qsort(r, N, sizeof(Req), cmpreq);
        printf("\n%s load (mean inter-arrival %.1f ms)\n", loads[L].label, loads[L].mean_gap);
        printf("%-7s %12s %12s %12s %12s %12s\n", "Alg", "avg move", "avg wait ms", "max wait ms", "std wait ms", "makespan ms");
        for (int a = 0; a < NALG; a++) {
            Stats s = run(r, N, a, 100, 0);
            double mean = s.sum_wait / N, var = s.sum_wait2 / N - mean * mean;
            printf("%-7s %12.2f %12.2f %12.2f %12.2f %12.0f\n", names[a], s.total_move / N, mean, s.max_wait, sqrt(var > 0 ? var : 0), s.makespan);
        }
        if (L == 2) {   /* fairness by region for heavy load */
            printf("\nHeavy load: mean wait (ms) by cylinder band\n%-7s %10s %10s %10s\n", "Alg", "0-19", "90-109", "180-199");
            for (int a = 0; a < NALG; a++) {
                run(r, N, a, 100, 0);
                double sum[3] = {0}; long cnt[3] = {0};
                for (int i = 0; i < N; i++) { int c = r[i].cyl, b = c < 20 ? 0 : (c >= 90 && c < 110 ? 1 : (c >= 180 ? 2 : -1)); if (b >= 0) { sum[b] += r[i].start - r[i].arrive; cnt[b]++; } }
                printf("%-7s %10.2f %10.2f %10.2f\n", names[a], sum[0] / cnt[0], sum[1] / cnt[1], sum[2] / cnt[2]);
            }
        }
        free(r);
    }
    return 0;
}
