#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	int n; int x;
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
		x = 0;
		printf("\nChild process\n");
		printf("Even number sum: ");
		
		for(int i = 1; i < n; i = i+2)
		{
			x = x+i;
		}
		
		printf("%d\t", x);
		printf("\n");
	}
	else
	{
		wait(NULL);
		x = 0;
		printf("\nParent Process\n");
		printf("Odd number sum : ");
		
		for(int i = 1; i < n; i = i+2)
		{
			x = x+i;
		}
		
		printf("%d\t", x);
		printf("\n");
	}
exit(0);
}
