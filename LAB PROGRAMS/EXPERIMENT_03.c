#include <stdio.h>
int main()
{
    int bt[100], wt[100], tat[100];
    int n, i;
    float avg_wt, avg_tat;
    int total_wt = 0;
    int total_tat = 0;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }
    wt[0] = 0;
    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        total_wt += wt[i];
    }
    avg_wt = (float)total_wt / n;
    printf("P BT WT TAT\n");
    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        total_tat += tat[i];

        printf("P%d %d %d %d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }
    avg_tat = (float)total_tat / n;
    printf("Average Waiting Time= %f", avg_wt);
    printf("\nAverage Turnaround Time= %f", avg_tat);
    return 0;
}

Input : 
Enter number of process: 4
Enter Burst Time:
P1: 12
P2: 14
P3: 15
P4: 16

Output :
P BT WT TAT
P1 12 0 12
P2 14 12 26
P3 15 26 41
P4 16 41 57
Average Waiting Time= 19.750000
Average Turnaround Time= 34.000000
