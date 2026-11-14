#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    size_t mb = argc > 1 ? (size_t)atol(argv[1]) : 16;
    size_t n = mb << 20;
    volatile char *p = malloc(n);            /* volatile: the compiler may not delete the stores */
    if (!p) return 1;
    for (size_t i = 0; i < n; i += 4096) p[i] = 1;   /* touch every page once */
    unsigned long sum = 0;
    for (size_t i = 0; i < n; i += 4096) sum += p[i];
    printf("touched %zu MB (%zu pages of 4 KB), checksum %lu\n", mb, n / 4096, sum);
    free((void *)p);
    return 0;
}
