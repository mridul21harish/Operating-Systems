#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>

void *runner(void *param);

int main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		printf("This is not allowed\n");
	}
	else
	{
		int count = atoi(argv[1]);
		pthread_t tid[count*2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		
		for(int i = 1; i <= count; i = i+1)
		{
			pthread_create(&tid[i], &attr, runner, &i);
			pthread_join(tid[i], NULL);
		}
	}
	return 0;
}

void *runner(void *param)
{
	int n = *((int *)param);
	int j; int flag = 1;
		
	if(n <= 1)
	{
		flag = 0;
	}
	else if(n == 2)
	{
		flag = 1;
	}
	else
	{
		for(int j = 2; j <= sqrt(n); j = j+1)
		{
			if(n%j == 0)
			{
				flag = 0;
				break;
			}
		}
	}

	if(flag == 1)
	{
		printf("%d\n", n);
	}
} 
