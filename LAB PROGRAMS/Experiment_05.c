Code:
#include <stdio.h>
int main()
{
    int n, bt[20], pr[20], p[20], wt[20], tat[20], i, j, t;
    float aw = 0, at = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("Enter burst time and priority of P%d: ", i + 1);
        scanf("%d%d", &bt[i], &pr[i]);
    }
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (pr[i] < pr[j])
            {
                t = pr[i]; pr[i] = pr[j]; pr[j] = t;
                t = bt[i]; bt[i] = bt[j]; bt[j] = t;
                t = p[i]; p[i] = p[j]; p[j] = t;
            }
    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    printf("Process BT Priority WT TAT\n");
    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        aw += wt[i]; at += tat[i];
        printf("P%d %d %d %d %d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
    }
    printf("Average Waiting Time = %.2f\n", aw / n);
    printf("Average Turnaround Time = %.2f\n", at / n);
    return 0;
}

Input:
3
10 2
5 3
8 1

Output:
Process BT Priority WT TAT
P2 5 3 0 5
P1 10 2 5 15
P3 8 1 15 23
Average Waiting Time = 6.67
Average Turnaround Time = 14.33
