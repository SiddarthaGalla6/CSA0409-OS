Code:
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, head, max, a[50], i, j, t, seek = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Enter initial head position and maximum track: ");
    scanf("%d%d", &head, &max);
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (a[i] > a[j]) { t = a[i]; a[i] = a[j]; a[j] = t; }
    for (i = 0; i < n; i++)
        if (a[i] >= head) { seek += abs(head - a[i]); head = a[i]; }
    seek += abs(max - head);
    seek += max;
    head = 0;
    for (i = 0; i < n; i++)
        if (a[i] < head || (head == 0 && a[i] < max && a[i] < a[n-1]))
        {
            seek += abs(head - a[i]);
            head = a[i];
        }
    printf("Total seek time: %d\n", seek);
    printf("Average seek time: %.2f\n", (float)seek / n);
    return 0;
}

Input:
5
82 170 43 140 24
50 199

Output:
Total seek time: 382
Average seek time: 76.40
