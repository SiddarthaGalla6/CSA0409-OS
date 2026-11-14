Code:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Block { char data[100]; struct Block *next; };
int main()
{
    struct Block *first = NULL, *last = NULL, *p, *newBlock;
    char choice;
    int n, i;
    do
    {
        printf("W to write, R to read, Q to quit: ");
        scanf(" %c", &choice);
        if (choice == 'W' || choice == 'w')
        {
            newBlock = (struct Block *)malloc(sizeof(struct Block));
            printf("Enter data: ");
            scanf(" %99[^\n]", newBlock->data);
            newBlock->next = NULL;
            if (first == NULL) first = newBlock;
            else last->next = newBlock;
            last = newBlock;
        }
        else if (choice == 'R' || choice == 'r')
        {
            printf("Block number: ");
            scanf("%d", &n);
            p = first;
            for (i = 1; p != NULL && i < n; i++) p = p->next;
            if (p) printf("Block data: %s\n", p->data);
            else printf("Block not found\n");
        }
    } while (choice != 'Q' && choice != 'q');
    while (first)
    {
        p = first;
        first = first->next;
        free(p);
    }
    return 0;
}

Input:
W
First block
W
Second block
R
2
Q

Output:
W to write, R to read, Q to quit: Enter data: W to write, R to read, Q to quit: Enter data: W to write, R to read, Q to quit: Block number: Block data: Second block
