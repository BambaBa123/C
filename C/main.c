#include <sys/types.h>
#include <sys/wait.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
 
int main(void)
{
    pid_t pid;
 
    if ((pid = fork()) < 0)
        return EXIT_FAILURE;
    else if (pid == 0)
        execl("script.bash", "script.bash", (char *)0);
 
    wait(NULL);
    return EXIT_SUCCESS;
}