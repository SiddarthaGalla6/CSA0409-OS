Code:
#include <stdio.h>
int main()
{
    int n, at[20], bt[20], p[20], done[20] = {0};
    int ct[20], time = 0, count = 0, pos, i, j, t;
    float aw = 0, atat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival and burst time of P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        p[i] = i + 1;
    }
    while (count < n)
    {
        pos = -1;
        for (i = 0; i < n; i++)
            if (!done[i] && at[i] <= time)
                if (pos == -1 || bt[i] < bt[pos]) pos = i;
        if (pos == -1) time++;
        else
        {
            time += bt[pos];
            ct[pos] = time;
            done[pos] = 1;
            count++;
        }
    }
    printf("Process AT BT WT TAT\n");
    for (i = 0; i < n; i++)
    {
        int tat = ct[i] - at[i], wt = tat - bt[i];
        aw += wt; atat += tat;
        printf("P%d %d %d %d %d\n", p[i], at[i], bt[i], wt, tat);
    }
    printf("Average Waiting Time = %.2f\n", aw / n);
    printf("Average Turnaround Time = %.2f\n", atat / n);
    return 0;
}

Input:
4
0 6
1 8
2 7
3 3

Output:
Process AT BT WT TAT
P1 0 6 0 6
P2 1 8 11 19
P3 2 7 15 22
P4 3 3 3 6
Average Waiting Time = 7.25
Average Turnaround Time = 13.25
