#include <stdio.h>
/* Effective access time (EAT) for single-level paging. Times in ns. */
int main(void)
{
    const double mem = 100.0, tlb = 10.0;
    double no_tlb = mem + mem;                      /* page-table access + data access */
    printf("Memory access = %.0f ns, TLB look-up = %.0f ns\n", mem, tlb);
    printf("Without TLB (single-level): EAT = %.1f ns\n", no_tlb);
    printf("Without TLB (4-level, x86-64): EAT = %.1f ns\n\n", 5 * mem);
    printf("hit ratio   EAT (1-level)   EAT (4-level)   slow-down vs. no paging\n");
    double h[] = {0.0, 0.50, 0.80, 0.90, 0.95, 0.99, 1.00};
    for (int i = 0; i < 7; i++) {
        double e1 = h[i] * (tlb + mem) + (1 - h[i]) * (tlb + 2 * mem);
        double e4 = h[i] * (tlb + mem) + (1 - h[i]) * (tlb + 5 * mem);
        printf("%5.0f%%      %8.2f ns     %8.2f ns     %6.1f%%\n", h[i] * 100, e1, e4, (e1 - mem) / mem * 100);
    }
    return 0;
}
