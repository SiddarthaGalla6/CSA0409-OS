Code:
#include <stdio.h>
int main()
{
    int n, bt[20], p[20], wt[20], tat[20], i, j, t;
    float aw = 0, at = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("P%d burst time: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (bt[i] > bt[j])
            {
                t = bt[i]; bt[i] = bt[j]; bt[j] = t;
                t = p[i]; p[i] = p[j]; p[j] = t;
            }
    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    printf("Process BT WT TAT\n");
    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        aw += wt[i]; at += tat[i];
        printf("P%d %d %d %d\n", p[i], bt[i], wt[i], tat[i]);
    }
    printf("Average Waiting Time = %.2f\n", aw / n);
    printf("Average Turnaround Time = %.2f\n", at / n);
    return 0;
}

Input:
4
6 8 7 3

Output:
Process BT WT TAT
P4 3 0 3
P1 6 3 9
P3 7 9 16
P2 8 16 24
Average Waiting Time = 7.00
Average Turnaround Time = 13.00
