Code:
#include <stdio.h>
int main()
{
    int n, at[10], bt[10], rem[10], ct[10], q, time = 0, done = 0, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival and burst time of P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rem[i] = bt[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", &q);
    while (done < n)
    {
        int ran = 0;
        for (i = 0; i < n; i++)
            if (at[i] <= time && rem[i] > 0)
            {
                ran = 1;
                if (rem[i] > q) { time += q; rem[i] -= q; }
                else { time += rem[i]; rem[i] = 0; ct[i] = time; done++; }
            }
        if (!ran) time++;
    }
    printf("Process BT TAT WT\n");
    for (i = 0; i < n; i++)
        printf("P%d %d %d %d\n", i + 1, bt[i], ct[i] - at[i], ct[i] - at[i] - bt[i]);
    return 0;
}

Input:
3
0 5
1 3
2 4
2

Output:
Process BT TAT WT
P1 5 12 7
P2 3 8 5
P3 4 9 5
