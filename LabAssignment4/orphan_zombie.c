#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main() 
{ 
	  
    	pid_t pid = fork(); 
  
    	if (pid > 0)
    	{ 
        	printf("IN PARENT PROCESS\nMY PROCESS ID : %d\n", getpid());
        }  
    	else if (pid == 0) 
    	{ 
        	sleep(5); 
        	pid_t pid = fork(); 
	} 
	 
	if (pid > 0) 
	{ 
   		printf("IN CHILD PROCESS\nMY PROCESS ID :%d\n PARENT PROCESS ID : %d\n", getpid(), getppid()); 
   
 	while(1) 
     		sleep(1); 
  
   	printf("IN CHILD PROCESS\nMY PARENT PROCESS ID : %d\n", getppid()); 
        }   
        else if (pid == 0)
	{ 
            	printf("IN CHILD'S CHILD PROCESS\n MY PARENT ID : %d\n", getppid()); 
	} 
  
    	return 0; 
} 

 
