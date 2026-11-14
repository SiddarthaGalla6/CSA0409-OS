/* CODE: */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
 
long copy_file(const char *src, const char *dst, size_t bufsize)
{
    char buf[8192];
    if (bufsize == 0 || bufsize > sizeof(buf)) return -1;
    int in = open(src, O_RDONLY);
    if (in < 0) return -1;
    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) { close(in); return -1; }
    long calls = 0;
    ssize_t n;
    while (1) {
        n = read(in, buf, bufsize);
        calls++;
        if (n == 0) break;
        if (n < 0) {
            if (errno == EINTR) continue;
            close(in); close(out); return -1;
        }
        ssize_t done = 0;
        while (done < n) {
            ssize_t w = write(out, buf + done, (size_t)(n - done));
            if (w < 0) {
                if (errno == EINTR) continue;
                close(in); close(out); return -1;
            }
            done += w;
        }
    }
    if (close(in) < 0) { close(out); return -1; }
    if (close(out) < 0) return -1;
    return calls;
}
int main(void)
{
    FILE *f = fopen("records.dat", "w");
    if (!f) return 1;
    for (int i = 0; i < 10000; i++) fputc('A' + i % 26, f);
    if (fclose(f) != 0) return 1;
    size_t sizes[] = {1, 512, 4096};
    for (int i = 0; i < 3; i++)
        printf("buffer %4zu bytes: %5ld read() calls\n",
               sizes[i], copy_file("records.dat", "copy.dat", sizes[i]));
    unlink("records.dat");
    unlink("copy.dat");
    return 0;
}

/*
Input:
No keyboard input. The program creates a 10,000-byte records.dat file, copies it using three buffer sizes, then removes the test files.
Output (reference/sample):
buffer    1 bytes: 10001 read() calls
buffer  512 bytes:    21 read() calls
buffer 4096 bytes:     4 read() calls
*/
