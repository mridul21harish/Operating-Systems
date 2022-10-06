#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define read_end 0
#define write_end 1

int main(int argc, char const *argv[])
{
	int pipefd1[2]; int pipefd2[2];
	int status1; int status2;
	
	char string1[12] = "MridulHarish";
	char string2[12];
	char string3[12]; 
	memset(string3, 0, sizeof(string3));
	
	status1 = pipe(pipefd1);
	if(status1 == -1)
	{
		printf("Pipe failed\n");
		return 0;
	}
	
	status2 = pipe(pipefd2);
	if(status2 == -1)
	{
		printf("Pipe failed\n");
		return 0;
	}
	
	pid_t pid = fork();
	if(pid > 0)
	{
		//parent pipe
		close(pipefd1[read_end]);
		close(pipefd2[write_end]);
		
		printf("The original string is %s\n", string1);
		write(pipefd1[write_end], string1, sizeof(string1)+1);
		
		read(pipefd2[read_end], string2, sizeof(string2));
		printf("The substring by the child is %s\n", string2);
	}
	else
	{
		//child pipe
		close(pipefd1[write_end]);
		close(pipefd2[read_end]);
		
		read(pipefd1[read_end], string2, sizeof(string2));
		for(int i = 0; i < 3; i = i+1)
		{
			string3[i] = string2[3+i];
		}
		write(pipefd2[write_end], string3, sizeof(string3)+1);
	}
	return 0;
}	  

