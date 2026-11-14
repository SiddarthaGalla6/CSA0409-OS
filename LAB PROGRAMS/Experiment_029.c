Code:
#include <stdio.h>
int mutex = 1, full = 0, empty = 5, item = 0;
void producer()
{
    if (mutex == 1 && empty > 0)
    {
        mutex = 0; item++; full++; empty--;
        printf("Producer produces item %d\n", item);
        mutex = 1;
    }
    else printf("Buffer is full\n");
}
void consumer()
{
    if (mutex == 1 && full > 0)
    {
        mutex = 0;
        printf("Consumer consumes item %d\n", item);
        item--; full--; empty++;
        mutex = 1;
    }
    else printf("Buffer is empty\n");
}
int main()
{
    int choice;
    do
    {
        printf("1.Producer 2.Consumer 3.Exit\n");
        scanf("%d", &choice);
        if (choice == 1) producer();
        if (choice == 2) consumer();
    } while (choice != 3);
    return 0;
}

Input:
1
2
3

Output:
1.Producer 2.Consumer 3.Exit
Producer produces item 1
1.Producer 2.Consumer 3.Exit
Consumer consumes item 1
