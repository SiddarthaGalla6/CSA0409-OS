Code:
#include <stdio.h>
#include <string.h>
int main()
{
    char files[20][30], name[30];
    int n = 0, choice, i, found;
    do
    {
        printf("\n1.Create 2.List 3.Delete 4.Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter filename: ");
            scanf("%29s", name);
            strcpy(files[n++], name);
        }
        else if (choice == 2)
        {
            for (i = 0; i < n; i++) printf("%s\n", files[i]);
        }
        else if (choice == 3)
        {
            printf("Enter filename: ");
            scanf("%29s", name);
            found = 0;
            for (i = 0; i < n; i++)
                if (strcmp(files[i], name) == 0)
                {
                    for (; i < n - 1; i++) strcpy(files[i], files[i + 1]);
                    n--; found = 1; break;
                }
            printf(found ? "File deleted\n" : "File not found\n");
        }
    } while (choice != 4);
    return 0;
}

Input:
1
notes.txt
2
4

Output:
1.Create 2.List 3.Delete 4.Exit
Enter filename: 
1.Create 2.List 3.Delete 4.Exit
notes.txt
