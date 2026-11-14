#include "libenc.h"
#ifndef ENC_V2
const char *enc_version(void) { return "libenc v1 (XOR cipher)"; }
void encrypt_buf(unsigned char *buf, size_t n, unsigned char key)
{
    for (size_t i = 0; i < n; i++) buf[i] ^= key;
}
#else
const char *enc_version(void) { return "libenc v2 (XOR + rotate, security fix)"; }
void encrypt_buf(unsigned char *buf, size_t n, unsigned char key)
{
    for (size_t i = 0; i < n; i++) {
        unsigned char x = buf[i] ^ (unsigned char)(key + i);
        buf[i] = (unsigned char)((x << 3) | (x >> 5));
    }
}
#endif
