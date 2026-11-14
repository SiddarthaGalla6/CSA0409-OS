Code:
#include <stdio.h>
#include <string.h>
int main()
{
    char dirs[10][20], files[10][10][20], d[20], f[20];
    int counts[10] = {0}, nd = 0, choice, i, j, k;
    do
    {
        printf("\n1.Create Directory 2.Create File 3.List 4.Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Directory name: ");
            scanf("%19s", dirs[nd++]);
        }
        else if (choice == 2)
        {
            printf("Directory name and file name: ");
            scanf("%19s%19s", d, f);
            for (i = 0; i < nd; i++)
                if (strcmp(dirs[i], d) == 0)
                    strcpy(files[i][counts[i]++], f);
        }
        else if (choice == 3)
            for (i = 0; i < nd; i++)
            {
                printf("%s:\n", dirs[i]);
                for (j = 0; j < counts[i]; j++) printf("  %s\n", files[i][j]);
            }
    } while (choice != 4);
    return 0;
}

Input:
1
student
2
student
os.txt
3
4

Output:
1.Create Directory 2.Create File 3.List 4.Exit
Directory name: 
Directory name and file name: 
student:
  os.txt
