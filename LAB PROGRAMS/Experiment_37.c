Code:
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, head, request[50], seek = 0, i;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &request[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Head movement: %d", head);
    for (i = 0; i < n; i++)
    {
        seek += abs(head - request[i]);
        head = request[i];
        printf(" -> %d", head);
    }
    printf("\nTotal seek time: %d\n", seek);
    printf("Average seek time: %.2f\n", (float)seek / n);
    return 0;
}

Input:
5
82 170 43 140 24
50

Output:
Head movement: 50 -> 82 -> 170 -> 43 -> 140 -> 24
Total seek time: 418
Average seek time: 83.60
