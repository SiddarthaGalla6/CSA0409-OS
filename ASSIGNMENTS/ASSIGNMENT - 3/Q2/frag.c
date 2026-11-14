#include <stdio.h>
#include <stdlib.h>
/* Internal fragmentation of 100 processes with random sizes (fixed seed for repeatability). */
static unsigned long long seed = 2024;
static unsigned long long rnd(void)            /* simple 64-bit LCG */
{
    seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
    return seed >> 33;
}
int main(void)
{
    enum { N = 100 };
    unsigned long long size[N], total = 0;
    for (int i = 0; i < N; i++) {              /* size between 10 KB and 8 MB */
        size[i] = 10240ULL + rnd() % (8ULL * 1024 * 1024 - 10240);
        total += size[i];
    }
    unsigned long long pg[] = {1024, 4096, 2097152};
    const char *name[] = {"1 KB", "4 KB", "2 MB"};
    printf("100 processes, total size %.2f MB, average %.1f KB\n\n", total / 1048576.0, total / 1024.0 / N);
    printf("page   pages used   wasted bytes   avg waste/process   waste %%   table entries (4 B)\n");
    for (int k = 0; k < 3; k++) {
        unsigned long long waste = 0, pages = 0;
        for (int i = 0; i < N; i++) {
            unsigned long long p = (size[i] + pg[k] - 1) / pg[k];
            pages += p; waste += p * pg[k] - size[i];
        }
        printf("%-5s %10llu %14llu %14.1f KB %9.3f %12llu\n", name[k], pages, waste,
               waste / 1024.0 / N, 100.0 * waste / (waste + total), pages);
    }
    return 0;
}
