#include <stdio.h>
/* Segment table: base and limit (classic textbook example). */
struct seg { unsigned base, limit; const char *name; };
struct seg table[5] = {
    {1400, 1000, "code"}, {6300, 400, "stack"}, {4300, 400, "data"},
    {3200, 1100, "heap"}, {4700, 1000, "library"}
};
int main(void)
{
    unsigned t[8][2] = {{0, 53}, {0, 999}, {1, 0}, {2, 399}, {3, 852}, {4, 1222}, {2, 500}, {5, 10}};
    printf("%-9s %-8s %-9s result\n", "(seg,off)", "segment", "limit");
    for (int i = 0; i < 8; i++) {
        unsigned s = t[i][0], o = t[i][1];
        printf("(%u,%4u)  ", s, o);
        if (s >= 5) { printf("%-8s %-9s TRAP: invalid segment number\n", "-", "-"); continue; }
        printf("%-8s %-9u ", table[s].name, table[s].limit);
        if (o >= table[s].limit) printf("TRAP: offset %u >= limit %u (addressing error)\n", o, table[s].limit);
        else printf("physical = %u + %u = %u\n", table[s].base, o, table[s].base + o);
    }
    return 0;
}
