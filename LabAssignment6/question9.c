#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>

struct key_value
{
	int key;
	int value;
};

int fib(int n);
void *runner(void *param);

int main()
{
	int range;
	printf("Enter the number of fibonacci numbers to generate : \n");
	scanf("%d", &range);
	
	struct key_value *generate = (struct key_value*)malloc(range*sizeof(struct key_value));
	
	pthread_t tid[range];
	
	printf("The generated Fibonacci series of %d terms is\n", range);
	for(int i = 0; i < range; i = i+1)
	{
		generate[i].key = i;
		pthread_create(&tid[i], NULL, runner, &generate[i]);
		pthread_join(tid[i], NULL);
	}
	
	for(int i = 0; i < range; i = i+1)
	{
		printf("%d\n", generate[i].value);
	}
	
	return 0;
}

int fib(int n)
{
	if(n == 0 || n ==1)
	{
		return n;
	}
	else
	{
		return fib(n-1) + fib(n-2);
	}
}

void *runner(void *param)
{
	struct key_value *temporary = (struct key_value*)param;
	temporary -> value = fib(temporary -> key);
	pthread_exit(NULL);
}
	
