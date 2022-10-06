#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>

int binarysearch(int *a, int n, int x);
void bubsort(int n, int *array);
void print(int n, int *array);
void swap(int *x, int *y);

int main()
{
	int n; int mid; int x; int count = 0;
	printf("Enter the number of elements in the series: ");
	fflush(stdin);
	scanf("%d", &n);
	int a[n];
	
	for(int i = 0; i < n; i = i+1)
	{
		printf("Enter number %d: ", i+1);
		fflush(stdin);
		scanf("%d", &a[i]);
	}
	
	printf("\nEnter the search key: ");
	fflush(stdin);
	scanf("%d", &x);
	bubsort(n, a);
	printf("\nThe sorted array\n");
	fflush(stdin);
	print(n, a);
	
	pid_t pid = vfork();
	
	if(pid < 0)
	{
		printf("Fork failed\n");
	}
	else if(pid == 0)
	{
		if((mid = binarysearch(a, n, x)) == -1)
		{
			printf("\n%d is not found in the array\n", x);
			exit(1);
		}
		else
		{
			printf("\n%d found at index %d\n", x, mid);
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		int i = mid -1;
		while(i > -1 && a[i] == x)
		{
			printf("%d found at index %d\n", x, i);	
			i = i-1;
		}
		i = mid + 1;
		
		while(i < n && a[i] == x)
		{
			printf("%d found at index %d\n", x, i);
			i = i+1;
		}
	}
	
exit(0);
}

int binarysearch(int *a, int n, int x)
{
	int l = 0; int r = n-1;
	while(l <= r)
	{
		int m = l + (r - l)/2;
		if(a[m] == x)
		{
			return m;
		}
		else if(a[m] < x)
		{
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}
	}
	return -1;
}

void bubsort(int n, int *array)
{
	for(int i = 0; i < n-1; i = i+1)
	{
		for(int j = 0; j < n - i - 1; j = j+1)
		{
			if((array[j], array[j+1]))
			{
				swap(&array[j], &array[j+1]);
			}
		}
	}
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
