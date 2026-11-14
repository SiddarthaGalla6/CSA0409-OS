/* Compare the physical frame numbers (PFN) behind a mapping in two processes.
   Usage: ./shared_pages PID1 PID2 name-fragment      (needs root for PFNs) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

static int find_map(int pid, const char *pat, unsigned long *lo, unsigned long *hi)
{
    char path[64], line[512];
    snprintf(path, sizeof path, "/proc/%d/maps", pid);
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    while (fgets(line, sizeof line, f))
        if (strstr(line, pat) && strstr(line, " r-xp ")) {
            sscanf(line, "%lx-%lx", lo, hi); fclose(f); return 1;
        }
    fclose(f); return 0;
}
static uint64_t pfn_of(int pid, unsigned long addr)
{
    char path[64]; uint64_t e = 0;
    snprintf(path, sizeof path, "/proc/%d/pagemap", pid);
    int fd = open(path, O_RDONLY);
    if (fd < 0) return 0;
    pread(fd, &e, 8, (addr / 4096) * 8);
    close(fd);
    return (e >> 63) ? (e & ((1ULL << 55) - 1)) : 0;
}
int main(int argc, char *argv[])
{
    if (argc < 4) return 1;
    int p1 = atoi(argv[1]), p2 = atoi(argv[2]);
    unsigned long a1, b1, a2, b2;
    if (!find_map(p1, argv[3], &a1, &b1) || !find_map(p2, argv[3], &a2, &b2)) {
        puts("mapping not found"); return 1;
    }
    int pages = (int)((b1 - a1) / 4096), same = 0, present = 0;
    printf("Mapping '%s' (code): process %d at %lx, process %d at %lx, %d pages\n",
           argv[3], p1, a1, p2, a2, pages);
    for (int i = 0; i < pages; i++) {
        uint64_t x = pfn_of(p1, a1 + 4096UL * i), y = pfn_of(p2, a2 + 4096UL * i);
        if (x) present++;
        if (x && x == y) same++;
        if (i < 3) printf("  page %d: PFN(process %d)=0x%llx  PFN(process %d)=0x%llx\n",
                          i, p1, (unsigned long long)x, p2, (unsigned long long)y);
    }
    printf("Resident pages: %d, pages backed by the SAME physical frame in both processes: %d\n", present, same);
    return 0;
}
