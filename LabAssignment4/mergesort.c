#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

void merge(int a[], int low, int mid, int high);
void merge_sort_parallel(int a[], int low, int high);
void merge_sort(int a[], int low, int high);


int main()
{
    	int n;
    	clock_t t1, t2;
    	
    	printf("Enter the size of the Array: ");
    	scanf("%d", &n);
    	
    	int a1[n]; int a2[n]; int x;
	
	printf("Enter the elements\n");
    	for(int i = 0; i < n; i = i+1)
   	{
        	scanf("%d", &x);
        	a1[i] = a2[i] = x;
    	}

    	printf("\nThe Unsorted Array is: ");
    	for(int i = 0; i < n; i = i+1)
    	{
    		printf("%d ", a1[i]);
    	}
    	
    	
    	t1 = clock();
    	merge_sort_parallel(a1, 0, n-1);
    	t2 = clock();
    
    	printf("\nSorted Array using Multiprocessing is: ");
    	for(int i = 0; i < n; i = i+1)
    	{
    		printf("%d ", a1[i]);
    	}
   	
   	printf("\nTime taken by Multiprocessing merge sort is: %lf\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    
    	t1 = clock();
    	merge_sort(a2, 0, n-1);
    	t2 = clock();
    
    	printf("\nSorted Array without using Multiprocessing is: ");
    	for(int i = 0; i < n; i = i+1)
    	{
    		printf("%d ", a2[i]);
    	}
    
    	printf("\nTime taken by Normalprocessing merge sort is: %lf\n\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    	
    	return 0;
}

void merge(int a[], int low, int mid, int high)
{
    	int i; int j; int k; 
    	int n1 = mid - low + 1; 
    	int n2 = high - mid; 
  
    	int left[n1], right[n2]; 
  
    	for (i = 0; i < n1; i = i+1)
    	{ 
        	left[i] = a[low + i];
        } 
    	for (j = 0; j < n2; j = j+1)
    	{ 
        	right[j] = a[mid + 1 + j];
        } 
  
    	i = 0;  
    	j = 0;  
    	k = low;  
    	
    	while (i < n1 && j < n2)
    	{ 
        	if (left[i] <= right[j])
        	{ 
            		a[k] = left[i]; 
            		i = i+1; 
        	} 
        	else
        	{ 
            		a[k] = right[j]; 
            		j = j+1; 
        	} 
        	k = k+1; 
    	} 
  
    	while (i < n1)
    	{ 
        	a[k] = left[i]; 
        	i = i+1; 
        	k = k+1; 
    	} 
  
    	while (j < n2)
    	{ 
        	a[k] = right[j]; 
        	j = j+1; 
        	k = k+1; 
    	} 
}

void merge_sort_parallel(int a[], int low, int high)
{
    	if(low < high)
    	{
        	int mid = low + (high - low) / 2;
        	pid_t pid;
        	pid = vfork();
        	
        	if(pid == 0)
        	{
            		merge_sort_parallel(a, low, mid);
            		exit(0);
        	}
        	else
        	{
           	merge_sort_parallel(a, mid + 1, high);
            	merge(a, low, mid, high);
        	}
    	}
}

void merge_sort(int a[], int low, int high)
{
    	if(low < high)
    	{
        	int mid = low + (high - low) / 2;
        	merge_sort(a, low, mid);
        	merge_sort(a, mid + 1, high);
        	merge(a, low, mid, high);
    	}
}


