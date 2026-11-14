#include <stdio.h>
/* Effective access time with page faults: EAT = (1-p)*mem + p*service. Times in ns. */
int main(void)
{
    const double mem = 100.0, service = 8e6;            /* 100 ns, 8 ms */
    double p[] = {1.0 / 1000, 1.0 / 100000, 1.0 / 1000000};
    const char *lab[] = {"1 in 1,000", "1 in 100,000", "1 in 1,000,000"};
    for (int i = 0; i < 3; i++) {
        double e = (1 - p[i]) * mem + p[i] * service;
        printf("p = %-15s EAT = %12.4f ns   slow-down = %10.1f x  (%.1f %% over %g ns)\n", lab[i], e, e / mem, (e - mem) / mem * 100, mem);
    }
    double pmax = (0.10 * mem) / (service - mem);        /* EAT <= 1.10 * mem */
    printf("\nFor a 10%% slow-down: EAT <= %.1f ns  ->  p <= %.3e  = 1 fault in %.0f accesses\n", 1.1 * mem, pmax, 1 / pmax);
    return 0;
}
