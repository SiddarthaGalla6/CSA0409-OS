#include <stdio.h>
int main()
{
    FILE *source, *destination;
    char name1[100], name2[100];
    char c;
    scanf("%s", name1);
    scanf("%s", name2);
    source = fopen(name1, "r");
    destination = fopen(name2, "w");
    while ((c = fgetc(source)) != EOF)
    {
        fputc(c, destination);
    }
    fclose(source);
    fclose(destination);
    return 0;
}

Output :
Hello Operating System
