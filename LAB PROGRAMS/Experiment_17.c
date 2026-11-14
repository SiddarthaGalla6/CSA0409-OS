Code:
#include <stdio.h>
int main()
{
    int alloc[5][3] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[5][3] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int avail[3] = {3,3,2}, need[5][3], finish[5] = {0}, safe[5];
    int i, j, k, count = 0, found;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 3; j++) need[i][j] = max[i][j] - alloc[i][j];
    while (count < 5)
    {
        found = 0;
        for (i = 0; i < 5; i++)
            if (!finish[i])
            {
                for (j = 0; j < 3 && need[i][j] <= avail[j]; j++);
                if (j == 3)
                {
                    for (k = 0; k < 3; k++) avail[k] += alloc[i][k];
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        if (!found) break;
    }
    if (count == 5)
    {
        printf("Safe sequence: ");
        for (i = 0; i < 5; i++) printf("P%d ", safe[i]);
    }
    else printf("System is not in safe state");
    return 0;
}


Output:
Safe sequence: P1 P3 P4 P0 P2
