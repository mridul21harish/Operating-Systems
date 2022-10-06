#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	char *args[] = {"/bin/ls", "-LR", NULL};
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("Fork failed\n");
	}
	else if(pid == 0)
	{
		execv("/bin/ls", args);
	}
	else
	{
		printf("Parent Process\n");
		wait(NULL);
		printf("Parent waited for completion of child process\n");
	}

exit(0);
}
