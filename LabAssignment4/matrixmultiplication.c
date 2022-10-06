#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<time.h>

void print(int a[][3]);
void input(int a[][3]);
void print(int a[][3]);
void multiply(int product[][3], int first[][3], int second[][3], int size);
int component(int pointer1, int pointer2, int first[][3], int second[][3], int size);

int main() 
{
	int first[3][3]; int second[3][3]; int product[3][3];
	
	printf("Enter the first matrix row by row :-\n");
	for (int i = 0; i < 3; i = i+1) 
  	{
		for (int j = 0; j < 3; j = j+1)
		{
      			scanf("%d", &first[i][j]);
      		}
  	}
  	
	printf("Enter the second matrix row by row :-\n");
	for (int i = 0; i < 3; i = i+1) 
  	{
		for (int j = 0; j < 3; j = j+1)
		{
      			scanf("%d", &second[i][j]);
      		}
  	}
  
  	multiply(product, first, second, 3);
  	
  	printf("The Product matrix is as below: \n");
  	print(product);
  	
 	return 0;
}

void multiply(int product[][3], int first[][3], int second[][3], int size) 
{
	for (int i = 0; i < size; i = i+1) 
	{
		for (int j = 0; j < size; j = j+1) 
		{
			int fd[2];          // this is the file descriptor array
			pipe(fd);
			if (fork() == 0)	//this is the child process	 
			{  
        			int prod = component(i, j, first, second, size);
        
        			close(fd[0]);				// Writing the Component Product value to the pipe 
        			write(fd[1], &prod, 10); 
        			close(fd[1]); 
        			exit(0);
      			} 
      			else		//this is the parent process 
      			{             
        			close(fd[1]); 				// Reading the Component Product value from the pipe
      				read(fd[0], &product[i][j], 10);	// Updating the Product matrix
        			close(fd[0]); 
      			} 
    		}
  	}
}

int component(int pointer1, int pointer2, int first[][3], int second[][3], int size) 
{
	int sum = 0;
  	for (int i = 0; i < size; i = i+1)
  	{
    		sum = sum + (first[pointer1][i] * second[i][pointer2]);
  	}
  	return sum;
}

void print(int a[][3]) 
{
  	for (int i = 0; i < 3; i++) 
  	{
    		for (int j = 0; j < 3; j = j+1)
    		{
      			printf("%d ", a[i][j]);
      		}
    		printf("\n");
  	}
  	printf("\n");
}
