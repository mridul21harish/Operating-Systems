#include<stdio.h>              
#include <string.h>
#include<stdlib.h>

void ascendingsort(int n, int *arr);
void descendingsort(int n, int *arr);


int main(int argc, char *argv[])                    
{
	int arr[100]; int n; int i; int j; int s; char a;
	
	n = atoi(argv[1]);
	s = atoi(argv[2]);
	
	for(int i = 3; i < argc; i = i+1)
	{
		arr[i-3] = atoi(argv[i]);
	}
	
	if(s == 1)                     
		ascendingsort(n, arr);
	else if(s == 2)
		descendingsort(n, arr);                       
}

void ascendingsort(int n, int *arr)
{
	for (int i = 0; i < n; i = i+1)                     
	{
		for (int j = 0; j < n; j = j+1)             
		{
			if (arr[j] > arr[i])               
			{
				int tmp = arr[i];         
				arr[i] = arr[j];            
				arr[j] = tmp;             
			}  
		}
	}
	for (int i = 0; i < n; i = i+1)                     
		{
			printf(" %d ", arr[i]);
		}
		

}
		
void descendingsort(int n, int *arr)
{
	for (int i = 0; i < n; i = i+1)                     
	{
		for (int j = 0; j < n; j = j+1)             
		{
			if (arr[j] < arr[i])                
			{
				int tmp = arr[i];         
				arr[i] = arr[j];            
				arr[j] = tmp;             
			}
		}
	}
	for (int i = 0; i < n; i =  i+1)                     
		{
			printf(" %d ", arr[i]);                   
		}
}
