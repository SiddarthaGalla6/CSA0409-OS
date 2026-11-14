#include <stdio.h>
#define PAGE_SIZE 4096
#define PAGES 8
int page_table[PAGES] = {5, 2, -1, 7, 0, -1, 3, 9};
static void tr(unsigned a, const char *why)
{
    unsigned p = a / PAGE_SIZE, d = a % PAGE_SIZE;
    printf("%-26s addr %6u -> page %u offset %4u : ", why, a, p, d);
    if (p >= PAGES) printf("invalid address (trap to OS)\n");
    else if (page_table[p] < 0) printf("page fault\n");
    else printf("physical %u\n", (unsigned)page_table[p] * PAGE_SIZE + d);
}
int main(void)
{
    tr(0, "start of page 0");
    tr(4095, "end of page 0");
    tr(4096, "start of page 1");
    tr(8191, "end of page 1");
    tr(8192, "start of page 2 (absent)");
    tr(28672, "start of last page 7");
    tr(32767, "end of last page 7");
    tr(32768, "beyond last page");
    return 0;
}
