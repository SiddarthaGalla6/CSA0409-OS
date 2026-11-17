#include <stdio.h>
#include <stdlib.h>
static int cmp(const void *a, const void *b) { return *(const int *)a - *(const int *)b; }
int main(void)
{
    int req[8] = {98, 183, 37, 122, 14, 124, 65, 67}, head = 53, N = 8;
    int s[8]; for (int i = 0; i < N; i++) s[i] = req[i];
    qsort(s, N, sizeof s[0], cmp);
    int pos = head, total = 0;
    printf("LOOK   %d", head);
    for (int i = N - 1; i >= 0; i--) if (s[i] < head) { printf(" %d", s[i]); total += abs(s[i] - pos); pos = s[i]; }
    for (int i = 0; i < N; i++) if (s[i] > head) { printf(" %d", s[i]); total += abs(s[i] - pos); pos = s[i]; }
    printf(" -> %d cylinders\n", total);
    pos = head; total = 0; int jump = 0;
    printf("C-LOOK %d", head);
    for (int i = 0; i < N; i++) if (s[i] > head) { printf(" %d", s[i]); total += abs(s[i] - pos); pos = s[i]; }
    jump = abs(pos - s[0]); pos = s[0];
    for (int i = 0; i < N; i++) if (s[i] < head) { printf(" %d", s[i]); total += abs(s[i] - pos); pos = s[i]; }
    printf(" -> %d cylinders (+%d for the jump = %d)\n", total, jump, total + jump);
    return 0;
}
