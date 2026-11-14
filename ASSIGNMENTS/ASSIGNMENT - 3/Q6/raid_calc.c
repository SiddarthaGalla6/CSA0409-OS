#include <stdio.h>
#include <math.h>
/* Usable capacity and data-loss probability for 6 disks of 4 TB. */
int main(void)
{
    int n = 6; double tb = 4.0;
    printf("Usable capacity of %d disks x %.0f TB (raw %.0f TB)\n", n, tb, n * tb);
    printf("  RAID 0  (striping)                 : %5.1f TB, survives 0 disk failures\n", n * tb);
    printf("  RAID 1  (all 6 disks mirrored)     : %5.1f TB, survives up to %d\n", tb, n - 1);
    printf("  RAID 1  (3 mirrored pairs, no stripe): %5.1f TB (same as RAID 10 capacity)\n", n / 2 * tb);
    printf("  RAID 5  (one parity)               : %5.1f TB, survives 1\n", (n - 1) * tb);
    printf("  RAID 6  (two parity)               : %5.1f TB, survives 2\n", (n - 2) * tb);
    printf("  RAID 10 (3 mirrored pairs, striped): %5.1f TB, survives 1 (up to 3 if in different pairs)\n\n", n / 2 * tb);

    double afr = 0.02, hours = 24.0;                    /* ASSUMPTIONS: 2 %% per disk per year, 24 h rebuild */
    double p = afr * hours / 8760.0;                    /* chance one given disk fails during the rebuild window */
    printf("Assumed annual failure rate = %.1f %%, rebuild time = %.0f h -> p(one disk fails in window) = %.3e\n", afr * 100, hours, p);
    printf("After ONE disk has already failed, probability of losing data during the rebuild:\n");
    printf("  RAID 1 (2-disk mirror): partner must fail      : %.3e\n", p);
    printf("  RAID 5 (6 disks)      : any of 5 others fails  : %.3e  (%.1f x RAID 1)\n", 1 - pow(1 - p, 5), (1 - pow(1 - p, 5)) / p);
    printf("  RAID 10 (3 pairs)     : only the partner       : %.3e\n", p);
    printf("  RAID 6 (6 disks)      : 2 more of 5 must fail  : %.3e\n", 10 * p * p);
    return 0;
}
