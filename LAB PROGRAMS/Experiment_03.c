Code:
#include <stdio.h>
int main()
{
    int n, bt[20], wt[20], tat[20], i, totalWT = 0, totalTAT = 0;
    float avgWT, avgTAT;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }
    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    printf("Process\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    avgWT = (float)totalWT / n;
    avgTAT = (float)totalTAT / n;
    printf("Average Waiting Time = %.2f\n", avgWT);
    printf("Average Turnaround Time = %.2f\n", avgTAT);
    return 0;
}

Input:
3\n5 3 2

Output:
Process\tBT\tWT\tTAT\nP1\t5\t0\t5\nP2\t3\t5\t8\nP3\t2\t8\t10\nAverage Waiting Time = 4.33\nAverage Turnaround Time = 7.67
