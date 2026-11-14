Code:
#include <stdio.h>
#include <sys/stat.h>
int main()
{
    char filename[] = "file.txt";
    mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if (chmod(filename, permissions) == 0)
        printf("File permissions changed successfully.\n");
    else
    {
        perror("chmod");
        return 1;
    }
    return 0;
}

Input:
Create a file named file.txt in the same folder before running.

Output:
File permissions changed successfully.
