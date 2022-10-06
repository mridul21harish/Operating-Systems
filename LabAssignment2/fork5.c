#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	printf("OS ");

	fork(); //A
	fork(); //B
	fork(); //C

	return 0;
}
