Code:
#include <stdio.h>
int main()
{
    int n, at[20], bt[20], pr[20], rem[20], ct[20];
    int time = 0, done = 0, pos, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time, burst time and priority of P%d: ", i + 1);
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
        rem[i] = bt[i];
    }
    while (done < n)
    {
        pos = -1;
        for (i = 0; i < n; i++)
            if (at[i] <= time && rem[i] > 0)
                if (pos == -1 || pr[i] < pr[pos])
                    pos = i;
        if (pos == -1) time++;
        else
        {
            rem[pos]--;
            time++;
            if (rem[pos] == 0)
            {
                ct[pos] = time;
                done++;
            }
        }
    }
    printf("Process AT BT Priority WT TAT\n");
    for (i = 0; i < n; i++)
        printf("P%d %d %d %d %d %d\n", i + 1, at[i], bt[i], pr[i],
               ct[i] - at[i] - bt[i], ct[i] - at[i]);
    return 0;
}

Input:
3
0 5 2
1 3 1
2 4 3

Output:
Process AT BT Priority WT TAT
P1 0 5 2 3 8
P2 1 3 1 0 3
P3 2 4 3 6 10
