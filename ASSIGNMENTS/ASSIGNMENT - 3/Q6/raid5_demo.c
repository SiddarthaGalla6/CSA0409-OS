#include <stdio.h>
#include <string.h>
/* RAID 5 with 4 disks: 3 data blocks + 1 XOR parity block per stripe; rotate parity; fail one disk and rebuild. */
#define D 4
#define STRIPES 4
#define BS 8
unsigned char disk[D][STRIPES][BS];
int main(void)
{
    const char *msg = "BANK-RECORD-01;PATIENT-1002;WARD-7;DOSE-5MG;DOCTOR-RAO;TIME-0930;";
    size_t pos = 0, len = strlen(msg);
    for (int s = 0; s < STRIPES; s++) {
        int pd = (D - 1 - s % D);                       /* parity disk rotates */
        unsigned char par[BS] = {0};
        for (int d = 0; d < D; d++) {
            if (d == pd) continue;
            for (int b = 0; b < BS; b++) { unsigned char c = pos < len ? (unsigned char)msg[pos++] : ' '; disk[d][s][b] = c; par[b] ^= c; }
        }
        memcpy(disk[pd][s], par, BS);
        printf("stripe %d: parity on disk %d\n", s, pd);
    }
    unsigned char saved[STRIPES][BS]; int failed = 1;
    memcpy(saved, disk[failed], sizeof saved);
    memset(disk[failed], 0, sizeof disk[failed]);        /* disk 1 dies */
    printf("\nDisk %d failed. Rebuilding every block by XOR of the surviving disks...\n", failed);
    for (int s = 0; s < STRIPES; s++)
        for (int b = 0; b < BS; b++) { unsigned char x = 0; for (int d = 0; d < D; d++) if (d != failed) x ^= disk[d][s][b]; disk[failed][s][b] = x; }
    printf("Rebuilt data %s the original.\n", memcmp(saved, disk[failed], sizeof saved) ? "DOES NOT match" : "matches");
    printf("Reading back the text from the data blocks: ");
    for (int s = 0; s < STRIPES; s++) { int pd = (D - 1 - s % D); for (int d = 0; d < D; d++) if (d != pd) for (int b = 0; b < BS; b++) putchar(disk[d][s][b]); }
    printf("\n");
    return 0;
}
