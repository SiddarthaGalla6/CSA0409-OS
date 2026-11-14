/* Minimal replacement for "/usr/bin/time -v": prints faults and max RSS of a child (wait4 + rusage). */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    struct rusage ru; int st; (void)argc;
    pid_t p = fork();
    if (p == 0) { execvp(argv[1], argv + 1); _exit(127); }
    wait4(p, &st, 0, &ru);
    printf("\tMaximum resident set size (kbytes): %ld\n", ru.ru_maxrss);
    printf("\tMajor (requiring I/O) page faults: %ld\n", ru.ru_majflt);
    printf("\tMinor (reclaiming a frame) page faults: %ld\n", ru.ru_minflt);
    printf("\tPage size (bytes): %ld\n", sysconf(_SC_PAGESIZE));
    return 0;
}
