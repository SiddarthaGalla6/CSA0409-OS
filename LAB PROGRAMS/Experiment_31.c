Code:
#include <stdio.h>
int main()
{
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int frames[3] = {-1,-1,-1}, pointer = 0, faults = 0, i, j, hit;
    for (i = 0; i < 13; i++)
    {
        hit = 0;
        for (j = 0; j < 3; j++)
            if (frames[j] == pages[i]) hit = 1;
        if (!hit)
        {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % 3;
            faults++;
        }
    }
    printf("Total Page Faults: %d\n", faults);
    return 0;
}


Output:
Total Page Faults: 10
