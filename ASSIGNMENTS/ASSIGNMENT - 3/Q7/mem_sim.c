/* Memory simulator for the edge device. Unit = one 2 MB "page group"; 1024 units = 2 GB.
   Global LRU replacement among UNPINNED frames. Pinned (mlock-ed) pages are never evicted.
   Tasks: 0 = real-time control (pinned), 1 = ML (file-backed model, evictable), 2 = logging, 3 = optional 4th task.
   Usage: ./mem_sim ml_units task4_units rt_pinned(1/0)                                    */
#include <stdio.h>
#include <stdlib.h>
#define FRAMES 1024
#define OS_UNITS 128                     /* kernel + OS: 256 MB, always resident */
#define STEPS 100000
static unsigned long long seed = 5;
static unsigned rnd(void) { seed = seed * 6364136223846793005ULL + 1442695040888963407ULL; return (unsigned)(seed >> 33); }
static int frame_of[4096], owner_page[FRAMES], pinned[FRAMES]; static long last[FRAMES];
static long faults[4], accesses[4], clock_t_ = 0; static int used = 0;
static void access_page(int task, int page, int is_pinned_task)
{
    accesses[task]++; clock_t_++;
    if (frame_of[page] >= 0) { last[frame_of[page]] = clock_t_; return; }
    faults[task]++;
    int v = -1;
    if (used < FRAMES) v = used++;
    else { long best = 1L << 60; for (int f = 0; f < FRAMES; f++) if (!pinned[f] && last[f] < best) { best = last[f]; v = f; }
           if (v < 0) { printf("OUT OF MEMORY (no evictable frame)\n"); exit(1); } frame_of[owner_page[v]] = -1; }
    owner_page[v] = page; frame_of[page] = v; last[v] = clock_t_; pinned[v] = is_pinned_task;
}
int main(int argc, char *argv[])
{
    int ml = argc > 1 ? atoi(argv[1]) : 750, t4 = argc > 2 ? atoi(argv[2]) : 0, rtpin = argc > 3 ? atoi(argv[3]) : 1;
    int RT = 32, LOG = 50, base_rt = 0, base_ml = 100, base_log = 1000, base_t4 = 2000;
    for (int i = 0; i < 4096; i++) frame_of[i] = -1;
    for (int i = 0; i < OS_UNITS; i++) { owner_page[used] = 3000 + i; frame_of[3000 + i] = used; pinned[used] = 1; used++; }
    for (int i = 0; i < RT; i++) { access_page(0, base_rt + i, rtpin); }       /* RT pages loaded (and locked) at start-up */
    for (int t = 0; t < 4; t++) faults[t] = accesses[t] = 0;                   /* count only run-time behaviour */
    int ml_pos = 0, log_pos = 0;
    for (int s = 0; s < STEPS; s++) {
        for (int k = 0; k < 4; k++) access_page(0, base_rt + (int)(rnd() % RT), rtpin);
        for (int k = 0; k < 8; k++) {                                          /* inference: sweep over the model + some random reads */
            int pg = (rnd() % 5 == 0) ? (int)(rnd() % ml) : ml_pos; if (pg == ml_pos) ml_pos = (ml_pos + 1) % ml;
            access_page(1, base_ml + pg, 0);
        }
        for (int k = 0; k < 2; k++) { access_page(2, base_log + log_pos, 0); log_pos = (log_pos + 1) % LOG; }
        if (t4) for (int k = 0; k < 4; k++) access_page(3, base_t4 + (int)(rnd() % t4), 0);
    }
    const char *nm[] = {"real-time control", "machine learning", "logging", "4th task"};
    printf("Config: ML=%d units (%d MB), 4th task=%d units (%d MB), RT pages %s. Evictable frames = %d\n", ml, ml * 2, t4, t4 * 2,
           rtpin ? "PINNED (mlock)" : "NOT pinned", FRAMES - OS_UNITS - (rtpin ? RT : 0));
    printf("%-18s %10s %10s %10s\n", "task", "accesses", "faults", "fault rate");
    for (int t = 0; t < (t4 ? 4 : 3); t++)
        printf("%-18s %10ld %10ld %9.3f%%\n", nm[t], accesses[t], faults[t], accesses[t] ? 100.0 * faults[t] / accesses[t] : 0.0);
    return 0;
}
