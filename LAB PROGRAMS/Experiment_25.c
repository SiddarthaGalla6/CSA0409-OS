Code:
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
int main()
{
    FILE *fp;
    struct stat info;
    fp = fopen("foo.txt", "w");
    if (fp == NULL) return 1;
    fputs("Sample file", fp);
    fclose(fp);
    if (stat("foo.txt", &info) == 0)
        printf("File size: %ld bytes\n", (long)info.st_size);
    remove("foo.txt");
    return 0;
}


Output:
File size: 11 bytes
