#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int pid1; int pid2; int pid3;
	
	pid1 = fork(); //creates 1 and 2
	if(pid1 < 0)
	{
		fprintf(stderr, "Failed fork call\n");
	}
	else if(pid1 == 0)
	{
		pid2 = fork(); //creates 2 and 4
		if(pid2 < 0)
		{
			fprintf(stderr, "Failed fork call\n");
		}
		else if(pid2 == 0)
		{
			fork(); //creates 4 and 8
		}
		else if(pid2 > 0)
		{
			fork(); //creates 2 and 5
			fork(); //creates 2 and 6, creates 5 and 9
		}
	}
	else if(pid1 > 0)
	{
		pid3 = fork(); //creates 1 and 3
		if(pid3 < 0)
		{
			fprintf(stderr, "Failed fork call\n");
		}
		else if(pid3 == 0)
		{
			fork(); //creates 3 and 7
		}
	}
	
	printf("This should be printed 9 times\n");
	return 0;
}
