Code:
#include <stdio.h>
struct Record { int number; char data[100]; };
int main()
{
    FILE *fp;
    struct Record r;
    int wanted;
    fp = fopen("sequential.dat", "wb");
    if (fp == NULL) return 1;
    while (1)
    {
        printf("Record number (0 to stop): ");
        scanf("%d", &r.number);
        if (r.number == 0) break;
        printf("Data: ");
        scanf(" %99[^\n]", r.data);
        fwrite(&r, sizeof(r), 1, fp);
    }
    fclose(fp);
    fp = fopen("sequential.dat", "rb");
    printf("Record to read: ");
    scanf("%d", &wanted);
    while (fread(&r, sizeof(r), 1, fp))
    {
        printf("%d %s\n", r.number, r.data);
        if (r.number == wanted) break;
    }
    fclose(fp);
    return 0;
}

Input:
1
Alpha
2
Beta
0
2

Output:
Record number (0 to stop): Data: Record number (0 to stop): Data: Record number (0 to stop): Record to read: 1 Alpha
2 Beta
