#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	printf("A");
	fork(); //A
	
	printf("B");
	
	return 0;
}
