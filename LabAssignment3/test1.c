#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main() 
{ 
if (fork()) 
	*(int *) 0 = 22; 
}
