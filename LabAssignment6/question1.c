#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void *generate(void *number);

int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	if(argc < 2)
	{
		printf("This is not allowed\n");
		return 0;
	}
	
	int n = atoi(argv[1]);
	for(int i = 1;i <= n; i = i+1)
	{
		int *number = (int*)malloc(2*sizeof(int));
		int original_number = i; int remainder; int result=0;
		while(original_number != 0) 
		{
			remainder = original_number % 10;
			result += remainder * remainder * remainder;
			original_number /= 10;
		}
	
		number[0] = i; 
		number[1] = result;
		pthread_attr_init(&attr);
		pthread_create(&tid, NULL, generate, (void *)number);
		pthread_join(tid, NULL);
		free(number);
	}
	return 0;
}

void *generate(void *number)
{
	int *parameter = (int *)number;
	if(parameter[0] == parameter[1])
	{
		printf("%d\n", parameter[0]);
	}
	pthread_exit(0);
}
