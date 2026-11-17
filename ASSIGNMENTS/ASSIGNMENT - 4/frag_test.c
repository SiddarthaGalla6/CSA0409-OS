#include <stdio.h>
#include <string.h>

#define BLOCKS 32

char disk[BLOCKS];                         /* '.' = free, otherwise the file letter */

/* Contiguous allocation, first fit: returns the start block or -1. */
int alloc_contiguous(char file, int size)
{
    int run = 0;                           /* length of the current run of free blocks */
    for (int b = 0; b < BLOCKS; b++) {
        if (disk[b] == '.') {
            run++;
            if (run == size) {             /* first run that is long enough */
                int start = b - size + 1;
                for (int i = start; i <= b; i++) disk[i] = file;
                return start;
            }
        } else {
            run = 0;                       /* an occupied block breaks the run */
        }
    }
    return -1;                             /* no run is long enough */
}

/* Indexed allocation: one index block plus any free data blocks. */
int alloc_indexed(char file, int size, int index[])
{
    int got = 0, idx = -1;
    for (int b = 0; b < BLOCKS && got <= size; b++) {
        if (disk[b] != '.') continue;
        if (idx < 0) idx = b;              /* first free block holds the index */
        else index[got++] = b;
        if (got == size) break;
    }
    if (idx < 0 || got < size) return -1;
    disk[idx] = (char)(file + 32);         /* lowercase letter = index block */
    for (int i = 0; i < size; i++) disk[index[i]] = file;
    return idx;
}

void release(char file)
{
    for (int b = 0; b < BLOCKS; b++) if (disk[b] == file) disk[b] = '.';
}

int main(void)
{
    memset(disk, '.', BLOCKS);
    alloc_contiguous('A', 6);
    alloc_contiguous('B', 8);
    alloc_contiguous('C', 5);
    alloc_contiguous('D', 7);
    release('B');
    release('D');
    int free_blocks = 0, longest = 0, run = 0;
    for (int b = 0; b < BLOCKS; b++) {
        if (disk[b] == '.') { free_blocks++; run++; if (run > longest) longest = run; }
        else run = 0;
    }
    printf("%.32s\n", disk);
    printf("free blocks = %d, longest free run = %d\n", free_blocks, longest);
    for (int size = 10; size <= 21; size += 5) {
        char saved[BLOCKS];
        memcpy(saved, disk, BLOCKS);
        int c = alloc_contiguous('E', size);
        memcpy(disk, saved, BLOCKS);
        int index[32];
        int ib = alloc_indexed('E', size, index);
        printf("E (%2d blocks): contiguous start %2d | indexed index block %2d\n", size, c, ib);
        memcpy(disk, saved, BLOCKS);
    }
    return 0;
}
