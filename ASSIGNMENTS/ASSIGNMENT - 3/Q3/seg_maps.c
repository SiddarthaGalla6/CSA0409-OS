#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int initialised = 42;          /* .data */
int uninitialised;             /* .bss  */
const char *text = "constant";/* literal in .rodata */
int main(void)
{
    int local = 0;
    void *h = malloc(1 << 20);
    printf("code (main)   : %p\nrodata (text) : %p\ndata          : %p\nbss           : %p\n"
           "heap (malloc) : %p\nstack (local) : %p\n\n", (void *)main, (const void *)text,
           (void *)&initialised, (void *)&uninitialised, h, (void *)&local);
    FILE *f = fopen("/proc/self/maps", "r"); char line[512];
    while (fgets(line, sizeof line, f))
        if (strstr(line, "seg_maps") || strstr(line, "[heap]") || strstr(line, "[stack]") || strstr(line, "libc.so"))
            fputs(line, stdout);
    fclose(f); free(h);
    return 0;
}
