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
		printf("Fork Failed\n");
	}
	else if(pid == 0)
	{
		execvp("ls", args);
	}
	else
	{
		printf("Parent process\n");
		wait(NULL);
		printf("Parent waited for completion of child process\n");
	}
	
exit(0);
}	
	
