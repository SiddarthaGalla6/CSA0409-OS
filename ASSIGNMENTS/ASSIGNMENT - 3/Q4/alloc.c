#include <stdio.h>
/* Frame allocation: equal and proportional. 62 free frames, processes of 10 and 127 pages. */
int main(void)
{
    int m = 62, s[2] = {10, 127}, S = s[0] + s[1];
    printf("m = %d frames, process sizes %d and %d pages (S = %d)\n", m, s[0], s[1], S);
    printf("Equal allocation       : %d frames each\n", m / 2);
    for (int i = 0; i < 2; i++)
        printf("Proportional, process %d : a = %d/%d x %d = %.2f -> %d frames\n", i + 1, s[i], S, m, (double)s[i] / S * m, (int)((double)s[i] / S * m));
    return 0;
}
