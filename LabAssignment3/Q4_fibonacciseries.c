#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>

void prime(int n);
int fib(int n);
void fibgen(int n);

int main()
{
	int n;
	printf("Enter the number of terms to be generated: ");
	fflush(stdin);
	scanf("%d", &n);
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("Fork Failed\n");
	}
	else if(pid == 0)
	{
		fibgen(n);
	}
	else
	{
		wait(NULL);
		prime(n);
	}
	
exit(0);
}

void prime(int n)
{
	int flag;
	
	printf("The set of first 'n' prime number are { ");
	
	for(int i = 1; i <= n; i = i+1)
	{
		if(i == 1 || i == 0)
		{
			continue;
		}
		
		flag = 1;
		
		for(int j = 2; j <= sqrt(i); ++j)
		{
			if(i % j == 0)
			{
				flag = 0;
				break;
			}
		}
		
		if(flag == 1)
		{
			printf("%d, ", i);
		}
	}
		
	printf("\b\b }\n");
}
	
int fib(int n)
{
	if(n <= 1)
		return n;
		
	return fib(n-1) + fib(n-2);
}

void fibgen(int n)
{
	printf("The set of first 'n' fibonacci series numbers are { ");
	
	for(int i = 0; i < n; i = i+1)
	{
		printf("%d, ", fib(i + 1));
	}
	printf("\b\b }\n");
} 	

