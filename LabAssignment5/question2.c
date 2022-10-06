#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define read_end 0
#define write_end 0

int main(int argc, char const *argv[])
{
	int pipefd1[2]; int pipefd2[2];
	int status1; int status2;
	
	char string1[5] = "Hello";
	char string2[5] = "There";
	char string3[10];
	
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
	if(pid == 0)
	{
		//child pipe
		close(pipefd1[read_end]);
		close(pipefd2[write_end]);
		write(pipefd1[write_end], string2, sizeof(string2) + 1);
	
		read(pipefd2[read_end], string3, sizeof(string3));
		printf("The concatenated string sent is %s\n", string3);
	}
	else
	{
		//parent pipe
		close(pipefd1[write_end]);
		close(pipefd2[read_end]);
		read(pipefd1[read_end], string2, sizeof(string2));
		
		//concatenation
		int k = 0;
		for(int i = 0; i < 5; i = i+1)
		{
			string3[i] = string1[i];
		}
		
		for(int j = 5; j < 10; j = j+1)
		{
			string3[j] = string2[k];
			k = k+1;
		}
		
		write(pipefd2[write_end], string3, sizeof(string3)+1);
	}
	return 0;
}
			
