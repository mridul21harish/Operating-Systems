#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	int n;
	printf("Enter the number of elements in the series : ");
	fflush(stdin);
	scanf("%d", &n);
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("Fork Failed\n");
	}
	else if(pid == 0)
	{
		printf("\nChild process\n");
		printf("Even number : \n");
		
		for(int i = 0; i < n; i = i+2)
		{
			printf("%d\t", i);
		}
		printf("\n");
	}
	else
	{
		wait(NULL);
		printf("\nParent Process\n");
		printf("Odd numbers : \n");
		
		for(int i = 1; i < n; i = i+2)
		{
			printf("%d\t", i);
		}
		printf("\n");
	}
exit(0);
}
