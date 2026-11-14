#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/resource.h>
static void show(const char *when)
{
    FILE *f = fopen("/proc/self/status", "r"); char l[256];
    while (f && fgets(l, sizeof l, f)) if (!strncmp(l, "VmLck", 5)) printf("%-22s %s", when, l);
    if (f) fclose(f);
}
int main(void)
{
    struct rlimit rl; getrlimit(RLIMIT_MEMLOCK, &rl);
    printf("RLIMIT_MEMLOCK soft limit = %lu bytes\n", (unsigned long)rl.rlim_cur);
    size_t n = 16UL << 20; char *p = malloc(n); memset(p, 0, n);
    show("before mlock:");
    if (mlock(p, n)) { perror("mlock"); return 1; }
    show("after mlock(16 MB):");
    munlock(p, n);
    show("after munlock:");
    if (mlockall(MCL_CURRENT | MCL_FUTURE)) { perror("mlockall"); return 1; }
    show("after mlockall:");
    return 0;
}
