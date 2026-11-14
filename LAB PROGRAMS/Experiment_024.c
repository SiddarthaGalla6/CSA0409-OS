Code:
#include <stdio.h>
int main()
{
    FILE *fp;
    char text[100];
    fp = fopen("sample.txt", "w");
    if (fp == NULL) return 1;
    fputs("Hello, World!\n", fp);
    fclose(fp);
    fp = fopen("sample.txt", "r");
    if (fp == NULL) return 1;
    while (fgets(text, sizeof(text), fp) != NULL)
        printf("%s", text);
    fclose(fp);
    remove("sample.txt");
    printf("File deleted successfully.\n");
    return 0;
}


Output:
Hello, World!
File deleted successfully.
