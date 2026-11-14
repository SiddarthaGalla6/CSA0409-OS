Code:
#include <stdio.h>
struct Employee { int id; char name[30]; float salary; };
int main()
{
    FILE *fp;
    struct Employee e;
    int choice;
    fp = fopen("employee.dat", "ab+");
    if (fp == NULL) return 1;
    do
    {
        printf("\n1.Add 2.Display by ID 3.Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            scanf("%d%29s%f", &e.id, e.name, &e.salary);
            fseek(fp, (e.id - 1) * sizeof(e), SEEK_SET);
            fwrite(&e, sizeof(e), 1, fp);
        }
        else if (choice == 2)
        {
            int id;
            scanf("%d", &id);
            fseek(fp, (id - 1) * sizeof(e), SEEK_SET);
            if (fread(&e, sizeof(e), 1, fp))
                printf("%d %s %.2f\n", e.id, e.name, e.salary);
            else printf("Employee not found\n");
        }
    } while (choice != 3);
    fclose(fp);
    return 0;
}

Input:
1
1
Siddu
25000
2
1
3

Output:
1.Add 2.Display by ID 3.Exit
1.Add 2.Display by ID 3.Exit
1 Siddu 25000.00
