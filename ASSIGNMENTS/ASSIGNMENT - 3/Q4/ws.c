#include <stdio.h>
/* Working-set size WSS(t, delta) = number of distinct pages among the last delta references. */
int main(void)
{
    int r[] = {1,2,1,3,2,1,2,3,1,2,   7,8,9,7,8,9,7,8,9,7,   1,2,3,1,2,3,4,5,6,7};
    int len = 30, delta = 5;
    printf("window delta = %d references\n  t : page  WSS\n", delta);
    int max = 0;
    for (int t = 0; t < len; t++) {
        int seen[16] = {0}, w = 0;
        for (int k = t; k > t - delta && k >= 0; k--) if (!seen[r[k]]) { seen[r[k]] = 1; w++; }
        if (w > max) max = w;
        printf("%3d : %4d  %3d\n", t + 1, r[t], w);
    }
    printf("Maximum WSS = %d frames\n", max);
    return 0;
}
