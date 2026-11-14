#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef const char *(*ver_fn)(void);
typedef void (*enc_fn)(unsigned char *, size_t, unsigned char);

int main(int argc, char *argv[])
{
    const char *path = argc > 1 ? argv[1] : "./libenc.so";
    void *h = dlopen(path, RTLD_LAZY);
    if (!h) { fprintf(stderr, "dlopen failed: %s\n", dlerror()); return 1; }
    dlerror();                                   /* clear old errors */
    ver_fn ver = (ver_fn)dlsym(h, "enc_version");
    enc_fn enc = (enc_fn)dlsym(h, "encrypt_buf");
    char *err = dlerror();
    if (err) { fprintf(stderr, "dlsym failed: %s\n", err); dlclose(h); return 2; }
    unsigned char msg[] = "ACCOUNT=1001;AMOUNT=2500";
    size_t n = strlen((char *)msg);
    printf("Loaded %s at run time\n", ver());
    printf("encrypt_buf is at address %p\n", (void *)enc);
    enc(msg, n, 0x5A);
    printf("Cipher text: ");
    for (size_t i = 0; i < n; i++) printf("%02X", msg[i]);
    printf("\n");
    dlclose(h);
    return 0;
}
