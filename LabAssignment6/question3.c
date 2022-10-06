#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#include<unistd.h>

int a[100]; int position = -1;

struct data
{
	int begin;
	int end;
	int m;
};

void *runner(void *param);
void print(int x);

int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		printf("This is not allowed\n");
	}
	else
	{
		int n = argc - 2;
		//printf("n = %d",n);
		for(int j = 0; j < n; j = j+1)
		{
			a[j] = atoi(argv[j+2]);
		}
	
		for(int k = 0; k < n; k = k+1)
		{
			 for(int l = 0; l < n-k-1; l = l+1)
			 {
			 	if(a[l] > a[l+1])
			 	{
			 		int temp = a[l];
			 		a[l] = a[l+1];
			 		a[l+1] = temp;
			 	}
			 }
		}
		
		printf("The sorted sequence is :-\n");
		for(int o = 0; o < n; o = o+1)
		{
			printf("%d ", a[o]);
		}
		printf("\n");
		
		//printf("n = %d\n",n);
		
		struct data param[4];
		param[0].begin = 0;
		param[0].end = n/4 - 1;
		param[0].m = atoi(argv[1]);
		param[1].begin = n/4;
		param[1].end = n/2 -1;
		param[1].m = atoi(argv[1]);
		param[2].begin = n/2;
		param[2].end = 3*n/4 - 1;
		param[2].m = atoi(argv[1]);
		param[3].begin = 3*n/4;
		param[3].end = n-1;		
		param[3].m = atoi(argv[1]);
		
		pthread_t tid[4];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		
		for(int p = 0; p < 4; p = p+1)
		{
			pthread_create(&tid[p], &attr, runner, &param[p]);
		}
		
		for(int q = 0; q < 4; q = q+1)
		{
			pthread_join(tid[q], NULL);
		}
		
		if(position > -1)
		{
			print(atoi(argv[1]));
		}
		else
		{
			printf("\n%d not found\n", atoi(argv[1]));
		}
		
		printf("\n");
	}
}

void *runner(void *param)
{
	struct data *dm = param;
	int begin = dm -> begin;
	int end = dm -> end;
	int m = dm -> m;
	//printf("begin = %d, end = %d, m = %d\n",begin, end, m);
	if(begin < end)
	{
		int mid = (begin + end)/2;
		
		if(a[mid] = m)
		{
			position = mid;
		}
		else
		{	
			pthread_t tid;
			pthread_attr_t attr;
			pthread_attr_init(&attr);
		
			struct data param;
			param.m = m;
		
			if(m < a[mid])
			{
				param.begin = begin;
				param.end = mid;
			}
			else if(m > a[mid])
			{
				param.begin = mid + 1;
				param.end = end;
			}
		
			pthread_create(&tid, &attr, runner, &param);
			pthread_join(tid, NULL);
		}
	}
	pthread_exit(0);
}

void print(int x)
{
	printf("%d is found at indice = ", x);
	
	int left_end = 0;
	while(left_end >= 0)
	{
		if(a[position - left_end] == x)
		{
			printf("%d ", position - left_end);
			left_end = -1;
		}
		else
		{
			left_end = left_end - 1;
		}
	}
	
	int right_end = 1;
	while(right_end >= 1)
	{
		if(a[position + right_end] == x)
		{
			printf("%d ", position - right_end);
			right_end =  -1;
		}
		else
		{
			right_end = right_end - 1;
		}
	}
}



		 
