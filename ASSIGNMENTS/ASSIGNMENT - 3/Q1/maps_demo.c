#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libenc.h"

int global_var = 7;
int main(void)
{
    int local = 1;
    void *heap = malloc(64);
    printf("main()        @ %p (code)\n", (void *)main);
    printf("encrypt_buf() @ %p (shared library code)\n", (void *)encrypt_buf);
    printf("global_var    @ %p (data)\n", (void *)&global_var);
    printf("malloc(64)    @ %p (heap)\n", heap);
    printf("local var     @ %p (stack)\n\n", (void *)&local);
    FILE *f = fopen("/proc/self/maps", "r");
    char line[512];
    while (fgets(line, sizeof line, f))
        if (strstr(line, "maps_demo") || strstr(line, "libenc") || strstr(line, "libc.so") ||
            strstr(line, "[heap]") || strstr(line, "[stack]") || strstr(line, "ld-linux"))
            fputs(line, stdout);
    fclose(f);
    free(heap);
    return 0;
}
