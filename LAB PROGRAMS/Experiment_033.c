Code:
#include <stdio.h>
int main()
{
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int frames[3] = {-1,-1,-1}, faults = 0, i, j, k, hit, pos, farthest, next;
    for (i = 0; i < 13; i++)
    {
        hit = 0;
        for (j = 0; j < 3; j++)
            if (frames[j] == pages[i]) hit = 1;
        if (!hit)
        {
            pos = -1; farthest = -1;
            for (j = 0; j < 3; j++)
            {
                if (frames[j] == -1) { pos = j; break; }
                next = 999;
                for (k = i + 1; k < 13; k++)
                    if (pages[k] == frames[j]) { next = k; break; }
                if (next > farthest) { farthest = next; pos = j; }
            }
            frames[pos] = pages[i];
            faults++;
        }
    }
    printf("Total Page Faults: %d\n", faults);
    return 0;
}


Output:
Total Page Faults: 7
