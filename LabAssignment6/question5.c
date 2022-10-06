#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>

#define MAX 512

int a[MAX];
int n; 

int cmpfunc(const void *a, const void *b);
void *mean(void *param);
void *median(void *param);
void *mode(void *param);

int main(int argc, char const *argv[])
{
	if(argc < 2)
	{
		printf("This is not allowed\n");
	}
	
	n = argc - 1;
	for(int i = 0; i < n; i = i+1)
	{
		a[i] = atoi(argv[i+1]);
	}
	
	pthread_t tid[3];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_create(&tid[0], &attr, mean, NULL);
	pthread_create(&tid[1], &attr, median, NULL);
	pthread_create(&tid[2], &attr, mode, NULL);
	
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	
	return 0;
}

int cmpfunc(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

void *mean(void *param)
{
	int temp[n];
	for(int i = 0; i < n; i = i+1)
	{
		temp[i] = a[i];
	}
	
	float mean;
	
	for(int i = 0; i < n; i = i+1)
	{
		mean = mean + temp[i];
	}
	
	mean = mean/n;
	
	printf("\nMean = %f\n", mean);
	pthread_exit(NULL);
}

void *median(void *param)
{
	int temp[n];
	for(int i = 0; i < n; i = i+1)
	{
		temp[i] = a[i];
	}
	
	qsort(temp, n, sizeof(int), cmpfunc);
	
	int median;
	if(n%2 == 1)
	{
		median = temp[(n - 1)/2];
	}
	else
	{
		median = (temp[n/2] + temp[n/2 - 1])/2;
	}
	
	printf("\nMedian = %d\n", median);
	pthread_exit(NULL);
}

void *mode(void *param)
{
	int temp[n];
	for(int i = 0; i < n; i = i+1)
	{
		temp[i] = a[i];
	}
	
	int mode;
	int max_count;
	for(int i = 0; i < n; i = i+1)
	{
		int count = 0;
		for(int j = 0; j < n; j = j+1)
		{
			if(temp[j] == temp[i])
			{
				count = count + 1;
			}
		}
		if(count > mode)
		{
			max_count = count;
			mode = temp[i];
		}
	}
	
	printf("\nMode = %d\n", mode);
	pthread_exit(NULL);
}	
	
