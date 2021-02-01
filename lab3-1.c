#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid, ppid;

	pid = fork();

	if (pid == -1)
	{
    		return 1;
	}

 	else if (pid == 0)
	{
    		printf("Child, pid = %d\n", getpid());
	}

 	else
	{
		printf("Parent, ppid = %d\n", getppid());
	}
	return 0;
}
