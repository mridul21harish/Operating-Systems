#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define MAX 100000
int top =- 1;

void push(int a[], int n);
void magic_square(int size, int a[][size]);
void odd_order_magic_square(int size, int a[][size]);
void doubly_even_magic_square(int size, int a[][size]);
void singly_even_magic_square(int size, int a[][size]);
void display_magic_square(int size, int a[][size]);
int magic_square_check(int size, int a[][size]);

int main()
{
    	int size;
    	printf("Enter order of square matrix: ");
    	scanf("%d", &size);
    	
    	int a[size][size];

    	pid_t pid;
    	pid = vfork();
    	if(pid == 0)
    	{
        	if(size < 3)
        	{
            		printf("Error: Order of matrix must be greater than 2\n");
            		exit(EXIT_FAILURE);
        	}

        	magic_square(size, a);
        	exit(0);
    	}
    	else
    	{
        	wait(NULL);
        	display_magic_square(size, a);
        	int valid = magic_square_check(size, a);
        	
        	if(valid == 1)
            		printf("\nIt is a valid Magic Square\n\n");
        	else
            		printf("It is not a valid Magic Square\n\n");
    	}
    
    	return 0;
}

void push(int a[], int n)
{
	if(top==MAX-1)
	{
		printf("\nStack is full!!");
	}
	else
	{
		top = top+1;
		a[top] = n;
	}
}

void magic_square(int size, int a[][size])
{
    	if(size % 2 == 1)
        	odd_order_magic_square(size, a);
    	else if(size % 4 == 0)
        	doubly_even_magic_square(size, a);
    	else
        	singly_even_magic_square(size, a);
}

void odd_order_magic_square(int size, int a[][size])
{
    	int square = size * size;
    	int i = 0; int j = size/2; int k;

    	for(k = 1; k <= square; ++k)
    	{
        	a[i][j] = k;
        	i = i-1;
        	j = j+1;

        	if(k % size == 0)
        	{
            		i = i+2;
            		--j;
        	}
        	else
        	{
            		if(j == size)
                	j = j - size;
            	else if(i < 0)
                	i = i + size;
        	}
    	}
}

void doubly_even_magic_square(int size, int a[][size])
{
    	int I[size][size];
    	int J[size][size];

    	int i; int j;
    	
    	int index=1;
    	for(i = 0; i < size; i = i+1)
        	for(j=  0; j < size; j = j+1)
        	{
            		I[i][j] = ((i+1)%4)/2;
            		J[j][i] = ((i+1)%4)/2;
            		a[i][j] = index;
            		index = index+1;
        	}

    	for(i = 0; i < size; i = i+1)
        	for(j = 0; j < size; j = j+1)
        	{
            		if(I[i][j] == J[i][j])
                	a[i][j] = size*size+1 - a[i][j];
        	}
}

void singly_even_magic_square(int size, int a[][size])
{
    	int N = size;
	int halfN = N/2; 
	int k = (N-2)/4; 
    
    	int temp;
    	int new[N];

    	int swap_coloumn[N]; 
    	int index=0; 
    	int mini_magic[halfN][halfN];

  	odd_order_magic_square(halfN, mini_magic);	
	
  	for(int i = 0; i < halfN; i = i+1)
    		for (int j = 0; j < halfN; j = j+1)
        	{
	        	a[i][j] = mini_magic[i][j]; 	  		  
      	    		a[i+halfN][j+halfN] = mini_magic[i][j]+halfN*halfN;   
            		a[i][j+halfN] = mini_magic[i][j]+2*halfN*halfN;       
            		a[i+halfN][j] = mini_magic[i][j]+3*halfN*halfN;       
            	}

    	for(int i = 1; i <= k; i = i+1)
        	swap_coloumn[index++] = i;
    
    	for (int i = N-k+2; i <= N; i = i+1)
        	swap_coloumn[index++] = i;

    
    	for(int i = 1; i <= halfN; i = i+1)
		for(int j = 1; j <= index; j = j+1)
        	{
            		temp = a[i-1][swap_coloumn[j-1]-1];
           	 	a[i-1][swap_coloumn[j-1]-1] = a[i+halfN-1][swap_coloumn[j-1]-1];
            		a[i+halfN-1][swap_coloumn[j-1]-1] = temp;
        	}

    	temp = a[k][0]; 
    	a[k][0] = a[k+halfN][0]; 
    	a[k+halfN][0] = temp;

    	temp = a[k+halfN][k]; 
    	a[k+halfN][k] = a[k][k]; 
   	a[k][k] = temp;
}

void display_magic_square(int size, int a[][size])
{
    	printf("Sum of each row, column and both diagonals is: %d\n\n", size*(size*size + 1) / 2);
    	for(int i = 0; i < size; i = i+1)
    	{
        	for(int j = 0; j < size; j = j+1)
        	{
            		printf(" %5d", a[i][j]);
        	}
        printf("\n");
    	}
}

int magic_square_check(int size, int a[][size])
{ 
    	int i; int sum1 = 0; int sum2 = 0;  
    	
    	for(i = 0; i < size; i = i+1) 
        	sum1 = sum1 + a[i][i]; 
        
        for(i = 0; i < size; i = i+1) 
        	sum2 = sum2 + a[i][size-1-i]; 
  
    	if(sum1 != sum2)  
        	return 0; 
    
    	for(i = 0; i < size; i = i+1)
    	{ 
        	int row_sum = 0;      
       	for(int j = 0; j < size; j = j+1) 
            	row_sum = row_sum + a[i][j]; 
          
         	if(row_sum != sum1) 
            		return 0; 
    	} 
   
    	for(i = 0; i < size; i = i+1)
    	{      
        	int coloumn_sum = 0;      
        	
        	for(int j = 0; j < size; j = j+1) 
            		coloumn_sum = coloumn_sum + a[j][i]; 
  
        	if(sum1 != coloumn_sum)  
        	return 0; 
    	} 
  
    	return 1; 
}
