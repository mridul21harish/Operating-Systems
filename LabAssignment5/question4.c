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
	
	char string1[24] = "mridulharishhsirahludirm";
	char string2[24]; 
	memset(string2, 0, sizeof(string2));
	char string3[24];
	memset(string3, 0, sizeof(string3));
	
	status1 == pipe(pipefd1);
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
		printf("The reversed string is %s\n", string2);
		
		int j = 0; int check = 1;
		for(int i = 0; i <= 9; i = i+1)
		{
			if(string2[i] != string1[i])
			{
				check = 0;
				break;
			}
			j = j+1;
		}
		if(check == 0)
		{
			printf("It is not a palindrome\n");
		}
		else
		{
			printf("It is a palindrome\n");
		}
	}
	else
	{
		//child pipe
		close(pipefd1[write_end]);
		close(pipefd2[read_end]);
		read(pipefd1[read_end], string2, sizeof(string2));
		
		int j = -1; int i = sizeof(string2)/sizeof(string2[0]) - 1;
		for(; i >= 0; i = i-1)
		{
			j = j+1;
			string3[j] = string2[i];
		}
		
		write(pipefd2[write_end], string3, sizeof(string3)+1);
	}
	return 0;
} 


