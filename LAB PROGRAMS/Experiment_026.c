Code:
#include <stdio.h>
int main()
{
    FILE *fp;
    char line[100];
    fp = fopen("example.txt", "w");
    if (fp == NULL) return 1;
    fprintf(fp, "Hello, World!\n");
    fprintf(fp, "File management example.\n");
    fclose(fp);
    fp = fopen("example.txt", "r");
    if (fp == NULL) return 1;
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);
    fclose(fp);
    return 0;
}


Output:
Hello, World!
File management example.
