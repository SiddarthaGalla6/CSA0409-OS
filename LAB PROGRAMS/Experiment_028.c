Code:
#include <stdio.h>
#include <string.h>
int main()
{
    FILE *fp;
    char filename[100], pattern[100], line[500];
    printf("Enter filename: ");
    scanf("%99s", filename);
    printf("Enter pattern: ");
    scanf("%99s", pattern);
    fp = fopen(filename, "r");
    if (fp == NULL) { printf("File not found\n"); return 1; }
    while (fgets(line, sizeof(line), fp))
        if (strstr(line, pattern) != NULL) printf("%s", line);
    fclose(fp);
    return 0;
}

Input:
sample.txt
OS

Output:
(If sample.txt contains 'Operating Systems', output: Operating Systems)
