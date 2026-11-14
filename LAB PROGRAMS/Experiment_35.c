Code:
#include <stdio.h>
struct Block { int number; char data[100]; };
int main()
{
    FILE *fp;
    struct Block b;
    long index[100] = {0};
    int n;
    fp = fopen("indexed.dat", "wb+");
    if (fp == NULL) return 1;
    while (1)
    {
        printf("Block number (0 to stop): ");
        scanf("%d", &b.number);
        if (b.number == 0) break;
        printf("Data: ");
        scanf(" %99[^\n]", b.data);
        index[b.number] = ftell(fp) + 1;
        fwrite(&b, sizeof(b), 1, fp);
    }
    printf("Block to read: ");
    scanf("%d", &n);
    if (n > 0 && n < 100 && index[n] != 0)
    {
        fseek(fp, index[n] - 1, SEEK_SET);
        fread(&b, sizeof(b), 1, fp);
        printf("%d %s\n", b.number, b.data);
    }
    else printf("Block not found\n");
    fclose(fp);
    return 0;
}

Input:
1
Apple
2
Banana
0
2

Output:
Block number (0 to stop): Data: Block number (0 to stop): Data: Block number (0 to stop): Block to read: 2 Banana
