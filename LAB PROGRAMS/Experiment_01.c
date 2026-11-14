Code:
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("Process creation failed\n");
        return 1;
    }
    if (pid == 0)
    {
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    }
    else
    {
        printf("Parent Process ID: %d\n", getpid());
        printf("Parent's Parent Process ID: %d\n", getppid());
    }
    return 0;
}

Output:
Child Process ID: 2452\nParent Process ID: 2451\nParent Process ID: 2451\nParent's Parent Process ID: 1800\n(Process IDs vary.)
