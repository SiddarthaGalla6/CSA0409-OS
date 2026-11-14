#ifndef LIBENC_H
#define LIBENC_H
#include <stddef.h>
/* Tiny "encryption" library of the bank (teaching example, NOT real crypto). */
const char *enc_version(void);
void encrypt_buf(unsigned char *buf, size_t n, unsigned char key);
#endif
