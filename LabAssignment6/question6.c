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
int q_sort[MAX];
int m_sort[MAX];

struct data
{
	int begin;
	int end;
};

int partition(int begin, int end);
void *quicksort(void *arg1);
void merge_array(int begin, int mid, int end);
void *mergesort(void *arg2);

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("This is not allowed\n");
	}
	else
	{
		int n = argc - 1;
		for(int i = 0; i < n; i = i+1)
		{
			q_sort[i] = atoi(argv[i + 1]);
			m_sort[i] = atoi(argv[i + 1]);
		}
	
		struct data param;
		param.begin = 0;
		param.end = n - 1;
	
		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
	
		pthread_create(&tid[0], &attr, mergesort, &param);
		pthread_create(&tid[1], &attr, quicksort, &param);
		
		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
	
		printf("Sorted array using Merge sort is : ");
		for(int i = 0; i < n; i = i+1)
		{
			printf("%d ", m_sort[i]);
		}
		
		printf("\n");
	
		printf("Sorted array using Quick sort is : ");
		for(int i = 0; i < n; i = i+1)
		{
			printf("%d ", q_sort[i]);
		}
	
		printf("\n");
	}
}

int partition(int begin, int end)
{
	int i = begin; int j = end;
	int p = begin;
	int val = p;
	
	while(i < j)
	{
		while(q_sort[p] >= q_sort[i] && i < end)
		{
			i = i+1;
		}
		
		while(q_sort[p] < q_sort[j] && j > begin)
		{
			if(j == p+1 && i <=p)
			{
				j = p-1;
			}
			else
			{
				j = j-1;
			}
		}
		
		if(i < j)
		{
			int temp = q_sort[i];
			q_sort[i] = q_sort[j];
			q_sort[j] = temp;
		}
	}
	
	int temp = q_sort[p];
	q_sort[p] = q_sort[j];
	q_sort[j] = temp;
	val = j;
	
	return val;
}

void *quicksort(void *arg1)
{
	struct data *temp = arg1;
	int begin = temp -> begin;
	int end = temp -> end;
	
	if(begin < end)
	{
		int j = partition(begin, end);
		
		struct data left;
		left.begin = begin;
		left. end = j-1;
		
		struct data right;
		right.begin = j+1;
		right.end = end;
		
		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		
		pthread_create(&tid[0], &attr, quicksort, &left);
		pthread_create(&tid[1], &attr, quicksort, &right);
		
		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
	}
	pthread_exit(0);
}

void merge_array(int begin, int mid, int end)
{
	int n1 = mid - begin + 1;
	int n2 = end - mid;
	
	int L[n1]; int R[n2];
	
	for(int i = 0; i < n1; i = i+1)
	{
		L[i] = m_sort[begin + i];
	}
	for(int j = 0; j < n2; j = j+1)
	{
		R[j] = m_sort[mid + 1 + j];
	}
	
	int i = 0; int j = 0; int k = begin;
	while(i < n1 && j < n2)
	{
		if(L[i] <= R[j])
		{
			m_sort[k] = L[i];
			i = i+1;
		}
		else
		{
			m_sort[k] = R[j];
			j = j+1;
		}
		k = k+1;
	}
	
	while(i < n1)
	{
		m_sort[k] = L[i];
		i = i+1;
		k = k+1;
	}
	while(j < n2)
	{
		m_sort[k] = R[j];
		j = j+1;
		k = k+1;
	}
}

void *mergesort(void *arg2)
{
	struct data *temp = arg2;
	int begin = temp -> begin;
	int end = temp -> end;
	
	if(begin < end)
	{
		int mid = (begin + end)/2;
		
		struct data left;
		left.begin = begin;
		left. end = mid;
		
		struct data right;
		right.begin = mid+1;
		right.end = end;
		
		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		
		pthread_create(&tid[0], &attr, mergesort, &left);
		pthread_create(&tid[1], &attr, mergesort, &right);
		
		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
		
		merge_array(begin, mid, end);
	}
	pthread_exit(0);
}	 
