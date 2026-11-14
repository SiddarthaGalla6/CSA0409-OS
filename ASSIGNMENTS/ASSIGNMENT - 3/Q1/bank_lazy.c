#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

static void print_mem(void)
{
    FILE *f = fopen("/proc/self/status", "r");
    char line[256];
    while (f && fgets(line, sizeof line, f))
        if (!strncmp(line, "VmSize", 6) || !strncmp(line, "VmRSS", 5))
            fputs(line, stdout);
    if (f) fclose(f);
}

/* Encrypts only when asked (argument "--encrypt"); the library is loaded at that moment. */
int main(int argc, char *argv[])
{
    int need_crypto = argc > 1 && !strcmp(argv[1], "--encrypt");
    if (need_crypto) {
        void *h = dlopen("./libenc.so", RTLD_NOW);
        if (!h) { fprintf(stderr, "encryption unavailable: %s\n", dlerror()); return 3; }
        void (*enc)(unsigned char *, size_t, unsigned char) = (void (*)(unsigned char *, size_t, unsigned char))dlsym(h, "encrypt_buf");
        if (!enc) { fprintf(stderr, "bad library: %s\n", dlerror()); dlclose(h); return 4; }
        unsigned char msg[] = "ACCOUNT=1001;AMOUNT=2500";
        enc(msg, strlen((char *)msg), 0x5A);
        printf("encrypted %zu bytes, first byte %02X\n", strlen((char *)msg), msg[0]);
        dlclose(h);
    } else {
        printf("balance enquiry only: no encryption needed, library not loaded\n");
    }
    if (argc > 2 && !strcmp(argv[2], "--stats")) print_mem();
    return 0;
}
