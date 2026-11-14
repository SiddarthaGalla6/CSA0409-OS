Code:
#include <stdio.h>
int main()
{
    int blocks[20], processes[20], m, n, choice, i, j, best, temp;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < m; i++) scanf("%d", &blocks[i]);
    for (i = 0; i < n; i++) scanf("%d", &processes[i]);
    printf("1.First Fit 2.Best Fit 3.Worst Fit: ");
    scanf("%d", &choice);
    for (i = 0; i < n; i++)
    {
        best = -1;
        for (j = 0; j < m; j++)
            if (blocks[j] >= processes[i])
                if (best == -1 || (choice == 2 && blocks[j] < blocks[best]) ||
                    (choice == 3 && blocks[j] > blocks[best]) || choice == 1)
                    best = j;
        if (best == -1) printf("P%d not allocated\n", i + 1);
        else
        {
            printf("P%d allocated in block %d\n", i + 1, best + 1);
            blocks[best] -= processes[i];
            if (choice == 1) { }
        }
    }
    return 0;
}

Input:
5 4
100 500 200 300 600
212 417 112 426
2

Output:
P1 allocated in block 4
P2 allocated in block 2
P3 allocated in block 3
P4 not allocated
