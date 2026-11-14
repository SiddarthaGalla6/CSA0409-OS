Code:
#include <stdio.h>
int main()
{
    FILE *src, *dest;
    char source[100], target[100], ch;
    printf("Enter source filename: ");
    scanf("%99s", source);
    printf("Enter destination filename: ");
    scanf("%99s", target);
    src = fopen(source, "r");
    if (src == NULL)
    {
        printf("Cannot open source file\n");
        return 1;
    }
    dest = fopen(target, "w");
    if (dest == NULL)
    {
        fclose(src);
        printf("Cannot open destination file\n");
        return 1;
    }
    while ((ch = fgetc(src)) != EOF)
        fputc(ch, dest);
    fclose(src);
    fclose(dest);
    printf("File copied successfully.\n");
    return 0;
}

Input:
source.txt
destination.txt
(source.txt contains: Hello World)

Output:
Enter source filename: destination.txt
File copied successfully.
