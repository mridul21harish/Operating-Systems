#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>

void bubsort(int n, int *array, bool comp(const void* , const void*));
bool asc(const void* a, const void* b);
bool desc(const void* a, const void* b);
void print(int n, int* array);
void swap(int* x, int *y);

int main()
{
	int n; int mid; int x = 0;
	printf("Enter the number of elements: ");
	fflush(stdin);
	scanf("%d", &n);
	mid = n/2;
	int a1[mid]; int a2[n - mid];
	
	for(int i = 0; i < mid; i = i+1)
	{
		printf("Enter number %d: ", ++x);
		fflush(stdin);
		scanf("%d", &a1[i]);
	}
	
	for(int i = 0; i < n - mid; i = i+1)
	{
		printf("Enter number %d: ", ++x);
		fflush(stdin);
		scanf("%d", &a2[i]);
	}
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("Fork failed\n");
	}
	else if(pid == 0)
	{
		printf("\nAscending sort of the first half\n");
		pid_t child = vfork();
		
		if(child < 0)
		{
			printf("Fork Failed\n");
		}
		else if(child == 0)
		{
			bubsort(mid, a1, asc);
		}
		else
		{
			wait(NULL);
			print(mid, a1);
		}
	}
	else
	{
		wait(NULL);
		printf("\nDescending sort of the second half\n");
		pid_t parent = vfork();
		
		if(parent < 0)
		{
			printf("Fork Failed\n");
		}
		else if(parent == 0)
		{
			bubsort(n - mid, a2, desc);
		}
		else
		{
			wait(NULL);
			print(n - mid, a2);
		}
	}
	
exit(0);
}

void bubsort(int n, int *array, bool comp(const void* , const void*))
{
	for(int i = 0; i < n-1; i = i+1)
	{
		for(int j = 0; j < n - i - 1; j = j+1)
		{
			if(comp(&array[j], &array[j+1]))
			{
				swap(&array[j], &array[j+1]);
			}
		}
	}
}

bool asc(const void* a, const void* b)
{
	return *(int*)a > *(int*)b;
}

bool desc(const void* a, const void* b)
{
	return *(int*)a < *(int*)b;
}

void print(int n, int *array)
{
	for(int i = 0; i < n; i = i+1)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void swap(int *x, int *y)
{
	int c = *x;
	*x = *y;
	*y = c;
}
