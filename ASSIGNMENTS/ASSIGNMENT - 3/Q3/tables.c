#include <stdio.h>
/* Table sizes for a 32-bit process with code 64 KB, data 40 KB, stack 8 KB (4 KB pages). */
int main(void)
{
    int code = 64, data = 40, stack = 8, page = 4;
    int pages = (code + page - 1) / page + (data + page - 1) / page + (stack + page - 1) / page;
    printf("Pages needed: code %d + data %d + stack %d = %d\n", code / page, (data + 3) / page, stack / page, pages);
    printf("Pure paging, flat table : 2^20 entries x 4 B           = %d bytes (4 MB)\n", (1 << 20) * 4);
    printf("Pure paging, 2-level    : 1 directory + 3 tables x 4 KB = %d bytes\n", 4 * 1024 + 3 * 4 * 1024);
    printf("Pure segmentation       : 3 segments x 8 B (base+limit) = %d bytes\n", 3 * 8);
    printf("Segmented paging        : 3 segment entries x 8 B + %d page entries x 4 B = %d bytes\n", pages, 3 * 8 + pages * 4);
    return 0;
}
