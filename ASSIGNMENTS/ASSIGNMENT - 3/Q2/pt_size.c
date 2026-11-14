#include <stdio.h>
/* Page-table size of a flat (single-level) table. */
static void calc(int va_bits, int page_kb, int entry_bytes)
{
    unsigned long long page = page_kb * 1024ULL;
    int offset_bits = 0; while ((1ULL << offset_bits) < page) offset_bits++;
    unsigned long long entries = 1ULL << (va_bits - offset_bits);
    unsigned long long bytes = entries * entry_bytes;
    printf("VA %2d bits, page %d KB: offset %2d bits, page number %2d bits, entries 2^%d = %llu, "
           "entry %d B -> table %llu bytes = %.2f MB = %.2f GB\n",
           va_bits, page_kb, offset_bits, va_bits - offset_bits, va_bits - offset_bits,
           entries, entry_bytes, bytes, bytes / 1048576.0, bytes / 1073741824.0);
}
int main(void)
{
    calc(32, 4, 4);
    calc(48, 4, 8);
    printf("\nMulti-level (x86-64, 4 levels of 512 entries, 8 B each): one table = %d bytes = 1 page\n", 512 * 8);
    printf("A tiny process (code, data, stack pages) needs at most 1 + 2 + 2 + 3 = 8 tables = %d KB\n"
           "instead of 512 GB, because unused parts of the address space get no tables.\n", 8 * 4);
    return 0;
}
