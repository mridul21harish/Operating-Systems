#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>

int main()
{
	int begin; int end;
	printf("Enter the beginning of the range : ");
	fflush(stdin);
	scanf("%d", &begin);
	printf("Enter the ending of the range : ");
	fflush(stdin);
	scanf("%d", &end);
	
	int n = end - begin + 1;
	int temp; int count = 0; int digit;
	int a[n];
	
	for(int i = 0; i < n; i = i+1)
	{
		a[i] = 0;
	}
	
	pid_t pid = vfork();
	
	if(pid < 0)
	{
		printf("Fork failed\n");
	}
	else if(pid == 0)
	{
		for(int i = begin; i < end + 1; i = i+1)
		{
			temp = i;
			while(temp != 0)
			{
				temp /= 10;
				count = count + 1;
			}
			
			temp = i;
			while(temp != 0)
			{
				digit = temp % 10;
				temp /= 10;
				a[i - begin] += pow(digit, count);
			}
			count = 0;
		}
	}
	else
	{
		wait(NULL);
		printf("Set of Armstrong numbers between %d and %d are {", begin, end);
		for(int i = begin; i < end + 1; i = i+1)
		{
			if(a[i - begin] == i)
			{	
				printf("%d, ", i);
			}	
		}
	printf("\b\b }\n");
	}
exit(0);
} 


