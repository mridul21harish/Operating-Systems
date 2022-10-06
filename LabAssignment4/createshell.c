#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

void history(char* cmd);

int main()
{
    	pid_t child;
    	char *command[2], *tok, *lineptr = NULL, *line;
    	size_t i; size_t n;
    	int status;
  
    	while (1)
    	{
        	printf("$ ");
        	
        	if (getline(&lineptr, &n, stdin) == -1)
            		break;
        	if (strncmp(lineptr, "exit", 4) == 0)
            		break;
        	
        	history(lineptr);
        	command[0] = strtok(lineptr, " \t\n\r");
        	command[1] = strtok(NULL, " \t\n\r");
        	
        	child = fork();
        	if (child == 0)
        	{
            		if (strncmp(command[0], "!", 1) == 0)
            		{
                		command[0][0] = '0';
                		int x = atoi(command[0]);
                		FILE* fp = fopen(".history", "r");
                		getline(&line, &i, fp);
                		while(x)
                		{
                    			getline(&line, &i, fp);
                    			printf("%s", line);
                    		x = x-1;
                		}
            		}
            		
            		if (strncmp(command[0], "cd", 2) == 0)
            		{
                		execl("/bin/sh", "cd", (const char *)0);
            		}
            		if (execlp(command[0], command[0], command[1], NULL))
            		{
                		perror("execlp");
                		exit(EXIT_FAILURE);
            		}
        	}
       	
       	if (child > 0)
            		wait(&status);
    	}
    	
    	putchar('\n');  
    	free(lineptr);
    	exit(status);
}

void history(char* cmd)
{
    FILE* curr = fopen("1.txt", "w");

    fputs(cmd, curr);

    fclose(curr);

    system("cp .history 2.txt");
    system("cat 1.txt 2.txt > .history");
    system("rm 1.txt 2.txt");
}
