#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		execl("/bin/ls", "ls", NULL);
	}
	else
	{
		wait(NULL);
		printf("Parent process gets the control\n");
		printf("Parent has waited for Child to complete\n");
	}
}
