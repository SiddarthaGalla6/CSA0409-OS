#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libenc.h"

static void print_mem(void)
{
    FILE *f = fopen("/proc/self/status", "r");
    char line[256];
    while (f && fgets(line, sizeof line, f))
        if (!strncmp(line, "VmSize", 6) || !strncmp(line, "VmRSS", 5))
            fputs(line, stdout);
    if (f) fclose(f);
}

int main(int argc, char *argv[])
{
    unsigned char msg[] = "ACCOUNT=1001;AMOUNT=2500";
    size_t n = strlen((char *)msg);
    encrypt_buf(msg, n, 0x5A);
    printf("%s\nCipher text: ", enc_version());
    for (size_t i = 0; i < n; i++) printf("%02X", msg[i]);
    printf("\n");
    if (argc > 1 && !strcmp(argv[1], "--stats")) print_mem();
    if (argc > 1 && !strcmp(argv[1], "--sleep")) { fflush(stdout); sleep(3); }
    return 0;
}
