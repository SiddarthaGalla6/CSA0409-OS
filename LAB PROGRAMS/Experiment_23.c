Code:
#include <stdio.h>
int main()
{
    int b[20], p[20], m, n, i, j, found;
    printf("Enter number of blocks and processes: ");
    scanf("%d%d", &m, &n);
    for (i = 0; i < m; i++) scanf("%d", &b[i]);
    for (i = 0; i < n; i++) scanf("%d", &p[i]);
    for (i = 0; i < n; i++)
    {
        found = 0;
        for (j = 0; j < m; j++)
            if (b[j] >= p[i])
            {
                printf("P%d allocated in block %d\n", i + 1, j + 1);
                b[j] -= p[i];
                found = 1;
                break;
            }
        if (!found) printf("P%d not allocated\n", i + 1);
    }
    return 0;
}

Input:
5 4
100 500 200 300 600
212 417 112 426

Output:
P1 allocated in block 2
P2 allocated in block 5
P3 allocated in block 2
P4 not allocated
