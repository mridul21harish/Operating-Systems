#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

int partition(int a[], int low, int high);
void quick_sort_parallel(int a[], int low, int high);
void quick_sort(int a[], int low, int high);

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
    	quick_sort_parallel(a1, 0, n-1);
    	t2 = clock();
    
    	printf("\nSorted Array using Multiprocessing is: ");
    	for(int i = 0; i < n; i = i+1)
    	{
    		printf("%d ", a1[i]);
    	}
   	
   	printf("\nTime taken by Multiprocessing merge sort is: %lf\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    
    	t1 = clock();
    	quick_sort(a2, 0, n-1);
    	t2 = clock();
    
    	printf("\nSorted Array without using Multiprocessing is: ");
    	for(int i = 0; i < n; i = i+1)
    	{
    		printf("%d ", a2[i]);
    	}
    
    	printf("\nTime taken by Normalprocessing merge sort is: %lf\n\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    	
    	return 0;
}

int partition(int a[], int low, int high)
{
    	int pivot = a[high];  
    	int i = (low - 1);  
  
    	for (int j = low; j <= high-1; j = j+1) 
    	{  
        	if (a[j] < pivot) 
        	{ 
            		i = i+1;
            		int temp = a[i];         
			a[i] = a[j];            
			a[j] = temp;  
  		}
    	}
    	int temp = a[i+1];         
	a[i+1] = a[high];            
	a[high] = temp; 
    	
    	return (i + 1); 
}

void quick_sort_parallel(int a[], int low, int high) 
{ 
    	if (low < high) 
    	{ 
        	int pi = partition(a, low, high); 
        	pid_t pid;
        	pid = vfork();
         
        	if(pid == 0)
       	{
            		quick_sort(a, low, pi - 1); 
            		exit(0);
        	}
        	else
        	{
            		quick_sort(a, pi + 1, high);
        	}
    	}	 
}

void quick_sort(int a[], int low, int high) 
{ 
    	if (low < high) 
    	{ 
        	int pi = partition(a, low, high); 
        	quick_sort(a, low, pi - 1); 
        	quick_sort(a, pi + 1, high); 
    	} 
} 


