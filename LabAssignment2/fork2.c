#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	printf("OS\n");
	
	fork(); //A
	fork(); //B
	fork(); //C
	
	return 0;
}
