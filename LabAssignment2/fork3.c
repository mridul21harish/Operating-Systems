#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main ()
{
	printf("This will be printed ? 1\n"); //pr1
	fork(); //A

	printf("This will be printed ? 2\n"); //pr2
	fork(); //B

	printf("This will be printed ? 3\n"); //pr3
	fork(); //C
	
	printf("This will be printed ? 4\n"); //pr4
	
	return 0;
}

