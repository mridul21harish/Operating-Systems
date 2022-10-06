#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void *generate(void *number);

int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	
	if (argc<2)
	{
		printf("This is not allowed\n");
		return 0;
	}
	
	int n = argc-1;
	int *number = (int *)malloc((n+1)*sizeof(int));
	
	for(int i = 1; i < argc; i = i+1)
	{
		number[i] = atoi(argv[i]);
	}
	
	number[0] = n;
	pthread_attr_init(&attr);
	pthread_create(&tid ,NULL, generate, (void *)number);
	pthread_join(tid,NULL);
	
	n = n+1;
	printf("Ascending order\n");
	for(int i = 1; i < n; i = i+1)
	{
		for(int j = i+1; j < n; j = j+1 )
		{
			if(number[j] < number[i])
			{
				int t = number[i];
				number[i] = number[j];
				number[j] = t;
			}
		}
	}
	
	for(int i = 1; i < n; i = i+1)
	{
		printf("%d ",number[i]);
	}
	
	printf("\n");
	
	free(number);
	return 0;
}

void *generate(void *number)
{
	int *parameter = (int *)number;
	int n = parameter[0];
	n = n+1;
	
	printf("Descending order\n");
	for(int i = 1; i < n; i = i+1)
	{
		for (int j = i+1; j < n; j = j+1 )
		{
			if(parameter[i] < parameter[j])
			{
				int t = parameter[i];
				parameter[i] = parameter[j];
				parameter[j] = t;
			}
		}
	}
	
	for(int i = 1;i < n;i = i+1)
	{
		printf("%d ", parameter[i]);
	}
	printf("\n");
	
	pthread_exit(0);
}
