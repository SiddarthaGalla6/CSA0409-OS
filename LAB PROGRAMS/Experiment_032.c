Code:
#include <stdio.h>
int main()
{
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int frames[3] = {-1,-1,-1}, last[3] = {0,0,0};
    int faults = 0, i, j, hit, pos, oldest, t;
    for (i = 0; i < 13; i++)
    {
        hit = 0; pos = -1;
        for (j = 0; j < 3; j++)
            if (frames[j] == pages[i]) { hit = 1; pos = j; }
        if (hit) last[pos] = i + 1;
        else
        {
            pos = 0;
            for (j = 0; j < 3; j++)
                if (frames[j] == -1) { pos = j; break; }
                else if (last[j] < last[pos]) pos = j;
            frames[pos] = pages[i];
            last[pos] = i + 1;
            faults++;
        }
    }
    printf("Total Page Faults: %d\n", faults);
    return 0;
}


Output:
Total Page Faults: 9
