/* CODE: */
#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(void) {
    const char msg[] = "Hospital system call demo\n";
    int fd = open("demo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }
    ssize_t n = write(fd, msg, sizeof(msg) - 1);
    if (n == -1) { perror("write"); close(fd); return 1; }
    if (close(fd) == -1) { perror("close"); return 1; }
    printf("Wrote %zd bytes\n", n);
    return 0;
}

/*
Input:
No keyboard input. The program creates/overwrites demo.txt and writes a fixed message.
Output (reference/sample):
Wrote 26 bytes
*/
