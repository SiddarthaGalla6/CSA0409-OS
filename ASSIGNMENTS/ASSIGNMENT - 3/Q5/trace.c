#include <stdio.h>
/* Step-by-step FIFO and LRU trace (3 frames) for hand verification. */
int main(void)
{
    int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}, len = 20, F = 3;
    for (int alg = 0; alg < 2; alg++) {
        int f[3] = {-1, -1, -1}, last[3] = {-1, -1, -1}, next = 0, faults = 0;
        printf("%s, %d frames\n ref | frames     | result\n", alg ? "LRU" : "FIFO", F);
        for (int i = 0; i < len; i++) {
            int k = -1; for (int j = 0; j < F; j++) if (f[j] == ref[i]) k = j;
            const char *res = "hit";
            if (k >= 0) last[k] = i;
            else {
                faults++; res = "FAULT";
                int v = -1; for (int j = 0; j < F; j++) if (f[j] < 0) { v = j; break; }
                if (v < 0) {
                    if (!alg) { v = next; next = (next + 1) % F; }
                    else { v = 0; for (int j = 1; j < F; j++) if (last[j] < last[v]) v = j; }
                }
                f[v] = ref[i]; last[v] = i;
            }
            printf("  %d  | ", ref[i]);
            for (int j = 0; j < F; j++) { if (f[j] < 0) printf("- "); else printf("%d ", f[j]); }
            printf("    | %s\n", res);
        }
        printf("Total faults = %d\n\n", faults);
    }
    return 0;
}
